#include "StoppingCriterion.hpp"

StoppingCriterion::StoppingCriterion(shared_ptr<PartitionedMSA> parted_msa, 
                                    unsigned int _n_ranks,
                                    unsigned int _n_groups, 
                                    unsigned int _n_threads, 
                                    bool _kh_test, 
                                    bool _count_spr_moves,
                                    int _seed) : 
    n_ranks(_n_ranks), n_groups(_n_groups), n_threads(_n_threads), 
    kh_test_case(_kh_test), count_spr_moves(_count_spr_moves), seed(_seed)
{   
    // is MPI fine grained 
    mpi_fine_grained = (n_ranks > 1 && n_groups == 1);
    
    // groups per rank
    n_groups_per_rank = std::max(n_groups/n_ranks, 1u);
    n_effective_groups = mpi_fine_grained ? 1 : n_groups_per_rank;

    // partitions
    part_count = parted_msa->part_count();
    
    // patterns
    pattern_compression = parted_msa->total_patterns() > 0 ? true : false;
    
    if(pattern_compression)
    {   
        total_patterns = parted_msa->total_patterns();
        
        patterns = new size_t[part_count];
        for(unsigned int i = 0; i < part_count; ++i)
            patterns[i] = parted_msa->part_info(i).length();

        pattern_weights.resize(n_effective_groups);
        for(auto &pa : pattern_weights){
            pa.resize(part_count);
            for(unsigned int i = 0; i < part_count; ++i)
            {
                pa[i] = new unsigned int[patterns[i]];
                std::fill(pa[i], pa[i] + patterns[i], 0u);
            }
        }
    }
    
    // sites
    total_sites = parted_msa->total_sites();
    sites = new size_t[part_count];
    for(unsigned int part = 0; part < part_count; ++part)
        sites[part] = pattern_compression ? 0 : parted_msa->part_info(part).length();
    
    epsilon = new double[n_effective_groups];
    p_value = new double[n_effective_groups];
    
    old_loglh = new double[n_effective_groups];
    if(kh_test_case) new_loglh = new double[n_effective_groups];
    if(count_spr_moves) increasing_moves = new unsigned long[n_effective_groups]; 
    
    // to delete
    vectors_initialized = false;
    vectors_uncompressed_initialized = false;
    sites_uncompressed_initialized = false;
    weights_initialized.resize(n_effective_groups);
    weights_initialized.assign(n_effective_groups, false);
    
    persite_lnl.resize(0);
    persite_lnl_new.resize(0);
    persite_lnl_uncompressed.resize(0);
    persite_lnl_uncompressed_new.resize(0);

    initialize_proc_offset();
}

StoppingCriterion::~StoppingCriterion(){
    
    for(auto &th: proc_offset) th.clear();
    proc_offset.clear();

    clear_persite_lnl_vector();
    delete[] sites;
    delete[] epsilon;
    delete[] p_value;

    if(pattern_compression)
    {    
        for(auto & pa : pattern_weights)
        {
            for(unsigned int i = 0; i < part_count; ++i)
                delete[] pa[i];
            
            pa.clear();
        }
        pattern_weights.clear();

        delete[] patterns;
    }

    delete[] old_loglh;
    if(kh_test_case) delete[] new_loglh;
    if(count_spr_moves) delete[] increasing_moves;
}

void StoppingCriterion::set_proc_offset(TreeInfo* treeinfo, 
                                        const PartitionAssignment& part_assignment, 
                                        int local_proc_id)
{
    // Step 1: Set all offsets first
    {
        ParallelContext::GroupLock lock;
        
        for (const auto& pa: part_assignment)
        {    
            int part = pa.part_id;

            if(proc_offset[local_proc_id][part] == -1) 
                proc_offset[local_proc_id][part] = pa.start;
        }
    }

    ParallelContext::thread_barrier();

    // Step 2: Handle all pattern compression cases together
    if(pattern_compression && !weights_initialized[ParallelContext::local_group_id()])
    {
        {
            ParallelContext::UniqueLock lock;
            vector<unsigned int *> weights = pattern_weights[ParallelContext::local_group_id()];

            // Initialize weights with offsets
            
            for (const auto& pa: part_assignment)
            {    
                int part = pa.part_id;
                
                // Apply offset to weights
                weights[part] += proc_offset[local_proc_id][part];
                
                // Copy pattern weights from treeinfo
                unsigned int cur_sites = treeinfo->pll_treeinfo().partitions[part]->sites; 
                for(unsigned int i = 0; i < cur_sites; ++i)
                {
                    weights[part][i] = 
                        treeinfo->pll_treeinfo().partitions[part]->pattern_weights[i];
                }
            }

        }
        ParallelContext::thread_barrier();
        
        // MPI reduction if needed
        if(mpi_fine_grained)
        {
            vector<unsigned int *> weights = pattern_weights[ParallelContext::local_group_id()];

            for(unsigned int part = 0; part < part_count; ++part)
                ParallelContext::mpi_allreduce_weights(weights[part], patterns[part], CORAX_REDUCE_SUM);
            
        }
        
        // Mark weights as initialized
        if(ParallelContext::group_master_thread())
            weights_initialized[ParallelContext::local_group_id()] = true;
        
    }

    ParallelContext::thread_barrier();
}

void StoppingCriterion::initialize_persite_lnl_vectors(){
    
    {
        ParallelContext::UniqueLock lock;
        if(!vectors_initialized)
        {   
            if(pattern_compression)
            {    
                initialize_persite_vector(persite_lnl);
                persite_lnl_uncompressed.resize(n_effective_groups);

                if(kh_test_case)
                {
                    initialize_persite_vector(persite_lnl_new);
                    persite_lnl_uncompressed_new.resize(n_effective_groups);
                }

            } 
            else 
            {
                initialize_persite_vector(persite_lnl_uncompressed);
                if(kh_test_case) initialize_persite_vector(persite_lnl_uncompressed_new);
            }

            vectors_initialized = true;
        }
    }

    ParallelContext::thread_barrier();

    if(pattern_compression) initialize_uncompressed();
    
}

void StoppingCriterion::initialize_uncompressed()
{
    {
        ParallelContext::UniqueLock lock;
            
        //pattern_weights
        if(!sites_uncompressed_initialized)
        {
            vector<unsigned int *> weights = pattern_weights[ParallelContext::local_group_id()];
            
            for(unsigned int part = 0; part < part_count; part++)
                for(unsigned int i = 0; i < patterns[part]; ++i)
                    sites[part] += weights[part][i];
            
            sites_uncompressed_initialized = true;
        }   
    
    }
 
    // group barrier
    ParallelContext::thread_barrier();

    {
        ParallelContext::UniqueLock lock;

        if(!vectors_uncompressed_initialized)
        {
            for(auto &p_lnl : persite_lnl_uncompressed)
            {
                p_lnl.resize(part_count);
                for(unsigned int part = 0; part < part_count; ++part)
                    p_lnl[part] = new double[sites[part]];
                    
            }

            if(kh_test_case)
            {
                for(auto &p_lnl_new : persite_lnl_uncompressed_new){
                    p_lnl_new.resize(part_count);
                    for(unsigned int part = 0; part < part_count; ++part)
                        p_lnl_new[part] = new double[sites[part]];
                    
                }
            }
            vectors_uncompressed_initialized = true;
        }
    }

    ParallelContext::thread_barrier();
}


void StoppingCriterion::initialize_persite_vector(vector<vector<double *>> &vec){
    
    size_t * lengths_array = 
        pattern_compression ? patterns : sites;
    
    vec.resize(n_effective_groups);
    
    for(auto &p_lnl : vec)
    {
        p_lnl.resize(part_count);
        for(unsigned int part = 0; part < part_count; ++part)
        {
            p_lnl[part] = new double[lengths_array[part]];
            std::fill(p_lnl[part], p_lnl[part] + lengths_array[part], 0.0);
        }
    }
}

void StoppingCriterion::clear_persite_lnl_vector(){
    
    for(auto &p_lnl : persite_lnl)
    {
        for(unsigned int part = 0; part < part_count; ++part)
            delete[] p_lnl[part];
        
        p_lnl.clear();
    }
    
    persite_lnl.clear();

    if(pattern_compression)
    {    
        for(auto &p_lnl : persite_lnl_uncompressed){
            for(unsigned int part = 0; part < part_count; ++part)
                delete[] p_lnl[part];
            
            p_lnl.clear();
        }
        
        persite_lnl_uncompressed.clear();
    }

    if(kh_test_case)
    {
        for(auto &p_lnl : persite_lnl_new)
        {
            for(unsigned int part = 0; part < part_count; ++part)
                delete[] p_lnl[part];
            
            p_lnl.clear();
        }
        persite_lnl_new.clear();

        if(pattern_compression)
        {
            for(auto &p_lnl : persite_lnl_uncompressed_new)
            {
                for(unsigned int part = 0; part < part_count; ++part)
                    delete[] p_lnl[part];
                
                p_lnl.clear();
            }
            persite_lnl_uncompressed_new.clear();
        }
    }
}

void StoppingCriterion::initialize_proc_offset()
{
    proc_offset.resize(n_threads);
    
    for(auto & th : proc_offset)
    {     
        th.resize(part_count);
        th.assign(part_count, -1);
    }
}

vector<double *> StoppingCriterion::get_vec(int local_group_id, int local_proc_id, bool plnl)
{
    // copy
    vector<double*> vec;

    if(pattern_compression) 
        vec = plnl ? persite_lnl[local_group_id] : persite_lnl_new[local_group_id] ;
    else 
        vec = plnl ? persite_lnl_uncompressed[local_group_id] : persite_lnl_uncompressed_new[local_group_id] ;

    for(unsigned int part = 0; part < vec.size(); part++)
    {
        int thread_offset = get_offset(local_proc_id, part);
        if (thread_offset != -1) vec[part] += get_offset(local_proc_id, part);
    }

    return vec;
}

void StoppingCriterion::store_uncompressed(bool plnl_old)
{   

    if(ParallelContext::group_master_thread())
    {   
        vector<double*> dest_vec = plnl_old ? 
            persite_lnl_uncompressed[ParallelContext::local_group_id()] :
            persite_lnl_uncompressed_new[ParallelContext::local_group_id()];

        vector<double*> source_vec = plnl_old ?
            persite_lnl[ParallelContext::local_group_id()] :
            persite_lnl_new[ParallelContext::local_group_id()];
        
        vector<unsigned int*> weights = 
            pattern_weights[ParallelContext::local_group_id()];
    
        for(unsigned int part = 0; part < part_count; ++part)
        {
            int dest_index = 0;    
            for(unsigned int i = 0; i < patterns[part]; ++i)
            {
                unsigned int weight_i = weights[part][i];
                double logl_i = source_vec[part][i] / weight_i;
                assert(weight_i > 0);
                
                while(weight_i > 0)
                {
                    dest_vec[part][dest_index] = logl_i;
                    dest_index++;
                    weight_i--;
                }
            }
        }
    }

    ParallelContext::thread_barrier();
}

void StoppingCriterion::reset_persite_vector(bool plnl_old)
{   
    if(ParallelContext::group_master_thread())
    { 
        /* 
        Instead of 0-index, I could use ParallelContext::local_group_id().
        But this reset happens only in MPI fine-grained parallelization,
        where I'm confident that there is only one effective thread group
        per node. 
        */
        vector<double*> uncompressed_vec = 
            plnl_old ? persite_lnl_uncompressed[0] : 
                       persite_lnl_uncompressed_new[0];
        
        for(unsigned int part = 0; part < part_count; ++part)
            std::fill(uncompressed_vec[part], 
                      uncompressed_vec[part] + sites[part], 
                      0.0);
        
        if(pattern_compression)
        {   
            vector<double*> compressed_vec = 
                plnl_old ? persite_lnl[0] : persite_lnl_new[0];
            
            for(unsigned int part = 0; part < part_count; ++part)
                std::fill(compressed_vec[part], 
                            compressed_vec[part] + patterns[part], 
                            0.0);

        }
    }

    ParallelContext::thread_barrier();
}

void StoppingCriterion::mpi_fill(bool plnl_old)
{   
    if(ParallelContext::group_master_thread() || true)
    {
        size_t * lengths_array = 
            pattern_compression ? patterns : sites;
        
        vector<double*> vec;

        if(pattern_compression)
        {   
            vec = plnl_old ? persite_lnl[0] : persite_lnl_new[0];
        }
        else
        {
            vec = plnl_old ? persite_lnl_uncompressed[0] : persite_lnl_uncompressed_new[0];
        }
        
        
        for(unsigned int part = 0; part < part_count; ++part)
        {
            //ParallelContext::parallel_reduce_cb((void *) nullptr, vec[part], lengths_array[part], CORAX_REDUCE_MIN);   
            // Theoretically it should work or ?
            ParallelContext::mpi_allreduce(vec[part], lengths_array[part], CORAX_REDUCE_SUM);
        }
        //ParallelContext::mpi_allreduce_alternative(vec[part], lengths_array[part], CORAX_REDUCE_SUM);
    
    }

    //ParallelContext::barrier();
}

void StoppingCriterion::store_loglh(double _loglh, bool plnl_old)
{
    if(ParallelContext::group_master_thread())
    {
        if(plnl_old)
            old_loglh[ParallelContext::local_group_id()] = _loglh;
        else
            new_loglh[ParallelContext::local_group_id()] = _loglh;
    }

    ParallelContext::thread_barrier();
}

void StoppingCriterion::compute_loglh(TreeInfo& treeinfo, vector<double*>& plnl, bool plnl_old)
{   
    if(mpi_fine_grained) reset_persite_vector(plnl_old);

    /* This should work theoretically on MPI-fine grained*/
    double _lnl = treeinfo.persite_loglh(plnl, true);
    
    if(mpi_fine_grained) mpi_fill(plnl_old);
    
    if(pattern_compression) store_uncompressed(plnl_old);

    store_loglh(_lnl, plnl_old);
}

void StoppingCriterion::set_increasing_moves(unsigned long _moves){

    if(ParallelContext::group_master_thread())
    {
        assert(count_spr_moves);
        increasing_moves[ParallelContext::local_group_id()] = _moves;
    }

    ParallelContext::thread_barrier();
}

std::pair<int, int> StoppingCriterion::find_by_site_index(unsigned int site_index){
    
    int pIndex = -1, sIndex = -1; 
    unsigned int cur_sites = 0;

    for(unsigned int i = 0; i < part_count; ++i){
        cur_sites += sites[i];
        if(cur_sites > site_index){
            pIndex = i;
            sIndex = site_index - (cur_sites - sites[i]); 
            break;
        }
    }

    return std::make_pair(pIndex, sIndex);
}

// statistical tests
void NoiseSamplingTest::run_test() {

    int group_id = ParallelContext::group_id();
    assert(count_spr_moves == false);

    double _epsilon = 0;
    unsigned i;

    if(rell) {
        
        int site_index, exp;
        int rell_size = 1000;
        double * rell_dist = new double[rell_size];
        double * logl_diff_dist = new double[rell_size];

        {
            ParallelContext::UniqueLock lock;
            srand(seed);
            
            for(exp = 0; exp < rell_size; exp++){
            
                double rell_loglh = 0;
                for (i = 0; i<total_sites; i++){
                    
                    site_index =  rand() % total_sites;
                    std::pair<int, int> p = find_by_site_index(site_index);
                    rell_loglh += persite_lnl_uncompressed[group_id][p.first][p.second];
                }

                rell_dist[exp] = rell_loglh;
            }

            for(exp = 0; exp < rell_size; exp++){
                int ind1 = rand() % rell_size;
                int ind2 = rand() % rell_size;
                logl_diff_dist[exp] = fabs(rell_dist[ind1] - rell_dist[ind2]);
            }
        }

        std::sort(logl_diff_dist, logl_diff_dist + rell_size);

        int epsilon_index = (int) (0.95*rell_size);
        _epsilon = logl_diff_dist[epsilon_index];

        delete[] logl_diff_dist;
        delete[] rell_dist;

    } else {

        double stdev = 0;
        double mean = old_loglh[group_id] / total_sites;

        for (unsigned int part = 0; part < part_count; ++part)
            for(i = 0; i < sites[part]; ++i)
                stdev += pow(persite_lnl_uncompressed[group_id][part][i] - mean, 2);

        stdev = sqrt(stdev / total_sites);
        
        _epsilon = 1.645 * M_SQRT2 * sqrt(total_sites) * stdev;
    }

    epsilon[group_id] = _epsilon;
}


void KHStoppingTest::run_test()
{
    if(ParallelContext::group_master_thread())
    {
        int group_id = ParallelContext::local_group_id();
        double ret_val = 0, L = old_loglh[group_id], NL = new_loglh[group_id];
        unsigned int i, pos = 0;
        
        if((NL - L) < lh_epsilon)
        {
            epsilon[group_id] = lh_epsilon;
            if(count_spr_moves) p_value[group_id] = 1;
            return;
        }

        double* logl_diffs = new double[total_sites];
        double mean = 0;

        for(unsigned int part = 0; part < part_count; ++part)
        {
            unsigned int part_sites = sites[part];

            for(i = 0; i<part_sites; ++i)
            {
                assert(persite_lnl_uncompressed_new[group_id][part][i] < 0.0 && persite_lnl_uncompressed[group_id][part][i] < 0.0);
                logl_diffs[pos] = persite_lnl_uncompressed_new[group_id][part][i] - persite_lnl_uncompressed[group_id][part][i];
                mean += logl_diffs[pos];
                pos++;
            }
        }

        mean = mean / total_sites;
        double stdev = 0;

        for (pos = 0; pos < total_sites; ++pos)
            stdev += pow(logl_diffs[pos] - mean, 2);

        stdev = sqrt(stdev / total_sites);

        // multiple testing correction
        if(count_spr_moves){
            if( increasing_moves[group_id] == 0)
            {
                ret_val = 1;
                epsilon[group_id] = (NL - L);
                
            } 
            else 
            {
                double x = (NL - L) / (stdev * sqrt(total_sites));
                StandardNormalDistribution ndist;
                ret_val = increasing_moves[group_id]*(1 - ndist.cdf(x));
                ret_val = ret_val < 1 ? ret_val : 1;
                epsilon[group_id] = ndist.inv_cdf(1 - (0.05 / increasing_moves[group_id])) * sqrt(total_sites) * stdev;
            }
            
            p_value[group_id] = ret_val;

        } 
        else 
        {
            ret_val = 1.645 * sqrt(total_sites) * stdev;
            ret_val = ret_val > lh_epsilon ? ret_val : lh_epsilon;
            epsilon[group_id] = ret_val;
        }

        delete[] logl_diffs;
    }
}
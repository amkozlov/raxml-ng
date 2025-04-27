#include "StoppingCriterion.hpp"

StoppingCriterion::StoppingCriterion(shared_ptr<PartitionedMSA> parted_msa, 
                                    int _n_groups, 
                                    int _n_threads, 
                                    bool _kh_test, 
                                    bool _count_spr_moves,
                                    int _seed) : 
    n_groups(_n_groups), n_threads(_n_threads), kh_test_case(_kh_test), count_spr_moves(_count_spr_moves), seed(_seed)
{   
    // partitions
    part_count = parted_msa->part_count();
    
    // patterns
    pattern_compression = parted_msa->total_patterns() > 0 ? true : false;

    if(pattern_compression)
    {   
        total_patterns = parted_msa->total_patterns();
        
        patterns = new unsigned int[part_count];
        for(int i = 0; i < part_count; ++i)
            patterns[i] = parted_msa->part_info(i).length();

        pattern_weights.resize(n_groups);
        for(auto &pa : pattern_weights){
            pa.resize(part_count);
            for(int i = 0; i < part_count; ++i)
                pa[i] = new unsigned int[patterns[i]];
        }
    }

    // sites
    total_sites = parted_msa->total_sites();
    sites = new unsigned int[part_count];
    for(int i = 0; i < part_count; ++i)
        sites[i] = pattern_compression ? 0 : parted_msa->part_info(i).length();
    
    epsilon = new double[n_groups];
    p_value = new double[n_groups];

    old_loglh = new double[n_groups];
    if(kh_test_case) new_loglh = new double[n_groups];
    if(count_spr_moves) increasing_moves = new unsigned long[n_groups]; 

    // here I don't have the details to initialize the uncompressed
    //initialize_persite_lnl_vectors(pattern_compression ? persite_lnl : persite_lnl_uncompressed, 
    //                           pattern_compression ? persite_lnl_new : persite_lnl_uncompressed_new);
    
    vectors_initialized = false;
    vectors_uncompressed_initialized = false;
    sites_uncompressed_initialized.resize(n_threads);
    sites_uncompressed_initialized.assign(n_threads, false);

    persite_lnl.resize(0);
    persite_lnl_new.resize(0);
    persite_lnl_uncompressed.resize(0);
    persite_lnl_uncompressed_new.resize(0);

    initialize_thread_offset();
}

StoppingCriterion::~StoppingCriterion(){
    
    for(auto &th: thread_offset) th.clear();
    thread_offset.clear();

    clear_persite_lnl_vector();
    delete[] sites;
    delete[] epsilon;
    delete[] p_value;

    if(pattern_compression) {
        
        for(auto & pa : pattern_weights){
            for(int i = 0; i < part_count; ++i)
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

void StoppingCriterion::initialize_persite_lnl_vectors(TreeInfo * treeinfo){
    
    {
        ParallelContext::UniqueLock lock;
        
        if(!vectors_initialized){
            if(pattern_compression){
                
                initialize_persite_vector(persite_lnl);
                persite_lnl_uncompressed.resize(n_groups);

                if(kh_test_case){
                    initialize_persite_vector(persite_lnl_new);
                    persite_lnl_uncompressed_new.resize(n_groups);
                }

            } else {
                initialize_persite_vector(persite_lnl_uncompressed);
                if(kh_test_case) initialize_persite_vector(persite_lnl_uncompressed_new);
            }
            vectors_initialized = true;
        }
    }

    ParallelContext::barrier();

    if(pattern_compression) initialize_uncompressed(treeinfo);
}

void StoppingCriterion::initialize_uncompressed(TreeInfo * treeinfo){

    {
        ParallelContext::GroupLock glock;

        {
            ParallelContext::UniqueLock lock;
            
            if(!sites_uncompressed_initialized[ParallelContext::local_thread_id()]){
                for(int part = 0; part < part_count; part++)
                    if(treeinfo->pll_treeinfo().partitions[part])
                        sites[part] += treeinfo->pll_treeinfo().partitions[part]->pattern_weight_sum;
                
                sites_uncompressed_initialized[ParallelContext::local_thread_id()] = true;
            }   
        }
    }
 
    // group barrier
    ParallelContext::barrier();

    {
        ParallelContext::GroupLock glock_new;
        {
            ParallelContext::UniqueLock lock_new;

            if(!vectors_uncompressed_initialized){
    
                for(auto &p_lnl : persite_lnl_uncompressed){
                    p_lnl.resize(part_count);
                    for(int part = 0; part < part_count; ++part)
                        p_lnl[part] = new double[sites[part]];
                }

                if(kh_test_case){
                    for(auto &p_lnl : persite_lnl_uncompressed_new){
                        p_lnl.resize(part_count);
                        for(int part = 0; part < part_count; ++part)
                            p_lnl[part] = new double[sites[part]];
                    }
                }
                vectors_uncompressed_initialized = true;
            }
        }
    }

    ParallelContext::barrier();
}


void StoppingCriterion::initialize_persite_vector(vector<vector<double *>> &vec){
    
    unsigned int * lengths_array = 
        pattern_compression ? patterns : sites;
    
    vec.resize(n_groups);
    
    for(auto &p_lnl : vec){
        p_lnl.resize(part_count);
        for(int part = 0; part < part_count; ++part)
            p_lnl[part] = new double[lengths_array[part]];
    }
}

void StoppingCriterion::clear_persite_lnl_vector(){
    
    for(auto &p_lnl : persite_lnl){
        for(int part = 0; part < part_count; ++part)
            delete[] p_lnl[part];
        
        p_lnl.clear();
    }
    
    persite_lnl.clear();

    if(pattern_compression){
        
        for(auto &p_lnl : persite_lnl_uncompressed){
            for(int part = 0; part < part_count; ++part)
                delete[] p_lnl[part];
            
            p_lnl.clear();
        }
        
        persite_lnl_uncompressed.clear();
    }

    if(kh_test_case){
        for(auto &p_lnl : persite_lnl_new){
            for(int part = 0; part < part_count; ++part)
                delete[] p_lnl[part];
            
            p_lnl.clear();
        }
        persite_lnl_new.clear();

        if(pattern_compression){
            for(auto &p_lnl : persite_lnl_uncompressed_new){
                for(int part = 0; part < part_count; ++part)
                    delete[] p_lnl[part];
                
                p_lnl.clear();
            }
            persite_lnl_uncompressed_new.clear();
        }
    }
}

void StoppingCriterion::initialize_thread_offset(){

    thread_offset.resize(n_threads);
    
    for(auto & th : thread_offset) {     
        th.resize(part_count);
        th.assign(part_count, -1);
    }
}

void StoppingCriterion::set_thread_offset(TreeInfo* treeinfo, const PartitionAssignment& part_assignment, int local_thread_id){
    
    {
        ParallelContext::GroupLock lock;
        int part = 0;
        
        for (const auto& pa: part_assignment){
            
            part = pa.part_id;

            if(thread_offset[local_thread_id][part] == -1 ) 
                thread_offset[local_thread_id][part] = pa.start;
            
            if(pattern_compression){

                vector<unsigned int *> vec = pattern_weights[ParallelContext::group_id()];
                vec[part] += thread_offset[local_thread_id][part];
                
                unsigned int cur_sites = treeinfo->pll_treeinfo().partitions[part]->sites; 
                for(unsigned int i = 0; i < cur_sites; ++i){
                    vec[part][i] = 
                        treeinfo->pll_treeinfo().partitions[part]->pattern_weights[i];

                    //tsites += vec[part][i];
                }
            }
            
        }
        //assert(tsites == total_sites);
    }

    ParallelContext::barrier();
}

vector<double *> StoppingCriterion::get_vec(int group_id, int local_thread_id, bool plnl){
    // copy
    vector<double*> vec;

    if(pattern_compression) 
        vec = plnl ? persite_lnl[group_id] : persite_lnl_new[group_id] ;
    else 
        vec = plnl ? persite_lnl_uncompressed[group_id] : persite_lnl_uncompressed_new[group_id] ;

    for(unsigned int part = 0; part < vec.size(); part++){
        //cout << "Thread " << ParallelContext::local_thread_id() 
        //        << ", Part " << part 
        //        << ", offset " << get_offset(local_thread_id, part) << endl;
        
        int thread_offset = get_offset(local_thread_id, part);
        if (thread_offset != -1) vec[part] += get_offset(local_thread_id, part);
    }

    return vec;
}

void StoppingCriterion::store_uncompressed(bool plnl_old){
    
    if(ParallelContext::group_master_thread()){
        
        vector<double*> dest_vec = plnl_old ? 
            persite_lnl_uncompressed[ParallelContext::group_id()] :
            persite_lnl_uncompressed_new[ParallelContext::group_id()];

        vector<double*> source_vec = plnl_old ?
            persite_lnl[ParallelContext::group_id()] :
            persite_lnl_new[ParallelContext::group_id()];
        
        vector<unsigned int*> weights = 
            pattern_weights[ParallelContext::group_id()];

        for(int part = 0; part < part_count; ++part){
            int dest_index = 0;
            
            for(unsigned int i = 0; i < patterns[part]; ++i){
                unsigned int weight_i = weights[part][i];
                double logl_i = source_vec[part][i] / weight_i;
                assert(weight_i > 0);
                
                while(weight_i > 0) {
                    dest_vec[part][dest_index] = logl_i;
                    dest_index++;
                    weight_i--;
                }
            }
        }
    }

    ParallelContext::barrier();
}

void StoppingCriterion::compute_loglh(TreeInfo& treeinfo, vector<double*>& plnl, bool plnl_old){
    double _lnl = treeinfo.persite_loglh(plnl, true);

    if(pattern_compression) store_uncompressed(plnl_old);

    if(ParallelContext::group_master_thread()){
        if(plnl_old)
            old_loglh[ParallelContext::group_id()] = _lnl;
        else
            new_loglh[ParallelContext::group_id()] = _lnl;
    }
    ParallelContext::barrier();
}

void StoppingCriterion::set_increasing_moves(unsigned long _moves){

    assert(count_spr_moves);

    int group_id = ParallelContext::group_id();
    if(ParallelContext::group_master_thread()) increasing_moves[group_id] = _moves;
    ParallelContext::barrier();

}

std::pair<int, int> StoppingCriterion::find_by_site_index(unsigned int site_index){
    
    int pIndex = -1, sIndex = -1; 
    unsigned int cur_sites = 0;

    for(int i = 0; i < part_count; ++i){
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
void NoiseSampling::run_test() {

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

        for (int part = 0; part < part_count; ++part)
            for(i = 0; i < sites[part]; ++i)
                stdev += pow(persite_lnl_uncompressed[group_id][part][i] - mean, 2);

        stdev = sqrt(stdev / total_sites);
        
        _epsilon = 1.645 * M_SQRT2 * sqrt(total_sites) * stdev;
        //cout << "NO-RELL epsilon " << epsilon << endl;
    }

    epsilon[group_id] = _epsilon;
}


void KH::run_test(){
    
    int group_id = ParallelContext::group_id();
    double ret_val = 0, L = old_loglh[group_id], NL = new_loglh[group_id];
    unsigned int i, pos = 0;
    
    if((NL - L ) < lh_epsilon) {
        epsilon[group_id] = lh_epsilon;
        return;
    }

    double* logl_diffs = new double[total_sites];
    double mean = 0;

    for(int part = 0; part < part_count; ++part){
        unsigned int part_sites = sites[part];

        for(i = 0; i<part_sites; ++i){
            //std::cout <<  " Partition " << part <<", Persite lnl[ " << pos << "] " << persite_lnl[group_id][part][i] << endl;
            logl_diffs[pos] = persite_lnl_uncompressed_new[group_id][part][i] - persite_lnl_uncompressed[group_id][part][i];
            mean += logl_diffs[pos];
            pos++;
        }
    }

    //std::cout << "NL " << NL << " and test NL " << test_NL << endl;
    //std::cout << "Success! Group id " << group_id <<  endl;

    mean = mean / total_sites;
    double stdev = 0;

    for (pos = 0; pos < total_sites; ++pos)
        stdev += pow(logl_diffs[pos] - mean, 2);

    stdev = sqrt(stdev / total_sites);

    // multiple testing correction
    if(count_spr_moves){
        //std::cout << "Increasing moves " << increasing_moves[group_id] << std::endl;
        if( increasing_moves[group_id] == 0){
            ret_val = 1;
            epsilon[group_id] = (NL - L);
            
        } else {
            double x = (NL - L) / (stdev * sqrt(total_sites));
            //cout << "X = " << x << endl;
            StandardNormalDistribution ndist;
            ret_val = increasing_moves[group_id]*(1 - ndist.cdf(x));
            ret_val = ret_val < 1 ? ret_val : 1;
            epsilon[group_id] = ndist.inv_cdf(1 - (0.05 / increasing_moves[group_id])) * sqrt(total_sites) * stdev;
        }
        
        p_value[group_id] = ret_val;

    } else {
        
        //double x = (NL - L) / (stdev * sqrt(total_sites));
        //cout << "X = " << x << endl;
        
        //cout << "HEY OP! stdev " << stdev << endl;
        ret_val = 1.645 * sqrt(total_sites) * stdev;
        ret_val = ret_val > lh_epsilon ? ret_val : lh_epsilon;
        epsilon[group_id] = ret_val;
    }

    delete[] logl_diffs;
}
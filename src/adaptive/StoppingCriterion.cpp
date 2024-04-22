#include "StoppingCriterion.hpp"

StoppingCriterion::StoppingCriterion(shared_ptr<PartitionedMSA> parted_msa, 
                                    int _n_groups, 
                                    int _n_threads, 
                                    bool _kh_test, 
                                    bool _count_spr_moves) : 
    n_groups(_n_groups), n_threads(_n_threads), kh_test_case(_kh_test), count_spr_moves(_count_spr_moves)
{
    part_count = parted_msa->part_count();
    total_sites = parted_msa->total_sites();
    
    sites = new unsigned int[part_count];
    for(int i = 0; i < part_count; ++i) sites[i] = parted_msa->part_info(i).length();

    epsilon = new double[n_groups];
    p_value = new double[n_groups];

    old_loglh = new double[n_groups];
    if(kh_test_case) new_loglh = new double[n_groups];
    if(count_spr_moves) increasing_moves = new unsigned long[n_groups]; 

    initialize_persite_lnl_vectors();
    initialize_thread_offset();
}

StoppingCriterion::~StoppingCriterion(){
    
    for(auto &th: thread_offset) th.clear();
    thread_offset.clear();

    clear_persite_lnl_vector();
    delete[] sites;
    delete[] epsilon;
    delete[] p_value;

    delete[] old_loglh;
    if(kh_test_case) delete[] new_loglh;
    if(count_spr_moves) delete[] increasing_moves;
}

void StoppingCriterion::initialize_persite_lnl_vectors(){
    
    persite_lnl.resize(n_groups);
    for(auto &p_lnl : persite_lnl){
        p_lnl.resize(part_count);
        for(int part = 0; part < part_count; ++part)
            p_lnl[part] = new double[sites[part]];
    }

    if(kh_test_case){
        persite_lnl_new.resize(n_groups);
        for(auto &p_lnl : persite_lnl_new){
            p_lnl.resize(part_count);
            for(int part = 0; part < part_count; ++part)
                p_lnl[part] = new double[sites[part]];
        }   
    }

}

void StoppingCriterion::clear_persite_lnl_vector(){
    
    for(auto &p_lnl : persite_lnl){
        for(int part = 0; part < part_count; ++part)
            delete[] p_lnl[part];
        
        p_lnl.clear();
    }
    
    persite_lnl.clear();

    if(kh_test_case){
        for(auto &p_lnl : persite_lnl_new){
            for(int part = 0; part < part_count; ++part)
                delete[] p_lnl[part];
            
            p_lnl.clear();
        }
        persite_lnl_new.clear();
    }
}

void StoppingCriterion::initialize_thread_offset(){

    thread_offset.resize(n_threads);
    
    for(auto & th : thread_offset) {     
        th.resize(part_count);
        th.assign(part_count, -1);
    }
}

void StoppingCriterion::set_thread_offset(const PartitionAssignment& part_assignment, int local_thread_id){
    {
        ParallelContext::UniqueLock lock;
        int part = 0;
        for (const auto& pa: part_assignment){
            if(thread_offset[local_thread_id][part] == -1 ) thread_offset[local_thread_id][part] = pa.start;
            part++;
        }
    }
}

vector<double *> StoppingCriterion::get_vec(int group_id, int local_thread_id, bool plnl){
    // copy
    vector<double*> vec = plnl ? persite_lnl[group_id] : persite_lnl_new[group_id] ;
    
    for(unsigned int part = 0; part < vec.size(); part++){
        vec[part] += get_offset(local_thread_id, part);
    }

    return vec;
}

void StoppingCriterion::compute_loglh(TreeInfo& treeinfo, vector<double*>& plnl, bool plnl_old){
    double _lnl = treeinfo.persite_loglh(plnl, true);
    if(ParallelContext::group_master()){
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
    if(ParallelContext::group_master()) increasing_moves[group_id] = _moves;
    ParallelContext::barrier();

}

// statistical tests
void NoiseSampling::run_test() {

    int group_id = ParallelContext::group_id();
    assert(count_spr_moves == false);

    double _epsilon = 0;
    unsigned i;
    
    if(rell) {
        
        int pIndex, sIndex, exp;
        int rell_size = 1000;
        double * rell_dist = new double[rell_size];
        double * logl_diff_dist = new double[rell_size];

        for(exp = 0; exp < rell_size; exp++){
        
            double rell_loglh = 0;
            for (i = 0; i<total_sites; i++){
                
                if(part_count > 1){
                    pIndex = rand() % part_count;
                } else {
                    pIndex = 0;
                }

                sIndex =  rand() % sites[pIndex];
                rell_loglh += persite_lnl[group_id][pIndex][sIndex];
            }

            rell_dist[exp] = rell_loglh;
        }

        for(exp = 0; exp < rell_size; exp++){
            int ind1 = rand() % rell_size;
            int ind2 = rand() % rell_size;
            logl_diff_dist[exp] = fabs(rell_dist[ind1] - rell_dist[ind2]);
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
                stdev += pow(persite_lnl[group_id][part][i] - mean, 2);

        stdev = sqrt(stdev / total_sites);
        
        _epsilon = 1.645 * M_SQRT2 * sqrt(total_sites) * stdev;
        //cout << "NO-RELL epsilon " << epsilon << endl;
    }

    epsilon[group_id] = _epsilon;
}


void KH::run_test(){

    int group_id = ParallelContext::group_id();

    double ret_val = 0, L = old_loglh[group_id], NL = new_loglh[group_id];
    double test_L = 0, test_NL = 0;
    unsigned int i, pos = 0;

    double* logl_diffs = new double[total_sites];
    double mean = 0;

    for(int part = 0; part < part_count; ++part){
        
        unsigned int part_sites = sites[part];
        for(i = 0; i<part_sites; ++i){
            
            //std::cout <<  " Partition " << part <<", Persite lnl[ " << pos << "] " << persite_lnl[group_id][part][i] << endl;
            logl_diffs[pos] = persite_lnl_new[group_id][part][i] - persite_lnl[group_id][part][i];
            
            test_L += persite_lnl[group_id][part][i];
            test_NL += persite_lnl_new[group_id][part][i];

            mean += logl_diffs[pos];
            pos++;
        }
    }

    //std::cout << "NL " << NL << " and test NL " << test_NL << endl;
    assert(fabs(L - test_L) < 1e-3);
    assert(fabs(NL - test_NL) < 1e-3);
    //std::cout << "Success! Group id " << group_id <<  endl;

    mean = mean / total_sites;
    double stdev = 0;

    for (pos = 0; pos < total_sites; ++pos)
        stdev += pow(logl_diffs[pos] - mean, 2);

    stdev = sqrt(stdev / total_sites);

    // multiple testing correction
    if(count_spr_moves){
        //std::cout << "Increasing moves " << increasing_moves[group_id] << std::endl;
        if( increasing_moves[group_id] == 0 || stdev < 1e-9){
            ret_val = 1;
            epsilon[group_id] = (NL - L) > 10 ? (NL - L) : 10;
            
        } else {
            double x = (NL - L) / (stdev * sqrt(total_sites));
            StandardNormalDistribution ndist;
            ret_val = increasing_moves[group_id]*(1 - ndist.cdf(x));
            ret_val = ret_val < 1 ? ret_val : 1;
            epsilon[group_id] = ndist.inv_cdf(1 - (0.05 / increasing_moves[group_id])) * sqrt(total_sites) * stdev;
        }
        
        p_value[group_id] = ret_val;

    } else {
        
        //cout << "HEY OP! stdev " << stdev << endl;
        ret_val = 1.645 * sqrt(total_sites) * stdev;
        ret_val = ret_val > 10 ? ret_val : 10;
        epsilon[group_id] = ret_val;
    }

    delete[] logl_diffs;
}
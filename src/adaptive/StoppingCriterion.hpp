#ifndef RAXML_ADAPTIVE_STOPPINGCRITERION_HPP_
#define RAXML_ADAPTIVE_STOPPINGCRITERION_HPP_

#include <corax/corax.h>
#include <vector>

#include "NormalDistribution.hpp"
#include "../PartitionedMSA.hpp"
#include "../loadbalance/PartitionAssignment.hpp"
#include "../TreeInfo.hpp"

using namespace std;

class StoppingCriterion {
    
    private:
        int n_groups;
        int n_threads;
        
        bool kh_test_case;

        vector<intVector> thread_offset;

        void initialize_persite_lnl_vectors();
        void initialize_thread_offset();
        void clear_persite_lnl_vector();
        
        int get_offset(int thread_id, int part_id) {return thread_offset[thread_id][part_id]; }
        std::vector<double *> get_vec(int group_id, int local_thread_id, bool plnl);

    protected:
        int part_count;
        unsigned int total_sites;
        unsigned int* sites;
        
        vector<vector<double *>> persite_lnl;
        vector<vector<double *>> persite_lnl_new;

        bool count_spr_moves;
        unsigned long *increasing_moves;

        double *old_loglh;
        double *new_loglh;

        double *epsilon;
        double *p_value;
        
    public:
        
        StoppingCriterion(shared_ptr<PartitionedMSA> parted_msa, 
                        int _n_groups, 
                        int _n_threads, 
                        bool _kh_test, 
                        bool _count_spr_moves = false);
        
        virtual ~StoppingCriterion();
        
        virtual void run_test() = 0 ;
        
        void compute_loglh(TreeInfo& treeinfo, vector<double*>& plnl, bool plnl_old = true);

        // setter
        void set_thread_offset(const PartitionAssignment& part_assignment, int local_thread_id);

        // getters
        std::vector<double *> get_persite_lnl(int group_id, int local_thread_id) { return get_vec(group_id, local_thread_id, true); }
        std::vector<double *> get_persite_lnl_new(int group_id, int local_thread_id) {return get_vec(group_id, local_thread_id, false); }
        
        double get_epsilon(int group_id) { return epsilon[group_id]; }
        double get_pvalue(int group_id) { return p_value[group_id]; }
        
        bool multi_test_correction() {return count_spr_moves; }
        bool kh_test() { return kh_test_case; }

        void set_increasing_moves(unsigned long _moves);
};

// implement the inheritance tomorrow
class NoiseSampling : public StoppingCriterion {
    
    bool rell;
    
    public:
        NoiseSampling(shared_ptr<PartitionedMSA> parted_msa, 
                int _n_groups, 
                int _n_threads,
                bool _rell = false) : StoppingCriterion(parted_msa, _n_groups, _n_threads, false, false) { rell = _rell; };

        void run_test() override;
};

class KH : public StoppingCriterion {

    public:
        KH(shared_ptr<PartitionedMSA> parted_msa, 
            int _n_groups, 
            int _n_threads, 
            bool _count_spr_moves = false) : StoppingCriterion(parted_msa, _n_groups, _n_threads, true, _count_spr_moves) {}

        void run_test() override;

};



#endif /* RAXML_ADAPTIVE_STOPPINGCRITERION_HPP_ */
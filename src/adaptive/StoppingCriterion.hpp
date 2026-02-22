#ifndef RAXML_ADAPTIVE_STOPPINGCRITERION_HPP_
#define RAXML_ADAPTIVE_STOPPINGCRITERION_HPP_

#include <corax/corax.h>
#include <vector>

#include "NormalDistribution.hpp"
#include "../PartitionedMSA.hpp"
#include "../loadbalance/PartitionAssignment.hpp"
#include "../TreeInfo.hpp"
#include <thread>

using namespace std;

class StoppingCriterion {
    
    private:
        unsigned int n_ranks;
        unsigned int n_groups;
        unsigned int n_threads; // this is threads (procs) per group
        unsigned int n_groups_per_rank;
        unsigned int n_effective_groups;
        
        bool kh_test_case;
        bool vectors_initialized;
        bool vectors_uncompressed_initialized;
        bool sites_uncompressed_initialized;
        vector<bool> weights_initialized;

        vector<intVector> proc_offset;
        
        void initialize_proc_offset();
        void clear_persite_lnl_vector();

        void initialize_persite_vector(vector<vector<double *>> &vec);
        void initialize_uncompressed();
        
        void store_uncompressed(bool plnl_old);
        int get_offset(int local_proc_id, int part_id) {return proc_offset[local_proc_id][part_id]; }
        std::vector<double *> get_vec(int local_group_id, int local_proc_id, bool plnl);

    protected:
        unsigned int part_count;
        unsigned int total_sites;
        unsigned int* sites;
        
        // MPI fine grained
        bool mpi_fine_grained;
        

        unsigned int total_patterns;
        unsigned int * patterns;
        vector<vector<unsigned int *>> pattern_weights;
        
        vector<vector<double *>> persite_lnl;
        vector<vector<double *>> persite_lnl_new;

        vector<vector<double *>> persite_lnl_uncompressed;
        vector<vector<double *>> persite_lnl_uncompressed_new;

        bool count_spr_moves;
        bool pattern_compression;
        unsigned long *increasing_moves;

        double *old_loglh;
        double *new_loglh;

        double *epsilon;
        double *p_value;

        int seed;
        
        std::pair<int, int> find_by_site_index(unsigned int site_index);
        void reset_persite_vector(bool plnl_old);
        void mpi_fill(bool plnl_old);
        void store_loglh(double _loglh, bool plnl_old);
        
    public:
        
        StoppingCriterion(shared_ptr<PartitionedMSA> parted_msa,
                        unsigned int _n_ranks, 
                        unsigned int _n_groups, 
                        unsigned int _n_threads, 
                        bool _kh_test, 
                        bool _count_spr_moves = false,
                        int _seed = 0);
        
        virtual ~StoppingCriterion();
        
        virtual void run_test() = 0 ;
        
        void compute_loglh(TreeInfo& treeinfo, vector<double*>& plnl, bool plnl_old = true);

        // setter
        void initialize_persite_lnl_vectors();
        void set_proc_offset(TreeInfo* treeinfo, const PartitionAssignment& part_assignment, int local_proc_id);

        // getters
        std::vector<double *> get_persite_lnl(int local_group_id, int local_proc_id) { return get_vec(local_group_id, local_proc_id, true); }
        std::vector<double *> get_persite_lnl_new(int local_group_id, int local_proc_id) {return get_vec(local_group_id, local_proc_id, false); }
        
        double get_epsilon(int local_group_id) { return epsilon[local_group_id]; }
        double get_pvalue(int local_group_id) { return p_value[local_group_id]; }
        
        bool multi_test_correction() {return count_spr_moves; }
        bool kh_test() { return kh_test_case; }
        
        void set_increasing_moves(unsigned long _moves);
};

// implement the inheritance tomorrow
class NoiseSamplingTest : public StoppingCriterion {
    
    bool rell;
    
    public:
        NoiseSamplingTest(shared_ptr<PartitionedMSA> parted_msa, 
                unsigned int _n_ranks,
                unsigned int _n_groups, 
                unsigned int _n_threads,
                bool _rell = false,
                int _seed = 0) : 
                    StoppingCriterion(parted_msa, _n_ranks, _n_groups, _n_threads, false, false, _seed),
                    rell(_rell) {}

        void run_test() override;
};

class KHStoppingTest : public StoppingCriterion {

    private:
        double lh_epsilon;

    public:
        KHStoppingTest(shared_ptr<PartitionedMSA> parted_msa, 
            unsigned int _n_ranks,
            unsigned int _n_groups, 
            unsigned int _n_threads, 
            bool _count_spr_moves = false,
            int _seed = 0,
            double _lh_epsilon = DEF_LH_EPSILON) : 
                StoppingCriterion(parted_msa, _n_ranks, _n_groups, _n_threads, true, _count_spr_moves, _seed),
                lh_epsilon(_lh_epsilon) {}

        void run_test() override;

};



#endif /* RAXML_ADAPTIVE_STOPPINGCRITERION_HPP_ */
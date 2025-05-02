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
        bool vectors_initialized;
        bool vectors_uncompressed_initialized;
        vector<bool> sites_uncompressed_initialized;

        vector<intVector> thread_offset;
        
        void initialize_thread_offset();
        void clear_persite_lnl_vector();

        void initialize_persite_vector(vector<vector<double *>> &vec);
        void initialize_uncompressed(TreeInfo * treeinfo);
        void set_thread_offset_uncompressed(TreeInfo * treeinfo, int local_thread_id);
        
        void store_uncompressed(bool plnl_old);
        int get_offset(int thread_id, int part_id) {return thread_offset[thread_id][part_id]; }
        std::vector<double *> get_vec(int group_id, int local_thread_id, bool plnl);

    protected:
        int part_count;
        unsigned int total_sites;
        unsigned int* sites;

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
        
    public:
        
        StoppingCriterion(shared_ptr<PartitionedMSA> parted_msa, 
                        int _n_groups, 
                        int _n_threads, 
                        bool _kh_test, 
                        bool _count_spr_moves = false,
                        int _seed = 0);
        
        virtual ~StoppingCriterion();
        
        virtual void run_test() = 0 ;
        
        void compute_loglh(TreeInfo& treeinfo, vector<double*>& plnl, bool plnl_old = true);

        // setter
        void initialize_persite_lnl_vectors(TreeInfo * treeinfo);
        void set_thread_offset(TreeInfo* treeinfo, const PartitionAssignment& part_assignment, int local_thread_id);

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
                bool _rell = false,
                int _seed = 0) : 
                    StoppingCriterion(parted_msa, _n_groups, _n_threads, false, false, _seed),
                    rell(_rell) {}

        void run_test() override;
};

class KH : public StoppingCriterion {

    private:
        double lh_epsilon;

    public:
        KH(shared_ptr<PartitionedMSA> parted_msa, 
            int _n_groups, 
            int _n_threads, 
            bool _count_spr_moves = false,
            int _seed = 0,
            double _lh_epsilon = 10.0) : 
                StoppingCriterion(parted_msa, _n_groups, _n_threads, true, _count_spr_moves, _seed),
                lh_epsilon(_lh_epsilon) {}

        void run_test() override;

};



#endif /* RAXML_ADAPTIVE_STOPPINGCRITERION_HPP_ */
#ifndef RAXML_ADAPTIVE_DIFFICULTYPREDICTOR_HPP_
#define RAXML_ADAPTIVE_DIFFICULTYPREDICTOR_HPP_

#include "../PartitionedMSA.hpp"
#include "../MSA.hpp"
#include "../topology/RFDistCalculator.hpp"
#include "../Tree.hpp"

#include <vector>
#include <map>
#include <tuple>
#include <math.h>
#include <memory.h>

using namespace std;

class DifficultyPredictor{

    private:
        
        double difficulty;
        size_t states;
        bool is_dna;
        const corax_state_t *states_map;
        const PartitionedMSA* partitioned_msa_ptr;
        
        // Parsimony trees treelist
        TreeList pars_tree_list;

        // RF distance calculator
        std::unique_ptr<RFDistCalculator> rf_dist_calc;

        // features
        corax_msa_features* features;

        // more functions
        double normal_pdf(double x, double m, double s);
        void printFeatures(double avg_rff, double prop_unique);

    public:

        // constructors
        DifficultyPredictor();
        ~DifficultyPredictor();
        
        // getters
        double getDifficulty(){ return difficulty; }

        // difficulty prediction
        double predict_difficulty(unsigned int attrs, int n_trees);
        int numStartTrees(double difficulty, double amp, double mean = 0.5, double s = 0.2);

        // setters
        void set_partitioned_msa_ptr(PartitionedMSA* _pmsa);
        void compute_msa_features(corax_msa_t* original_msa, bool _is_dna);
    
};


#endif /* RAXML_ADAPTIVE_DIFFICULTYPREDICTOR_HPP_ */

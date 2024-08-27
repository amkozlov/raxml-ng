#ifndef RAXML_ADAPTIVE_DIFFICULTYPREDICTOR_HPP_
#define RAXML_ADAPTIVE_DIFFICULTYPREDICTOR_HPP_

#include "../ParsimonyMSA.hpp"
#include "../MSA.hpp"
#include "../topology/RFDistCalculator.hpp"
#include "../Tree.hpp"

#include <vector>
#include <map>
#include <tuple>
#include <math.h>
#include <memory.h>

using namespace std;

class DifficultyPredictor
{
    private:
        double _difficulty;
        const ParsimonyMSA* _parsimony_msa_ptr;
        
        // Parsimony trees treelist
        TreeList _pars_tree_list;

        // RF distance calculator
        std::unique_ptr<RFDistCalculator> _rf_dist_calc;

        // features
        corax_msa_features* _features;

        // more functions
        double normal_pdf(double x, double m, double s);
        void print_features(double avg_rff, double prop_unique);

    public:

        // constructors
        DifficultyPredictor();
        ~DifficultyPredictor();
        
        // getter
        double difficulty() { return _difficulty; }

        // difficulty prediction
        double predict_difficulty(int n_trees);
        double predict_difficulty(const TreeList& pars_trees);
        int num_start_trees(double difficulty, double amp, double mean = 0.5, double s = 0.2);

        // setters
        void compute_msa_features(ParsimonyMSA* _pmsa);

        double load_pythia_score_from_log_file(const string& old_log_file);
};


#endif /* RAXML_ADAPTIVE_DIFFICULTYPREDICTOR_HPP_ */

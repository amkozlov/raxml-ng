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

struct AdaptiveCheckpoint
{
    double pythiaScore;

    AdaptiveCheckpoint() : pythiaScore(0.0) {}
    AdaptiveCheckpoint(double pScore) : 
            pythiaScore(pScore) {}
};

class DifficultyPredictor{

    private:
        
        double difficulty;
        size_t states;
        bool is_dna;
        bool ckpt;
        bool nofiles_mode;
        const corax_state_t *states_map;
        const ParsimonyMSA* parsimony_msa_ptr;
        string outfile;
        
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
        DifficultyPredictor(const string& _outfile, bool _nofiles_mode = false);        
        ~DifficultyPredictor();
        
        // getter
        double getDifficulty(){ return difficulty; }

        // difficulty prediction
        double predict_difficulty(int n_trees, bool store_in_file = true);
        int numStartTrees(double difficulty, double amp, double mean = 0.5, double s = 0.2);

        // setters
        void set_parsimony_msa_ptr(ParsimonyMSA* _pmsa);
        void compute_msa_features(corax_msa_t* original_msa, bool _is_dna);

        void store_difficulty_in_chkpt_file(double score, const string& out_file);
        double load_adaptive_chkpt(const string& bin_file);

        void set_checkpoint_true() { ckpt = true; }
        bool checkpoint_mode() {return ckpt;}
    
};


#endif /* RAXML_ADAPTIVE_DIFFICULTYPREDICTOR_HPP_ */

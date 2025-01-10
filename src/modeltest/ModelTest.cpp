
#include "ModelTest.hpp"
#include "ModelDefinitions.hpp"

ModelTest::ModelTest(TreeInfo &treeinfo, const Tree &tree, Optimizer& optimizer) : treeinfo(treeinfo), tree(tree), optimizer(optimizer){ }



struct ModelEvaluation {
    string model_descriptor;
    Model model;
    std::vector<double> partition_loglh;
};

void ModelTest::optimize_model() {
    const auto num_models = dna_substitution_matrix_names.size() * default_frequency_type.size() * default_rate_heterogeneity.size();

    auto index = 1U;

    std::vector<ModelEvaluation> result;
    for (const auto& entry : dna_substitution_matrix_names) {
        const auto subst_model = entry.first;

        for (const auto &frequency_type : default_frequency_type) {
            for (const auto &rate_heterogeneity : default_rate_heterogeneity) {

                const string model_descriptor = subst_model
                + frequency_type_label.at(frequency_type)
                + rate_heterogeneity_label.at(rate_heterogeneity);

                LOG_INFO << "[" << index++ << "/" << num_models << "] Testing model " << model_descriptor << "\n";

                Model model(model_descriptor);

                for (const auto p : treeinfo.parts_master()) {
                    treeinfo.model(p, model);
                }

                LOG_INFO << "\tInitial LogLH = " << treeinfo.loglh(false) << std::endl;

                optimizer.optimize_model(treeinfo);

                LOG_INFO << "\tAfter Model opt = " << treeinfo.loglh(false) << std::endl;
            }
        }

    }
}

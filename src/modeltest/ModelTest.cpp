
#include "ModelTest.hpp"

#include <memory>
#include <utility>

#include "ModelDefinitions.hpp"
#include "../ICScoreCalculator.hpp"
#include "corax/tree/treeinfo.h"

ModelTest::ModelTest(const Options &options, PartitionedMSA &msa, const Tree &tree, const IDVector &tip_msa_idmap,
                     const PartitionAssignment &part_assign,
                     Optimizer &optimizer): options(options), msa(msa), tree(tree), tip_msa_idmap(tip_msa_idmap),
                                            part_assign(part_assign), optimizer(optimizer) {
}


vector<candidate_model_t> ModelTest::generate_candidate_model_names(const DataType &dt) const {
    vector<candidate_model_t> candidate_models;
    check_supported_datatype(dt);

    const auto &matrix_names = dt == DataType::dna ? dna_substitution_matrix_names : aa_model_names;

    const auto freerate_cmin = options.free_rate_min_categories;
    const auto freerate_cmax = options.free_rate_max_categories;

    // TODO: balance memory consumption by varying rate heterogeneity the fastest but still computing _all_ free rate models
    // first
    for (const auto &rate_heterogeneity: default_rate_heterogeneity) {
        for (const auto &subst_model: matrix_names) {
            for (const auto &frequency_type: default_frequency_type) {
                if (rate_heterogeneity == rate_heterogeneity_t::FREE_RATE) {
                    // If category range is not positive, skip freerate models
                    if (freerate_cmin == 0 && freerate_cmax == 0) {
                        continue;
                    }

                    candidate_models.emplace_back(dt, subst_model, frequency_type, rate_heterogeneity,
                                                  options.free_rate_min_categories, options.free_rate_max_categories);
                } else {
                    candidate_models.emplace_back(dt, subst_model, frequency_type, rate_heterogeneity);
                }
            }
        }
    }

    return candidate_models;
}


class ExecutionStatus final {
public:
    ExecutionStatus() : partition_index(0), partition_count(0), model_index(0), model_count(0) {
    }

    void initialize(size_t model_count, size_t partition_count) {
        this->partition_index = 0;
        this->model_index = 0;
        this->partition_count = partition_count;
        this->model_count = model_count;
        this->results = std::unique_ptr<Results>(
            new std::vector<vector<PartitionModelEvaluation> >(partition_count));
    }

    virtual ~ExecutionStatus() = default;


    void store_results(int partition_index, PartitionModelEvaluation &result) {
        std::lock_guard<std::mutex> lock(mutex_results);
        results->at(partition_index).push_back(result);
    }

    bool get_next_model(size_t &next_partition_index, size_t &next_model_index) {
        if (partition_count < 1 || model_count < 1) {
            throw std::logic_error("attempted to get next model before initialization");
        }

        std::lock_guard<std::mutex> lock(mutex_model_index);

        next_partition_index = partition_index;
        next_model_index = model_index;

        if (model_index == model_count - 1) {
            ++partition_index;
        }

        model_index = (model_index + 1) % model_count;


        return (next_partition_index < partition_count && next_model_index < model_count);
    }

    vector<vector<PartitionModelEvaluation> > &get_results() const {
        return *results;
    }

private:
    using Results = vector<vector<PartitionModelEvaluation> >;
    size_t partition_index, partition_count;
    size_t model_index, model_count;
    std::mutex mutex_model_index;
    std::mutex mutex_results;

    // Results in flat array with models being the major index, i.e. the results for a single model are grouped by partition
    std::unique_ptr<Results> results;
};

ExecutionStatus execution_status; // shared across all threads.

void ModelTest::optimize_model() {
    LOG_INFO << std::setprecision(20) << std::setfill(' ') << std::left;

    auto candidate_models = generate_candidate_model_names(msa.part_info(0).model().data_type());

    if (ParallelContext::master()) {
        execution_status.initialize(candidate_models.size(), msa.part_count());
    }

    ParallelContext::barrier();

    size_t partition_index, model_index;

    const bool enable_freerate_heuristic = std::getenv("MODELTEST_FREERATE_NOSKIP") == nullptr;

    while (execution_status.get_next_model(partition_index, model_index)) {
        const auto &model_under_test = candidate_models.at(model_index);

        double last_score = std::numeric_limits<double>::infinity();
        for (unsigned int num_rate_cats = model_under_test.rate_categories;
             num_rate_cats <= model_under_test.max_rate_categories; ++num_rate_cats) {
            const auto &model_descriptor = model_under_test.descriptor + (
                                               model_under_test.rate_heterogeneity == rate_heterogeneity_t::FREE_RATE
                                                   ? std::to_string(num_rate_cats)
                                                   : "");

            LOG_INFO << RAXML_LOG_TIMESTAMP << "Partition " << partition_index << " model " << model_index << " " <<
                    model_descriptor << endl;

            Model model(model_descriptor);
            assign(model, msa.part_info(partition_index).stats());
            TreeInfo treeinfo(options, tree, msa, tip_msa_idmap, part_assign, partition_index, model);
            optimizer.optimize_model(treeinfo);

            PartitionModelEvaluation partition_results;

            const double partition_loglh = treeinfo.pll_treeinfo().partition_loglh[0];
            const size_t free_params = model.num_free_params() + treeinfo.tree().num_branches();
            const size_t sample_size = msa.part_info(partition_index).stats().site_count;
            ICScoreCalculator ic_score_calculator(free_params, sample_size);

            partition_results.ic_criteria = ic_score_calculator.all(partition_loglh);
            partition_results.model = model;
            partition_results.partition_loglh = partition_loglh;

            const double new_score = partition_results.ic_criteria.at(InformationCriterion::bic);
            execution_status.store_results(partition_index, partition_results);

            if (model_under_test.rate_heterogeneity == rate_heterogeneity_t::FREE_RATE && enable_freerate_heuristic &&
                new_score >= last_score) {
                break; // Skip evaluating freerate
            }

            last_score = new_score;
        }
    }

    ParallelContext::barrier();

    if (ParallelContext::master()) {
        auto xml_fname = options.output_fname("modeltest.xml");
        fstream xml_stream(xml_fname, std::ios::out);

        print_xml(xml_stream, execution_status.get_results(), msa.part_count());
        xml_stream.close();

        LOG_INFO << "XML model selection file written to " << xml_fname << endl;
    }

    auto results = execution_status.get_results();
    for (auto p = 0U; p < msa.part_count(); ++p) {
        auto bic_ranking = rank_by_score(results, InformationCriterion::bic, p, msa.part_count());
        const auto &best_model = results.at(p).at(bic_ranking.at(0));
        LOG_INFO << "Partition #" << p << ": " << best_model.model.to_string() << " BIC = " << best_model.
                ic_criteria.
                at(InformationCriterion::bic) << " LogLH = " << best_model.partition_loglh << endl;
    }
}

vector<size_t> ModelTest::rank_by_score(const EvaluationResults &results,
                                        InformationCriterion ic,
                                        unsigned int partition_idx,
                                        unsigned int part_count) {
    std::vector<size_t> ranking(results.size() / part_count, 0);
    std::iota(ranking.begin(), ranking.end(), 0);

    std::sort(ranking.begin(), ranking.end(),
              [partition_idx, ic, &results](const size_t &a, const size_t &b) {
                  return results.at(partition_idx).at(a).ic_criteria.at(ic) <
                         results.at(partition_idx).at(b).ic_criteria.at(ic);
              });

    return ranking;
}


vector<double> transform_delta_to_weight(const vector<double> &deltas) {
    vector<double> weights(deltas.size());
    weights.clear();

    for (const double &delta: deltas) {
        weights.push_back(std::exp(-delta / 2));
    }

    // normalize
    const double fac = 1 / std::accumulate(weights.begin(), weights.end(), 0.0);

    for (double &w: weights) {
        w *= fac;
    }

    return weights;
}


void ModelTest::print_xml(ostream &os, EvaluationResults &results, unsigned int partition_count) {
    os << setprecision(17);
    os << "<modeltestresults>" << endl;

    unsigned int partition_index = 0;

    for (const auto &partition_result: results) {
        os << "<partition id=\"" << partition_index++ << "\">" << endl;
        for (const auto &result: partition_result) {
            os << "<model name=\"" << result.model.to_string()
                    << "\" lnL=\"" << result.partition_loglh
                    << "\" score-bic=\"" << result.ic_criteria.at(InformationCriterion::bic)
                    << "\" score-aic=\"" << result.ic_criteria.at(InformationCriterion::aic)
                    << "\" score-aicc=\"" << result.ic_criteria.at(InformationCriterion::aicc)
                    << "\" free-params=\"" << result.model.num_free_params() << "\" />" << endl;
        }
        os << "</partition>" << endl;
    }

    os << "</modeltestresults>" << endl;
}

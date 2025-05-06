
#include "ModelTest.hpp"

#include <memory>

#include "ModelDefinitions.hpp"
#include "../ICScoreCalculator.hpp"
#include "RHASHeuristic.hpp"
#include "corax/tree/treeinfo.h"

Options modify_options(const Options &other) {
    Options options(other);
    options.lh_epsilon = 0.01; // Use same LH-epsilon as ModelTest-NG

    return options;
}

ModelTest::ModelTest(const Options &original_options, const PartitionedMSA &msa, const Tree &tree, const IDVector &tip_msa_idmap,
                     const PartitionAssignment &part_assign)
    : options(modify_options(original_options)), optimizer(options), msa(msa), tree(tree),
                                            tip_msa_idmap(tip_msa_idmap), part_assign(part_assign) { }


vector<candidate_model_t> ModelTest::generate_candidate_model_names(const DataType &dt) const {
    vector<candidate_model_t> candidate_models;
    check_supported_datatype(dt);

    const auto &matrix_names = dt == DataType::dna ? dna_substitution_matrix_names : aa_model_names;

    const auto freerate_cmin = options.free_rate_min_categories;
    const auto freerate_cmax = options.free_rate_max_categories;

    for (const auto &subst_model: matrix_names) {
        for (const auto &frequency_type: default_frequency_type) {
            for (const auto &rate_heterogeneity: default_rate_heterogeneity) {
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

    void initialize(std::vector<candidate_model_t> candidate_models, size_t partition_count, bool use_rhas_heuristic = false) {
        this->partition_index = 0;
        this->model_index = 0;
        this->partition_count = partition_count;
        this->model_count = candidate_models.size();
        this->candidate_models = std::move(candidate_models);
        this->results = std::unique_ptr<Results>(
            new std::vector<vector<PartitionModelEvaluation>>(partition_count));
        this->use_rhas_heuristic = use_rhas_heuristic;

        const auto reference_matrix = this->candidate_models.at(0).matrix_name;
        this->rhas_heuristic_per_part.clear();
        this->rhas_heuristic_per_part.resize(partition_count, RHASHeuristic(reference_matrix));
    }

    virtual ~ExecutionStatus() = default;


    void store_results(int partition_index, const candidate_model_t &candidate_model, PartitionModelEvaluation &result) {
        std::lock_guard<std::mutex> lock(mutex_results);

        results->at(partition_index).push_back(result);

        if (use_rhas_heuristic) {
            const double bic = result.ic_criteria.at(InformationCriterion::bic);
            this->rhas_heuristic_per_part.at(partition_index).update(candidate_model, bic);
        }
    }

    bool get_next_model(size_t &next_partition_index, candidate_model_t **next_candidate_model) {
        if (partition_count < 1 || model_count < 1) {
            throw std::logic_error("attempted to get next model before initialization");
        }

        std::lock_guard<std::mutex> lock(mutex_model_index);

        // Skip computation of models according to RHAS heuristic
        while (use_rhas_heuristic && 
                is_index_valid() &&
                rhas_heuristic_per_part.at(partition_index)\
                    .can_skip(candidate_models.at(model_index))) {
            increment_model_index();
        }

        bool found_model = is_index_valid();
        if (found_model) {
            *next_candidate_model = &candidate_models.at(model_index);
            next_partition_index = partition_index;
        } else {
            next_candidate_model = nullptr;
        }

        increment_model_index();


        return found_model;
    }


    vector<vector<PartitionModelEvaluation> > &get_results() const {
        return *results;
    }

private:
    using Results = vector<vector<PartitionModelEvaluation>>;
    std::vector<candidate_model_t> candidate_models;
    size_t partition_index, partition_count;
    size_t model_index, model_count;
    std::mutex mutex_model_index;
    std::mutex mutex_results;

    bool use_rhas_heuristic;
    std::vector<RHASHeuristic> rhas_heuristic_per_part;

    std::unique_ptr<Results> results;

    void increment_model_index() {
        // Increment model index and optionally partition index
        if (model_index == model_count - 1) {
            ++partition_index;
        }

        model_index = (model_index + 1) % model_count;

    }

    bool is_index_valid() const {
        return partition_index < partition_count && model_index < model_count; 
    }
};

ExecutionStatus execution_status; // shared across all threads.

vector<string> ModelTest::optimize_model() {
    const bool enable_rhas_heuristic = std::getenv("MODELTEST_RHAS_NOSKIP") == nullptr;
    const bool enable_freerate_heuristic = std::getenv("MODELTEST_FREERATE_NOSKIP") == nullptr;

    LOG_INFO << std::setprecision(20) << std::setfill(' ') << std::left;


    if (ParallelContext::master()) {
        // TODO: support multiple partitions with mixed datatypes
        auto candidate_models = generate_candidate_model_names(msa.part_info(0).model().data_type());
        execution_status.initialize(candidate_models, msa.part_count(), enable_rhas_heuristic);
    }

    ParallelContext::barrier();

    size_t partition_index;
    candidate_model_t *candidate_model;



    while (execution_status.get_next_model(partition_index, &candidate_model)) {
        double last_score = std::numeric_limits<double>::infinity();
        for (unsigned int num_rate_cats = candidate_model->rate_categories;
             num_rate_cats <= candidate_model->max_rate_categories; ++num_rate_cats) {
            const auto &model_descriptor = candidate_model->descriptor + (
                                               candidate_model->rate_heterogeneity == rate_heterogeneity_t::FREE_RATE
                                                   ? std::to_string(num_rate_cats)
                                                   : "");

            LOG_WORKER_TS(LogLevel::info) << "partition " << partition_index + 1 << "/" << msa.part_count()
                << " model " << normalize_model_name(model_descriptor) << endl;

            Model model(model_descriptor);
            assign(model, msa.part_info(partition_index).stats());
            TreeInfo treeinfo(options, tree, msa, tip_msa_idmap, part_assign, partition_index, model);
            optimizer.optimize_model(treeinfo);

            // Retrieve values from optimized partition
            // partition id is always 0, since our treeinfo only contains a single partition
            assign(model, treeinfo, 0); 


            const double partition_loglh = treeinfo.pll_treeinfo().partition_loglh[0];
            const size_t free_params = model.num_free_params() + treeinfo.tree().num_branches();
            const size_t sample_size = msa.part_info(partition_index).stats().site_count;
            ICScoreCalculator ic_score_calculator(free_params, sample_size);

            PartitionModelEvaluation partition_results { model, partition_loglh, ic_score_calculator.all(partition_loglh) };

            const double new_score = partition_results.ic_criteria.at(InformationCriterion::bic);
            execution_status.store_results(partition_index, *candidate_model, partition_results);

            if (candidate_model->rate_heterogeneity == rate_heterogeneity_t::FREE_RATE && enable_freerate_heuristic &&
                new_score >= last_score) {
                break; // Skip evaluating freerate
            }

            last_score = new_score;
        }
    }

    ParallelContext::barrier();

    vector<string> best_model_per_part;
    if (ParallelContext::master()) {
        auto xml_fname = options.output_fname("modeltest.xml");
        fstream xml_stream(xml_fname, std::ios::out);

        print_xml(xml_stream, execution_status.get_results());
        xml_stream.close();

        LOG_DEBUG << "XML model selection file written to " << xml_fname << endl;




        auto bestmodel_fname = options.output_fname("modeltest.bestModel");
        fstream bestmodel_stream(bestmodel_fname, std::ios::out);

        LOG_INFO << endl;
        auto results = execution_status.get_results();
        for (auto p = 0U; p < msa.part_count(); ++p) {
            auto bic_ranking = rank_by_score(results, InformationCriterion::bic, p);
            const auto &best_model = results.at(p).at(bic_ranking.at(0));
            LOG_INFO << "Partition #" << p << ": " << best_model.model.to_string() << " BIC = " << best_model.
                    ic_criteria.
                    at(InformationCriterion::bic) << " LogLH = " << best_model.partition_loglh << endl;

            bestmodel_stream << best_model.model.to_string(true, logger().precision(LogElement::model)) << ", " << msa.part_info(p).name() 
                << " = " << msa.part_info(p).range_string() << endl;


            best_model_per_part.emplace_back(best_model.model.to_string(false));
        }
    }
    return best_model_per_part;
}

vector<size_t> ModelTest::rank_by_score(const EvaluationResults &results,
                                        InformationCriterion ic,
                                        unsigned int partition_idx) {
    std::vector<size_t> ranking(results.at(partition_idx).size(), 0);
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


void ModelTest::print_xml(ostream &os, EvaluationResults &results) {
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

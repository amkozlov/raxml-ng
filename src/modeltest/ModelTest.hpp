#ifndef MODELTEST_HPP_
#define MODELTEST_HPP_
#include <iosfwd>
#include <optional>
#include <vector>

#include "../TreeInfo.hpp"
#include "../Optimizer.hpp"
#include "ModelDefinitions.hpp"

/** We use heuristics to reduce the number of candidate models that must be
 * tested. Results that the heuristic uses to decide which models to skip
 * should be given priority to reduce the number of unnecessary computations.
 */
enum class EvaluationPriority {
    NORMAL, /**< Default priority */
    HIGH /**< Indicates that result should be computed as soon as possible */
};

enum class EvaluationStatus {
    WAITING,
    RUNNING,
    ABORTED,
    FINISHED
};

struct EvaluationResult {
    Model model;
    double partition_loglh;
    std::map<InformationCriterion, double> ic_criteria;

    EvaluationResult &operator=(EvaluationResult &other) {
        model = other.model;
        partition_loglh = other.partition_loglh;
        ic_criteria = other.ic_criteria;

        return *this;
    }
};

/** Describes the (possibly multi-threaded) evaluation of a given candidate_model_t on a partition.
 * All calls to non-const methods must be protected with a mutex!
 */
class PartitionModelEvaluation {
public:
    PartitionModelEvaluation(candidate_model_t &candidate_model, size_t partition_index, EvaluationPriority priority,
                             size_t proposed_thread_count);

    /** Try to add calling thread with specified thread_id to the team */
    bool join_team();

    void abort();

    /** Store results from a finished computation. */
    void store_result(EvaluationResult &&result);

    /** Block until the status changes from WAITING to either RUNNING or
     * ABORTED. May only be called by threads that are part of the team */
    EvaluationStatus wait() const;

    const EvaluationResult &get_result() const;

    const volatile EvaluationStatus &get_status() const;

    const size_t &partition_index() const;
    const unsigned int &thread_id() const;
    const unsigned int volatile &assigned_threads() const;
    const size_t &proposed_thread_count() const;

    const candidate_model_t &candidate_model() const;

    EvaluationPriority priority() const;

    void barrier();
     
    static void reduce(void *context, double *data, size_t size, int op);
private:
    size_t _proposed_thread_count;
    candidate_model_t &_candidate_model;
    size_t _partition_index;

    EvaluationPriority _priority;

    volatile EvaluationStatus status;
    volatile unsigned int _barrier_counter;
    volatile int _barrier_proceed;
    static thread_local int _barrier_mycycle;

    volatile unsigned int _assigned_threads;
    vector<double> _reduce_buffer;

    static thread_local unsigned int _thread_id;

    /* Only valid when status == FINISHED */
    EvaluationResult _result;
};


class ModelTest {
public:
    ModelTest(const Options &options, const PartitionedMSA &msa, const Tree &tree, const IDVector &tip_msa_idmap,
              const PartitionAssignment &part_assign);

    vector<candidate_model_t> generate_candidate_model_names(const DataType &dt) const;

    /* Optimize the model and return model name per partition */
    vector<Model> optimize_model();

private:
    Options options;
    Optimizer optimizer;
    const PartitionedMSA &msa;
    const Tree &tree;
    const IDVector &tip_msa_idmap;
    const PartitionAssignment &part_assign;

    /// map from model descriptor to per-partition evaluation results
    [[nodiscard]]
    static vector<size_t> rank_by_score(const vector<EvaluationResult> &results,
                                        InformationCriterion ic);

    static void print_xml(ostream &os, const vector<PartitionModelEvaluation> &results);
};


#endif //MODELTEST_HPP_

#ifndef EVALUATION_HPP_
#define EVALUATION_HPP_

#include <optional>
#include <vector>

#include "ModelDefinitions.hpp"
#include "../Model.hpp"
#include "../PartitionInfo.hpp"

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

/** Describes the (possibly multi-threaded) evaluation of a given candidate_model_t on a partition.
 * All calls to non-const methods must be protected with a mutex!
 */
class ModelEvaluator {
public:
    ModelEvaluator(candidate_model_t *candidate_model, const PartitionStats &stats, size_t partition_index, EvaluationPriority priority,
                             size_t proposed_thread_count);

    /** Try to add calling thread with specified thread_id to the team */
    bool join_team();

    void abort();

    /** Store results from a finished computation. */
    void store_result(ModelEvaluation evaluation);

    /** Block until the status changes from WAITING to either RUNNING or
     * ABORTED. May only be called by threads that are part of the team */
    EvaluationStatus wait() const;

    const ModelEvaluation &get_result() const;

    const volatile EvaluationStatus &get_status() const;

    const size_t &partition_index() const;
    const unsigned int &thread_id() const;
    const unsigned int volatile &assigned_threads() const;
    const size_t &proposed_thread_count() const;

    const candidate_model_t *candidate_model() const;

    EvaluationPriority priority() const;

    void barrier();
     
    static void reduce(void *context, double *data, size_t size, int op);
private:
    size_t _proposed_thread_count;
    candidate_model_t *_candidate_model;
    size_t _partition_index;

    EvaluationPriority _priority;
    ModelEvaluation _result;

    /* Variables required for thread synchronization */
    volatile EvaluationStatus status;
    volatile unsigned int _barrier_counter;
    volatile int _barrier_proceed;
    static thread_local int _barrier_mycycle;

    volatile unsigned int _assigned_threads;
    std::vector<double> _reduce_buffer;

    static thread_local unsigned int _thread_id;
};

#endif

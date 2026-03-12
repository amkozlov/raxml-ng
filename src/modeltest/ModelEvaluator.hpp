#ifndef EVALUATION_HPP_
#define EVALUATION_HPP_

#include <vector>

#include "../Model.hpp"
#include "../PartitionInfo.hpp"
#include "ModelDefinitions.hpp"

/** We use heuristics to reduce the number of candidate models that must be
 * tested. Results that the heuristic uses to decide which models to skip
 * should be given priority to reduce the number of unnecessary computations.
 */
enum class EvaluationPriority
{
  LOW = 0,
  NORMAL, /**< Default priority */
  HIGH,
  HIGHEST /**< Indicates that result should be computed as soon as possible */
};

enum class EvaluationStatus
{
  WAITING,
  RUNNING,
  SKIPPED,
  FINISHED
};

/** Captures the run-time state of a possibly multi-threaded evaluation of a given ModelDescriptor on a partition.
 * All calls to non-const methods must be protected with an external mutex!
 */
class ModelEvaluator
{
public:
  ModelEvaluator(const ModelDescriptor &candidate_model, const PartitionStats &stats, size_t partition_index,
                 EvaluationPriority priority, size_t proposed_thread_count);

  /** Try to add calling thread with specified thread_id to the team */
  bool join_team();

  /** Mark this particular evaluation exempted. */
  void skip();

  /** Store results from a finished computation. */
  void store_result(const ModelEvaluation &evaluation);

  /** Block until the status changes from WAITING to either RUNNING or
   * SKIPPED. May only be called by threads that are part of the team */
  void wait() const;

  const ModelEvaluation &get_result() const;

  const volatile EvaluationStatus &get_status() const;

  const size_t &partition_index() const;

  const unsigned int &thread_id() const;

  const unsigned int volatile &assigned_threads() const;

  const size_t &proposed_thread_count() const;

  const ModelDescriptor &candidate_model() const;

  EvaluationPriority priority() const;

  void barrier();

  /** Custom reduction callback for synchronization between threads belonging to a given Evaluator/team.
   * @param context a pointer to the Evaluator
   */
  static void reduce(void *context, double *data, size_t size, int op);


  /** Copy rate-heterogeneity parameters (α, proportion of invariant sites, rates and weights) from other model evaluation.
   * @return true if parameters were copied successfully, false otherwise
   */
  bool copy_rhas_parameters(const ModelEvaluator *other);

private:
  size_t _proposed_thread_count;

  /* Pointer instead of reference to permit move operations when sorting evaluators*/
  const ModelDescriptor *_candidate_model;
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

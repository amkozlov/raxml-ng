#include "ModelEvaluator.hpp"
#include "ModelDefinitions.hpp"
#include <cmath>
#include <utility>

thread_local unsigned int ModelEvaluator::_thread_id = 0;
thread_local int ModelEvaluator::_barrier_mycycle = 0;

size_t max_reduction_cardinality(const RateHeterogeneityDescriptor &rhas)
{
    if (rhas.type == RateHeterogeneityType::FREE_RATE || rhas.type == RateHeterogeneityType::INVARIANT_FREE_RATE)
    {
        return std::max(2U, rhas.category_count);
    }
    return 2;
}

ModelEvaluator::ModelEvaluator(const ModelDescriptor &candidate_model, const PartitionStats &stats,
                                                   size_t partition_index, EvaluationPriority priority,
                                                   const size_t proposed_thread_count)
    : _proposed_thread_count{proposed_thread_count},
      _candidate_model{&candidate_model},
      _partition_index{partition_index},
      _priority{priority}, _result{Model(_candidate_model->descriptor()), NAN, NAN},
      status{EvaluationStatus::WAITING},
      _barrier_counter(0),
      _barrier_proceed(0),
      _assigned_threads(0),
      _reduce_buffer(_proposed_thread_count * max_reduction_cardinality(candidate_model.rate_heterogeneity), 0.) {
    assign(_result.model, stats);
}

bool ModelEvaluator::join_team() {
    if (status != EvaluationStatus::WAITING)
        return false;

    assert(_assigned_threads < _proposed_thread_count);

    _thread_id = _assigned_threads++;
    _barrier_mycycle = 0;

    if (_assigned_threads == _proposed_thread_count) {
        status = EvaluationStatus::RUNNING;
    }


    return true;
}

void ModelEvaluator::skip() {
    status = EvaluationStatus::SKIPPED;
}

void ModelEvaluator::wait() const {
    while (status == EvaluationStatus::WAITING) {
    }
}

void ModelEvaluator::store_result(ModelEvaluation result) {
    if (status == EvaluationStatus::FINISHED)
        return;

    _result = std::move(result);
    status = EvaluationStatus::FINISHED;
}

const volatile EvaluationStatus &ModelEvaluator::get_status() const {
    return status;
}

const size_t &ModelEvaluator::partition_index() const {
    return _partition_index;
}

const ModelDescriptor &ModelEvaluator::candidate_model() const {
    return *_candidate_model;
} 

const unsigned int &ModelEvaluator::thread_id() const {
    return _thread_id;
}

const unsigned int volatile &ModelEvaluator::assigned_threads() const {
    return _assigned_threads;
}

EvaluationPriority ModelEvaluator::priority() const {
    return _priority;
}

const ModelEvaluation &ModelEvaluator::get_result() const {
    return _result;
}

/* cf. ParallelContext::thread_barrier */
void ModelEvaluator::barrier()
{
    assert(status != EvaluationStatus::WAITING);

    __sync_fetch_and_add( &_barrier_counter, 1);

    if(_thread_id == 0)
    {
        while(_barrier_counter != _assigned_threads);
        _barrier_counter = 0;
        _barrier_proceed = !_barrier_proceed;
    }
    else
    {
        while(_barrier_mycycle == _barrier_proceed);
        _barrier_mycycle = !_barrier_mycycle;
    }
}

void ModelEvaluator::reduce(void *context, double *data, size_t size, int op)
{
    ModelEvaluator *c = static_cast<ModelEvaluator *>(context);

    assert(c->_reduce_buffer.size() >= size * c->_assigned_threads);

    /* synchronize */
    c->barrier();

    double *double_buf = (double*) c->_reduce_buffer.data();

    /* collect data from threads */
    size_t i, j;
    for (i = 0; i < size; ++i)
        double_buf[c->_thread_id * size + i] = data[i];

    /* synchronize */
    c->barrier();

    /* reduce */
    for (i = 0; i < size; ++i)
    {
        switch(op)
        {
        case CORAX_REDUCE_SUM:
        {
            data[i] = 0.;
            for (j = 0; j < c->_assigned_threads; ++j)
            data[i] += double_buf[j * size + i];
        }
        break;
        case CORAX_REDUCE_MAX:
        {
            data[i] = double_buf[i];
            for (j = 1; j < c->_assigned_threads; ++j)
            data[i] = std::max(data[i], double_buf[j * size + i]);
        }
        break;
        case CORAX_REDUCE_MIN:
        {
            data[i] = double_buf[i];
            for (j = 1; j < c->_assigned_threads; ++j)
            data[i] = std::min(data[i], double_buf[j * size + i]);
        }
        break;
        }
    }
}

const size_t &ModelEvaluator::proposed_thread_count() const
{
    return _proposed_thread_count;
}

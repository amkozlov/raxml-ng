#include "Evaluation.hpp"
#include "../ICScoreCalculator.hpp"
#include "../io/binary_io.hpp"
#include "ModelDefinitions.hpp"
#include <cmath>
#include <memory>

thread_local unsigned int PartitionModelEvaluation::_thread_id = 0;
thread_local int PartitionModelEvaluation::_barrier_mycycle = 0;

PartitionModelEvaluation::PartitionModelEvaluation(candidate_model_t *candidate_model,
                                                   size_t partition_index, EvaluationPriority priority,
                                                   const size_t proposed_thread_count)
    : _proposed_thread_count{proposed_thread_count},
      _candidate_model{candidate_model},
      _partition_index{partition_index},
      _priority{priority}, _result(*_candidate_model),
      status{EvaluationStatus::WAITING},
      _barrier_counter(0),
      _barrier_proceed(0),
      _assigned_threads(0),
      _reduce_buffer(_proposed_thread_count * 2, 0.) {
}

bool PartitionModelEvaluation::join_team() {
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

void PartitionModelEvaluation::abort() {
    status = EvaluationStatus::ABORTED;
}

EvaluationStatus PartitionModelEvaluation::wait() const {
    while (status == EvaluationStatus::WAITING) {
    }

    return status;
}

void PartitionModelEvaluation::store_result(double loglh, double ic_score) {
    if (status != EvaluationStatus::RUNNING) {
        return;
    }

    _result.loglh = loglh;
    _result.ic_score = ic_score;
    status = EvaluationStatus::FINISHED;
}

const volatile EvaluationStatus &PartitionModelEvaluation::get_status() const {
    return status;
}

const size_t &PartitionModelEvaluation::partition_index() const {
    return _partition_index;
}

const candidate_model_t *PartitionModelEvaluation::candidate_model() const {
    return _candidate_model;
}

const unsigned int &PartitionModelEvaluation::thread_id() const {
    return _thread_id;
}

const unsigned int volatile &PartitionModelEvaluation::assigned_threads() const {
    return _assigned_threads;
}

EvaluationPriority PartitionModelEvaluation::priority() const {
    return _priority;
}

EvaluationResult &PartitionModelEvaluation::modify_result() {
    return _result;
}

const EvaluationResult &PartitionModelEvaluation::get_result() const {
    return _result;
}

/* cf. ParallelContext::thread_barrier */
void PartitionModelEvaluation::barrier()
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

void PartitionModelEvaluation::reduce(void *context, double *data, size_t size, int op)
{
    PartitionModelEvaluation *c = static_cast<PartitionModelEvaluation *>(context);

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

const size_t &PartitionModelEvaluation::proposed_thread_count() const
{
    return _proposed_thread_count;

}


BasicBinaryStream& operator<<(BasicBinaryStream& stream, const EvaluationResult& result)
{
    stream.write(std::addressof(result.loglh), sizeof(result.loglh));
    stream.write(std::addressof(result.ic_score), sizeof(result.ic_score));

    stream << *result.model;

    return stream;
}

BasicBinaryStream& operator>>(BasicBinaryStream& stream, EvaluationResult& result)
{
    stream.read(std::addressof(result.loglh), sizeof(result.loglh));
    stream.read(std::addressof(result.ic_score), sizeof(result.ic_score));

    stream >> *result.model;

    return stream;
}

EvaluationResult::EvaluationResult(const candidate_model_t &candidate_model)
 : model(std::make_unique<Model>(candidate_model.descriptor())), loglh(NAN), ic_score(NAN) {}

/*
EvaluationResult::EvaluationResult()
 : loglh(NAN), ic_score(NAN) {}

EvaluationResult::EvaluationResult(Model &&model, double partition_loglh, double ic_score)
    : model(std::make_unique<Model>(model)), loglh(partition_loglh), ic_score(ic_score)
{ }
*/

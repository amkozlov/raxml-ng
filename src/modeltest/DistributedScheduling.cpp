#include "DistributedScheduling.hpp"
#include "ModelEvaluator.hpp"
#include "../io/binary_io.hpp"

#ifdef _RAXML_MPI
#include <mpi.h>
DistributedSchedulingMPI::DistributedSchedulingMPI(size_t results_capacity)
    : local_results_offset(sizeof(uint64_t)),
      results_capacity(results_capacity)
{
    const bool main_rank = ParallelContext::rank_id() == MAIN_SCHEDULING_RANK;
    void *baseptr;
    const auto index_window_size = main_rank ? sizeof(uint64_t) : 0;

    MPI_Win_allocate(index_window_size, sizeof(uint64_t),
            MPI_INFO_NULL, MPI_COMM_WORLD,
            &baseptr, &win_index);
    
    const auto results_window_size = main_rank ? results_capacity : 0;

    MPI_Win_allocate(results_window_size, 1,
            MPI_INFO_NULL, MPI_COMM_WORLD,
            &baseptr, &win_results);

    local_results_offset = sizeof(uint64_t);
    if (main_rank) {

        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, MAIN_SCHEDULING_RANK, 0, win_results);

        // Initialize results displacement to the first entry after the counter
        MPI_Put(&local_results_offset, 1, MPI_UINT64_T, 
               MAIN_SCHEDULING_RANK, 0, 1, MPI_UINT64_T, 
               win_results);

        MPI_Win_unlock(0, win_results);

        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, MAIN_SCHEDULING_RANK, 0, win_index);
        // Initialize global evaluation index to zero
        const uint64_t zero = 0;
        MPI_Put(&zero, 1, MPI_UINT64_T, 
               MAIN_SCHEDULING_RANK, 0, 1, MPI_UINT64_T, 
               win_index);
        MPI_Win_unlock(0, win_index);
    }
    

    MPI_Win_fence(0, win_results);
    MPI_Win_fence(0, win_index);

}

DistributedSchedulingMPI::~DistributedSchedulingMPI() {
    MPI_Win_free(&win_results);
    MPI_Win_free(&win_index);
}

uint64_t DistributedSchedulingMPI::next_evaluation_index() 
{
    const uint64_t one = 1;
    uint64_t assigned_evaluation_index;

    MPI_Win_lock(MPI_LOCK_SHARED, MAIN_SCHEDULING_RANK, 0, win_index);

    MPI_Fetch_and_op(&one, &assigned_evaluation_index, MPI_UINT64_T, MAIN_SCHEDULING_RANK, 0, MPI_SUM, win_index);

    MPI_Win_unlock(MAIN_SCHEDULING_RANK, win_index);

    return assigned_evaluation_index;
}

void DistributedSchedulingMPI::announce_result(uint64_t index, const ModelEvaluation &result)
{
    const size_t result_size = sizeof(index) + BinaryStream::serialized_size(result);
    serialization_buffer.resize(result_size);

    BinaryStream stream(serialization_buffer.data(), serialization_buffer.size());
    stream.write(&index, sizeof(index));
    stream << result;

    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, MAIN_SCHEDULING_RANK, 0, win_results);
    MPI_Request req;

    uint64_t result_displacement;
    MPI_Rget(&result_displacement, 1, MPI_UINT64_T,
            MAIN_SCHEDULING_RANK, 0, 1, MPI_UINT64_T,
            win_results, &req);
    MPI_Wait(&req, MPI_STATUSES_IGNORE);

    MPI_Put(serialization_buffer.data(), stream.size(), MPI_BYTE,
            MAIN_SCHEDULING_RANK, result_displacement, stream.size(), MPI_BYTE,
            win_results);

    if (local_results_offset == result_displacement) {
        local_results_offset += stream.size();
    }

    result_displacement += stream.size();
    assert(result_displacement <= results_capacity);
    MPI_Put(&result_displacement, 1, MPI_UINT64_T,
            MAIN_SCHEDULING_RANK, 0, 1, MPI_UINT64_T,
            win_results);

    MPI_Win_unlock(MAIN_SCHEDULING_RANK, win_results);
}

void DistributedSchedulingMPI::fetch_results(ModelUpdateCallback callback)
{
    uint64_t new_offset;
    MPI_Request req;
    MPI_Win_lock(MPI_LOCK_SHARED, MAIN_SCHEDULING_RANK, 0, win_results);

    MPI_Rget(&new_offset, 1, MPI_UINT64_T,
            MAIN_SCHEDULING_RANK, 0, 1, MPI_UINT64_T,
            win_results, &req);

    MPI_Wait(&req, MPI_STATUS_IGNORE);

    const auto fetch_size = new_offset - local_results_offset;
    if (fetch_size > 0) {
        deserialization_buffer.resize(fetch_size);
        MPI_Get(deserialization_buffer.data(), fetch_size, MPI_BYTE,
                MAIN_SCHEDULING_RANK, local_results_offset, fetch_size, MPI_BYTE,
                win_results);
    }

    MPI_Win_unlock(MAIN_SCHEDULING_RANK, win_results);

    BinaryStream stream(deserialization_buffer.data(), deserialization_buffer.size());

    while (stream.pos() < stream.size()) {
        uint64_t index;
        stream.read(&index, sizeof(index));
        ModelEvaluation result;
        stream >> result;
        callback(index, result);
    }
}

#else

DistributedSchedulingDummy::DistributedSchedulingDummy(uint64_t evaluation_count)
    : evaluation_index{0}
{
    RAXML_UNUSED(evaluation_count);
}

DistributedSchedulingDummy::~DistributedSchedulingDummy() {}

uint64_t DistributedSchedulingDummy::next_evaluation_index()
{
    return evaluation_index++;
}

void DistributedSchedulingDummy::announce_result(uint64_t index, const ModelEvaluation &result)
{
    RAXML_UNUSED(index);
    RAXML_UNUSED(result);
}

void DistributedSchedulingDummy::fetch_results(ModelUpdateCallback callback)
{
    RAXML_UNUSED(callback);
}

#endif

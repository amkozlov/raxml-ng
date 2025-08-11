#ifndef DISTRIBUTED_SCHEDULING_HPP_
#define DISTRIBUTED_SCHEDULING_HPP_

#include <cstdint>
#include "Evaluation.hpp"

struct IndexedEvaluationResult
{
    uint64_t index;
    EvaluationResult result;
};
BasicBinaryStream& operator<<(BasicBinaryStream& stream, const IndexedEvaluationResult &result);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, IndexedEvaluationResult &result);

/** Contains methods required to coordinate scheduling and communicate results on distributed-memory machines.
 * This class is not thread-safe and all calls must be protected with a mutex.
 */
class DistributedScheduling
{
    public:
    virtual uint64_t next_evaluation_index() = 0;
    virtual void announce_result(const IndexedEvaluationResult &) = 0;
    virtual void fetch_results(std::function<void(IndexedEvaluationResult)> callback) = 0;
    virtual void finalize() = 0;
};

#ifdef _RAXML_MPI
constexpr int MAIN_SCHEDULING_RANK = 0;
constexpr size_t MAX_MODEL_STRING_LEN = 256;
class DistributedSchedulingMPI final : public DistributedScheduling
{
    public:
        DistributedSchedulingMPI(uint64_t evaluation_count);
        virtual void finalize() override;

        uint64_t next_evaluation_index() override;
        void announce_result(const IndexedEvaluationResult &result) override;
        void fetch_results(std::function<void(IndexedEvaluationResult)> callback) override;
    private:
        MPI_Win win_index, win_results;
        std::vector<char> serialization_buffer, deserialization_buffer;
        uint64_t local_results_offset;
};

using DistributedSchedulingImpl = DistributedSchedulingMPI;
#else 
class DistributedSchedulingDummy final : public DistributedScheduling
{
    public:
        DistributedSchedulingDummy(uint64_t evaluation_count);
        virtual void finalize() override;

        uint64_t next_evaluation_index() override;
        void announce_result(const IndexedEvaluationResult &result) override;
        void fetch_results(std::function<void(IndexedEvaluationResult)> callback) override;

    private:
        uint64_t evaluation_index;
};
using DistributedSchedulingImpl = DistributedSchedulingDummy;
#endif

#endif

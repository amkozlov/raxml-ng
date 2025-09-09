#ifndef DISTRIBUTED_SCHEDULING_HPP_
#define DISTRIBUTED_SCHEDULING_HPP_

#include "ModelEvaluator.hpp"
#include <cstdint>

typedef std::function<void(uint64_t index, const ModelEvaluation &m)> ModelUpdateCallback;
/** Contains methods required to coordinate scheduling and communicate results on distributed-memory machines.
 * This class is not thread-safe and all calls must be protected with a mutex.
 */
class DistributedScheduling
{
public:
  virtual uint64_t next_evaluation_index() = 0;

  virtual void announce_result(uint64_t index, const ModelEvaluation &) = 0;

  virtual void fetch_results(ModelUpdateCallback callback) = 0;

  virtual ~DistributedScheduling() {}
};

#ifdef _RAXML_MPI
constexpr int MAIN_SCHEDULING_RANK = 0;
constexpr size_t MAX_MODEL_STRING_LEN = 256;

class DistributedSchedulingMPI final : public DistributedScheduling
{
public:
  DistributedSchedulingMPI(size_t results_capacity);

  virtual ~DistributedSchedulingMPI();

  uint64_t next_evaluation_index() override;

  void announce_result(uint64_t index, const ModelEvaluation &result) override;

  /* TODO: prettify call interface */
  void fetch_results(ModelUpdateCallback callback) override;

private:
  MPI_Win win_index, win_results;
  std::vector<char> serialization_buffer, deserialization_buffer;
  uint64_t local_results_offset;

  const size_t results_capacity;
};

using DistributedSchedulingImpl = DistributedSchedulingMPI;
#else
class DistributedSchedulingDummy final : public DistributedScheduling
{
public:
  DistributedSchedulingDummy(uint64_t evaluation_count);
  virtual ~DistributedSchedulingDummy();

  uint64_t next_evaluation_index() override;
  void announce_result(uint64_t index, const ModelEvaluation &result) override;
  void fetch_results(ModelUpdateCallback callback) override;

private:
  uint64_t evaluation_index;
};
using DistributedSchedulingImpl = DistributedSchedulingDummy;
#endif

#endif

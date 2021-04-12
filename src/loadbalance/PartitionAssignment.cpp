#include "PartitionAssignment.hpp"

PartitionAssignmentStats::PartitionAssignmentStats(const PartitionAssignmentList& part_assign)
{
  num_cores = part_assign.size();
  total_parts = total_sites = total_weight = 0;
  max_thread_sites = max_thread_parts = 0;
  max_thread_weight = 0.;
  min_thread_sites = min_thread_parts = std::numeric_limits<size_t>::max();
  min_thread_weight = std::numeric_limits<double>::max();
  for (const auto& pa: part_assign)
  {
    min_thread_parts = std::min(min_thread_parts, pa.num_parts());
    max_thread_parts = std::max(max_thread_parts, pa.num_parts());
    min_thread_sites = std::min(min_thread_sites, pa.length());
    max_thread_sites = std::max(max_thread_sites, pa.length());
    min_thread_weight = std::min(min_thread_weight, pa.weight());
    max_thread_weight = std::max(max_thread_weight, pa.weight());
    total_sites += pa.length();
    total_weight += pa.weight();
    total_parts += pa.num_parts();
  }
}

std::ostream& operator<<(std::ostream& stream, const PartitionAssignment& pa)
{
  stream << "part#\tstart\tlength" << std::endl;
  for (const auto& range: pa)
    stream << range.part_id << "\t" << range.start << "\t" << range.length << std::endl;
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const PartitionAssignmentList& pal)
{
  stream << "thread#\tpart#\tstart\tlength\tweight" << std::endl;
  size_t i = 0;
  for (const auto& pa: pal)
  {
    for (const auto& range: pa)
    {
      stream << i << "\t" << range.part_id << "\t"
             << range.start << "\t" << range.length
             << "\t" << (size_t) range.weight() << std::endl;
    }
    stream << std::endl;
    ++i;
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const PartitionAssignmentStats& stats)
{
  stream << "max. partitions/sites/weight per thread: " << stats.max_thread_parts << " / "
         << stats.max_thread_sites << " / "
         << (size_t) stats.max_thread_weight;
  return stream;
}


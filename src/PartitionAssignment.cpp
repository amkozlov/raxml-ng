#include "PartitionAssignment.hpp"

std::ostream& operator<<(std::ostream& stream, const PartitionAssignment& pa)
{
  stream << "part#\tstart\tlength" << std::endl;
  for (auto const& range: pa)
    stream << range.part_id << "\t" << range.start << "\t" << range.length << std::endl;
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const PartitionAssignmentList& pal)
{
  stream << "thread#\tpart#\tstart\tlength" << std::endl;
  size_t i = 0;
  for (auto const& pa: pal)
  {
    for (auto const& range: pa)
      stream << i << "\t" << range.part_id << "\t" <<
                range.start << "\t" << range.length << std::endl;
    stream << std::endl;
    ++i;
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const PartitionAssignmentStats& stats)
{
  stream << "partitions/thread: " << stats.min_thread_parts << "-" << stats.max_thread_parts <<
      ", patterns/thread: " << stats.min_thread_sites << "-" << stats.max_thread_sites;
  return stream;
}


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



#ifndef RAXML_PARTITIONASSIGNMENT_HPP_
#define RAXML_PARTITIONASSIGNMENT_HPP_

#include <vector>
#include <ostream>
#include <algorithm>

struct PartitionRange
{
  PartitionRange() : part_id(0), start(0), length(0) {}
  PartitionRange(size_t part_id, size_t start, size_t length):
    part_id(part_id), start(start), length(length) {};

  size_t part_id;
  size_t start;
  size_t length;
};

struct PartitionAssignment
{
  typedef std::vector<PartitionRange>         container;
  typedef typename container::iterator        iterator;
  typedef typename container::const_iterator  const_iterator;

  PartitionAssignment() : weight_(0.0) {}

  size_t weight() const { return (size_t) weight_; }
  const PartitionRange& operator[](size_t i) const { return part_range_list_.at(i); }
  const_iterator find(size_t part_id) const
  {
    return std::find_if( part_range_list_.cbegin(),  part_range_list_.cend(),
                         [part_id](const PartitionRange& r) { return (r.part_id == part_id);} );
  };

  void assign_sites(size_t partition_id, size_t offset, size_t length)
  {
    part_range_list_.emplace_back(partition_id, offset, length);
    weight_ += length;
  }

  const_iterator begin() const { return part_range_list_.cbegin(); };
  const_iterator end() const { return part_range_list_.cend(); };

private:
  container part_range_list_;
  double weight_;
};

typedef std::vector<PartitionAssignment> PartitionAssignmentList;

std::ostream& operator<<(std::ostream& stream, const PartitionAssignment& pa);
std::ostream& operator<<(std::ostream& stream, const PartitionAssignmentList& pal);

#endif /* RAXML_PARTITIONASSIGNMENT_HPP_ */

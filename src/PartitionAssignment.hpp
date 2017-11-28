#ifndef RAXML_PARTITIONASSIGNMENT_HPP_
#define RAXML_PARTITIONASSIGNMENT_HPP_

#include <vector>
#include <ostream>
#include <algorithm>
#include <limits>

struct PartitionRange
{
  PartitionRange() : part_id(0), start(0), length(0) {}
  PartitionRange(size_t part_id, size_t start, size_t length):
    part_id(part_id), start(start), length(length) {};

  bool master() const { return start == 0; };

  size_t part_id;
  size_t start;
  size_t length;
};

struct PartitionAssignment
{
  typedef std::vector<PartitionRange>         container;
  typedef typename container::iterator        iterator;
  typedef typename container::const_iterator  const_iterator;

  PartitionAssignment() : _weight(0.0) {}

  size_t num_parts() const { return _part_range_list.size(); }
  size_t weight() const { return (size_t) _weight; }
  const PartitionRange& operator[](size_t i) const { return _part_range_list.at(i); }
  const_iterator find(size_t part_id) const
  {
    return std::find_if( _part_range_list.cbegin(),  _part_range_list.cend(),
                         [part_id](const PartitionRange& r) { return (r.part_id == part_id);} );
  };

  void assign_sites(size_t partition_id, size_t offset, size_t length)
  {
    _part_range_list.emplace_back(partition_id, offset, length);
    _weight += length;
  }

  const_iterator begin() const { return _part_range_list.cbegin(); };
  const_iterator end() const { return _part_range_list.cend(); };
  iterator begin() { return _part_range_list.begin(); };
  iterator end() { return _part_range_list.end(); };

private:
  container _part_range_list;
  double _weight;
};

typedef std::vector<PartitionAssignment> PartitionAssignmentList;

struct PartitionAssignmentStats
{
  PartitionAssignmentStats(const PartitionAssignmentList& part_assign)
  {
    total_sites = 0;
    max_thread_sites = max_thread_parts = 0;
    min_thread_sites = min_thread_parts = std::numeric_limits<size_t>::max();
    for (auto pa: part_assign)
    {
      min_thread_sites = std::min(min_thread_sites, pa.weight());
      min_thread_parts = std::min(min_thread_parts, pa.num_parts());
      max_thread_sites = std::max(max_thread_sites, pa.weight());
      max_thread_parts = std::max(max_thread_parts, pa.num_parts());
      total_sites += pa.weight();
    }
  }

  size_t total_sites;
  size_t min_thread_sites;
  size_t min_thread_parts;
  size_t max_thread_sites;
  size_t max_thread_parts;
};

std::ostream& operator<<(std::ostream& stream, const PartitionAssignment& pa);
std::ostream& operator<<(std::ostream& stream, const PartitionAssignmentList& pal);
std::ostream& operator<<(std::ostream& stream, const PartitionAssignmentStats& stats);

#endif /* RAXML_PARTITIONASSIGNMENT_HPP_ */

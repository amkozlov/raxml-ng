#ifndef RAXML_PARTITIONASSIGNMENT_HPP_
#define RAXML_PARTITIONASSIGNMENT_HPP_

#include <vector>
#include <ostream>
#include <algorithm>
#include <limits>

struct PartitionRange
{
  PartitionRange() : part_id(0), start(0), length(0), per_site_weight(1.) {}
  PartitionRange(size_t part_id, size_t start, size_t length, double site_weight = 1.):
    part_id(part_id), start(start), length(length), per_site_weight(site_weight) {};

  bool master() const { return start == 0; };
  double weight() const { return length * per_site_weight; }

  size_t part_id;
  size_t start;
  size_t length;
  double per_site_weight;
};

struct PartitionAssignment
{
  typedef std::vector<PartitionRange>         container;
  typedef typename container::iterator        iterator;
  typedef typename container::const_iterator  const_iterator;

  PartitionAssignment() : _length(0.0), _weight(0.0) {}

  bool empty() const { return _part_range_list.empty(); }
  size_t num_parts() const { return _part_range_list.size(); }
  size_t length() const { return _length; }
  double weight() const { return _weight; }
  const PartitionRange& operator[](size_t i) const { return _part_range_list.at(i); }
  const_iterator find(size_t part_id) const
  {
    return std::find_if( _part_range_list.cbegin(),  _part_range_list.cend(),
                         [part_id](const PartitionRange& r) { return (r.part_id == part_id);} );
  };

  void assign_sites(size_t partition_id, size_t offset, size_t length, double site_weight = 1.)
  {
    _part_range_list.emplace_back(partition_id, offset, length, site_weight);
    _length += length;
    _weight += length * site_weight;
  }

  const_iterator begin() const { return _part_range_list.cbegin(); };
  const_iterator end() const { return _part_range_list.cend(); };
  iterator begin() { return _part_range_list.begin(); };
  iterator end() { return _part_range_list.end(); };

private:
  container _part_range_list;
  size_t _length;
  double _weight;
};

typedef std::vector<PartitionAssignment> PartitionAssignmentList;

struct PartitionAssignmentStats
{
  PartitionAssignmentStats(const PartitionAssignmentList& part_assign);

  size_t num_cores;
  size_t total_parts;
  size_t total_sites;
  size_t total_weight;
  size_t min_thread_parts;
  size_t max_thread_parts;
  size_t min_thread_sites;
  size_t max_thread_sites;
  double min_thread_weight;
  double max_thread_weight;
};

std::ostream& operator<<(std::ostream& stream, const PartitionAssignment& pa);
std::ostream& operator<<(std::ostream& stream, const PartitionAssignmentList& pal);
std::ostream& operator<<(std::ostream& stream, const PartitionAssignmentStats& stats);

#endif /* RAXML_PARTITIONASSIGNMENT_HPP_ */

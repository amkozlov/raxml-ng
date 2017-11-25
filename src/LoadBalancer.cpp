#include <assert.h>
#include <stack>
#include <algorithm>
#include <stdexcept>

#include "LoadBalancer.hpp"

using namespace std;

LoadBalancer::LoadBalancer ()
{
  // TODO Auto-generated constructor stub

}

LoadBalancer::~LoadBalancer ()
{
  // TODO Auto-generated destructor stub
}

PartitionAssignmentList LoadBalancer::get_all_assignments(const PartitionAssignment& part_sizes,
                                                          size_t num_procs)
{
  if (num_procs == 1)
    return PartitionAssignmentList(1, part_sizes);
  else
    return compute_assignments(part_sizes, num_procs);
}

PartitionAssignment LoadBalancer::get_proc_assignments(const PartitionAssignment& part_sizes,
                                                       size_t num_procs, size_t proc_id)
{
  if (proc_id >= num_procs)
    throw std::out_of_range("Process ID out of range");

  if (num_procs == 1)
    return part_sizes;
  else
    return compute_assignments(part_sizes, num_procs).at(proc_id);
}

PartitionAssignmentList SimpleLoadBalancer::compute_assignments(const PartitionAssignment& part_sizes,
                                                                    size_t num_procs)
{
  PartitionAssignmentList part_assign(num_procs);

  size_t proc_id = 0;
  for (auto& proc_assign: part_assign)
  {
    for (auto const& full_range: part_sizes)
    {
      const size_t total_sites = full_range.length;
      const size_t proc_sites = total_sites / num_procs;
      auto part_id = full_range.part_id;
      auto start = full_range.start + proc_id * proc_sites;
      auto length = (proc_id == num_procs-1) ? total_sites - start : proc_sites;
      proc_assign.assign_sites(part_id, start, length);
    }
    ++proc_id;
  }

  assert(proc_id == part_assign.size());

  return part_assign;
}

PartitionAssignmentList KassianLoadBalancer::compute_assignments(const PartitionAssignment& part_sizes,
                                                                 size_t num_procs)
{
  PartitionAssignmentList bins(num_procs);

  // Sort the partitions by size in ascending order
  vector<const PartitionRange*> sorted_partitions;
  for (auto const& range: part_sizes)
    sorted_partitions.push_back(&range);
  sort(sorted_partitions.begin(), sorted_partitions.end(),
       [](const PartitionRange *r1, const PartitionRange *r2) { return (r1->length < r2->length);} );

  // Compute the maximum number of sites per Bin
  size_t total_sites = 0;
  for (auto const& range: part_sizes)
  {
    total_sites += range.length;
  }

  size_t max_sites = (total_sites - 1) / bins.size() + 1;
  size_t r = (max_sites * bins.size()) - total_sites;
  size_t target_full_bins = bins.size() - r;
  size_t curr_part = 0; // index in sorted_partitons (AND NOT IN _partitions)
  size_t full_bins = 0;
  size_t current_bin = 0;

//  vector<size_t> weights(num_procs, 0);
  vector<bool> full(num_procs, false);

  // Assign partitions in a cyclic manner to bins until one is too big
  for (; curr_part < sorted_partitions.size(); ++curr_part)
  {
    const PartitionRange *partition = sorted_partitions[curr_part];
    current_bin = curr_part % bins.size();
    if (partition->length + bins[current_bin].weight() > max_sites)
    {
      // the partition exceeds the current bin's size, go to the next step of the algo
      break;
    }
    // add the partition !
    bins[current_bin].assign_sites(partition->part_id, 0, partition->length);
    if (bins[current_bin].weight() == max_sites)
    {
      // one more bin is exactly full
      if (++full_bins == target_full_bins)
      {
        // border case : the remaining bins should not exceed max_sites - 1
        max_sites--;
      }
      // flag it as full (its harder to rely on max_sites because its value changes)
      full[current_bin] = true;
    }
  }

  stack<PartitionAssignment *> qlow_;
  stack<PartitionAssignment *> *qlow = &qlow_; // hack to assign qhigh to qlow when qlow is empty
  stack<PartitionAssignment *> qhigh;
  for (unsigned int i = 0; i < current_bin; ++i)
  {
    if (!full[i])
    {
      qhigh.push(&bins[i]);
    }
  }
  for (unsigned int i = current_bin; i < bins.size(); ++i)
  {
    if (!full[i])
    {
      qlow->push(&bins[i]);
    }
  }

  size_t remaining = sorted_partitions[curr_part]->length;
  while (curr_part < sorted_partitions.size() && (qlow->size() || qhigh.size()))
  {
    const PartitionRange *partition = sorted_partitions[curr_part];
    // try to dequeue a process from Qhigh and to fill it
    if (qhigh.size() && (qhigh.top()->weight() + remaining >= max_sites))
    {
      PartitionAssignment * bin = qhigh.top();
      qhigh.pop();
      size_t toassign = max_sites - bin->weight();
      bin->assign_sites(partition->part_id, partition->length - remaining, toassign);
      assert(remaining >= toassign);
      remaining -= toassign;
      if (++full_bins == target_full_bins) {
        max_sites--;
      }
    }
    else if ((qlow->top()->weight() + remaining >= max_sites))
    { // same with qlow
      PartitionAssignment * bin = qlow->top();
      qlow->pop();
      size_t toassign = max_sites - bin->weight();
      bin->assign_sites(partition->part_id, partition->length - remaining, toassign);
      assert(remaining >= toassign);
      remaining -= toassign;
      if (++full_bins == target_full_bins) {
        max_sites--;
      }
    }
    else
    {
      PartitionAssignment * bin = qlow->top();
      qlow->pop();
      bin->assign_sites(partition->part_id, partition->length - remaining, remaining);
      remaining = 0;
      qhigh.push(bin);
    }

    if (!qlow->size())
    {
      qlow = &qhigh;
    }
    if (!remaining)
    {
      if (++curr_part < sorted_partitions.size())
      {
        remaining = sorted_partitions[curr_part]->length;
      }
    }
  }

  return bins;
}

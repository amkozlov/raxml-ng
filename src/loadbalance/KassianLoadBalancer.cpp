#include <assert.h>
#include <stack>
#include <algorithm>
#include <stdexcept>

#include "LoadBalancer.hpp"

using namespace std;

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

  size_t orig_max_sites = (total_sites - 1) / bins.size() + 1;
  size_t max_sites = orig_max_sites;
  size_t r = (max_sites * bins.size()) - total_sites;
  size_t target_full_bins = bins.size() - r;
  size_t curr_part = 0; // index in sorted_partitons (AND NOT IN _partitions)
  size_t full_bins = 0;
  size_t current_bin = 0;

  vector<bool> full(num_procs, false);

  // Assign partitions in a cyclic manner to bins until one is too big
  for (; curr_part < sorted_partitions.size(); ++curr_part)
  {
    const PartitionRange *partition = sorted_partitions[curr_part];
    current_bin = curr_part % bins.size();
    if (partition->length + bins[current_bin].length() > max_sites)
    {
      // the partition exceeds the current bin's size, go to the next step of the algo
      break;
    }
    // add the partition !
    bins[current_bin].assign_sites(partition->part_id, 0, partition->length,
                                   partition->per_site_weight);
    if (bins[current_bin].length() == max_sites)
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

  /* all partitions have been assigned during phase 1 -> return result immediately */
  if (curr_part == sorted_partitions.size())
    return bins;

  stack<PartitionAssignment *> qlow_;
  stack<PartitionAssignment *> *qlow = &qlow_; // hack to assign qhigh to qlow when qlow is empty
  stack<PartitionAssignment *> qhigh;
  for (unsigned int i = 0; i < bins.size(); ++i)
  {
    if (bins[i].length() >= max_sites)
    {
      full[i] = true;
    }
    else if (i < current_bin)
    {
      qhigh.push(&bins[i]);
    }
    else
    {
      qlow->push(&bins[i]);
    }
  }

  size_t remaining = sorted_partitions[curr_part]->length;
  while (curr_part < sorted_partitions.size() && (qlow->size() || qhigh.size()))
  {
    const PartitionRange *partition = sorted_partitions[curr_part];
    // try to dequeue a process from Qhigh and to fill it
    if (qhigh.size() && (qhigh.top()->length() + remaining >= max_sites))
    {
      PartitionAssignment * bin = qhigh.top();
      qhigh.pop();
      size_t toassign = max_sites - bin->length();
      bin->assign_sites(partition->part_id, partition->length - remaining, toassign,
                        partition->per_site_weight);
      assert(remaining >= toassign);
      remaining -= toassign;
      if (++full_bins == target_full_bins) {
        max_sites--;
      }
    }
    else if ((qlow->top()->length() + remaining >= max_sites))
    { // same with qlow
      PartitionAssignment * bin = qlow->top();
      qlow->pop();
      size_t toassign = max_sites - bin->length();
      bin->assign_sites(partition->part_id, partition->length - remaining, toassign,
                        partition->per_site_weight);
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
      bin->assign_sites(partition->part_id, partition->length - remaining, remaining,
                        partition->per_site_weight);
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

  assert(orig_max_sites - max_sites <= 1);

  return bins;
}

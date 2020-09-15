#include <assert.h>
#include <stack>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <float.h>

#include "LoadBalancer.hpp"

using namespace std;

struct BalancerState
{
  size_t num_parts;
  size_t num_procs;
  vector<const PartitionRange*> sorted_partitions;
  PartitionAssignmentList bins;
  double opt_bin_weight;
  double min_bin_weight;
  double max_bin_weight;
  double rest_over_weight;
  size_t curr_part;
  size_t current_bin;
  size_t remaining;
  size_t total_remaining;
  size_t empty_bins;

  stack<PartitionAssignment *> qlow_;
  stack<PartitionAssignment *> qhigh_;
};

static void init(BalancerState& s, const PartitionAssignment& part_sizes, size_t num_procs)
{
  s.num_procs = num_procs;
  s.bins.resize(s.num_procs);
  s.empty_bins = s.num_procs;
  s.num_parts = part_sizes.num_parts();

  // Sort the partitions by size in ascending order
  for (auto const& range: part_sizes)
    s.sorted_partitions.push_back(&range);
  sort(s.sorted_partitions.begin(), s.sorted_partitions.end(),
       [](const PartitionRange *r1, const PartitionRange *r2)
          { return (r1->weight() < r2->weight());} );

  double total_weight =   part_sizes.weight();
  double total_sites =   part_sizes.length();
  double max_site_weight = 0.;
  double min_site_weight = FLT_MAX;
  s.total_remaining = total_sites;
  for (auto const& range: part_sizes)
  {
    max_site_weight = std::max(max_site_weight, range.per_site_weight);
    min_site_weight = std::min(min_site_weight, range.per_site_weight);
  }

  assert(max_site_weight > 0.);

  // Compute the optimum number of sites per bin
  s.opt_bin_weight = total_weight / s.num_procs;
  s.min_bin_weight = std::max(s.opt_bin_weight - max_site_weight, min_site_weight);
  s.max_bin_weight = s.opt_bin_weight + max_site_weight;
  s.rest_over_weight = 0.8 * s.opt_bin_weight;

//  printf("%lf  %lf   %lf  %lf\n",
//         s.opt_bin_weight, s.min_bin_weight, s.max_bin_weight, s.rest_over_weight);

  s.curr_part = 0; // index in sorted_partitons (AND NOT IN _partitions)
  s.current_bin = 0;

//  printf("bins: %lu, weight total / opt / max: %f / %f / %f\n",
//         s.bins.size(), total_weight, s.opt_bin_weight, s.max_bin_wesinight);
}

static size_t assign_sites(BalancerState& s, PartitionAssignment& bin, size_t part_id,
                         size_t offset, size_t len, double per_site_weight)
{
  if (!len)
    return 0;
  if (bin.empty())
    s.empty_bins--;
  size_t sites_toassign = std::min(len, s.total_remaining - s.empty_bins);
  bin.assign_sites(part_id, offset, sites_toassign, per_site_weight);
  s.total_remaining -= sites_toassign;
  return sites_toassign;
}

static void kassian_phase1(BalancerState& s)
{
  // Phase 1: Assign FULL partitions in a cyclic manner to bins until one is too big
  for (; s.curr_part < s.sorted_partitions.size(); ++s.curr_part)
  {
    s.current_bin = s.curr_part % s.bins.size();
    PartitionAssignment& bin = s.bins[s.current_bin];
    const PartitionRange *partition = s.sorted_partitions[s.curr_part];

    // the partition exceeds the current bin's size, go to the next step of the algo
    if (partition->weight() + bin.weight() > s.max_bin_weight)
      break;

    // add the partition
    assign_sites(s, bin, partition->part_id, 0, partition->length, partition->per_site_weight);

    if (bin.weight() > s.opt_bin_weight)
      s.rest_over_weight -= bin.weight() - s.opt_bin_weight;
  }
}

static void fill_queues(BalancerState& s)
{
  for (unsigned int i = 0; i < s.bins.size(); ++i)
  {
    PartitionAssignment * bin = &s.bins[i];

    // do not add bins which are already full
    if (bin->weight() >= s.min_bin_weight)
      continue;

    if (i < s.current_bin)
      s.qhigh_.push(bin);
    else
      s.qlow_.push(bin);
  }
}

static bool can_fill_bin(BalancerState& s,  stack<PartitionAssignment *>& q, double add_weight,
    double per_site_weight)
{
  if (!q.size())
    return false;
  else
  {
    // here check that:
    // 1) remaining partition weight (add_weight) is enough to fill up the bin (free_capacity)
    //    AND
    // 2) we can assign at least 1 site to the bin (exceeding its optimal weight if
    //    there is still rest_over_weight left)
    auto free_capacity = s.opt_bin_weight - q.top()->weight();
    return (add_weight >= free_capacity) &&
        (per_site_weight < free_capacity || s.rest_over_weight > 0);
  }
}

static void fill_bin(BalancerState& s,  stack<PartitionAssignment *>& q)
{
  const PartitionRange *partition = s.sorted_partitions[s.curr_part];

  assert(s.remaining > 0);
  assert(!q.empty());

  // sites from current partition can fill a bin from qhigh COMPLETELY
  PartitionAssignment * bin = q.top();
  q.pop();

  size_t toassign = 0;
  if (s.qhigh_.empty() && s.qlow_.empty())
  {
    // special case: this is the LAST bin so we assign ALL remaining sites to it
    // this could lead to a slightly suboptimal load-balancing in extremely rare cases,
    // but allows to simplify the algorithm and avoid splitting a small partition
    // remainder across multiple bins (which would also be suboptimal)
    assert(s.curr_part == s.num_parts - 1);
    toassign = s.remaining;
//    printf("assign remainder: %u\n", toassign);
  }
  else
  {
    double opt_toassign = (s.opt_bin_weight - bin->weight()) / partition->per_site_weight;
    toassign = (s.rest_over_weight > 0.) ? ceil(opt_toassign) : floor(opt_toassign);
    toassign = std::min(toassign, s.remaining);
//    printf("opt/cur_wgt/opt_add/add/qsize: %f / %f / %f / %u / %u\n",
//           s.opt_bin_weight, bin->weight(), opt_toassign, toassign, q.size());
//    printf("qsize h/l: %u / %u\n", s.qhigh_.size(), s.qlow_.size());
  }
  assert(toassign > 0 && toassign <= s.remaining);

  auto assigned = assign_sites(s, *bin, partition->part_id, partition->length - s.remaining,
                               toassign, partition->per_site_weight);
  s.remaining -= assigned;

  if (bin->weight() > s.opt_bin_weight)
    s.rest_over_weight -= bin->weight() - s.opt_bin_weight;
}

static void kassian_phase2(BalancerState& s)
{
  // Phase 2: Assign PARTIAL partitions in a cyclic manner to bins

  stack<PartitionAssignment *> * qlow = &s.qlow_; // hack to assign qhigh to qlow when qlow is empty
  stack<PartitionAssignment *> * qhigh = &s.qhigh_;

  s.remaining = s.sorted_partitions[s.curr_part]->length;
  while (s.curr_part < s.sorted_partitions.size() && (qlow->size() || qhigh->size()))
  {
    const PartitionRange *partition = s.sorted_partitions[s.curr_part];
    double remaining_weight = s.remaining * partition->per_site_weight;

    assert(s.remaining > 0);
    if (can_fill_bin(s, *qhigh, remaining_weight, partition->per_site_weight))
    {
      fill_bin(s, *qhigh);
    }
    else if (can_fill_bin(s, *qlow, remaining_weight, partition->per_site_weight))
    {
      fill_bin(s, *qlow);
    }
    else
    {
      // current partition can not fill a bin from qhigh/qlow,
      // so just assign ALL its remaining sites
      PartitionAssignment * bin = qlow->top();
      qlow->pop();
      auto assigned = assign_sites(s, *bin, partition->part_id, partition->length - s.remaining, s.remaining,
                   partition->per_site_weight);
      s.remaining -= assigned;

      if (bin->weight() < s.min_bin_weight)
      {
        qhigh->push(bin);
      }
    }

    if (qlow->empty())
      qlow = qhigh;

    if (!s.remaining)
    {
      s.curr_part++;
      if (s.curr_part < s.sorted_partitions.size())
        s.remaining = s.sorted_partitions[s.curr_part]->length;
    }
  }

  assert(s.remaining == 0);
  assert(s.curr_part == s.num_parts);
}

PartitionAssignmentList
BenoitLoadBalancer::compute_assignments(const PartitionAssignment& part_sizes,
                                                 size_t num_procs)
{
  BalancerState bs;
  init(bs, part_sizes, num_procs);

  kassian_phase1(bs);

  /* check whether all partitions have been assigned during phase 1 */
  if (bs.curr_part < bs.num_parts)
  {
    fill_queues(bs);
    kassian_phase2(bs);
  }

  return bs.bins;
}


#include <assert.h>
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
  {
    if (part_sizes.length() < num_procs)
    {
      throw LoadBalancerException("There are fewer alignment sites (" +
                                  to_string(part_sizes.length()) +
                                  ") than processes (" + to_string(num_procs) + ")!");
    }

    return compute_assignments(part_sizes, num_procs);
  }
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

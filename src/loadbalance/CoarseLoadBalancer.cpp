#include <stdexcept>

#include "CoarseLoadBalancer.hpp"

CoarseLoadBalancer::CoarseLoadBalancer ()
{
  // TODO Auto-generated constructor stub

}

CoarseLoadBalancer::~CoarseLoadBalancer ()
{
  // TODO Auto-generated destructor stub
}

CoarseAssignmentList CoarseLoadBalancer::get_all_assignments(const CoarseAssignment& search_ids,
                                                          size_t num_workers)
{
  if (num_workers == 1)
    return CoarseAssignmentList(1, search_ids);
  else
    return compute_assignments(search_ids, num_workers);
}

CoarseAssignment CoarseLoadBalancer::get_proc_assignments(const CoarseAssignment& search_ids,
                                                       size_t num_workers, size_t worker_id)
{
  if (worker_id >= num_workers)
    throw std::out_of_range("Worker ID out of range");

  if (num_workers == 1)
    return search_ids;
  else
    return compute_assignments(search_ids, num_workers).at(worker_id);
}


CoarseAssignmentList SimpleCoarseLoadBalancer::compute_assignments(const CoarseAssignment& search_ids,
                                                 size_t num_workers)
{
  CoarseAssignmentList search_assign(num_workers);

  auto wrk = search_assign.begin();

  for (auto id: search_ids)
  {
    wrk->push_back(id);

    wrk++;
    if (wrk == search_assign.end())
      wrk = search_assign.begin();
  }

  return search_assign;
}


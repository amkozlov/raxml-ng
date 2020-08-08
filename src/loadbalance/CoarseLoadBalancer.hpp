#ifndef RAXML_COARSELOADBALANCER_HPP_
#define RAXML_COARSELOADBALANCER_HPP_

#include <vector>

typedef std::vector<size_t> CoarseAssignment;
typedef std::vector<CoarseAssignment> CoarseAssignmentList;

class CoarseLoadBalancer
{
public:
  CoarseLoadBalancer ();
  virtual
  ~CoarseLoadBalancer ();

  CoarseAssignmentList get_all_assignments(const CoarseAssignment& search_ids,
                                              size_t num_workers);

  CoarseAssignment get_proc_assignments(const CoarseAssignment& search_ids,
                                           size_t num_workers, size_t worker_id);

protected:
  virtual CoarseAssignmentList compute_assignments(const CoarseAssignment& search_ids,
                                                   size_t num_workers) = 0;
};

/* Simple round-robin load balancer */
class SimpleCoarseLoadBalancer : public CoarseLoadBalancer
{
protected:
  virtual CoarseAssignmentList compute_assignments(const CoarseAssignment& search_ids,
                                                   size_t num_workers);
};


#endif /* RAXML_COARSELOADBALANCER_HPP_ */

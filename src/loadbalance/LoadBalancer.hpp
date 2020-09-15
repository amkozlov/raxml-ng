#ifndef RAXML_LOADBALANCER_HPP_
#define RAXML_LOADBALANCER_HPP_

#include "PartitionAssignment.hpp"
#include "../common.h"

class LoadBalancer
{
public:
  LoadBalancer ();
  virtual
  ~LoadBalancer ();

  PartitionAssignmentList get_all_assignments(const PartitionAssignment& part_sizes,
                                              size_t num_procs);

  PartitionAssignment get_proc_assignments(const PartitionAssignment& part_sizes,
                                           size_t num_procs, size_t proc_id);

protected:
  virtual PartitionAssignmentList compute_assignments(const PartitionAssignment& part_sizes,
                                                      size_t num_procs) = 0;
};

class SimpleLoadBalancer : public LoadBalancer
{
protected:
  virtual PartitionAssignmentList compute_assignments(const PartitionAssignment& part_sizes,
                                                      size_t num_procs);
};

class KassianLoadBalancer : public LoadBalancer
{
protected:
  virtual PartitionAssignmentList compute_assignments(const PartitionAssignment& part_sizes,
                                                      size_t num_procs);
};

class BenoitLoadBalancer : public LoadBalancer
{
protected:
  virtual PartitionAssignmentList compute_assignments(const PartitionAssignment& part_sizes,
                                                      size_t num_procs);
};

class LoadBalancerException : public RaxmlException
{
public:
  LoadBalancerException(const std::string& message) : RaxmlException(message) {}
};



#endif /* RAXML_LOADBALANCER_HPP_ */

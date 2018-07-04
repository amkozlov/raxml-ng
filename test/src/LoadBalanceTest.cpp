#include "RaxmlTest.hpp"

#include "src/loadbalance/LoadBalancer.hpp"

using namespace std;

static void check_common(const PartitionAssignment& part_sizes,
                         const PartitionAssignmentList& pa_list)
{
  size_t total_sites = 0;
  size_t assigned_sites = 0;
  double total_weight = 0.;
  double assigned_weight = 0.;
  for (auto& p: part_sizes)
  {
    total_sites += p.length;
    total_weight += p.weight();
  }

  for (auto& pa: pa_list)
  {
    for (auto& range: pa)
    {
      const auto pid = range.part_id;
      EXPECT_LT(pid, part_sizes.num_parts());

      const auto& part = part_sizes[pid];
      EXPECT_LE(range.length, part.length);
      EXPECT_GT(range.length, 0);
      EXPECT_LT(range.start, part.length);

      assigned_sites += range.length;
    }
    assigned_weight += pa.weight();
  }

  EXPECT_EQ(assigned_sites, total_sites);
  EXPECT_EQ(assigned_weight, total_weight);
}

static void check_assignment_kassian(const PartitionAssignment& part_sizes,
                                     size_t num_proc)
{
  KassianLoadBalancer lb;

  auto pa_list = lb.get_all_assignments(part_sizes, num_proc);
  EXPECT_EQ(pa_list.size(), num_proc);

  auto stats = PartitionAssignmentStats(pa_list);

//  std::cout << "threads: " << num_proc << ", " << stats << std::endl;

  check_common(part_sizes, pa_list);

  EXPECT_LE(stats.max_thread_parts - stats.min_thread_parts, 1);
  EXPECT_LE(stats.max_thread_sites - stats.min_thread_sites, 1);
}

static void check_assignment_benoit(const PartitionAssignment& part_sizes,
                                     size_t num_proc)
{
  BenoitLoadBalancer lb;

  double max_site_weight = 0.;
  for (auto const& range: part_sizes)
  {
    max_site_weight = std::max(max_site_weight, range.per_site_weight);
  }

  auto pa_list = lb.get_all_assignments(part_sizes, num_proc);
  EXPECT_EQ(pa_list.size(), num_proc);

  check_common(part_sizes, pa_list);

  auto stats = PartitionAssignmentStats(pa_list);
  auto opt_thread_weight = stats.total_weight / stats.num_cores;

//  std::cout << "threads: " << num_proc << ", " << stats << std::endl;

//  if (num_proc == 4 && part_sizes.num_parts() == 4)
//    std::cout << pa_list;

  EXPECT_GT(stats.min_thread_parts, 0);
  EXPECT_LE(stats.max_thread_parts - stats.min_thread_parts, 1);
  EXPECT_GT(stats.min_thread_sites, 0);
  EXPECT_GT(stats.min_thread_weight, 0.);
  EXPECT_LE(stats.max_thread_weight, opt_thread_weight + max_site_weight);
}


static void check_assignment_all(const PartitionAssignment& part_sizes,
                                     size_t num_proc)
{
  check_assignment_kassian(part_sizes, num_proc);
  check_assignment_benoit(part_sizes, num_proc);
}

TEST(LoadBalanceTest, testSMALL)
{
  // buildup
  PartitionAssignment part_sizes;

  part_sizes.assign_sites(0, 0, 159, 16);
  part_sizes.assign_sites(1, 0, 124, 16);
  part_sizes.assign_sites(2, 0, 168, 80);
  part_sizes.assign_sites(3, 0, 218, 20);

  // tests
  check_assignment_all(part_sizes, 4);
  check_assignment_all(part_sizes, 16);
  check_assignment_all(part_sizes, 32);
}


TEST(LoadBalanceTest, testSMALL2)
{
  // buildup
  PartitionAssignment part_sizes;

  part_sizes.assign_sites(0, 0, 170, 16);
  part_sizes.assign_sites(1, 0, 112, 16);
  part_sizes.assign_sites(2, 0, 171, 16);
  part_sizes.assign_sites(3, 0, 228, 16);

  // tests
  check_assignment_all(part_sizes, 4);
  check_assignment_all(part_sizes, 16);
  check_assignment_all(part_sizes, 32);
}

TEST(LoadBalanceTest, testLARGE)
{
  // buildup
  std::uniform_int_distribution<size_t> distr_sites(1, 1e5);
  std::uniform_int_distribution<size_t> distr_parts(5, 5000);
  std::uniform_int_distribution<size_t> distr_weights(2, 80);

  for (size_t r = 1; r <= 10; ++r)
  {
    std::mt19937 gen(r);
    PartitionAssignment part_sizes;
    auto pcount = distr_parts(gen);
    for (size_t i = 0; i < pcount; ++i)
    {
      const size_t psize = distr_sites(gen);
      const size_t pweight = distr_weights(gen);
      part_sizes.assign_sites(i, 0, psize, pweight);
    }

    // tests
    check_assignment_all(part_sizes, 2);
    check_assignment_all(part_sizes, 9);
    check_assignment_all(part_sizes, 16);
    check_assignment_all(part_sizes, 512);
    check_assignment_all(part_sizes, 1999);
  }
}

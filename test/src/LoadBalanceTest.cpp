#include "RaxmlTest.hpp"

#include "src/LoadBalancer.hpp"

using namespace std;

static void check_assignment_kassian(const PartitionAssignment& part_sizes,
                                     size_t num_proc)
{
  KassianLoadBalancer lb;

  auto pa_list = lb.get_all_assignments(part_sizes, num_proc);
  EXPECT_EQ(pa_list.size(), num_proc);

  auto stats = PartitionAssignmentStats(pa_list);
  EXPECT_LE(stats.max_thread_parts - stats.min_thread_parts, 1);
  EXPECT_LE(stats.max_thread_sites - stats.min_thread_sites, 1);

//  std::cout << "threads: " << num_proc << ", " << stats << std::endl;

  for (auto& pa: pa_list)
  {
    for (auto& range: pa)
    {
      const auto pid = range.part_id;
      EXPECT_LT(pid, part_sizes.num_parts());

      const auto& part = part_sizes[pid];
      EXPECT_LE(range.length, part.length);
      EXPECT_LT(range.start, part.length);
    }
  }
}

TEST(LoadBalanceTest, testSMALL)
{
  // buildup
  PartitionAssignment part_sizes;

  part_sizes.assign_sites(0, 0, 159);
  part_sizes.assign_sites(1, 0, 124);
  part_sizes.assign_sites(2, 0, 168);
  part_sizes.assign_sites(3, 0, 218);

  // tests
  check_assignment_kassian(part_sizes, 4);
  check_assignment_kassian(part_sizes, 16);
  check_assignment_kassian(part_sizes, 32);
}

TEST(LoadBalanceTest, testLARGE)
{
  // buildup
  std::uniform_int_distribution<size_t> distr_sites(1, 1e5);
  std::uniform_int_distribution<size_t> distr_parts(5, 5000);

  for (size_t r = 1; r <= 10; ++r)
  {
    std::mt19937 gen(r);
    PartitionAssignment part_sizes;
    auto pcount = distr_parts(gen);
    for (size_t i = 0; i < pcount; ++i)
    {
      const size_t psize = distr_sites(gen);
      part_sizes.assign_sites(i, 0, psize);
    }

    // tests
    check_assignment_kassian(part_sizes, 2);
    check_assignment_kassian(part_sizes, 9);
    check_assignment_kassian(part_sizes, 16);
    check_assignment_kassian(part_sizes, 512);
    check_assignment_kassian(part_sizes, 1999);
  }
}

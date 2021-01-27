#include "RaxmlTest.hpp"

#include "src/PartitionedMSAView.hpp"

using namespace std;

MSA simple_msa()
{
  MSA msa;

  msa.append("ATGGCATATCCCATACAACTAGGATTCCAAGATGCAACATCACCAATCATAGAAGAACTA", "t1");
  msa.append("ATGGCCAACCACTCCCAACTAGGCTTTCAAGACGCCTCATCCCCCATCATAGAAGAGCTC", "t2");
  msa.append("ATGGCACATGCAGCGCAAGTAGGTCTACAAGACGCTACTTCCCCTATCATAGAAGAGCTT", "t3");
  msa.append("ATGGCACATCCCACACAATTAGGATTCCAAGACGCGGCCTCACCCGTAATAGAAGAACTT", "t4");
  msa.append("ATGGCCTACCCATTCCAACTTGGTCTACAAGACGCCACATCCCCTATTATAGAAGAGCTA", "t5");

  EXPECT_EQ(5, msa.size());
  EXPECT_EQ(60, msa.length());

  return msa;
}

PartitionedMSA part_msa_p1(bool compress)
{
  PartitionedMSA pmsa;

  pmsa.emplace_part_info("p1", DataType::dna, "GTR");
  pmsa.full_msa(simple_msa());

  pmsa.split_msa();

  if (compress)
    pmsa.compress_patterns();

  EXPECT_EQ(1, pmsa.part_count());

  return pmsa;
}

PartitionedMSA part_msa_p3(bool compress)
{
  PartitionedMSA pmsa;

  pmsa.emplace_part_info("p1", DataType::dna, "GTR", "1-10");
  pmsa.emplace_part_info("p2", DataType::dna, "GTR", "11-45");
  pmsa.emplace_part_info("p3", DataType::dna, "GTR", "46-60");
  pmsa.full_msa(simple_msa());

  pmsa.split_msa();

  if (compress)
    pmsa.compress_patterns();

  EXPECT_EQ(3, pmsa.part_count());

  return pmsa;
}

void test_identity(const PartitionedMSA& pmsa, const PartitionedMSAView& vmsa)
{
  EXPECT_EQ(true, vmsa.identity());
  EXPECT_EQ(0, vmsa.excluded_site_count());
  EXPECT_EQ(pmsa.taxon_count(), vmsa.taxon_count());
  EXPECT_EQ(pmsa.part_count(), vmsa.part_count());
  EXPECT_EQ(pmsa.total_length(), vmsa.total_length());

  for (size_t t = 0; t < pmsa.taxon_count(); ++t)
    EXPECT_EQ(pmsa.taxon_names().at(t), vmsa.taxon_name(t));

  for (size_t p = 0; p < pmsa.part_count(); ++p)
  {
    auto& msa = pmsa.part_info(p).msa();
    EXPECT_EQ(msa.num_sites(),  vmsa.part_sites(p));

    for (size_t t = 0; t < pmsa.taxon_count(); ++t)
      EXPECT_EQ(msa.at(t), vmsa.part_sequence(t, p, false));
  }
}

void view_dummy_test(bool compress)
{
  auto pmsa = part_msa_p1(compress);
  PartitionedMSAView vmsa(pmsa);
  test_identity(pmsa, vmsa);

  auto pmsa2 = part_msa_p3(compress);
  PartitionedMSAView vmsa2(pmsa2);
  test_identity(pmsa2, vmsa2);
}

TEST(PartitionedMSAViewTest, view_dummy)
{
  view_dummy_test(false);
}

TEST(PartitionedMSAViewTest, view_dummy_patcomp)
{
  view_dummy_test(true);
}

void check_vmsa_part(PartitionedMSA& pmsa, PartitionedMSAView& vmsa, size_t p,
                     size_t num_ex, size_t weight_ex, FloatWeightVector weights = FloatWeightVector())
{
  auto& msa = pmsa.part_info(p).msa();
  size_t num_sites = weights.empty() ? msa.num_sites() :
                      std::accumulate(weights.begin(), weights.end(), 0);
  EXPECT_EQ(msa.length()-num_ex,  vmsa.part_length(p));
  EXPECT_EQ(num_sites-weight_ex,  vmsa.part_sites(p));

  for (size_t t = 0; t < vmsa.taxon_count(); ++t)
  {
    auto taxid = pmsa.taxon_id_map().empty() ? t :
                                              pmsa.taxon_id_map().at(vmsa.orig_taxon_name(t));
    string seq = msa.at(taxid);
    if (vmsa.excluded_site_count() > 0)
    {
      for (auto s = vmsa.exclude_sites(p).rbegin(); s != vmsa.exclude_sites(p).rend(); ++s)
        seq.erase(*s, 1);
    }
    EXPECT_STREQ(seq.c_str(), vmsa.part_sequence(t, p, false).c_str());

    stringstream ss;
    seq = msa.at(taxid);
    for (size_t s = 0; s < msa.length(); ++s)
    {
      if (vmsa.excluded_site_count() == 0 || vmsa.exclude_sites(p).count(s) == 0)
      {
        auto w = !weights.empty() ? weights.at(s) :
                   (!msa.weights().empty() ? msa.weights().at(s) : 1);
        for (size_t i = 0; i < w; ++i)
          ss << seq[s];
      }
    }
    EXPECT_STREQ(ss.str().c_str(), vmsa.part_sequence(t, p, true).c_str());
  }
}

void view_exclude_test_p1(bool compress)
{
  size_t num_ex = 0;
  size_t weight_ex = 0;

  auto pmsa = part_msa_p1(compress);
  PartitionedMSAView vmsa(pmsa);
  IDVector ex = {3, 5};
  vmsa.exclude_site(0, 0);
  num_ex += 1;
  vmsa.exclude_sites(0, ex);
  num_ex += ex.size();
  vmsa.exclude_taxon(3);
  vmsa.map_taxon_name("t2", "Mouse");

  if (compress)
  {
    auto w = pmsa.part_info(0).msa().weights();
    weight_ex += w[0];
    for (auto s: ex)
      weight_ex += w[s];
  }
  else
    weight_ex = num_ex;

  EXPECT_EQ(false, vmsa.identity());
  EXPECT_EQ(3, vmsa.excluded_site_count());
  EXPECT_EQ(pmsa.taxon_count()-1, vmsa.taxon_count());
  EXPECT_EQ(pmsa.part_count(), vmsa.part_count());
  EXPECT_EQ(pmsa.total_length()-num_ex, vmsa.total_length());
  EXPECT_EQ(pmsa.total_sites()-weight_ex, vmsa.total_sites());
  EXPECT_EQ("Mouse", vmsa.taxon_name(1));

  check_vmsa_part(pmsa, vmsa, 0, num_ex, weight_ex);
}

void view_exclude_test_p3(bool compress)
{
  auto pmsa = part_msa_p3(compress);
  PartitionedMSAView vmsa(pmsa);
  vector<size_t> weight_ex(3);
  vector<size_t> num_ex(3);

  vmsa.exclude_site(0, 0);
  vmsa.exclude_site(0, 2);
  num_ex[0] = 2;
  auto w = pmsa.part_info(0).msa().weights();
  weight_ex[0] = compress ? w[0] + w[2] : 2;

  vmsa.exclude_site(1, 5);
  num_ex[1] = 1;
  w = pmsa.part_info(1).msa().weights();
  weight_ex[1] = compress ? w[5] : 1;

  vmsa.exclude_site(2, 3);
  vmsa.exclude_site(2, 4);
  vmsa.exclude_site(2, 5);
  num_ex[2] = 3;
  w = pmsa.part_info(1).msa().weights();
  weight_ex[2] = compress ? w[3] + w[4] + w[5] : 3;

  size_t weight_ex_total = weight_ex[0] + weight_ex[1] + weight_ex[2];

  EXPECT_EQ(false, vmsa.identity());
  EXPECT_EQ(6, vmsa.excluded_site_count());
  EXPECT_EQ(pmsa.taxon_count(), vmsa.taxon_count());
  EXPECT_EQ(pmsa.part_count(), vmsa.part_count());
  EXPECT_EQ(pmsa.total_length()-6, vmsa.total_length());
  EXPECT_EQ(pmsa.total_sites()-weight_ex_total, vmsa.total_sites());

  for (size_t p = 0; p < vmsa.part_count(); ++p)
  {
    check_vmsa_part(pmsa, vmsa, p, num_ex[p], weight_ex[p]);
  }
}

void view_exclude_test(bool compress)
{
  view_exclude_test_p1(compress);
  view_exclude_test_p3(compress);
}


TEST(PartitionedMSAViewTest, view_exclude)
{
  view_exclude_test(false);
}

TEST(PartitionedMSAViewTest, view_exclude_patcomp)
{
  view_exclude_test(true);
}

void view_weight_test_p1(bool compress)
{
  auto pmsa = part_msa_p1(compress);
  PartitionedMSAView vmsa(pmsa);

  FloatWeightVector w(pmsa.part_info(0).msa().length(), 1);

  for (size_t s = 0; s < pmsa.part_info(0).msa().length(); ++s)
    w[s] = s % 5;

  vmsa.site_weights(0, w);

  auto total_sites = std::accumulate(w.begin(), w.end(), 0);

  EXPECT_EQ(false, vmsa.identity());
  EXPECT_EQ(0, vmsa.excluded_site_count());
  EXPECT_EQ(pmsa.taxon_count(), vmsa.taxon_count());
  EXPECT_EQ(pmsa.part_count(), vmsa.part_count());
  EXPECT_EQ(pmsa.total_length(), vmsa.total_length());
  EXPECT_EQ(total_sites, vmsa.total_sites());

  check_vmsa_part(pmsa, vmsa, 0, 0, 0, w);
}

void view_weight_test_p3(bool compress)
{
  auto pmsa = part_msa_p3(compress);
  PartitionedMSAView vmsa(pmsa);

  FloatWeightVectorList ww(3);

  auto total_sites = 0;

  for (size_t p = 0; p < vmsa.part_count(); ++p)
  {
    auto& w = ww[p];
    w = FloatWeightVector(pmsa.part_info(p).msa().length(), 1);

    for (size_t s = 0; s < w.size(); ++s)
      w[s] = s % 5;

    total_sites += std::accumulate(w.begin(), w.end(), 0);
  }

  vmsa.site_weights(ww);

  EXPECT_EQ(false, vmsa.identity());
  EXPECT_EQ(0, vmsa.excluded_site_count());
  EXPECT_EQ(pmsa.taxon_count(), vmsa.taxon_count());
  EXPECT_EQ(pmsa.part_count(), vmsa.part_count());
  EXPECT_EQ(pmsa.total_length(), vmsa.total_length());
  EXPECT_EQ(total_sites, vmsa.total_sites());

  for (size_t p = 0; p < vmsa.part_count(); ++p)
  {
    check_vmsa_part(pmsa, vmsa, p, 0, 0, ww[p]);
  }
}

void view_weight_test(bool compress)
{
  view_weight_test_p1(compress);
  view_weight_test_p3(compress);
}

TEST(PartitionedMSAViewTest, view_weight)
{
  view_weight_test(false);
}

TEST(PartitionedMSAViewTest, view_weight_patcomp)
{
  view_weight_test(true);
}

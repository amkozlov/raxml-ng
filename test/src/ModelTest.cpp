#include "RaxmlTest.hpp"

#include "src/Model.hpp"

using namespace std;

TEST(ModelTest, defaults)
{
  // buildup
  auto model = Model();

  // tests
  EXPECT_EQ(model.to_string(), "GTR+FO");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "GTR");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_FIXED);
  EXPECT_EQ(model.num_ratecats(), 1);
  EXPECT_EQ(model.params_to_optimize(), PLLMOD_OPT_PARAM_SUBST_RATES | PLLMOD_OPT_PARAM_FREQUENCIES);
}

TEST(ModelTest, GTR)
{
  // buildup
  auto model = Model(DataType::autodetect, "GTR+F+G");

  // tests
  EXPECT_EQ(model.to_string(), "GTR+F+G4");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "GTR");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), PLLMOD_OPT_PARAM_SUBST_RATES | PLLMOD_OPT_PARAM_ALPHA);
}

TEST(ModelTest, JCI_user)
{
  // buildup
  auto model = Model(DataType::autodetect, "JC+G+I{0.7}");

  // tests
  EXPECT_EQ(model.to_string(), "JC+I{0.7}+G4");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "JC");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), PLLMOD_OPT_PARAM_ALPHA);
  EXPECT_EQ(model.pinv(), 0.7);
}

TEST(ModelTest, LGFI)
{
  // buildup
  auto model = Model(DataType::autodetect, "LG+F+I+G8");

  // tests
  EXPECT_EQ(model.to_string(), "LG+F+I+G8");
  EXPECT_EQ(model.data_type(), DataType::protein);
  EXPECT_EQ(model.name(), "LG");
  EXPECT_EQ(model.num_states(), 20);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 8);
  EXPECT_EQ(model.params_to_optimize(), PLLMOD_OPT_PARAM_PINV | PLLMOD_OPT_PARAM_ALPHA);
}

TEST(ModelTest, LG4X)
{
  // buildup
  auto model = Model(DataType::autodetect, "LG4X");

  // tests
  EXPECT_EQ(model.to_string(), "LG4X+R4");
  EXPECT_EQ(model.data_type(), DataType::protein);
  EXPECT_EQ(model.name(), "LG4X");
  EXPECT_EQ(model.num_states(), 20);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_FREE);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), PLLMOD_OPT_PARAM_FREE_RATES | PLLMOD_OPT_PARAM_RATE_WEIGHTS);
}

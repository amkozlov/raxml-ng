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
  EXPECT_EQ(model.to_string(), "GTR+FC+G4m");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "GTR");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), PLLMOD_OPT_PARAM_SUBST_RATES | PLLMOD_OPT_PARAM_ALPHA);
}

TEST(ModelTest, GTR_R_user)
{
  // buildup
  auto model = Model(DataType::autodetect, "GTR{0.1/0.5/1/2/3.5/0.5}+R3+Fc");

  // tests
  EXPECT_EQ(model.to_string(), "GTR{0.2/1/2/4/7/1}+FC+R3");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "GTR");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_FREE);
  EXPECT_EQ(model.num_ratecats(), 3);
  EXPECT_EQ(model.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES), ParamValue::user);
  EXPECT_EQ(model.params_to_optimize(), PLLMOD_OPT_PARAM_RATE_WEIGHTS | PLLMOD_OPT_PARAM_FREE_RATES);
}


TEST(ModelTest, JCI_user)
{
  // buildup
  auto model = Model(DataType::autodetect, "JC+G+IU{0.7}");

  // tests
  EXPECT_EQ(model.to_string(), "JC+IU{0.7}+G4m");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "JC");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), PLLMOD_OPT_PARAM_ALPHA);
  EXPECT_EQ(model.pinv(), 0.7);
}

TEST(ModelTest, JCFG_user)
{
  // buildup
  auto model = Model(DataType::autodetect, "JC+FC+G{2.5}");

  // tests
  EXPECT_EQ(model.to_string(), "JC+FC+G4m{2.5}");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "JC");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES), ParamValue::empirical);
  EXPECT_EQ(model.param_mode(PLLMOD_OPT_PARAM_ALPHA), ParamValue::user);
  EXPECT_EQ(model.params_to_optimize(), 0);
  EXPECT_EQ(model.alpha(), 2.5);
}

TEST(ModelTest, HKY_user_freqs)
{
  // buildup
  auto model = Model(DataType::autodetect, "HKY+FU{0.1/0.299/0.201/0.4}");

  // tests
  EXPECT_EQ(model.to_string(), "HKY+FU{0.1/0.299/0.201/0.4}");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "HKY");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_FIXED);
  EXPECT_EQ(model.num_ratecats(), 1);
  EXPECT_EQ(model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES), ParamValue::user);
  EXPECT_EQ(model.params_to_optimize(), PLLMOD_OPT_PARAM_SUBST_RATES);
  EXPECT_EQ(model.base_freqs(0).size(), 4);
  EXPECT_EQ(model.base_freqs(0)[0], 0.1);
  EXPECT_EQ(model.base_freqs(0)[1], 0.299);
  EXPECT_EQ(model.base_freqs(0)[2], 0.201);
  EXPECT_EQ(model.base_freqs(0)[3], 0.4);
}

TEST(ModelTest, HKY_user_rates)
{
  // buildup
  auto model = Model(DataType::autodetect, "HKY{1/2.424}+FC");

  // tests
  EXPECT_EQ(model.to_string(), "HKY{1/2.424}+FC");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "HKY");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_FIXED);
  EXPECT_EQ(model.num_ratecats(), 1);
  EXPECT_EQ(model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES), ParamValue::empirical);
  EXPECT_EQ(model.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES), ParamValue::user);
  EXPECT_EQ(model.params_to_optimize(), 0);
  EXPECT_EQ(model.subst_rates(0).size(), 6);
  EXPECT_EQ(model.subst_rates(0)[0], 1.0);
  EXPECT_EQ(model.subst_rates(0)[1], 2.424);
  EXPECT_EQ(model.subst_rates(0)[2], 1.0);
  EXPECT_EQ(model.subst_rates(0)[3], 1.0);
  EXPECT_EQ(model.subst_rates(0)[4], 2.424);
  EXPECT_EQ(model.subst_rates(0)[5], 1.0);
}

TEST(ModelTest, LGFI)
{
  // buildup
  auto model = Model(DataType::autodetect, "LG+F+I+G8a");

  // tests
  EXPECT_EQ(model.to_string(), "LG+FC+I+G8a");
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

TEST(ModelTest, LG_R4_user)
{
  // buildup
  auto model = Model(DataType::autodetect, "LG+R4{1/2/3/4}");

  // tests
  EXPECT_EQ(model.to_string(), "LG+R4{0.4/0.8/1.2/1.6}{0.25/0.25/0.25/0.25}");
  EXPECT_EQ(model.data_type(), DataType::protein);
  EXPECT_EQ(model.name(), "LG");
  EXPECT_EQ(model.num_states(), 20);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_FREE);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), 0);
  EXPECT_EQ(model.param_mode(PLLMOD_OPT_PARAM_FREE_RATES), ParamValue::user);
  EXPECT_EQ(model.param_mode(PLLMOD_OPT_PARAM_RATE_WEIGHTS), ParamValue::user);
  EXPECT_EQ(model.ratecat_weights().size(), 4);
  EXPECT_EQ(model.ratecat_weights()[0], 1. / 4.);
  EXPECT_EQ(model.ratecat_weights()[1], 1. / 4.);
  EXPECT_EQ(model.ratecat_weights()[2], 1. / 4.);
  EXPECT_EQ(model.ratecat_weights()[3], 1. / 4.);
  EXPECT_EQ(model.ratecat_rates().size(), 4);
  EXPECT_EQ(model.ratecat_rates()[0], 0.4);
  EXPECT_EQ(model.ratecat_rates()[1], 0.8);
  EXPECT_EQ(model.ratecat_rates()[2], 1.2);
  EXPECT_EQ(model.ratecat_rates()[3], 1.6);
}

TEST(ModelTest, aliases)
{
  // buildup
  auto model = Model(DataType::autodetect, "TrNef+G");

  // tests
  EXPECT_EQ(model.to_string(), "TN93ef+G4m");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "TN93ef");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), PLLMOD_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), PLLMOD_OPT_PARAM_SUBST_RATES | PLLMOD_OPT_PARAM_ALPHA);

  model = Model(DataType::autodetect, "TrN");
  EXPECT_EQ(model.name(), "TN93");
  model = Model(DataType::autodetect, "TPM1");
  EXPECT_EQ(model.name(), "K81");
  model = Model(DataType::autodetect, "TPM1uf");
  EXPECT_EQ(model.name(), "K81uf");
}

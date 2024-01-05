#include "RaxmlTest.hpp"

#include "src/Model.hpp"

using namespace std;

string list_to_string(const NameList& list)
{
  string res = "";
  for (auto& s: list)
    res += s;

  return res;
}

template<typename T>
string map_to_string(const unordered_map<T, string>& map)
{
  string res = "";
  for (auto it: map)
    res += it.second;

  std::sort(res.begin(), res.end());

  return res;
}

TEST(ModelTest, defaults)
{
  // buildup
  auto model = Model();

  // tests
  EXPECT_EQ(model.to_string(), "GTR+FO");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "GTR");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_FIXED);
  EXPECT_EQ(model.num_ratecats(), 1);
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_SUBST_RATES | CORAX_OPT_PARAM_FREQUENCIES);
  EXPECT_EQ(model.num_free_params(), 8);
  EXPECT_EQ(list_to_string(model.state_names()), "ACGT");
  EXPECT_EQ(map_to_string(model.full_state_namemap()), "-ABCDGHKMRSTVWY");
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
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_SUBST_RATES | CORAX_OPT_PARAM_ALPHA);
  EXPECT_EQ(model.num_free_params(), 9);
}

TEST(ModelTest, GTR_R_user)
{
  // buildup
  auto model = Model(DataType::autodetect, "GTR{0.1/0.5/1/2/3.5/0.5}+R3+Fc");

  // tests
  EXPECT_EQ(model.to_string(), "GTR{0.2/1/2/4/7/1}+FC+R3");
  EXPECT_EQ(model.to_string(false, 2), "GTR{0.20/1.00/2.00/4.00/7.00/1.00}+FC+R3");
  EXPECT_EQ(model.to_string(true, 3),
            "GTR{0.200/1.000/2.000/4.000/7.000/1.000}+FC+R3{0.189/0.712/2.099}{0.333/0.333/0.333}");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "GTR");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_FREE);
  EXPECT_EQ(model.num_ratecats(), 3);
  EXPECT_EQ(model.param_mode(CORAX_OPT_PARAM_SUBST_RATES), ParamValue::user);
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_RATE_WEIGHTS | CORAX_OPT_PARAM_FREE_RATES);
  EXPECT_EQ(model.num_free_params(), 7);
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
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_ALPHA);
  EXPECT_EQ(model.pinv(), 0.7);
  EXPECT_EQ(model.num_free_params(), 1);
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
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.param_mode(CORAX_OPT_PARAM_FREQUENCIES), ParamValue::empirical);
  EXPECT_EQ(model.param_mode(CORAX_OPT_PARAM_ALPHA), ParamValue::user);
  EXPECT_EQ(model.params_to_optimize(), 0);
  EXPECT_EQ(model.alpha(), 2.5);
  EXPECT_EQ(model.num_free_params(), 3);
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
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_FIXED);
  EXPECT_EQ(model.num_ratecats(), 1);
  EXPECT_EQ(model.param_mode(CORAX_OPT_PARAM_FREQUENCIES), ParamValue::user);
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_SUBST_RATES);
  EXPECT_EQ(model.base_freqs(0).size(), 4);
  EXPECT_EQ(model.base_freqs(0)[0], 0.1);
  EXPECT_EQ(model.base_freqs(0)[1], 0.299);
  EXPECT_EQ(model.base_freqs(0)[2], 0.201);
  EXPECT_EQ(model.base_freqs(0)[3], 0.4);
  EXPECT_EQ(model.num_free_params(), 1);
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
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_FIXED);
  EXPECT_EQ(model.num_ratecats(), 1);
  EXPECT_EQ(model.param_mode(CORAX_OPT_PARAM_FREQUENCIES), ParamValue::empirical);
  EXPECT_EQ(model.param_mode(CORAX_OPT_PARAM_SUBST_RATES), ParamValue::user);
  EXPECT_EQ(model.params_to_optimize(), 0);
  EXPECT_EQ(model.subst_rates(0).size(), 6);
  EXPECT_EQ(model.subst_rates(0)[0], 1.0);
  EXPECT_EQ(model.subst_rates(0)[1], 2.424);
  EXPECT_EQ(model.subst_rates(0)[2], 1.0);
  EXPECT_EQ(model.subst_rates(0)[3], 1.0);
  EXPECT_EQ(model.subst_rates(0)[4], 2.424);
  EXPECT_EQ(model.subst_rates(0)[5], 1.0);
  EXPECT_EQ(model.num_free_params(), 3);
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
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 8);
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_PINV | CORAX_OPT_PARAM_ALPHA);
  EXPECT_EQ(list_to_string(model.state_names()), "ARNDCQEGHILKMFPSTWYV");
  EXPECT_EQ(map_to_string(model.full_state_namemap()), "*ABCDEFGHIJKLMNPQRSTVWYZ");
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
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_FREE);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_FREE_RATES | CORAX_OPT_PARAM_RATE_WEIGHTS);
  EXPECT_EQ(model.num_free_params(), 6);
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
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_FREE);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), 0);
  EXPECT_EQ(model.param_mode(CORAX_OPT_PARAM_FREE_RATES), ParamValue::user);
  EXPECT_EQ(model.param_mode(CORAX_OPT_PARAM_RATE_WEIGHTS), ParamValue::user);
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
  EXPECT_EQ(model.num_free_params(), 0);
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
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_SUBST_RATES | CORAX_OPT_PARAM_ALPHA);
  EXPECT_EQ(model.num_free_params(), 3);

  model = Model(DataType::autodetect, "TrN");
  EXPECT_EQ(model.name(), "TN93");
  EXPECT_EQ(model.num_free_params(), 5);
  model = Model(DataType::autodetect, "TPM1+FE");
  EXPECT_EQ(model.name(), "K81");
  EXPECT_EQ(model.num_free_params(), 2);
  model = Model(DataType::autodetect, "TPM1uf");
  EXPECT_EQ(model.name(), "K81uf");
  EXPECT_EQ(model.num_free_params(), 5);
}

TEST(ModelTest, multistate)
{
  // buildup
  auto model = Model(DataType::autodetect, "MULTI8_MK+G");

  // tests
  EXPECT_EQ("MULTI8_MK+G4m", model.to_string());
  EXPECT_EQ(DataType::multistate, model.data_type());
  EXPECT_EQ("MULTI8_MK", model.name());
  EXPECT_EQ(8, model.num_states());
  EXPECT_EQ(CORAX_UTIL_MIXTYPE_GAMMA, model.ratehet_mode());
  EXPECT_EQ(4, model.num_ratecats());
  EXPECT_EQ(CORAX_OPT_PARAM_ALPHA, model.params_to_optimize());
  EXPECT_NE(nullptr, model.charmap());
  EXPECT_EQ(model.num_free_params(), 1);
  EXPECT_EQ(list_to_string(model.state_names()), "01234567");

  model = Model(DataType::autodetect, "MULTI53_GTR");
  EXPECT_EQ(DataType::multistate, model.data_type());
  EXPECT_EQ(53, model.num_states());
  EXPECT_EQ(CORAX_OPT_PARAM_SUBST_RATES | CORAX_OPT_PARAM_FREQUENCIES,
            model.params_to_optimize());
  EXPECT_EQ(model.num_free_params(), (53*(53-1) / 2 - 1) + (53-1));
  EXPECT_EQ(list_to_string(model.state_names()), "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,/:;<=");
}

TEST(ModelTest, multistate_custom)
{
  // buildup
  auto model = Model(DataType::autodetect, "MULTI6_GTR+M{AbCDef}{X-?}");

  // tests
  EXPECT_EQ("MULTI6_GTR+FO+M{AbCDef}{X-?}", model.to_string());
  EXPECT_EQ(DataType::multistate, model.data_type());
  EXPECT_EQ("MULTI6_GTR", model.name());
  EXPECT_EQ(6, model.num_states());
  EXPECT_EQ(CORAX_UTIL_MIXTYPE_FIXED, model.ratehet_mode());
  EXPECT_EQ(1, model.num_ratecats());
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_SUBST_RATES | CORAX_OPT_PARAM_FREQUENCIES);
  EXPECT_NE(nullptr, model.charmap());
  EXPECT_EQ(model.num_free_params(), 19);
  EXPECT_EQ(list_to_string(model.state_names()), "AbCDef");
  EXPECT_EQ(map_to_string(model.full_state_namemap()), "-ACDbef");

  model = Model(DataType::autodetect, "MULTI5_MK+Mi{AbCdF}+F+G+I");
  EXPECT_EQ("MULTI5_MK+FC+I+G4m+Mi{AbCdF}", model.to_string());
  EXPECT_EQ(DataType::multistate, model.data_type());
  EXPECT_EQ("MULTI5_MK", model.name());
  EXPECT_EQ(5, model.num_states());
  EXPECT_EQ(CORAX_UTIL_MIXTYPE_GAMMA, model.ratehet_mode());
  EXPECT_EQ(4, model.num_ratecats());
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_ALPHA | CORAX_OPT_PARAM_PINV);
  EXPECT_NE(nullptr, model.charmap());
  EXPECT_EQ(6, model.num_free_params());
  EXPECT_EQ(list_to_string(model.state_names()), "ABCDF");
  EXPECT_EQ(map_to_string(model.full_state_namemap()), "ABCDF");
}

TEST(ModelTest, genotype)
{
  // buildup
  auto model = Model(DataType::autodetect, "GT10");

  // tests
  EXPECT_EQ("GT10+FO", model.to_string());
  EXPECT_EQ(DataType::genotype10, model.data_type());
  EXPECT_EQ("GT10", model.name());
  EXPECT_EQ(10, model.num_states());
  EXPECT_EQ(CORAX_UTIL_MIXTYPE_FIXED, model.ratehet_mode());
  EXPECT_EQ(1, model.num_ratecats());
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_SUBST_RATES | CORAX_OPT_PARAM_FREQUENCIES);
  EXPECT_NE(nullptr, model.charmap());
  EXPECT_EQ(model.num_free_params(), 15);
  EXPECT_EQ(list_to_string(model.state_names()), "ACGTMRWSYK");
  EXPECT_EQ(map_to_string(model.full_state_namemap()), "-ACGKMRSTWY");
}


TEST(ModelTest, DNA_usersym)
{
  // buildup
  auto model = Model(DataType::autodetect, "DNA001122");

  // tests
  EXPECT_EQ(model.to_string(), "DNA001122+FO");
  EXPECT_EQ(model.data_type(), DataType::dna);
  EXPECT_EQ(model.name(), "DNA001122");
  EXPECT_EQ(model.num_states(), 4);
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_FIXED);
  EXPECT_EQ(model.num_ratecats(), 1);
  EXPECT_EQ(model.param_mode(CORAX_OPT_PARAM_SUBST_RATES), ParamValue::ML);
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_SUBST_RATES | CORAX_OPT_PARAM_FREQUENCIES);
  EXPECT_EQ(model.num_free_params(), 5);
}

TEST(ModelTest, multistate_usersym)
{
  // buildup
  auto model = Model(DataType::autodetect, "MULTI5_USER1234561231+FC+G");

  // tests
  EXPECT_EQ(model.to_string(), "MULTI5_USER1234561231+FC+G4m");
  EXPECT_EQ(model.data_type(), DataType::multistate);
  EXPECT_EQ(model.name(), "MULTI5_USER1234561231");
  EXPECT_EQ(model.num_states(), 5);
  EXPECT_EQ(model.ratehet_mode(), CORAX_UTIL_MIXTYPE_GAMMA);
  EXPECT_EQ(model.num_ratecats(), 4);
  EXPECT_EQ(model.param_mode(CORAX_OPT_PARAM_SUBST_RATES), ParamValue::ML);
  EXPECT_EQ(model.params_to_optimize(), CORAX_OPT_PARAM_SUBST_RATES | CORAX_OPT_PARAM_ALPHA);
  EXPECT_EQ(model.num_free_params(), 10);
}


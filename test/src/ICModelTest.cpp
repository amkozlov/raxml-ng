#include "RaxmlTest.hpp"
#include <gmock/gmock.h>
#include <src/modeltest/FreerateHeuristic.hpp>
#include <src/modeltest/ModelDefinitions.hpp>

#include <src/modeltest/ModelTest.hpp>
#include <src/modeltest/RHASHeuristic.hpp>

TEST(ICModelTest, ModelNameNormalization) {
    /*
    EXPECT_EQ(normalize_model_name("F81+FE+COMPLICATED_MIXTURE_MODEL"), "JC+COMPLICATED_MIXTURE_MODEL");
    EXPECT_EQ(normalize_model_name("GTR+FE+I+G4m"), "SYM+I+G4m");

    auto candidates = generate_candidate_model_names(DataType::dna);
    ASSERT_THAT(candidates, testing::Contains("SYM+I+G4"));
    */
}

TEST(ICModelTest, RHASHeuristic) {
    RHASHeuristic h(substitution_model_t("GTR", frequency_type_t::ESTIMATED), 10.0);

    using C = candidate_model_t;
    const auto gtr = C(DataType::dna, "GTR", frequency_type_t::ESTIMATED, rate_heterogeneity_type::UNIFORM, 1);
    const auto gtr_i = C(DataType::dna, "GTR", frequency_type_t::ESTIMATED, rate_heterogeneity_type::INVARIANT, 1);
    const auto gtr_g4 = C(DataType::dna, "GTR", frequency_type_t::ESTIMATED, rate_heterogeneity_type::GAMMA, 4);
    const auto gtr_ig4 = C(DataType::dna, "GTR", frequency_type_t::ESTIMATED, rate_heterogeneity_type::INVARIANT_GAMMA,
                           4);
    const auto gtr_r4 = C(DataType::dna, "GTR", frequency_type_t::ESTIMATED, rate_heterogeneity_type::FREE_RATE, 4);
    const auto gtr_r5 = C(DataType::dna, "GTR", frequency_type_t::ESTIMATED, rate_heterogeneity_type::FREE_RATE, 5);

    const auto jc = C(DataType::dna, "JC", frequency_type_t::FIXED, rate_heterogeneity_type::UNIFORM, 1);
    const auto jc_i = C(DataType::dna, "JC", frequency_type_t::FIXED, rate_heterogeneity_type::INVARIANT, 1);
    const auto jc_g4 = C(DataType::dna, "JC", frequency_type_t::FIXED, rate_heterogeneity_type::GAMMA, 4);
    const auto jc_ig4 = C(DataType::dna, "JC", frequency_type_t::FIXED, rate_heterogeneity_type::INVARIANT_GAMMA, 4);
    const auto jc_r4 = C(DataType::dna, "JC", frequency_type_t::FIXED, rate_heterogeneity_type::FREE_RATE, 4);
    const auto jc_r5 = C(DataType::dna, "JC", frequency_type_t::FIXED, rate_heterogeneity_type::FREE_RATE, 5);

    h.update(gtr, 130.0);
    h.update(gtr_i, 125.0);
    h.update(gtr_g4, 105.0);
    h.update(gtr_ig4, 103.0);
    h.update(gtr_r4, 100.0);
    h.update(gtr_r5, 110.2);
    EXPECT_FALSE(h.can_skip(gtr));
    EXPECT_FALSE(h.can_skip(gtr_i));
    h.reference_complete();

    EXPECT_TRUE(h.can_skip(jc));
    EXPECT_TRUE(h.can_skip(jc_i));
    EXPECT_FALSE(h.can_skip(jc_g4));
    EXPECT_FALSE(h.can_skip(jc_ig4));
    EXPECT_FALSE(h.can_skip(jc_r4));
    EXPECT_TRUE(h.can_skip(jc_r5));

    h.clear();
    EXPECT_FALSE(h.can_skip(jc));
    EXPECT_FALSE(h.can_skip(gtr));
}

TEST(ICModelTest, FreerateHeuristic) {
    auto FreeRateModel = [](const auto matrix_name, unsigned int cat_count, frequency_type_t freq_type = frequency_type_t::ESTIMATED) {
        return candidate_model_t(DataType::dna, matrix_name, freq_type,
                                 rate_heterogeneity_type::FREE_RATE, cat_count);
    };

    FreerateHeuristic h(4, 8);

    auto gtr_r4 = FreeRateModel("GTR", 4);
    auto gtr_r5 = FreeRateModel("GTR", 5);
    auto gtr_r6 = FreeRateModel("GTR", 6);
    auto gtr_r7 = FreeRateModel("GTR", 7);
    auto gtr_r8 = FreeRateModel("GTR", 8);
    auto gtr_r9 = FreeRateModel("GTR", 9);
    auto gtr_r10 = FreeRateModel("GTR", 10);

    auto jc_r8 = FreeRateModel("JC", 8);
    auto gtr_r8_fe = FreeRateModel("GTR", 8, frequency_type_t::FIXED);


    EXPECT_FALSE(h.can_skip(gtr_r4));
    h.update(gtr_r4, 33.0);
    EXPECT_FALSE(h.can_skip(gtr_r5));

    h.update(gtr_r5, 32.0); // score decreased
    EXPECT_FALSE(h.can_skip(gtr_r6));

    h.update(gtr_r6, 35.0); // score higher than before
    EXPECT_TRUE(h.can_skip(gtr_r7));
    EXPECT_FALSE(h.can_skip(FreeRateModel("JC", 7)));

    h.clear();
    EXPECT_FALSE(h.can_skip(gtr_r7));

    // Add values out of order
    h.update(gtr_r6, 200.0);
    EXPECT_FALSE(h.can_skip(gtr_r4));
    EXPECT_FALSE(h.can_skip(gtr_r5));
    EXPECT_FALSE(h.can_skip(gtr_r7));
    EXPECT_FALSE(h.can_skip(gtr_r8));

    h.update(gtr_r7, 210.0);
    EXPECT_FALSE(h.can_skip(gtr_r4));
    EXPECT_FALSE(h.can_skip(gtr_r5));
    EXPECT_TRUE(h.can_skip(gtr_r8));
    EXPECT_TRUE(h.can_skip(gtr_r9));
    EXPECT_TRUE(h.can_skip(gtr_r10));

    // Heuristic should not work across model matrices or frequency types
    EXPECT_FALSE(h.can_skip(jc_r8));
    EXPECT_FALSE(h.can_skip(gtr_r8_fe));

    // only freerate models should influence the heuristic
    auto gtr_g5 = candidate_model_t(DataType::dna, "GTR", frequency_type_t::FIXED, rate_heterogeneity_type::GAMMA, 5);
    h.clear();
    h.update(gtr_r4, -20.0);
    h.update(gtr_g5, 34.0);
    EXPECT_FALSE(h.can_skip(gtr_g5));
    EXPECT_FALSE(h.can_skip(gtr_r6));
    h.update(gtr_r5, -10);
    EXPECT_TRUE(h.can_skip(gtr_r7));
    EXPECT_TRUE(h.can_skip(gtr_r8));
}

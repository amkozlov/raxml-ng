#include "RaxmlTest.hpp"
#include "src/modeltest/Heuristics.hpp"
#include "src/types.hpp"
#include <gmock/gmock.h>
#include <src/modeltest/FreerateHeuristic.hpp>
#include <src/modeltest/ModelDefinitions.hpp>

#include <src/modeltest/ModelTest.hpp>
#include <src/modeltest/RHASHeuristic.hpp>
#include <regex>

candidate_model_t C(const std::string &s) {
    const static std::regex exp(R"(^([^+]+)(\+F|)(|\+E|\+I|\+G|\+I\+G|\+R)(\d+|)$)");
    std::smatch m;
    assert(std::regex_match(s, m, exp));

    const std::string matrix_name = m[1];
    const frequency_type_t freq = m[2].length() == 0 ? frequency_type_t::FIXED : frequency_type_t::ESTIMATED;
    rate_heterogeneity_type rhas_type;

    if (m[3] == "" || m[3] == "+E") {
        rhas_type = rate_heterogeneity_type::UNIFORM;
    } else if (m[3] == "+I") {
        rhas_type = rate_heterogeneity_type::INVARIANT;
    } else if (m[3] == "+I+G") {
        rhas_type = rate_heterogeneity_type::INVARIANT_GAMMA;
    } else if (m[3] == "+G") {
        rhas_type = rate_heterogeneity_type::GAMMA;
    } else if (m[3] == "+R") {
        rhas_type = rate_heterogeneity_type::FREE_RATE;
    } else {
        assert(0);
    }

    const unsigned int category_count = m[4] == "" ? 1 : std::stoi(m[4]);

    return candidate_model_t(DataType::dna, matrix_name, freq, rhas_type, category_count);
}

TEST(ICModelTest, StringParser) {
    EXPECT_EQ(C("TIM2+I"), candidate_model_t(DataType::dna, "TIM2", frequency_type_t::FIXED, rate_heterogeneity_type::INVARIANT));
    EXPECT_EQ(C("GTR+F+I+G99"), candidate_model_t(DataType::dna, "GTR", frequency_type_t::ESTIMATED, rate_heterogeneity_type::INVARIANT_GAMMA, 99));
}

TEST(ICModelTest, ModelNameNormalization) {
    /*
    EXPECT_EQ(normalize_model_name("F81+FE+COMPLICATED_MIXTURE_MODEL"), "JC+COMPLICATED_MIXTURE_MODEL");
    EXPECT_EQ(normalize_model_name("GTR+FE+I+G4m"), "SYM+I+G4m");

    auto candidates = generate_candidate_model_names(DataType::dna);
    ASSERT_THAT(candidates, testing::Contains("SYM+I+G4"));
    */
}

TEST(ICModelTest, RHASHeuristic) {
    RHASHeuristic h(substitution_model_t("GTR", frequency_type_t::ESTIMATED),
                    {
                    rate_heterogeneity_t(rate_heterogeneity_type::UNIFORM, 1),
                    rate_heterogeneity_t(rate_heterogeneity_type::INVARIANT, 1),
                    rate_heterogeneity_t(rate_heterogeneity_type::INVARIANT_GAMMA, 1),
                    rate_heterogeneity_t(rate_heterogeneity_type::GAMMA, 4),
                    rate_heterogeneity_t(rate_heterogeneity_type::FREE_RATE, 4),
                    rate_heterogeneity_t(rate_heterogeneity_type::FREE_RATE, 5)
                    }, 10.0);

    h.update(C("GTR+F"), 130.0);
    h.update(C("GTR+F+I"), 125.0);
    h.update(C("GTR+F+G4"), 105.0);
    h.update(C("GTR+F+I+G4"), 103.0);
    h.update(C("GTR+F+R4"), 100.0);

    EXPECT_FALSE(h.can_skip(C("GTR+F")));
    EXPECT_FALSE(h.can_skip(C("GTR+F+I")));
    h.update(C("GTR+F+R5"), 110.2); // Only now all candidates have been seen

    EXPECT_TRUE(h.can_skip(C("JC")));
    EXPECT_TRUE(h.can_skip(C("JC+I")));
    EXPECT_FALSE(h.can_skip(C("JC+G4")));
    EXPECT_FALSE(h.can_skip(C("JC+I+G4")));
    EXPECT_FALSE(h.can_skip(C("JC+R4")));
    EXPECT_TRUE(h.can_skip(C("JC+R5")));
}

TEST(ICModelTest, FreerateHeuristic) {
    FreerateHeuristic h(4, 8);

    EXPECT_FALSE(h.can_skip(C("GTR+F+R4")));
    h.update(C("GTR+F+R4"), 33.0);
    EXPECT_FALSE(h.can_skip(C("GTR+F+R5")));

    h.update(C("GTR+F+R5"), 32.0); // score decreased
    EXPECT_FALSE(h.can_skip(C("GTR+F+R6")));

    h.update(C("GTR+F+R6"), 35.0); // score higher than before
    EXPECT_TRUE(h.can_skip(C("GTR+F+R7")));
    EXPECT_FALSE(h.can_skip(C("JC+R7")));

    h.clear();
    EXPECT_FALSE(h.can_skip(C("GTR+F+R7")));

    // Add values out of order
    h.update(C("GTR+F+R6"), 200.0);
    EXPECT_FALSE(h.can_skip(C("GTR+F+R4")));
    EXPECT_FALSE(h.can_skip(C("GTR+F+R5")));
    EXPECT_FALSE(h.can_skip(C("GTR+F+R7")));
    EXPECT_FALSE(h.can_skip(C("GTR+F+R8")));

    h.update(C("GTR+F+R7"), 210.0);
    EXPECT_FALSE(h.can_skip(C("GTR+F+R4")));
    EXPECT_FALSE(h.can_skip(C("GTR+F+R5")));
    EXPECT_TRUE(h.can_skip(C("GTR+F+R8")));
    EXPECT_TRUE(h.can_skip(C("GTR+F+R9")));
    EXPECT_TRUE(h.can_skip(C("GTR+F+R10")));

    // Heuristic should not work across model matrices or frequency types
    EXPECT_FALSE(h.can_skip(C("JC+R8")));
    EXPECT_FALSE(h.can_skip(C("GTR+R8")));

    // only freerate models should influence the heuristic
    h.clear();
    h.update(C("GTR+F+R4"), -20.0);
    h.update(C("GTR+F+G5"), 34.0);
    EXPECT_FALSE(h.can_skip(C("GTR+F+G5")));
    EXPECT_FALSE(h.can_skip(C("GTR+F+R6")));
    h.update(C("GTR+F+R5"), -10);
    EXPECT_TRUE(h.can_skip(C("GTR+F+R7")));
    EXPECT_TRUE(h.can_skip(C("GTR+F+R8")));
}

TEST(ICModelTest, RHASFreerateHeuristicCombined) {
    RHASHeuristic h(substitution_model_t("GTR", frequency_type_t::ESTIMATED),
                    {
                    rate_heterogeneity_t(rate_heterogeneity_type::UNIFORM, 1),
                    rate_heterogeneity_t(rate_heterogeneity_type::INVARIANT, 1),
                    rate_heterogeneity_t(rate_heterogeneity_type::GAMMA, 4),
                    rate_heterogeneity_t(rate_heterogeneity_type::INVARIANT_GAMMA, 4),
                    rate_heterogeneity_t(rate_heterogeneity_type::FREE_RATE, 4),
                    rate_heterogeneity_t(rate_heterogeneity_type::FREE_RATE, 5),
                    rate_heterogeneity_t(rate_heterogeneity_type::FREE_RATE, 6),
                    rate_heterogeneity_t(rate_heterogeneity_type::FREE_RATE, 7)
                    }, 10.0);

    h.update(C("GTR+F"), 130.0);
    h.update(C("GTR+F+I"), 125.0);
    h.update(C("GTR+F+G4"), 105.0);
    h.update(C("GTR+F+I+G4"), 103.0);
    h.update(C("GTR+F+R4"), 100.0);

    EXPECT_FALSE(h.can_skip(C("JC+R5")));
    EXPECT_FALSE(h.can_skip(C("GTR+F+R5")));

    h.update(C("GTR+F+R5"), 110.2); // score increased
    h.freerate_complete(4);
    EXPECT_TRUE(h.can_skip(C("JC")));
    EXPECT_TRUE(h.can_skip(C("JC+I")));
    EXPECT_FALSE(h.can_skip(C("JC+G4")));
    EXPECT_FALSE(h.can_skip(C("JC+I+G4")));
    EXPECT_FALSE(h.can_skip(C("JC+R4")));
    EXPECT_TRUE(h.can_skip(C("JC+R5")));
    EXPECT_TRUE(h.can_skip(C("HKY+F+R5")));
}

TEST(ICModelTest, RHASFreerateOptimum) {
    Heuristics h(1, {HeuristicType::FREERATE, HeuristicType::RHAS}, {
                    rate_heterogeneity_t(rate_heterogeneity_type::UNIFORM, 1),
                    rate_heterogeneity_t(rate_heterogeneity_type::FREE_RATE, 4),
                    rate_heterogeneity_t(rate_heterogeneity_type::FREE_RATE, 5),
                    rate_heterogeneity_t(rate_heterogeneity_type::FREE_RATE, 6),
                    },
                    substitution_model_t("GTR", frequency_type_t::ESTIMATED), 4, 6);

    h.update(0, C("GTR+F"), 430.0);

    // All have ΔBIC < 10, but only the optimal one should be selected
    h.update(0, C("GTR+F+R4"), 208.0);
    h.update(0, C("GTR+F+R6"), 206.0);
    h.update(0, C("GTR+F+R5"), 201.0);

    EXPECT_FALSE(h.can_skip(0, C("JC+R5")));
    EXPECT_TRUE(h.can_skip(0, C("JC+R4")));
    EXPECT_TRUE(h.can_skip(0, C("JC+R6")));
    EXPECT_TRUE(h.can_skip(0, C("JC+R6")));
    EXPECT_TRUE(h.can_skip(0, C("JC")));



}

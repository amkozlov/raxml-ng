#include "RaxmlTest.hpp"
#include "src/modeltest/Heuristics.hpp"
#include "src/types.hpp"
#include <gmock/gmock.h>
#include <src/modeltest/FreerateHeuristic.hpp>
#include <src/modeltest/ModelDefinitions.hpp>

#include <src/modeltest/ModelTest.hpp>
#include <src/modeltest/RHASHeuristic.hpp>
#include <regex>

ModelDescriptor C(const std::string &s, const DataType datatype = DataType::dna) {
    const static std::regex exp(R"(^([^+]+)(\+FC?|\+FO|)(|\+E|\+I|\+G|\+I\+G|\+R|\+I\+R)(\d+|)$)");
    std::smatch m;
    assert(std::regex_match(s, m, exp));

    const std::string matrix_name = m[1];
    const BaseFrequencyType freq = m[2].length() == 0 ? BaseFrequencyType::FIXED : BaseFrequencyType::ESTIMATED;
    RateHeterogeneityType rhas_type;

    if (m[3] == "" || m[3] == "+E") {
        rhas_type = RateHeterogeneityType::UNIFORM;
    } else if (m[3] == "+I") {
        rhas_type = RateHeterogeneityType::INVARIANT;
    } else if (m[3] == "+I+G") {
        rhas_type = RateHeterogeneityType::INVARIANT_GAMMA;
    } else if (m[3] == "+G") {
        rhas_type = RateHeterogeneityType::GAMMA;
    } else if (m[3] == "+R") {
        rhas_type = RateHeterogeneityType::FREE_RATE;
    } else if (m[3] == "+I+R") {
        rhas_type = RateHeterogeneityType::INVARIANT_FREE_RATE;
    } else {
        assert(0);
    }

    const unsigned int category_count = m[4] == "" ? 1 : std::stoi(m[4]);

    return ModelDescriptor(datatype, matrix_name, freq, rhas_type, category_count);
}

ModelDescriptor Cp(const std::string &s) {
    return C(s, DataType::protein);
}

void EXPECT_SKIP(Heuristics &h, unsigned int partition,
                      std::vector<ModelDescriptor> can_skip,
                      std::vector<ModelDescriptor> no_skip_possible)
{
    for (const auto &c : can_skip) {
        EXPECT_TRUE(h.can_skip(partition, c)) << "Expected to skip " << c.descriptor() << endl;
    }

    for (const auto &c : no_skip_possible) {
        EXPECT_FALSE(h.can_skip(partition, c)) << "Unexpected skip for " << c.descriptor() << endl;
    }
}


TEST(ICModelTest, StringParser) {
    EXPECT_EQ(C("TIM2+I"), ModelDescriptor(DataType::dna, "TIM2", BaseFrequencyType::FIXED, RateHeterogeneityType::INVARIANT));
    EXPECT_EQ(C("GTR+F+I+G99"), ModelDescriptor(DataType::dna, "GTR", BaseFrequencyType::ESTIMATED, RateHeterogeneityType::INVARIANT_GAMMA, 99));
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
    RHASHeuristic h(SubstitutionModelDescriptor("GTR", BaseFrequencyType::ESTIMATED),
                    {
                    RateHeterogeneityDescriptor(RateHeterogeneityType::UNIFORM, 1),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::INVARIANT, 1),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::INVARIANT_GAMMA, 1),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::GAMMA, 4),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 4),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 5)
                    }, 10.0, RHASHeuristicMode::AllSignficantCategoryCounts);

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
    const auto reference= C("GTR+F");
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

TEST(ICModelTest, InvariantFreerateHeuristic) {
    FreerateHeuristic h(10, 13, RateHeterogeneityType::INVARIANT_FREE_RATE);

    // Should ignore all non-invariant freerate models
    h.update(C("GTR+F+R10"), 832.2);
    h.update(C("GTR+F+R11"), 837.2);
    h.update(C("GTR+F+R12"), 833.2);
    EXPECT_FALSE(h.can_skip(C("GTR+F+R11")));
    EXPECT_FALSE(h.can_skip(C("GTR+F+R12")));
    EXPECT_FALSE(h.can_skip(C("GTR+F+R13")));

    h.update(C("JC+F+I+R11"), 890.2);
    h.update(C("JC+F+I+R10"), 880.9);
    EXPECT_TRUE(h.can_skip(C("JC+F+I+R12")));

    h.update(C("GTR+F+I+R10"), 832.2);
    h.update(C("GTR+F+I+R11"), 830.1); // score improved
    EXPECT_FALSE(h.can_skip(C("GTR+F+I+R12")));

    h.update(C("GTR+F+I+R12"), 830.1002); // score worsened marginally
    EXPECT_TRUE(h.can_skip(C("GTR+F+I+R13")));
}

TEST(ICModelTest, RHASFreerateHeuristicCombined) {
    std::vector<RateHeterogeneityDescriptor> selected_rhas {
                    RateHeterogeneityDescriptor(RateHeterogeneityType::UNIFORM, 1),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::INVARIANT, 1),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::GAMMA, 4),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::INVARIANT_GAMMA, 4),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 4),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 5),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 6),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 7)
                    };
    RHASHeuristic h(SubstitutionModelDescriptor("GTR", BaseFrequencyType::ESTIMATED),
                    selected_rhas, 10.0, RHASHeuristicMode::AllSignficantCategoryCounts);

    h.update(C("GTR+F"), 130.0);
    h.update(C("GTR+F+I"), 125.0);
    h.update(C("GTR+F+G4"), 105.0);
    h.update(C("GTR+F+I+G4"), 103.0);
    h.update(C("GTR+F+R4"), 100.0);

    EXPECT_FALSE(h.can_skip(C("JC+R5")));
    EXPECT_FALSE(h.can_skip(C("GTR+F+R5")));

    h.update(C("GTR+F+R5"), 110.2); // score increased
    h.set_optimal_category_count(RateHeterogeneityType::FREE_RATE, 4);
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
                    RateHeterogeneityDescriptor(RateHeterogeneityType::UNIFORM, 1),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 4),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 5),
                    RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 6),
                    },
                    SubstitutionModelDescriptor("GTR", BaseFrequencyType::ESTIMATED), 4, 6, 10.0, RHASHeuristicMode::OnlyOptimalCategoryCount);

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


TEST(ICModelTest, ScenarioI) {
    auto f = [](RHASHeuristicMode mode) {
        Heuristics h(1, {HeuristicType::FREERATE, HeuristicType::RHAS}, {
                        RateHeterogeneityDescriptor(RateHeterogeneityType::UNIFORM, 1),
                        RateHeterogeneityDescriptor(RateHeterogeneityType::INVARIANT, 1),
                        RateHeterogeneityDescriptor(RateHeterogeneityType::GAMMA, 4),
                        RateHeterogeneityDescriptor(RateHeterogeneityType::INVARIANT_GAMMA, 4),
                        RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 2),
                        RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 3),
                        RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 4),
                        RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 5),
                        RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 6),
                        RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 7),
                        RateHeterogeneityDescriptor(RateHeterogeneityType::FREE_RATE, 8),
                        },
                        SubstitutionModelDescriptor("GTR", BaseFrequencyType::ESTIMATED), 2, 8, 55.0, mode);

        // * marks BIC difference less than 55
        h.update(0, C("GTR+FO+R2"), 108235.701256);
        h.update(0, C("GTR+FO+R3"), 106452.031796);
        h.update(0, C("GTR+FO+R4"), 106076.144608);    // *
        h.update(0, C("GTR+FO"), 113728.701996);
        h.update(0, C("GTR+FO+I"), 111260.685201);
        h.update(0, C("GTR+FO+G4"), 106089.096135);    // *
        h.update(0, C("GTR+FO+I+G4"), 106050.785099);  // *
        h.update(0, C("GTR+FO+R5"), 106105.199021);    // *

        return h;
    };

    auto h1 = f(RHASHeuristicMode::AllSignficantCategoryCounts);
    EXPECT_SKIP(h1, 0, 
                    {C("HKY+FO+R2"), C("HKY+FO+R3"), C("HKY+FO"), C("HKY+FO+I"), C("HKY+FO+R6"), C("HKY+FO+R7")},
                    {C("HKY+FO+R4"), C("HKY+FO+R5"), C("HKY+FO+G4"), C("HKY+FO+I+G4")});

    auto h2 = f(RHASHeuristicMode::OnlyOptimalCategoryCount);
    EXPECT_SKIP(h2, 0, 
                    {C("HKY+FO+R2"), C("HKY+FO+R3"), C("HKY+FO+R5"), C("HKY+FO+R7"), C("HKY+FO"), C("HKY+FO+I")},
                    {C("HKY+FO+R4"), C("HKY+FO+G4"), C("HKY+FO+I+G4")});
}



const std::vector<RateHeterogeneityDescriptor> selected_rhas(bool uniform, bool invariant, bool gamma, bool invariant_gamma, unsigned int freerate_min_cat = 0, unsigned int freerate_max_cat = 0)
{
    std::vector<RateHeterogeneityDescriptor>  result;
    if (uniform) result.emplace_back(RateHeterogeneityType::UNIFORM, 1);
    if (invariant) result.emplace_back(RateHeterogeneityType::INVARIANT, 1);
    if (gamma) result.emplace_back(RateHeterogeneityType::GAMMA, 1);
    if (invariant_gamma) result.emplace_back(RateHeterogeneityType::INVARIANT_GAMMA, 1);

    if (freerate_max_cat >= freerate_min_cat && freerate_min_cat > 0)
        for (auto c = freerate_min_cat; c <= freerate_max_cat; ++c)
            result.emplace_back(RateHeterogeneityType::FREE_RATE, c);

    return result;
}

TEST(ICModelTest, HeuristicsII)
{
    Heuristics h{1, 
    {HeuristicType::FREERATE, HeuristicType::RHAS},
    selected_rhas(true, true, true, true, 2, 9), 
    SubstitutionModelDescriptor("DAYHOFF", BaseFrequencyType::ESTIMATED), 
    2, 9, 10.0, RHASHeuristicMode::AllSignficantCategoryCounts};

    h.update(0, Cp("DAYHOFF+FC+R2"), 6240.672506897783);    // <- 4.
    h.update(0, Cp("DAYHOFF+FC+R3"), 6235.7333918985969);   // <- 3.
    h.update(0, Cp("DAYHOFF+FC+R4"), 6242.2205774062613);   // <- 5.
    h.update(0, Cp("DAYHOFF+FC"), 6341.6649461173183);      // <- 7.
    h.update(0, Cp("DAYHOFF+FC+I"), 6296.4370656226893);    // <- 6.
    h.update(0, Cp("DAYHOFF+FC+G4"), 6226.4904756415253);   // <- 2. *
    h.update(0, Cp("DAYHOFF+FC+I+G4"), 6224.7664659972925); // <- 1. *

    EXPECT_TRUE(h.can_skip(0, Cp("DAYHOFF+FC+R5")));
    EXPECT_TRUE(h.can_skip(0, Cp("DAYHOFF+FC+R9")));
    EXPECT_TRUE(h.can_skip(0, Cp("FLU+R7")));
    EXPECT_TRUE(h.can_skip(0, Cp("FLU+R5")));
    EXPECT_TRUE(h.can_skip(0, Cp("BLOSUM62")));
    EXPECT_TRUE(h.can_skip(0, Cp("MTREV+FC+I")));
    EXPECT_FALSE(h.can_skip(0, Cp("DCMUT+FC+G4")));
    EXPECT_FALSE(h.can_skip(0, Cp("DAYHOFF+FC+I+G4")));
}

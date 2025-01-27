#include "RaxmlTest.hpp"
#include <gmock/gmock.h>
#include <src/modeltest/ModelDefinitions.hpp>

#include <src/modeltest/ModelTest.hpp>

TEST(ICModelTest, ModelNameNormalization) {
    EXPECT_EQ(normalize_model_name("F81+FE+COMPLICATED_MIXTURE_MODEL"), "JC+COMPLICATED_MIXTURE_MODEL");
    EXPECT_EQ(normalize_model_name("GTR+FE+I+G4m"), "SYM+I+G4m");

    auto candidates = generate_candidate_model_names(DataType::dna);
    ASSERT_THAT(candidates, testing::Contains("SYM+I+G4"));
}
#ifndef MODEL_DEFS_H
#define MODEL_DEFS_H

#include <string>
#include <array>
#include <unordered_map>

constexpr auto N_DNA_ALLMATRIX_COUNT = 203;
constexpr auto N_DNA_MODEL_MATRICES = 11;

using std::string;
using std::unordered_map;
using std::array;


enum class frequency_type_t {
    FIXED,
    ESTIMATED
};

const array<frequency_type_t, 2> default_frequency_type{frequency_type_t::FIXED, frequency_type_t::ESTIMATED};

const unordered_map<frequency_type_t, std::string> frequency_type_label{
    {frequency_type_t::FIXED, "+FE"},
    {frequency_type_t::ESTIMATED, "+FO"},
};

enum class rate_heterogeneity_t {
    UNIFORM,
    INVARIANT,
    GAMMA,
    INVARIANT_GAMMA,
    FREE_RATE
};

const array<rate_heterogeneity_t, 4> default_rate_heterogeneity{
    rate_heterogeneity_t::UNIFORM,
    rate_heterogeneity_t::INVARIANT,
    rate_heterogeneity_t::GAMMA,
    rate_heterogeneity_t::INVARIANT_GAMMA,
};

const unordered_map<rate_heterogeneity_t, string> rate_heterogeneity_label{
    {rate_heterogeneity_t::UNIFORM, ""},
    {rate_heterogeneity_t::INVARIANT, "+I"},
    {rate_heterogeneity_t::GAMMA, "+G4"},
    {rate_heterogeneity_t::INVARIANT_GAMMA, "+I+G"},
    {rate_heterogeneity_t::FREE_RATE, "+R4"},
};


// Names of DNA models. Resolved into matrix indices by means of the `dna_model_matrices_indices` array below
const std::vector<std::pair<string, size_t> > dna_substitution_matrix_names{
    {"F81", 0},
    {"HKY", 18},
    {"TrN", 59},
    {"TPM1", 116},
    {"TPM2", 72},
    {"TPM3", 100},
    {"TIM1", 167},
    {"TIM2", 139},
    {"TIM3", 155},
    {"TVM", 194},
    {"GTR", 202},
};


const std::array<std::pair<string, string>, 3> model_name_with_freq{
    {
        {"F81+FE", "JC"},
        {"HKY+FE", "K80"},
        {"GTR+FE", "SYM"}
    }
};

std::string normalize_model_name(const std::string &model_name) {
    for (const auto &e: model_name_with_freq) {
        const auto &search_str = e.first;
        const auto &replacement = e.second;

        if (search_str == model_name.substr(0, search_str.size())) {
            return replacement + model_name.substr(search_str.size());
        }
    }

    return model_name;
}

const array<string, N_DNA_ALLMATRIX_COUNT> dna_model_matrices{
    "000000", // 0

    "000001", "000010", "000011", "000100", "000101", "000110", "000111", // 1
    "001000", "001001", "001010", "001011", "001100", "001101", "001110",
    "001111", "010000", "010001", "010010", "010011", "010100", "010101",
    "010110", "010111", "011000", "011001", "011010", "011011", "011100",
    "011101", "011110", "011111",

    "000012", "000102", "000112", "000120", "000121", "000122", "001002", // 32
    "001012", "001020", "001021", "001022", "001102", "001112", "001120",
    "001121", "001122", "001200", "001201", "001202", "001210", "001211",
    "001212", "001220", "001221", "001222", "010002", "010012", "010020",
    "010021", "010022", "010102", "010112", "010120", "010121", "010122",
    "010200", "010201", "010202", "010210", "010211", "010212", "010220",
    "010221", "010222", "011002", "011012", "011020", "011021", "011022",
    "011102", "011112", "011120", "011121", "011122", "011200", "011201",
    "011202", "011210", "011211", "011212", "011220", "011221", "011222",
    "012000", "012001", "012002", "012010", "012011", "012012", "012020",
    "012021", "012022", "012100", "012101", "012102", "012110", "012111",
    "012112", "012120", "012121", "012122", "012200", "012201", "012202",
    "012210", "012211", "012212", "012220", "012221", "012222",

    "000123", "001023", "001123", "001203", "001213", "001223", "001230", //122
    "001231", "001232", "001233", "010023", "010123", "010203", "010213",
    "010223", "010230", "010231", "010232", "010233", "011023", "011123",
    "011203", "011213", "011223", "011230", "011231", "011232", "011233",
    "012003", "012013", "012023", "012030", "012031", "012032", "012033",
    "012103", "012113", "012123", "012130", "012131", "012132", "012133",
    "012203", "012213", "012223", "012230", "012231", "012232", "012233",
    "012300", "012301", "012302", "012303", "012310", "012311", "012312",
    "012313", "012320", "012321", "012322", "012323", "012330", "012331",
    "012332", "012333",

    "001234", "010234", "011234", "012034", "012134", "012234", "012304", //187
    "012314", "012324", "012334", "012340", "012341", "012342", "012343",
    "012344",

    "012345" //202
};
#endif
#pragma once
#include <cassert>
#include <stdexcept>
#include <type_traits>
#ifndef MODEL_DEFS_H
#define MODEL_DEFS_H

#include <corax/corax.h>
#include "../types.hpp"

#include <string>
#include <array>
#include <unordered_map>
#include <vector>

class unsupported_datatype_error : public std::logic_error {
public:
    unsupported_datatype_error() : std::logic_error("Modeltesting currently only supports DNA & AA data") {
    }
};

inline void check_supported_datatype(const DataType &datatype) {
    if (!(datatype == DataType::dna || datatype == DataType::protein || datatype == DataType::binary)) {
        throw unsupported_datatype_error();
    }
}

constexpr auto N_DNA_ALLMATRIX_COUNT = 203;
constexpr auto N_DNA_MODEL_MATRICES = 11;

using std::string;
using std::unordered_map;
using std::array;


enum class frequency_type_t {
    FIXED,
    ESTIMATED
};

const array<frequency_type_t, 2> default_frequency_type{frequency_type_t::ESTIMATED, frequency_type_t::FIXED};

inline std::string frequency_type_label(const DataType &datatype, const frequency_type_t &f) {
    check_supported_datatype(datatype);
    switch (f) {
        case frequency_type_t::FIXED:
            return datatype == DataType::dna ? "+FE" : "";
        case frequency_type_t::ESTIMATED:
            return datatype == DataType::dna ? "+FO" : "+FC";
        default:
            throw std::logic_error("unsupported frequency type");
    }
}


enum class rate_heterogeneity_type {
    // Compute free-rate first, to resolve among-category-count dependency quickly
    FREE_RATE,
    INVARIANT_FREE_RATE,

    UNIFORM,
    INVARIANT,
    GAMMA,
    INVARIANT_GAMMA
};

const std::array<std::string, 6> rate_heterogeneity_label{
    "R", "I+R", "", "I", "G", "I+G",
};

using RateHeterogeneitySelection = std::set<rate_heterogeneity_type>;

const RateHeterogeneitySelection default_rate_heterogeneity_selection{
    rate_heterogeneity_type::FREE_RATE, 
    rate_heterogeneity_type::UNIFORM,
    rate_heterogeneity_type::INVARIANT,
    rate_heterogeneity_type::GAMMA,
    rate_heterogeneity_type::INVARIANT_GAMMA,
};


class rate_heterogeneity_t {
public:
    rate_heterogeneity_t(rate_heterogeneity_type type, unsigned int count)
        : type{type}, category_count{count} {
    }

    rate_heterogeneity_t(const rate_heterogeneity_t &other) = default;

    rate_heterogeneity_type type;
    unsigned int category_count;

    std::string label() const {
        const size_t lookup_index = static_cast<size_t>(type);

        switch (type) {
            case rate_heterogeneity_type::UNIFORM:
                return rate_heterogeneity_label.at(lookup_index);
            case rate_heterogeneity_type::INVARIANT:
                return "+" + rate_heterogeneity_label.at(lookup_index);
            case rate_heterogeneity_type::GAMMA:
            case rate_heterogeneity_type::INVARIANT_GAMMA:
            case rate_heterogeneity_type::FREE_RATE:
            case rate_heterogeneity_type::INVARIANT_FREE_RATE:
                return "+" + rate_heterogeneity_label.at(lookup_index) + std::to_string(category_count);
            default:
                assert(0);
        }
    }

    bool operator==(const rate_heterogeneity_t &other) const {
        return type == other.type && category_count == other.category_count;
    }
};

template<>
struct std::hash<rate_heterogeneity_t> {
    std::size_t operator()(const rate_heterogeneity_t &r) const noexcept {
        return (static_cast<unsigned int>(r.type) << 16) ^ r.category_count;
    }
};
static_assert(std::is_copy_constructible<rate_heterogeneity_t>(), "necessary for use as key in std::unordered_map");

class substitution_model_t {
    public:
        std::string matrix_name;
        frequency_type_t base_frequency;

        substitution_model_t(std::string matrix_name, frequency_type_t base_frequency)
            : matrix_name{matrix_name}, base_frequency{base_frequency}
        {}

        substitution_model_t(const substitution_model_t &other) = default;

        bool operator==(const substitution_model_t &other) const {
            return matrix_name == other.matrix_name && base_frequency == other.base_frequency;
        }

        bool operator!=(const substitution_model_t &other) const {
            return !(*this == other);
        }

};

template<>
struct std::hash<substitution_model_t> {
    std::size_t operator()(const substitution_model_t &m) const noexcept {
        return (static_cast<unsigned int>(m.base_frequency) << 24) ^ std::hash<std::string>{}(m.matrix_name);
    }
};
static_assert(std::is_copy_constructible<substitution_model_t>(), "necessary for use as key in std::unordered_map");

/**
 * Description of a model that is to be tested.
 * It only describes the model matrix, frequency modifier and rate heterogeneity type, unlike the Model class, which also
 * associates values with these parameters.
 */
class candidate_model_t {
public:
    DataType datatype;
    substitution_model_t substitution_model;
    rate_heterogeneity_t rate_heterogeneity;

    candidate_model_t(DataType datatype, string matrix_name, const frequency_type_t frequency_type,
                      const rate_heterogeneity_type rate_heterogeneity, unsigned int rate_categories = 1)
        : datatype(datatype), substitution_model(matrix_name, frequency_type),
          rate_heterogeneity(rate_heterogeneity, rate_categories) { }

    std::string descriptor() const {
        return substitution_model.matrix_name + frequency_type_label(datatype, substitution_model.base_frequency) + rate_heterogeneity.label();
    }

    bool operator==(const candidate_model_t &other) const {
        return datatype == other.datatype && substitution_model == other.substitution_model &&
               rate_heterogeneity == other.rate_heterogeneity;
    }
};

template<>
struct std::hash<candidate_model_t> {
    std::size_t operator()(const candidate_model_t &m) const noexcept {
        return (std::hash<substitution_model_t>()(m.substitution_model) << 32) ^ (std::hash<rate_heterogeneity_t>()(m.rate_heterogeneity));
    }
};


struct PartitionCandidateModel
{
    size_t partition;
    candidate_model_t candidate_model;

    bool operator==(const PartitionCandidateModel &other) const {
        return partition == other.partition && candidate_model == other.candidate_model;
    }
};


template<>
struct std::hash<PartitionCandidateModel> {
    std::size_t operator()(const PartitionCandidateModel &m) const noexcept {
        return std::hash<size_t>()(m.partition) ^ (std::hash<candidate_model_t>()(m.candidate_model) << 1);
    }
};


/** Used as flags to enable/disable certain heuristics. */
enum class HeuristicType
{
    FREERATE = 1,
    RHAS = 2,
};

using HeuristicSelection = std::unordered_set<HeuristicType>;

// Names of DNA models.
const std::vector<string> dna_substitution_matrix_names{
    "GTR",
    "F81",
    "HKY",
    "TN93",
    "TPM1",
    "TPM2",
    "TPM3",
    "TIM1",
    "TIM2",
    "TIM3",
    "TVM",
};

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

const std::array<std::pair<string, string>, 3> dna_model_name_with_freq{
    {
        {"F81+FE", "JC"},
        {"HKY+FE", "K80"},
        {"GTR+FE", "SYM"}
    }
};

inline std::string normalize_model_name(const std::string &model_name) {
    for (const auto &e: dna_model_name_with_freq) {
        const auto &search_str = e.first;
        const auto &replacement = e.second;

        if (search_str == model_name.substr(0, search_str.size())) {
            return replacement + model_name.substr(search_str.size());
        }
    }

    return model_name;
}

const std::vector<std::string> aa_substitution_matrix_names{
    "LG", //  1
    "DAYHOFF", //  0
    "DCMUT", //  2
    "JTT", //  3
    "MTREV", //  4
    "WAG", //  5
    "RTREV", //  6
    "CPREV", //  7
    "VT", //  8
    "BLOSUM62", //  9
    "MTMAM", // 10
    "MTART", // 11
    "MTZOA", // 12
    "PMB", // 13
    "HIVB", // 14
    "HIVW", // 15
    "JTT-DCMUT", // 16
    "FLU", // 17
    "FLAVI",
    "mtMET",
    "mtINV",
    "mtVER",
    "DEN",
    "STMTREV",
    "Q.PFAM",
    "Q.PFAM_GB",
    "Q.LG",
    "Q.BIRD",
    "Q.INSECT",
    "Q.MAMMAL",
    "Q.PLANT",
    "Q.YEAST",
    /* additional mixture matrices
    "LG4M",      // 19
    "LG4X",      // 20
    * matrices not included by default*
    "GTR"        // 21
    */
};

#endif

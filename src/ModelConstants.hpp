#pragma once

#include <map>
#include <string>
#include <set>
#include <corax/corax.h>

template <typename A, typename B>
std::map<B, A> swap_map(const std::map<A, B> &source) {
    std::map<B, A> target;

    for (const auto &e : source) {
        target[e.second] = e.first;
    }

    return target;
}
template <typename A, typename B>
std::set<A> all_keys_of_map(const std::map<A, B> &source) {
    std::set<A> target;

    for (const auto &e : source) {
        target.insert(e.first);
    }

    return target;
}

const std::map<int, char> GAMMA_MODE_LABEL_MAP {
    {CORAX_GAMMA_RATES_MEAN, 'm'},
    {CORAX_GAMMA_RATES_MEDIAN, 'a'},
    {CORAX_GAMMA_RATES_WEIGHTS_LLOYD_MAX, 's'},
    {CORAX_GAMMA_RATES_WEIGHTS_LAGUERRE, 'q'},
};
const std::map<int, std::string> GAMMA_MODE_HUMAN_LABEL_MAP {
    {CORAX_GAMMA_RATES_MEAN, "mean"},
    {CORAX_GAMMA_RATES_MEDIAN, "median"},
    {CORAX_GAMMA_RATES_WEIGHTS_LLOYD_MAX, "DGM-star"},
    {CORAX_GAMMA_RATES_WEIGHTS_LAGUERRE, "laguerre"},
};
const std::map<char, int> GAMMA_LABEL_MODE_MAP = swap_map(GAMMA_MODE_LABEL_MAP);
const std::map<std::string, int> GAMMA_HUMAN_LABEL_MODE_MAP = swap_map(GAMMA_MODE_HUMAN_LABEL_MAP);
const std::set<int> ALL_GAMMA_MODES = all_keys_of_map(GAMMA_MODE_LABEL_MAP);

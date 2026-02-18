#ifdef _RAXML_JSON
#include "json.hpp"


#include <nlohmann/json.hpp>
using json = nlohmann::json;

json moose_json(const Options &options, const ModelTest *modeltest, const PartitionedMSA *msa) {
  auto results = modeltest->get_results();
  if (results.empty()) {
    return {};
  }

  const auto datatype = options.data_type;
  const auto datatype_name = results.at(0).at(0)->model.data_type_name();
  const auto matrices = moose_matrix_names(options.data_type);

  vector<string> frequencies;
  frequencies.reserve(default_frequency_type.size());
  for (auto f : default_frequency_type) {
    frequencies.push_back(frequency_type_label(datatype, f));
  }

  vector<string> rhas_labels;
  rhas_labels.reserve(options.modeltest_rhas.size());
  for (auto rhas : options.modeltest_rhas) {
    rhas_labels.push_back(rate_heterogeneity_label[static_cast<size_t>(rhas)]);
  }

  json heuristics;
  if (options.modeltest_heuristics.find(HeuristicType::RHAS) != options.modeltest_heuristics.cend()) {
    heuristics["RHAS"] = {
      {"ic_delta", options.modeltest_significant_ic_delta},
      {"mode", options.modeltest_rhas_heuristic_mode == RHASHeuristicMode::AllSignficantCategoryCounts ? "all significant" : "only optimal"}
    };
  }
  if (options.modeltest_heuristics.find(HeuristicType::FREERATE) != options.modeltest_heuristics.cend()) {
    heuristics["freerate"] = {};
  }

  auto tree = BasicTree(msa->taxon_count());
  auto num_branches = tree.num_branches();

  auto best_fit = json::array();
  auto evaluation_results = json::array();
  for (auto p = 0U; p < results.size(); ++p) {
    const auto &best_model = results[p][0]->model;

    const auto &part = msa->part_list().at(p);

    best_fit.push_back({
      {"partition_name", part.name()},
      {"sites", part.range_string()},
      {"model", best_model.to_string()},
      {"model_params", best_model.to_string(true, RAXML_DEFAULT_PRECISION)}
    });

    json evaluations;
    for (auto result : results[p]) {
      const auto &model = result->model;
      evaluations.push_back({
        {"model", model.to_string()},
        {"model_params", model.to_string(true, RAXML_DEFAULT_PRECISION)},
        {"free_params", num_branches + model.num_free_params()},
        {"ic_score", result->ic_score},
        {"lnL", result->loglh}
      });
    }
    evaluation_results.push_back(evaluations);
  }

  return {
    {"ic_criterion", options.ic_name()},
    {"lh_epsilon", options.lh_epsilon},
    {"candidate_selection", {
      datatype_name, {
        {"substitution_matrix", matrices},
        {"frequency", frequencies},
        {"rhas", {
          {"type", rhas_labels},
          {"min_freerate_categories", options.free_rate_min_categories},
          {"max_freerate_categories", options.free_rate_max_categories},
          {"gamma_categories", 4}
        }}
      }
    }},
    {"heuristics", heuristics},
    {"best_fit", best_fit},
    {"results", evaluation_results}
  };

}


void print_json(const Options& opts, const PartitionedMSA *msa, const CheckpointFile& checkp, const ModelTest *modeltest, double used_wh) {
  if (opts.json_file().empty()) {
    return;
  }

  json j = {
    {"$schema",  "https://raxml.ng/schema/raxml-ng-schema-v1.json"},
    {"metadata", {
      {"elapsed_time", global_timer().elapsed_seconds()},
      {"elapsed_time_total", checkp.elapsed_seconds + global_timer().elapsed_seconds()},
      {"invocation", opts.cmdline},
      {"invocation_time", sysutil_fmt_time(global_timer().start_time())},
      {"num_threads", opts.num_threads},
      {"num_workers", opts.num_workers},
      {"opt_freerate", opts.free_rate_opt_method_short_name()},
      {"opt_pattern_compression", opts.use_pattern_compression},
      {"opt_rate_scalers", opts.use_rate_scalers},
      {"opt_simd", opts.simd_arch_name()},
      {"opt_site_repeats", opts.use_repeats},
      {"opt_tip_inner", opts.use_tip_inner},
      {"random_seed", opts.random_seed},
      {"release_date", RAXML_DATE},
      {"release", RAXML_VERSION},
      {"system_cpu_cores", sysutil_get_cpu_cores()},
      {"system_cpu_model", sysutil_get_cpu_model()},
      {"system_mem_total_bytes", sysutil_get_memtotal()},
    }},
  };

  if (used_wh > 0) {
    j["metadata"]["used_wh"] = used_wh;
  }

  if(msa != nullptr) {
    j["alignment"] = {
      {"taxa", msa->taxon_count()},
      {"sites", msa->total_sites()},
      {"patterns", msa->total_patterns()},
      {"num_partitions", msa->part_count()},
    };
  }

  if (opts.auto_model() && modeltest != nullptr) {
    j["moose"] = moose_json(opts, modeltest, msa);
  }

  if (opts.command == Command::evaluate) {
    for (const auto &tree : checkp.ml_trees) {
      const double lnL = tree.second.first;
      j["evaluate"].push_back({
        {"lnL", lnL},
      });
    }
  }

  std::ofstream of(opts.json_file());
  of << j << "\n";
}

#endif

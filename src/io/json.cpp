#ifdef _RAXML_JSON
#include "json.hpp"


#include <nlohmann/json.hpp>
using json = nlohmann::json;

void print_json(const Options& opts, const PartitionedMSA *msa, const CheckpointFile& checkp, const ModelTest *modeltest, double used_wh) {
  if (opts.json_file().empty()) {
    return;
  }

  json j = {
    {"$schema",  "https://raxml.ng/schema/raxml-ng-schema-v1.json"},
    {"metadata", {
      {"release", RAXML_VERSION},
      {"release_date", RAXML_DATE},
      {"invocation", opts.cmdline},
      {"invocation_time", sysutil_fmt_time(global_timer().start_time())},
      {"random_seed", opts.random_seed},
      {"opt_simd", opts.simd_arch_name()},
      {"opt_tip_inner", opts.use_tip_inner},
      {"opt_rate_scalers", opts.use_rate_scalers},
      {"opt_site_repeats", opts.use_repeats},
      {"opt_pattern_compression", opts.use_pattern_compression},
      {"opt_freerate", opts.free_rate_opt_method_short_name()},
      {"num_workers", opts.num_workers},
      {"num_threads", opts.num_threads},
      {"system_cpu_model", sysutil_get_cpu_model()},
      {"system_cpu_cores", sysutil_get_cpu_cores()},
      {"system_mem_total_bytes", sysutil_get_memtotal()},
      {"elapsed_time", global_timer().elapsed_seconds()},
      {"total_elapsed_time", checkp.elapsed_seconds + global_timer().elapsed_seconds()},
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
    j["moose"] = modeltest->get_json();
  }

  if (opts.command == Command::evaluate) {
    for (const auto &tree : checkp.ml_trees) {
      j["evaluate"].push_back({
        "lnL", tree.second.first
      });
    }
  }

  std::ofstream of(opts.json_file());
  of << j << "\n";
}

#endif

#ifndef RAXML_CHECKPOINT_HPP_
#define RAXML_CHECKPOINT_HPP_

#include "common.h"
#include "TreeInfo.hpp"
#include "io/binary_io.hpp"

constexpr int RAXML_CKP_VERSION = 5;
constexpr int RAXML_CKP_MIN_SUPPORTED_VERSION = 5;

struct MLTree
{
  double loglh;
  Tree tree;
  ModelMap models;
};

enum class CheckpointStep
{
  start,
  brlenOpt,
  modOpt1,
  radiusDetect,
  modOpt2,
  fastSPR,
  modOpt3,
  slowSPR,
  modOpt4,
  finish
};

struct SearchState
{
  SearchState() : step(CheckpointStep::start), loglh(0.), iteration(0), fast_spr_radius(0) {}

  CheckpointStep step;
  double loglh;

  int iteration;
  spr_round_params spr_params;
  int fast_spr_radius;
};

struct Checkpoint
{
  Checkpoint() : search_state(), tree_index(0), tree(), models(), last_loglh(0.) {}

  Checkpoint(const Checkpoint&) = default;
  Checkpoint& operator=(const Checkpoint&) = default;
  Checkpoint(Checkpoint&&) = default;
  Checkpoint& operator=(Checkpoint&&) = default;

  SearchState search_state;

  size_t tree_index;
  Tree tree;
  ModelMap models;
  double last_loglh;

  double loglh() const { return search_state.loglh; }

  void reset_search_state();
};

struct CheckpointFile
{
  CheckpointFile() : version(RAXML_CKP_VERSION), elapsed_seconds(0.), consumed_wh(0.) {}

  int version;
  double elapsed_seconds;
  double consumed_wh;
  Options opts;

  std::vector<Checkpoint> checkp_list;

  ModelMap best_models;         /* model parameters for the best-scoring ML tree */
  ScoredTopologyMap ml_trees;   /* ML trees from all individual searches*/
  ScoredTopologyMap bs_trees;   /* bootstrap replicate trees */

  MLTree best_tree() const;
  Tree tree() const;

  void write_tmp_tree(const Tree& tree, const std::string fname, bool append = false) const;
  void write_tmp_best_tree() const;
  void write_tmp_ml_tree(const Tree& tree) const;
  void write_tmp_bs_tree(const Tree& tree) const;
};

class CheckpointManager
{
public:
  CheckpointManager(const Options& opts);

  const CheckpointFile& checkp_file() const { return _checkp_file;  }

  const Checkpoint& checkpoint(size_t ckp_id = ParallelContext::local_group_id()) const;
  Checkpoint& checkpoint(size_t ckp_id = ParallelContext::local_group_id());

  //TODO: this is not very elegant, but should do the job for now
  SearchState& search_state();
  void reset_search_state();

  void init_checkpoints(const Tree& tree, const ModelCRefMap& models);

  void enable() { _active = true; }
  void disable() { _active = false; }

  void update_and_write(const TreeInfo& treeinfo);

  void save_ml_tree();
  void save_bs_tree();

  bool read() { return read(_ckp_fname); }
  bool read(const std::string& ckp_fname);
  void write() const { write(_ckp_fname); }
  void write(const std::string& ckp_fname) const;

  void remove();
  void backup() const;
  void remove_backup() const;

  void gather_ml_trees();
  void gather_bs_trees();

private:
  bool _active;
  std::string _ckp_fname;
  CheckpointFile _checkp_file;
  IDSet _updated_models;
  SearchState _empty_search_state;

  void gather_model_params();
  std::string backup_fname() const { return _ckp_fname + ".bk"; }
};

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const Checkpoint& ckp);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, Checkpoint& ckp);

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const CheckpointFile& ckpfile);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, CheckpointFile& ckpfile);

void assign_tree(Checkpoint& ckp, const TreeInfo& treeinfo);
void assign_models(Checkpoint& ckp, const TreeInfo& treeinfo);
void assign_models(TreeInfo& treeinfo, const Checkpoint& ckp);

void assign(Checkpoint& ckp, const TreeInfo& treeinfo);
void assign(TreeInfo& treeinfo, const Checkpoint& ckp);

#endif /* RAXML_CHECKPOINT_HPP_ */

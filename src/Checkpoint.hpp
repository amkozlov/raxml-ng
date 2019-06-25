#ifndef RAXML_CHECKPOINT_HPP_
#define RAXML_CHECKPOINT_HPP_

#include "common.h"
#include "TreeInfo.hpp"
#include "io/binary_io.hpp"

constexpr int RAXML_CKP_VERSION = 2;
constexpr int RAXML_CKP_MIN_SUPPORTED_VERSION = 2;

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
  Checkpoint() : search_state(), tree(), models() {}

  Checkpoint(const Checkpoint&) = delete;
  Checkpoint& operator=(const Checkpoint&) = delete;
  Checkpoint(Checkpoint&&) = default;
  Checkpoint& operator=(Checkpoint&&) = default;

  SearchState search_state;

  Tree tree;
  ModelMap models;
//  ModelMap best_models;  /* model parameters for the best-scoring ML tree */
//
//  TreeCollection ml_trees;
//  TreeCollection bs_trees;

  double loglh() const { return search_state.loglh; }

  void reset_search_state();

//  void save_ml_tree();
//  void save_bs_tree();
};

struct CheckpointFile
{
  CheckpointFile() : version(RAXML_CKP_VERSION), elapsed_seconds(0.) {}

  int version;
  double elapsed_seconds;
  Options opts;

  std::vector<Checkpoint> checkp_list;

  ModelMap best_models;         /* model parameters for the best-scoring ML tree */
  ScoredTopologyMap ml_trees;   /* ML trees from all individual searches*/
  ScoredTopologyMap bs_trees;   /* bootstrap replicate trees */

  MLTree best_tree() const;
  Tree tree() const;
};

class CheckpointManager
{
public:
  CheckpointManager(const Options& opts);

  const CheckpointFile& checkp_file() const { return _checkp_file;  }

  const Checkpoint& checkpoint() const;
  Checkpoint& checkpoint();

  //TODO: this is not very elegant, but should do the job for now
  SearchState& search_state();
  void reset_search_state();

  void init_models(const ModelCRefMap& models);

  void enable() { _active = true; }
  void disable() { _active = false; }

  void update_and_write(const TreeInfo& treeinfo);

  void save_ml_tree(size_t index);
  void save_bs_tree(size_t index);

  bool read() { return read(_ckp_fname); }
  bool read(const std::string& ckp_fname);
  void write() const { write(_ckp_fname); }
  void write(const std::string& ckp_fname) const;

  void remove();
  void backup() const;
  void remove_backup() const;

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

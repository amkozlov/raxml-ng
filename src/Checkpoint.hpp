#ifndef RAXML_CHECKPOINT_HPP_
#define RAXML_CHECKPOINT_HPP_

#include "common.h"
#include "TreeInfo.hpp"
#include "io/binary_io.hpp"

constexpr int CKP_VERSION = 1;
constexpr int CKP_MIN_SUPPORTED_VERSION = 1;

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
  Checkpoint() : version(CKP_VERSION), search_state(), tree(), models() {}

  Checkpoint(const Checkpoint& other) = delete;
  Checkpoint& operator=(const Checkpoint& other) = delete;
  Checkpoint(Checkpoint&& other) = default;
  Checkpoint& operator=(Checkpoint&& other) = default;

  int version;

  SearchState search_state;

  Tree tree;
  std::unordered_map<size_t, Model> models;

  double loglh() const { return search_state.loglh; }
};

class CheckpointManager
{
public:
  CheckpointManager(const std::string& ckp_fname) : _ckp_fname(ckp_fname) {}

  const Checkpoint& checkpoint() { return _checkp; }
  void checkpoint(Checkpoint&& ckp) { _checkp = std::move(ckp); }

  //TODO: this is not very elegant, but should do the job for now
  SearchState& search_state() { return _checkp.search_state; };
  void update_and_write(const TreeInfo& treeinfo);

  void write() const { write(_ckp_fname); };
  void write(const std::string& ckp_fname) const;
  bool read() { return read(_ckp_fname); };
  bool read(const std::string& ckp_fname);

private:
  std::string _ckp_fname;
  Checkpoint _checkp;
  IDSet _updated_models;

  void gather_model_params();
};

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const Checkpoint& ckp);
BasicBinaryStream& operator>>(BasicBinaryStream& stream, Checkpoint& ckp);

void assign_tree(Checkpoint& ckp, const TreeInfo& treeinfo);
void assign_models(Checkpoint& ckp, const TreeInfo& treeinfo);

void assign(Checkpoint& ckp, const TreeInfo& treeinfo);
void assign(TreeInfo& treeinfo, const Checkpoint& ckp);

#endif /* RAXML_CHECKPOINT_HPP_ */

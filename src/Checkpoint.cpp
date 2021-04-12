#include <stdio.h>

#include "Checkpoint.hpp"
#include "io/binary_io.hpp"
#include "io/file_io.hpp"
#include "util/EnergyMonitor.hpp"

using namespace std;

void Checkpoint::reset_search_state()
{
  search_state = SearchState();
};

Tree CheckpointFile::tree() const
{
  return checkp_list.at(0).tree;
}

MLTree CheckpointFile::best_tree() const
{
  MLTree result;
  result.loglh = -INFINITY;
  result.tree = tree();

  if (!ml_trees.empty())
  {
    auto best = ml_trees.best()->second;
    if (best.first > result.loglh)
    {
      result.loglh = best.first;
      result.tree.topology(best.second);
      result.models = best_models;
    }
  }

  for (const auto& ckp: checkp_list)
  {
    if (ckp.tree_index > 0 && ckp.last_loglh > result.loglh)
    {
      result.loglh = ckp.last_loglh;
      result.tree = ckp.tree;
//      printf("New best tree: %u, loglh: %lf\n ", ckp.tree_index, ckp.last_loglh);
    }
  }

  return result;
}

void CheckpointFile::write_tmp_tree(const Tree& tree, const std::string fname, bool append) const
{
  if (ParallelContext::group_master())
  {
      auto mode = ios::out;
      if (append)
        mode |= ios::app;
      NewickStream ns(fname, mode);
      ns << tree;
  }
}

void CheckpointFile::write_tmp_best_tree() const
{
  /* NB: do not print last-best tree in bootstrapping stage! */
  if (opts.write_interim_results && ml_trees.size() < opts.num_searches)
    write_tmp_tree(best_tree().tree, opts.tmp_best_tree_file());
}

void CheckpointFile::write_tmp_ml_tree(const Tree& tree) const
{
  if (opts.write_interim_results)
    write_tmp_tree(tree, opts.tmp_ml_trees_file(), true);
}

void CheckpointFile::write_tmp_bs_tree(const Tree& tree) const
{
  if (opts.write_interim_results)
    write_tmp_tree(tree, opts.tmp_bs_trees_file(), true);
}

CheckpointManager::CheckpointManager(const Options& opts) :
    _active(opts.nofiles_mode ? false : true), _ckp_fname(opts.checkp_file())
{
  _checkp_file.opts = opts;
}

const Checkpoint& CheckpointManager::checkpoint(size_t ckp_id) const
{
  return _checkp_file.checkp_list.at(ckp_id);
}

Checkpoint& CheckpointManager::checkpoint(size_t ckp_id)
{
  return _checkp_file.checkp_list.at(ckp_id);
}

void CheckpointManager::init_checkpoints(const Tree& tree, const ModelCRefMap& models)
{
  /* create one checkpoint per *local* worker */
  for (size_t i = 0; i < ParallelContext::num_local_groups(); ++i)
    _checkp_file.checkp_list.emplace_back();

  for (auto& ckp: _checkp_file.checkp_list)
  {
    ckp.tree = tree;
    for (auto& it: models)
      ckp.models[it.first] = it.second;
  }

  for (auto& it: models)
    _checkp_file.best_models[it.first] = it.second;
}

void CheckpointManager::write(const std::string& ckp_fname) const
{
  /* MPI+coarse mode -> master thread in each rank writes rank-specific ckp file
   * otherwise -> only master thread in master rank writes global ckp file
   * */
  if (ParallelContext::master() ||
      (ParallelContext::master_thread() && ParallelContext::coarse_mpi()))
  {
//    printf("write ckp rank=%lu\n", ParallelContext::rank_id());

    backup();

    BinaryFileStream fs(ckp_fname, std::ios::out);

    fs << _checkp_file;

    remove_backup();
  }
}

bool CheckpointManager::read(const std::string& ckp_fname)
{
  if (sysutil_file_exists(ckp_fname))
  {
    try
    {
      BinaryFileStream fs(ckp_fname, std::ios::in);

      fs >> _checkp_file;

      return true;
    }
    catch (runtime_error& e)
    {
      if (ParallelContext::group_master_thread())
        checkpoint().reset_search_state();
      LOG_DEBUG << "Error reading checkpoint: " << e.what() << endl;
      return false;
    }
  }
  else
    return false;
}

void CheckpointManager::remove()
{
  if (sysutil_file_exists(_ckp_fname))
    std::remove(_ckp_fname.c_str());
}

void CheckpointManager::backup() const
{
  if (sysutil_file_exists(_ckp_fname))
    std::rename(_ckp_fname.c_str(), backup_fname().c_str());
}

void CheckpointManager::remove_backup() const
{
  if (sysutil_file_exists(backup_fname()))
    std::remove(backup_fname().c_str());
}

SearchState& CheckpointManager::search_state()
{
  return checkpoint().search_state;
};

void CheckpointManager::reset_search_state()
{
  ParallelContext::thread_barrier();

  if (ParallelContext::group_master_thread())
    checkpoint().reset_search_state();

  ParallelContext::thread_barrier();
};

void CheckpointManager::save_ml_tree()
{
  if (ParallelContext::group_master())
  {
    /* we will modify a global data in _checkp_file -> define critical section */
    ParallelContext::UniqueLock lock;

    Checkpoint& ckp = checkpoint();

//    printf("WORKER %u: save ML tree # %u index loglh = %lf\n",
//           ParallelContext::group_id(), index, ckp.loglh());

    auto& ml_trees = _checkp_file.ml_trees;
    if (ml_trees.empty() || ckp.loglh() > ml_trees.best_score())
      _checkp_file.best_models = ckp.models;

    ml_trees.insert(ckp.tree_index, ScoredTopology(ckp.loglh(), ckp.tree.topology()));

    ckp.tree_index = 0;

    if (_active)
      write();

    _checkp_file.write_tmp_ml_tree(ckp.tree);
  }
}

void CheckpointManager::save_bs_tree()
{
  if (ParallelContext::group_master())
  {
    /* we will modify a global data in _checkp_file -> define critical section */
    ParallelContext::UniqueLock lock;

    Checkpoint& ckp = checkpoint();

//    printf("WORKER %u: save BS tree # %u index loglh = %lf\n",
//           ParallelContext::group_id(), index, ckp.loglh());

    _checkp_file.bs_trees.insert(ckp.tree_index, ScoredTopology(ckp.loglh(), ckp.tree.topology()));

    ckp.tree_index = 0;

    if (_active)
      write();

    _checkp_file.write_tmp_bs_tree(ckp.tree);
  }
}

void CheckpointManager::update_and_write(const TreeInfo& treeinfo)
{
  if (ParallelContext::master_thread())
    _updated_models.clear();

  ParallelContext::barrier();

  Checkpoint& ckp = checkpoint();

  for (auto p: treeinfo.parts_master())
  {
    /* we will modify a global map -> define critical section */
    ParallelContext::UniqueLock lock;

    assign(ckp.models.at(p), treeinfo, p);

    /* remember which models were updated but this rank ->
     * will be used later to collect them at the master */
    _updated_models.insert(p);
  }

  ParallelContext::barrier();

  if (ParallelContext::ranks_per_group() > 1)
    gather_model_params();

  if (ParallelContext::group_master())
  {
    ParallelContext::UniqueLock lock;
    assign_tree(ckp, treeinfo);
    ckp.last_loglh = ckp.search_state.loglh;
    if (_active)
      write();

    _checkp_file.write_tmp_best_tree();
  }
}

void CheckpointManager::gather_model_params()
{
  /* send callback -> worker ranks */
  auto worker_cb = [this](void * buf, size_t buf_size) -> size_t
      {
        BinaryStream bs((char*) buf, buf_size);
        bs << _updated_models.size();
        for (auto p: _updated_models)
        {
          bs << p << checkpoint().models.at(p);
        }
        return bs.pos();
      };

  /* receive callback -> master rank */
  auto master_cb = [this](void * buf, size_t buf_size, size_t /* rank */)
     {
       BinaryStream bs((char*) buf, buf_size);
       auto model_count = bs.get<size_t>();
       for (size_t m = 0; m < model_count; ++m)
       {
         size_t part_id;
         bs >> part_id;

         // read parameter estimates from binary stream
         bs >> checkpoint().models[part_id];
       }
     };

  ParallelContext::mpi_gather_custom(worker_cb, master_cb);
}

void CheckpointManager::gather_ml_trees()
{
  if (ParallelContext::num_ranks() == 1 || ParallelContext::num_groups() == 1)
    return;

  /* send callback -> worker ranks */
  auto worker_cb = [this](void * buf, size_t buf_size) -> size_t
      {
        BinaryStream bs((char*) buf, buf_size);

        bs << _checkp_file.ml_trees;

        bs << _checkp_file.best_models;

//        printf("after worker: %u\n", bs.pos());

        // clear this batch of ML trees from the worker, since they will now be stored by master
        _checkp_file.ml_trees.clear();

        return bs.pos();
      };

  /* receive callback -> master rank */
  auto master_cb = [this](void * buf, size_t buf_size, size_t /* rank */)
     {
       double old_score = _checkp_file.ml_trees.best_score();
       BinaryStream bs((char*) buf, buf_size);

       bs >>  _checkp_file.ml_trees;

       if (_checkp_file.ml_trees.best_score() > old_score)
         bs >> _checkp_file.best_models;
     };

  ParallelContext::mpi_gather_custom(worker_cb, master_cb);
}

void CheckpointManager::gather_bs_trees()
{
  if (ParallelContext::num_ranks() == 1 || ParallelContext::num_groups() == 1)
    return;

  /* send callback -> worker ranks */
  auto worker_cb = [this](void * buf, size_t buf_size) -> size_t
      {
        BinaryStream bs((char*) buf, buf_size);

        bs << _checkp_file.bs_trees;

//        printf("after worker: %u\n", bs.pos());

        // clear this batch of BS trees from the worker, since they will now be stored by master
        _checkp_file.bs_trees.clear();

        return bs.pos();
      };

  /* receive callback -> master rank */
  auto master_cb = [this](void * buf, size_t buf_size, size_t /* rank */)
     {
       BinaryStream bs((char*) buf, buf_size);

       bs >>  _checkp_file.bs_trees;
     };

  ParallelContext::mpi_gather_custom(worker_cb, master_cb);
}

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const Checkpoint& ckp)
{
  stream << ckp.search_state;

  stream << ckp.tree_index;

  stream << ckp.tree.topology();

  stream << ckp.models;

  return stream;
}

BasicBinaryStream& operator>>(BasicBinaryStream& stream, Checkpoint& ckp)
{
  stream >> ckp.search_state;

  stream >> ckp.tree_index;

  ckp.tree.topology(stream.get<TreeTopology>());

  stream >> ckp.models;

  return stream;
}

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const CheckpointFile& ckpfile)
{
  stream << ckpfile.version;

  // NB: accumulated runtime from past runs + current elapsed time
  stream << ckpfile.elapsed_seconds + global_timer().elapsed_seconds();

  stream << ckpfile.consumed_wh + global_energy_monitor.consumed_wh(false);

  stream << ckpfile.opts;

  stream << ckpfile.checkp_list;

  stream << ckpfile.best_models;

  stream << ckpfile.ml_trees;

  stream << ckpfile.bs_trees;

  return stream;
}

BasicBinaryStream& operator>>(BasicBinaryStream& stream, CheckpointFile& ckpfile)
{
  stream >> ckpfile.version;

  if (ckpfile.version < RAXML_CKP_MIN_SUPPORTED_VERSION || ckpfile.version > RAXML_CKP_VERSION)
  {
    throw runtime_error("Unsupported checkpoint file version!");
  }

  stream >> ckpfile.elapsed_seconds;

  if (ckpfile.version > 3)
  {
    stream >> ckpfile.consumed_wh;

    stream >> ckpfile.opts;
  }

  {
    // we should take special care in case number of workers has been changed after restart:
    // - if #workers increased, "extra" workers will start tree search from scratch
    // - if #workers decreased, "extra" checkpoints in file will be ignored (not optimal, but simpler)
    size_t num_ckp_in_file = stream.get<size_t>();
    size_t num_ckp_to_load = std::min(num_ckp_in_file, ckpfile.checkp_list.size());
    auto dummy_ckp = (num_ckp_to_load < num_ckp_in_file) ? ckpfile.checkp_list[0] : Checkpoint();
    for (size_t i = 0; i < num_ckp_in_file; ++i)
    {
      if (i < num_ckp_to_load)
        stream >> ckpfile.checkp_list[i];
      else
        stream >> dummy_ckp;
    }
  }

  stream >> ckpfile.best_models;

  stream >> ckpfile.ml_trees;

  stream >> ckpfile.bs_trees;

  return stream;
}


void assign_tree(Checkpoint& ckp, const TreeInfo& treeinfo)
{
  ckp.tree = treeinfo.tree();
}

void assign_model(Checkpoint& ckp, const TreeInfo& treeinfo, size_t index)
{
  assign(ckp.models.at(index), treeinfo, index);
}

void assign_models(Checkpoint& ckp, const TreeInfo& treeinfo)
{
  for (auto p: treeinfo.parts_master())
    assign_model(ckp, treeinfo, p);
}

void assign_models(TreeInfo& treeinfo, const Checkpoint& ckp)
{
  const pllmod_treeinfo_t& pll_treeinfo = treeinfo.pll_treeinfo();
  for (auto& m: ckp.models)
  {
    if (!pll_treeinfo.partitions[m.first])
      continue;

    treeinfo.model(m.first, m.second);
  }
}

void assign(Checkpoint& ckp, const TreeInfo& treeinfo)
{
  assign_tree(ckp, treeinfo);
  assign_models(ckp, treeinfo);
}

void assign(TreeInfo& treeinfo, const Checkpoint& ckp)
{
  // TODO: it is currently not possible to change tree after pll_treeinfo has been created
  // this should be fixed while doing refactoring to change pll_unode_t -> pll_tree_t
  assert(0);
  treeinfo.tree(ckp.tree);

  assign_models(treeinfo, ckp);
}


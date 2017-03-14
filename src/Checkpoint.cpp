#include <stdio.h>

#include "Checkpoint.hpp"
#include "io/binary_io.hpp"
#include "io/file_io.hpp"

using namespace std;

void CheckpointManager::write(const std::string& ckp_fname) const
{
  backup();

  BinaryFileStream fs(ckp_fname, std::ios::out);

  fs << _checkp;

  remove_backup();
}

bool CheckpointManager::read(const std::string& ckp_fname)
{
  if (sysutil_file_exists(ckp_fname))
  {
    try
    {
      BinaryFileStream fs(ckp_fname, std::ios::in);

      fs >> _checkp;

      return true;
    }
    catch (runtime_error& e)
    {
      _checkp.search_state = SearchState();
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
  if (_active)
    return _checkp.search_state;
  else
  {
    _empty_search_state = SearchState();
    return _empty_search_state;
  }
};

void CheckpointManager::reset_search_state()
{
  ParallelContext::thread_barrier();

  if (ParallelContext::master_thread())
    _checkp.search_state = SearchState();

  ParallelContext::thread_barrier();
};

void CheckpointManager::save_ml_tree()
{
  if (ParallelContext::master_thread())
  {
    _checkp.save_ml_tree();
    if (_active)
      write();
  }
}

void CheckpointManager::save_bs_tree()
{
  if (ParallelContext::master_thread())
  {
    _checkp.save_bs_tree();
    if (_active)
      write();
  }
}

void CheckpointManager::update_and_write(const TreeInfo& treeinfo)
{
  if (!_active)
    return;

  if (ParallelContext::master_thread())
    _updated_models.clear();

  ParallelContext::barrier();

  for (auto p: treeinfo.parts_master())
  {
    /* we will modify a global map -> define critical section */
    ParallelContext::UniqueLock lock;

    assign(_checkp.models.at(p), treeinfo, p);

    /* remember which models were updated but this rank ->
     * will be used later to collect them at the master */
    _updated_models.insert(p);
  }

  ParallelContext::barrier();

  if (ParallelContext::num_ranks() > 1)
    gather_model_params();

  if (ParallelContext::master())
  {
    assign_tree(_checkp, treeinfo);
    write();
  }
}

void CheckpointManager::gather_model_params()
{
  /* send callback -> worker ranks */
  auto worker_cb = [this](void * buf, size_t buf_size) -> int
      {
        BinaryStream bs((char*) buf, buf_size);
        bs << _updated_models.size();
        for (auto p: _updated_models)
        {
          bs << p << _checkp.models.at(p);
        }
        return (int) bs.pos();
      };

  /* receive callback -> master rank */
  auto master_cb = [this](void * buf, size_t buf_size)
     {
       BinaryStream bs((char*) buf, buf_size);
       auto model_count = bs.get<size_t>();
       for (size_t m = 0; m < model_count; ++m)
       {
         size_t part_id;
         bs >> part_id;

         // read parameter estimates from binary stream
         bs >> _checkp.models[part_id];
       }
     };

  ParallelContext::mpi_gather_custom(worker_cb, master_cb);
}

BasicBinaryStream& operator<<(BasicBinaryStream& stream, const Checkpoint& ckp)
{
  stream << ckp.version;

  stream << ckp.search_state;

  stream << ckp.tree.topology();

  stream << ckp.models.size();
  for (const auto& m: ckp.models)
    stream << m.first << m.second;

  stream << ckp.ml_trees;

  stream << ckp.bs_trees;

  return stream;
}

BasicBinaryStream& operator>>(BasicBinaryStream& stream, Checkpoint& ckp)
{
  stream >> ckp.version;

  if (ckp.version < CKP_MIN_SUPPORTED_VERSION)
  {
    throw runtime_error("Unsupported checkpoint file version!");
  }

  stream >> ckp.search_state;

//  auto topol = fs.get<TreeTopology>();
//
//  printf("READ topology size: %u\n", topol.size());

  ckp.tree.topology(stream.get<TreeTopology>());

  size_t num_models, part_id;
  stream >> num_models;
  assert(num_models == ckp.models.size());
  for (size_t m = 0; m < num_models; ++m)
  {
    stream >> part_id;
    stream >> ckp.models[part_id];
  }

  stream >> ckp.ml_trees;

  stream >> ckp.bs_trees;

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

void assign(Checkpoint& ckp, const TreeInfo& treeinfo)
{
  assign_tree(ckp, treeinfo);
  assign_models(ckp, treeinfo);
}

void assign(TreeInfo& treeinfo, const Checkpoint& ckp)
{
  treeinfo.tree(ckp.tree);

  const pllmod_treeinfo_t& pll_treeinfo = treeinfo.pll_treeinfo();
  for (auto& m: ckp.models)
  {
    if (!pll_treeinfo.partitions[m.first])
      continue;

    treeinfo.model(m.first, m.second);
  }
}


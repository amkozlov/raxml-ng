#include "Optimizer.hpp"
#include "topology/RFDistCalculator.hpp"

using namespace std;

Optimizer::Optimizer (const Options &opts) :
    _lh_epsilon(opts.lh_epsilon), _lh_epsilon_brlen_triplet(opts.lh_epsilon_brlen_triplet), 
    _spr_radius(opts.spr_radius), _spr_cutoff(opts.spr_cutoff), 
    _nni_epsilon(opts.nni_epsilon), _nni_tolerance(opts.nni_tolerance)
{
}

Optimizer::~Optimizer ()
{
  // TODO Auto-generated destructor stub
}

double Optimizer::optimize_model(TreeInfo& treeinfo, double lh_epsilon)
{
  double new_loglh = treeinfo.loglh();

//  if (!params_to_optimize)
//    return new_loglh;

  int iter_num = 0;
  double cur_loglh;
  do
  {
    cur_loglh = new_loglh;

    treeinfo.optimize_params_all(lh_epsilon);

    new_loglh = treeinfo.loglh();

//      printf("old: %f, new: %f\n", cur_loglh, new_loglh);

    iter_num++;
    LOG_DEBUG << "Iteration " << iter_num <<  ": logLH = " << new_loglh << endl;
  }
  while (new_loglh - cur_loglh > lh_epsilon);

  return new_loglh;
}

void Optimizer::nni(TreeInfo& treeinfo, nni_round_params& nni_params, double& loglh){
  // nni round
  LOG_PROGRESS(loglh) << "NNI round tolerance = " <<  nni_params.tolerance << ", epsilon = " << nni_params.lh_epsilon << endl;
  loglh = treeinfo.nni_round(nni_params);
  
}

double Optimizer::optimize_topology(TreeInfo& treeinfo, CheckpointManager& cm)
{
  const double fast_modopt_eps = 10.;
  const double interim_modopt_eps = 3.;
  const double final_modopt_eps = 0.1;

  SearchState local_search_state = cm.search_state();
  auto& search_state = ParallelContext::group_master_thread() ? cm.search_state() : local_search_state;
  ParallelContext::barrier();

  /* set references such that we can work directly with checkpoint values */
  double &loglh = search_state.loglh;
  int& iter = search_state.iteration;
  spr_round_params& spr_params = search_state.spr_params;
  int& best_fast_radius = search_state.fast_spr_radius;

  spr_params.lh_epsilon_brlen_full = _lh_epsilon;
  spr_params.lh_epsilon_brlen_triplet = _lh_epsilon_brlen_triplet;

  CheckpointStep resume_step = search_state.step;

  /* Compute initial LH of the starting tree */
  loglh = treeinfo.loglh();

  auto do_step = [&search_state,resume_step](CheckpointStep step) -> bool
      {
        if (step >= resume_step)
        {
          search_state.step = step;
          return true;
        }
        else
          return false;;
      };

  if (do_step(CheckpointStep::brlenOpt))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Initial branch length optimization" << endl;
    loglh = treeinfo.optimize_branches(fast_modopt_eps, 1);
  }

  /* Initial fast model optimization */
  if (do_step(CheckpointStep::modOpt1))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << fast_modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, fast_modopt_eps);

    /* start spr rounds from the beginning */
    iter = 0;
  }

  // do SPRs
  const int radius_limit = min(22, (int) treeinfo.pll_treeinfo().tip_count - 3 );
  const int radius_step = 5;

//  treeinfo->counter = 0;

  if (_spr_radius > 0)
    best_fast_radius = _spr_radius;
  else
  {
    /* auto detect best radius for fast SPRs */

    if (do_step(CheckpointStep::radiusDetect))
    {
      if (iter == 0)
      {
        spr_params.thorough = 0;
        spr_params.radius_min = 1;
        best_fast_radius = spr_params.radius_max = 5;
        spr_params.ntopol_keep = 0;
        spr_params.subtree_cutoff = 0.;
      }

      double best_loglh = loglh;

      while (spr_params.radius_min < radius_limit)
      {
        cm.update_and_write(treeinfo);

        ++iter;
        LOG_PROGRESS(best_loglh) << "AUTODETECT spr round " << iter << " (radius: " <<
            spr_params.radius_max << ")" << endl;
        loglh = treeinfo.spr_round(spr_params);

        if (loglh - best_loglh > 0.1)
        {
          /* LH improved, try to increase the radius */
          best_fast_radius = spr_params.radius_max;
          spr_params.radius_min += radius_step;
          spr_params.radius_max += radius_step;
          best_loglh = loglh;
        }
        else
          break;
      }
    }
  }

  LOG_PROGRESS(loglh) << "SPR radius for FAST iterations: " << best_fast_radius << " (" <<
                 (_spr_radius > 0 ? "user-specified" : "autodetect") << ")" << endl;

  if (do_step(CheckpointStep::modOpt2))
  {
    cm.update_and_write(treeinfo);

    /* optimize model parameters a bit more thoroughly */
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " <<
                                                            interim_modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, interim_modopt_eps);

    /* reset iteration counter for fast SPRs */
    iter = 0;

    /* initialize search params */
    spr_params.thorough = 0;
    spr_params.radius_min = 1;
    spr_params.radius_max = best_fast_radius;
    spr_params.ntopol_keep = 20;
    spr_params.subtree_cutoff = _spr_cutoff;
    spr_params.reset_cutoff_info(loglh);
  }

  double old_loglh;

  if (do_step(CheckpointStep::fastSPR))
  {
    do
    {
      cm.update_and_write(treeinfo);
      ++iter;
      old_loglh = loglh;
      LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
          " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;
      loglh = treeinfo.spr_round(spr_params);

      /* optimize ALL branches */
      loglh = treeinfo.optimize_branches(_lh_epsilon, 1);
    }
    while (loglh - old_loglh > _lh_epsilon);
  }

  if (do_step(CheckpointStep::modOpt3))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << 1.0 << ")" << endl;
    loglh = optimize_model(treeinfo, 1.0);

    /* init slow SPRs */
    spr_params.thorough = 1;
    spr_params.radius_min = 1;
    spr_params.radius_max = radius_step;
    iter = 0;
  }

  if (do_step(CheckpointStep::slowSPR))
  {
    do
    {
      cm.update_and_write(treeinfo);
      ++iter;
      old_loglh = loglh;
      LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
          " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;
      loglh = treeinfo.spr_round(spr_params);

      /* optimize ALL branches */
      loglh = treeinfo.optimize_branches(_lh_epsilon, 1);

      bool impr = (loglh - old_loglh > _lh_epsilon);
      if (impr)
      {
        /* got improvement in thorough mode: reset min radius to 1 */
        spr_params.radius_min = 1;
        /* reset max radius to 5; or maybe better keep old value? */
        spr_params.radius_max = radius_step;
      }
      else
      {
        /* no improvement in thorough mode: set min radius to old max,
         * and increase max radius by the step */
        spr_params.radius_min = spr_params.radius_max + 1;
        spr_params.radius_max += radius_step;
      }
    }
    while (spr_params.radius_min >= 0 && spr_params.radius_min < radius_limit);
  }

  /* Final thorough model optimization */
  if (do_step(CheckpointStep::modOpt4))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << final_modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, final_modopt_eps);
  }

  if (do_step(CheckpointStep::finish))
    cm.update_and_write(treeinfo);

  return loglh;
}

double Optimizer::optimize_topology_adaptive(TreeInfo& treeinfo, CheckpointManager& cm, double difficulty)
{
  // TODO: connect the command line arguments for nni-epsilon and nni-tolerance with nni_params.lh_epsilon and 
  // nni_params.tolerance
  const double fast_modopt_eps = 10.;
  const double interim_modopt_eps = 3.;
  const double final_modopt_eps = 0.1;

  // to store all the intermediate trees
  TreeList intermediate_trees;

  SearchState local_search_state = cm.search_state();
  auto& search_state = ParallelContext::group_master_thread() ? cm.search_state() : local_search_state;
  ParallelContext::barrier();

  /* set references such that we can work directly with checkpoint values */
  double &loglh = search_state.loglh;
  
  // spr round - basics
  spr_round_params& spr_params = search_state.spr_params;
  int slow_spr_radius = adaptive_slow_spr_radius(difficulty); // slow spr radius is determined by difficulty
  slow_spr_radius = min(slow_spr_radius, (int) treeinfo.pll_treeinfo().tip_count - 3 );
  spr_params.lh_epsilon_brlen_full = _lh_epsilon;
  spr_params.lh_epsilon_brlen_triplet = _lh_epsilon_brlen_triplet;
  int iter = 0;

  // nni round - basics
  nni_round_params& nni_params = search_state.nni_params;
  nni_params.tolerance = _nni_tolerance;
  nni_params.lh_epsilon = _nni_epsilon;

  // rf distance calculator
  std::unique_ptr<RFDistCalculator> rfDist(new RFDistCalculator());

  /* Compute initial LH of the starting tree */
  loglh = treeinfo.loglh();

  /* Initial branch length optimization */
  cm.update_and_write(treeinfo);
  LOG_PROGRESS(loglh) << "Initial branch length optimization" << endl;
  loglh = treeinfo.optimize_branches(fast_modopt_eps, 1);
  
  /* Initial fast model optimization */
  cm.update_and_write(treeinfo);
  LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << fast_modopt_eps << ")" << endl;
  loglh = optimize_model(treeinfo, fast_modopt_eps);
  
  /* push back the initial tree */
  intermediate_trees.emplace_back(treeinfo.tree());
  rfDist->set_tree_list(intermediate_trees);

  // If the dataset is "easy" or "difficult", start with an NNI round
  if(difficulty < 0.3 || difficulty > 0.7){
    
    cm.update_and_write(treeinfo);
    nni(treeinfo, nni_params, loglh);

    // + model parameter optimization
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << interim_modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, fast_modopt_eps);

    intermediate_trees.emplace_back(treeinfo.tree());

  }

  // do SPRs
  const int radius_limit = min(22, (int) treeinfo.pll_treeinfo().tip_count - 3 );
  const int radius_step = 5; // HAVE TO CHANGE THAT

  // setting up fast SPR parameters
  spr_params.thorough = 0;
  spr_params.radius_min = 1;
  spr_params.radius_max = 5;
  spr_params.ntopol_keep = 0;
  spr_params.subtree_cutoff = 0.;

  size_t rf_distance = 1;
  bool skip_intermid_model_opt = false;
  bool impr = true;
  double old_loglh;

  if(converged(cm, loglh, 0.01)) skip_intermid_model_opt = true;

  /* Fast SPR-NNI rounds */
  while( !converged(cm, loglh, 0.01) && rf_distance != 0 && impr) {

    ++iter;
    old_loglh = loglh;
    cm.update_and_write(treeinfo);
    
    // spr round
    LOG_PROGRESS(loglh) << "SPR round " << iter << " (radius: " <<
        spr_params.radius_max << ")" << endl;
    loglh = treeinfo.spr_round(spr_params);
    
    // nni round
    nni(treeinfo, nni_params, loglh);

    if(intermediate_trees.size() == 1){
      
      intermediate_trees.emplace_back(treeinfo.tree());
      rfDist->recalculate_rf();
      rf_distance = rfDist->rf(0,1);
        
    } else {

      intermediate_trees.emplace_back(treeinfo.tree());
      intermediate_trees.erase(intermediate_trees.begin());
      assert(intermediate_trees.size() == 2);

      rfDist->recalculate_rf();
      rf_distance = rfDist->rf(0,1);
    
    }

    if (spr_params.radius_min + radius_step < radius_limit)
    {
      spr_params.radius_min += radius_step;
      spr_params.radius_max += radius_step;
    }

    impr = (loglh - old_loglh > _lh_epsilon);

  }
  
  
  if (!skip_intermid_model_opt)
  {

    cm.update_and_write(treeinfo);

    /* optimize model parameters a bit more thoroughly */
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " <<
                                                            interim_modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, interim_modopt_eps);

  }

  // slow spr setup
  iter = 0;
  spr_params.thorough = 1;
  spr_params.radius_min = 1;
  spr_params.radius_max = slow_spr_radius;
  spr_params.ntopol_keep = 20;
  spr_params.subtree_cutoff = _spr_cutoff;
  spr_params.reset_cutoff_info(loglh);

  do
  {
    cm.update_and_write(treeinfo);
    ++iter;
    old_loglh = loglh;

    LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
        " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;
    loglh = treeinfo.spr_round(spr_params);
    nni(treeinfo, nni_params, loglh);
    
    /* optimize ALL branches */
    loglh = treeinfo.optimize_branches(_lh_epsilon, 1);

    impr = (loglh - old_loglh > _lh_epsilon);
    
  } while (impr);
  
  cm.update_and_write(treeinfo);
  LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << final_modopt_eps << ")" << endl;
  loglh = optimize_model(treeinfo, final_modopt_eps);

  cm.update_and_write(treeinfo);

  return loglh;
}

double Optimizer::evaluate(TreeInfo& treeinfo, CheckpointManager& cm)
{
  const double fast_modopt_eps = 10.;

  SearchState local_search_state = cm.search_state();
  auto& search_state = ParallelContext::group_master_thread() ? cm.search_state() : local_search_state;
  ParallelContext::barrier();

  double &loglh = search_state.loglh;

  /* Compute initial LH of the starting tree */
  loglh = treeinfo.loglh();

  CheckpointStep resume_step = search_state.step;
  auto do_step = [&search_state,resume_step](CheckpointStep step) -> bool
      {
        if (step >= resume_step)
        {
          search_state.step = step;
          return true;
        }
        else
          return false;;
      };

  if (do_step(CheckpointStep::brlenOpt))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Initial branch length optimization" << endl;
    loglh = treeinfo.optimize_branches(fast_modopt_eps, 1);
  }

  /* Model optimization */
  if (do_step(CheckpointStep::modOpt1))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << _lh_epsilon << ")" << endl;
    loglh = optimize_model(treeinfo);
  }

  if (do_step(CheckpointStep::finish))
    cm.update_and_write(treeinfo);

  return loglh;
}

double Optimizer::convergence_rate(CheckpointManager& cm, double test_loglh){
  
  double retval;

  if (cm.best_loglh() == -INFINITY){
    retval = -INFINITY;
  } else {
    if(test_loglh > cm.best_loglh()) retval = 0;
    else {
      retval = (cm.best_loglh() - test_loglh) / fabs(cm.best_loglh());
    }
  }

  return retval;
}

bool Optimizer::first_search_done(CheckpointManager& cm){
  return (cm.best_loglh() != -INFINITY);
}

bool Optimizer::converged(CheckpointManager& cm, double test_loglh, double epsilon){
  if(first_search_done(cm)){
    return convergence_rate(cm,test_loglh) < epsilon ? true : false;
  } 
  else return false;
}

int Optimizer::adaptive_slow_spr_radius(double difficulty){
  if (difficulty <= 0.5){
    return (int) (50*difficulty + 5);
  } else {
    return (int) (-50*difficulty + 55);
  }
}
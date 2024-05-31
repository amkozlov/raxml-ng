#include "Optimizer.hpp"
#include "topology/RFDistCalculator.hpp"
#include "adaptive/StoppingCriterion.hpp"

using namespace std;

Optimizer::Optimizer (const Options &opts) :
    _lh_epsilon(opts.lh_epsilon), _lh_epsilon_brlen_triplet(opts.lh_epsilon_brlen_triplet), 
    _spr_radius(opts.spr_radius), _spr_cutoff(opts.spr_cutoff), 
    _nni_epsilon(opts.nni_epsilon), _nni_tolerance(opts.nni_tolerance), 
    _stopping_criterion(opts.stopping_rule), _modified_version(opts.modified_version)
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

void Optimizer::nni(TreeInfo& treeinfo, nni_round_params& nni_params, double& loglh)
{
  // nni round
  LOG_PROGRESS(loglh) << "NNI round tolerance = " <<  nni_params.tolerance << ", epsilon = " << nni_params.lh_epsilon << endl;
  loglh = treeinfo.nni_round(nni_params);
}

double Optimizer::optimize_topology(TreeInfo& treeinfo, CheckpointManager& cm)
{
  if(call_modified_version()) return optimize_topology_modified(treeinfo, cm);

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
  spr_params.total_moves = nullptr;
  spr_params.increasing_moves = nullptr;

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

    if (do_step(CheckpointStep::radiusDetectOrNNI))
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

double Optimizer::optimize_topology_adaptive(TreeInfo& treeinfo, CheckpointManager& cm)
{
  // TODO: connect the command line arguments for nni-epsilon and nni-tolerance with nni_params.lh_epsilon and 
  // nni_params.tolerance
  
  if(call_modified_version()) return optimize_topology_modified(treeinfo, cm);

  const double fast_modopt_eps = 10.;
  const double interim_modopt_eps = 3.;
  const double final_modopt_eps = 0.1;

  SearchState local_search_state = cm.search_state();
  auto& search_state = ParallelContext::group_master_thread() ? cm.search_state() : local_search_state;
  ParallelContext::barrier();

  /* set references such that we can work directly with checkpoint values */
  double &loglh = search_state.loglh;
  int& iter = search_state.iteration;

  // spr round - basics
  spr_round_params& spr_params = search_state.spr_params;

  // spr parameters - basics
  spr_params.lh_epsilon_brlen_full = _lh_epsilon;
  spr_params.lh_epsilon_brlen_triplet = _lh_epsilon_brlen_triplet;
  spr_params.total_moves = nullptr;
  spr_params.increasing_moves = nullptr;
  

  // nni round - basics
  nni_round_params& nni_params = search_state.nni_params;
  nni_params.tolerance = _nni_tolerance;
  nni_params.lh_epsilon = _nni_epsilon;

  double difficulty = cm.checkp_file().pythia_score;
  bool easy_or_difficult = (difficulty <= 0.3) || (difficulty >= 0.7);

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

  /* Compute initial LH of the starting tree */
  loglh = treeinfo.loglh();

  /* Initial branch-length model optimization */
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
  const int radius_limit = difficulty != -1 ? 
                      min(spr_radius_limit_adaptive(difficulty), (int) treeinfo.pll_treeinfo().tip_count - 3) :
                      min(20, (int) treeinfo.pll_treeinfo().tip_count - 3 );
  
  int radius_step = difficulty != -1 ? spr_radius_step_adaptive(radius_limit) : 5;
  double old_loglh;
  bool impr = true;
  double impr_perc = 1;

  // If the dataset is "easy" or "difficult", start with an NNI round
  if (do_step(CheckpointStep::radiusDetectOrNNI))
  {
    cm.update_and_write(treeinfo);
    
    if(iter == 0)
    {
      if (easy_or_difficult)
        nni(treeinfo, nni_params, loglh);
      
      spr_params.thorough = 0;
      spr_params.radius_min = 1;
      spr_params.radius_max = radius_step;
      spr_params.ntopol_keep = 0;
      spr_params.subtree_cutoff = 0.;
    }

    /* Fast SPR-NNI rounds */
    while(impr)
    {
      cm.update_and_write(treeinfo);
      ++iter;
      old_loglh = loglh;
      
      // spr round
      LOG_PROGRESS(loglh) << "SPR round " << iter << " (radius: " <<
          spr_params.radius_max << ")" << endl;
      loglh = treeinfo.spr_round(spr_params);
      
      // nni round
      if (spr_params.radius_max > radius_step)
        nni(treeinfo, nni_params, loglh);

      impr_perc = (loglh - old_loglh) / fabs(loglh);
      impr = (loglh - old_loglh > _lh_epsilon);

      if (impr_perc <= 0.01 && (spr_params.radius_min + radius_step < radius_limit))
      {
        spr_params.radius_min += radius_step;
        spr_params.radius_max += radius_step;
      }     
    }
  }
  
  // + model parameter optimization
  if (do_step(CheckpointStep::modOpt2))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << fast_modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, fast_modopt_eps);

    /* reset iteration counter for fast SPRs */
    iter = 0;

    /* initialize search params */
    spr_params.thorough = 0;
    spr_params.radius_min = 1;
    spr_params.radius_max = radius_limit;
    spr_params.ntopol_keep = 20;
    spr_params.subtree_cutoff = _spr_cutoff;
    spr_params.reset_cutoff_info(loglh);
  }

  // setting up fast SPR parameters
  if(do_step(CheckpointStep::fastSPR))
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

      impr = (loglh - old_loglh > _lh_epsilon);
    }
    while (impr);
  }
  
  if (do_step(CheckpointStep::modOpt3))
  {
    cm.update_and_write(treeinfo);

    /* optimize model parameters a bit more thoroughly */
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " <<
                                                            interim_modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, interim_modopt_eps);

    // slow spr setup
    iter = 0;
    spr_params.thorough = 1;
    spr_params.radius_min = 1;
    spr_params.radius_max = radius_step;
    spr_params.ntopol_keep = 20;
    spr_params.subtree_cutoff = _spr_cutoff;
    spr_params.reset_cutoff_info(loglh);
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
      
      if (spr_params.radius_min > radius_step)
        nni(treeinfo, nni_params, loglh);

      /* optimize ALL branches */
      loglh = treeinfo.optimize_branches(_lh_epsilon, 1);
      
      impr = (loglh - old_loglh > _lh_epsilon);
      
      if (!impr)
      {
        /* no improvement in thorough mode: set min radius to old max,
         * and increase max radius by the step */
        spr_params.radius_min = spr_params.radius_max + 1;
        spr_params.radius_max += radius_step;
      }
    }
    while (spr_params.radius_min >= 0 && spr_params.radius_min < radius_limit);
  }

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

double Optimizer::optimize_topology_modified(TreeInfo& treeinfo, CheckpointManager& cm){

  // delete
  //int delete_file_counter = 1;
  //std::string delete_file = "../persite_lnl_";
  
  assert(_modified_version || criterion != nullptr);

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

  unsigned long int total_moves = 0, increasing_moves = 0;
  spr_params.total_moves = (criterion && criterion->multi_test_correction()) ? &total_moves : nullptr;
  spr_params.increasing_moves = (criterion && criterion->multi_test_correction()) ? &increasing_moves : nullptr;
  
  bool use_kh_like = (criterion) ? criterion->kh_test() : false;

  vector<double *> persite_lnl, persite_lnl_new;
  
  if(criterion){

    persite_lnl = criterion->get_persite_lnl(ParallelContext::local_group_id(), ParallelContext::local_thread_id()); 
    if (use_kh_like) 
      persite_lnl_new = criterion->get_persite_lnl_new(ParallelContext::local_group_id(),  ParallelContext::local_thread_id()); 
  
  }
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
    loglh = treeinfo.optimize_branches(interim_modopt_eps, 1);
  }

  /* Initial fast model optimization */
  if (do_step(CheckpointStep::modOpt1))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << interim_modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, interim_modopt_eps);

    /* start spr rounds from the beginning */
    iter = 0;
  }

  string approach;
  if(criterion){
    switch (_stopping_criterion)
    {
      case 0:
        approach = "Sampling Noise RELL";
        break;
      
      case 1:
        approach = "Sampling Noise Normal";
        break;

      case 2:
        approach = "KH";
        break;
      
      case 3:
        approach = "KH - multiple testing correction";
        break;
      
      default:
        break;
    }
    
    LOG_PROGRESS(loglh) << "Stopping criterion: " << approach << " apporach." << endl;
  
  } else {

    LOG_PROGRESS(loglh) << "Modified version called" << endl;  
  }

  
  
  // fix that later
  if(_stopping_criterion == 0 || _stopping_criterion == 1){
    
    criterion->compute_loglh(treeinfo, persite_lnl, true);
    
    if(ParallelContext::group_master_thread()) 
      criterion->run_test();
      
    ParallelContext::barrier();

    _lh_epsilon = criterion->get_epsilon(ParallelContext::group_id());
    LOG_PROGRESS(loglh) << approach << " apporach. Epsilon = " << _lh_epsilon << endl;
  }

  best_fast_radius = _spr_radius > 0 ?  _spr_radius : 10; // maybe change that idk

  LOG_PROGRESS(loglh) << "SPR radius for FAST iterations: " << best_fast_radius << endl;

  if (do_step(CheckpointStep::modOpt2))
  {
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
  bool impr = true;

  if (do_step(CheckpointStep::fastSPR))
  {
    double epsilon;
    do
    { 
      epsilon =_lh_epsilon ;
      
      cm.update_and_write(treeinfo);
      ++iter;

      if(use_kh_like) criterion->compute_loglh(treeinfo, persite_lnl, true);

      old_loglh = loglh;
      LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
          " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;
      
      loglh = treeinfo.spr_round(spr_params);

      /* optimize ALL branches */
      loglh = treeinfo.optimize_branches(_lh_epsilon, 1);

      if(use_kh_like){
        
        criterion->compute_loglh(treeinfo,persite_lnl_new, false);
        
        if(criterion->multi_test_correction()) 
          criterion->set_increasing_moves((*spr_params.increasing_moves));

        if(ParallelContext::group_master_thread())
          criterion->run_test();
          
        ParallelContext::barrier();

        if(spr_params.increasing_moves){
          
          double p_value = criterion->get_pvalue(ParallelContext::group_id());
          epsilon = criterion->get_epsilon(ParallelContext::group_id()); 
          LOG_PROGRESS(loglh) << "KH-like multiple-testing epsilon = " << epsilon << endl;
          impr = ((loglh - old_loglh > epsilon) && (p_value < 1));
          
        } else {

          epsilon = criterion->get_epsilon(ParallelContext::group_id());
          LOG_PROGRESS(loglh) << "KH-like criterion epsilon = " << epsilon << endl;
          impr = (loglh - old_loglh > epsilon);
        }
      } else {

        impr = (loglh - old_loglh > epsilon);
      }
    }
    while (impr);
  }

  if (do_step(CheckpointStep::modOpt3))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << interim_modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, interim_modopt_eps);

    /* init slow SPRs */
    spr_params.thorough = 1;
    spr_params.radius_min = 1;
    spr_params.radius_max = best_fast_radius;   
    iter = 0;
  }
  
  if (do_step(CheckpointStep::slowSPR))
  {
    double epsilon;

    do
    {
      epsilon = _lh_epsilon ;

      cm.update_and_write(treeinfo);
      ++iter;
      old_loglh = loglh;

      if(use_kh_like) criterion->compute_loglh(treeinfo,persite_lnl, true);

      LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
          " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;

      loglh = treeinfo.spr_round(spr_params);
      loglh = treeinfo.optimize_branches(_lh_epsilon, 1);

      if(use_kh_like){
        
        criterion->compute_loglh(treeinfo, persite_lnl_new, false);

        if(criterion->multi_test_correction()) 
          criterion->set_increasing_moves((*spr_params.increasing_moves));

        if(ParallelContext::group_master_thread())
          criterion->run_test();
          
        ParallelContext::barrier();

        if(spr_params.increasing_moves){
          
          double p_value = criterion->get_pvalue(ParallelContext::group_id());
          epsilon = criterion->get_epsilon(ParallelContext::group_id()); 
          LOG_PROGRESS(loglh) << "KH-like multiple-testing epsilon = " << epsilon << endl;
          impr = ((loglh - old_loglh > epsilon) && (p_value < 1));

        } else {

          epsilon = criterion->get_epsilon(ParallelContext::group_id());
          LOG_PROGRESS(loglh) << "KH-like criterion epsilon = " << epsilon << endl;
          impr = (loglh - old_loglh > epsilon);
        }
      } else {

        impr = (loglh - old_loglh > epsilon);
      }
    }
    while (impr);
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

int Optimizer::spr_radius_limit_adaptive(double difficulty){
  if (difficulty <= 0.5){
    return (int) (30*difficulty + 5);
  } else {
    return (int) (-30*difficulty + 35);
  }
}

int Optimizer::spr_radius_step_adaptive(int spr_radius_max){

  int radius_step = 0;

  if(spr_radius_max <= 7){
    radius_step = spr_radius_max;
  } else if (spr_radius_max <= 13){
    radius_step = (int) (spr_radius_max / 2);
  } else {
    radius_step = (int) (spr_radius_max / 3);
  }

  return radius_step;
}
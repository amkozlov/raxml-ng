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
  LOG_PROGRESS(loglh) << "NNI round tolerance = " <<  nni_params.tolerance 
                      << ", bl-opt epsilon = " << nni_params.lh_epsilon << endl;
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

double Optimizer::optimize_topology_adaptive(TreeInfo& treeinfo, CheckpointManager& cm)
{
  // TODO: connect the command line arguments for nni-epsilon and nni-tolerance with nni_params.lh_epsilon and 
  // nni_params.tolerance
  
  if(call_modified_version()) return optimize_topology_modified(treeinfo, cm);

  const double fast_modopt_eps = 10.;
  const double interim_modopt_eps = 3.;
  const double final_modopt_eps = 0.1;
  
  assert(criterion && criterion->multi_test_correction() && criterion->kh_test());
  
  SearchState local_search_state = cm.search_state();
  auto& search_state = ParallelContext::group_master_thread() ? cm.search_state() : local_search_state;
  ParallelContext::barrier();

  /* set references such that we can work directly with checkpoint values */
  double &loglh = search_state.loglh;
  int& iter = search_state.iteration;
  int& best_fast_radius = search_state.fast_spr_radius;

  // spr round - basics
  spr_round_params& spr_params = search_state.spr_params;
  spr_params.lh_epsilon_brlen_full = _lh_epsilon;
  spr_params.lh_epsilon_brlen_triplet = _lh_epsilon_brlen_triplet;
  
  unsigned long int total_moves = 0, increasing_moves = 0;
  spr_params.total_moves = &total_moves;
  spr_params.increasing_moves = &increasing_moves;
  
  vector<double *> persite_lnl = 
    criterion->get_persite_lnl(ParallelContext::group_id(), ParallelContext::local_thread_id());
  vector<double *> persite_lnl_new = 
    criterion->get_persite_lnl_new(ParallelContext::group_id(),  ParallelContext::local_thread_id());
  
  // nni round - basics
  nni_round_params& nni_params = search_state.nni_params;
  nni_params.tolerance = _nni_tolerance;
  nni_params.lh_epsilon = _nni_epsilon;

  double difficulty = cm.checkp_file().pythia_score;

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

  // Determine FAST and SLOW SPR maximum radius
  best_fast_radius = difficulty != -1 ? 
              min(fast_spr_radius_adaptive(difficulty), (int) treeinfo.pll_treeinfo().tip_count - 3) :
              min(10, (int) treeinfo.pll_treeinfo().tip_count - 3 );
  
  // in case the user has specified their own values
  if(_spr_radius > 0){
    best_fast_radius = _spr_radius;
    LOG_PROGRESS(loglh) << "User specified SPR radius for FAST/SLOW iterations: " << best_fast_radius << endl;
  }

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
    spr_params.thorough = 0;
    spr_params.radius_min = 1;
    spr_params.radius_max = best_fast_radius;
    spr_params.ntopol_keep = 20;
    spr_params.subtree_cutoff = _spr_cutoff;
    spr_params.reset_cutoff_info(loglh);
  }

  double old_loglh;
  bool impr = true;
  double epsilon;

  if (do_step(CheckpointStep::fastSPR))
  {
    do
    {
      epsilon = _lh_epsilon;

      cm.update_and_write(treeinfo);
      ++iter;

      /* Computing the per-site loglh vector before the SPR round */
      criterion->compute_loglh(treeinfo, persite_lnl, true);

      old_loglh = loglh;
      LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
          " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;
      
      loglh = treeinfo.spr_round(spr_params);

      /* Computing the per-site loglh vector after the SPR round */
      criterion->compute_loglh(treeinfo,persite_lnl_new, false);
      criterion->set_increasing_moves((*spr_params.increasing_moves));

      /* KH test with multiple testing correction */
      if(ParallelContext::group_master_thread())
        criterion->run_test();
        
      ParallelContext::barrier();

      double p_value = criterion->get_pvalue(ParallelContext::group_id());
      epsilon = criterion->get_epsilon(ParallelContext::group_id()); 
      LOG_DEBUG << "KH-like multiple-testing epsilon = " << epsilon << endl;
      impr = ((loglh - old_loglh > epsilon) && (p_value < 1)); 
    
    } while (impr);
  }
  
  if (do_step(CheckpointStep::modOpt3))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << interim_modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, interim_modopt_eps);

    /* init slow SPRs */
    spr_params.thorough = 1;
    iter = 0;
  }
  
  if (do_step(CheckpointStep::slowSPR))
  {
    if(iter == 0)
      nni(treeinfo, nni_params, loglh);

    do
    {
      epsilon = _lh_epsilon ;

      cm.update_and_write(treeinfo);
      ++iter;
      old_loglh = loglh;

      /* Computing the per-site loglh vector before the SPR round */
      criterion->compute_loglh(treeinfo, persite_lnl, true);

      LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
          " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;

      loglh = treeinfo.spr_round(spr_params);
      
      /* Computing the per-site loglh vector after the SPR round */
      criterion->compute_loglh(treeinfo, persite_lnl_new, false);

      /* KH test with multiple testing correction */
      if(criterion->multi_test_correction()) 
        criterion->set_increasing_moves((*spr_params.increasing_moves));

      if(ParallelContext::group_master_thread())
        criterion->run_test();
        
      ParallelContext::barrier();

      double p_value = criterion->get_pvalue(ParallelContext::group_id());
      epsilon = criterion->get_epsilon(ParallelContext::group_id()); 
      LOG_DEBUG << "KH-like multiple-testing epsilon = " << epsilon << endl;
      impr = ((loglh - old_loglh > epsilon) && (p_value < 1));

    } while (impr);
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
  best_fast_radius = 10;
  
  double br_len_epsilon = _lh_epsilon;
  spr_params.lh_epsilon_brlen_full = _lh_epsilon;
  spr_params.lh_epsilon_brlen_triplet = _lh_epsilon_brlen_triplet;

  unsigned long int total_moves = 0, increasing_moves = 0;
  spr_params.total_moves = (criterion && criterion->multi_test_correction()) ? &total_moves : nullptr;
  spr_params.increasing_moves = (criterion && criterion->multi_test_correction()) ? &increasing_moves : nullptr;
  
  bool use_kh_like = (criterion) ? criterion->kh_test() : false;

  vector<double *> persite_lnl, persite_lnl_new;
  
  if(criterion){
    persite_lnl = criterion->get_persite_lnl(ParallelContext::group_id(), ParallelContext::local_thread_id()); 
    if (use_kh_like) 
      persite_lnl_new = criterion->get_persite_lnl_new(ParallelContext::group_id(),  ParallelContext::local_thread_id()); 
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

  /* Print statement about which stopping criterion is used */
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
    
    LOG_PROGRESS(loglh) << "sRAxML-NG: Stopping criterion: " << approach << " apporach." << endl;

    if(resume_step > CheckpointStep::modOpt1){
      {
        _lh_epsilon = cm.get_epsilon();
        LOG_PROGRESS(loglh) << approach << " apporach. Epsilon = " << _lh_epsilon << endl;
      }
    }
    
  } else {

    LOG_PROGRESS(loglh) << "Simplified version (sRAxML-NG) called" << endl;  
  }

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
    spr_params.thorough = 0;
    spr_params.radius_min = 1;
    spr_params.radius_max = best_fast_radius;
    spr_params.ntopol_keep = 20;
    spr_params.subtree_cutoff = _spr_cutoff;
    spr_params.reset_cutoff_info(loglh);

    /* If the selected stopping criterion is either SN-Normal or SN-RELL,
      we have to compute the _lh_epsilon here */
    if(_stopping_criterion == 0 || _stopping_criterion == 1){

      criterion->compute_loglh(treeinfo, persite_lnl, true);
      
      if(ParallelContext::group_master_thread()) 
        criterion->run_test();
        
      ParallelContext::barrier();

      _lh_epsilon = criterion->get_epsilon(ParallelContext::group_id());
      LOG_PROGRESS(loglh) << approach << " apporach. Epsilon = " << _lh_epsilon << endl;

      if(ParallelContext::group_master_thread())
        cm.set_epsilon(_lh_epsilon);
      
      ParallelContext::barrier();
    }
  }

  double old_loglh, epsilon;
  bool impr = true;
  
  if(_spr_radius > 0){
    best_fast_radius = _spr_radius; // maybe change that idk
    spr_params.radius_max = best_fast_radius;
    LOG_PROGRESS(loglh) << "SPR radius for FAST/SLOW iterations: " << best_fast_radius << endl;
  }
  if (do_step(CheckpointStep::fastSPR))
  {
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
      loglh = treeinfo.optimize_branches(br_len_epsilon, 1);

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
    do
    {
      epsilon = _lh_epsilon ;

      cm.update_and_write(treeinfo);
      ++iter;
      old_loglh = loglh;

      if(use_kh_like) criterion->compute_loglh(treeinfo, persite_lnl, true);

      LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
          " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;

      loglh = treeinfo.spr_round(spr_params);
      loglh = treeinfo.optimize_branches(br_len_epsilon, 1);

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

int Optimizer::fast_spr_radius_adaptive(double difficulty){
  if(difficulty < 0) {
    return 10;
  } else if (difficulty < 0.4) {
    return (int) ( 12.5*difficulty + 5);
  } else if (difficulty <= 0.6){
    return 10;
  } else {
    return (int) ((-12.5)*difficulty + 17.5);
  }
}
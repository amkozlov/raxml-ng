#include "Optimizer.hpp"
#include "topology/RFDistCalculator.hpp"
#include "adaptive/StoppingCriterion.hpp"

using namespace std;

Optimizer::Optimizer (const Options &opts, bool rapid_bs /* = false */) :
    _topology_opt_method(opts.topology_opt_method),
    _lh_epsilon(opts.lh_epsilon), _lh_epsilon_brlen_triplet(opts.lh_epsilon_brlen_triplet), 
    _spr_radius(opts.spr_radius), _spr_cutoff(opts.spr_cutoff), _rstate(nullptr),
    _nni_epsilon(opts.nni_epsilon), _nni_tolerance(opts.nni_tolerance), 
    _stopping_rule(opts.stopping_rule)
{
  _spr_ntopol_keep = rapid_bs ? 5 : 20;
  if (rapid_bs)
  {
    _spr_cutoff = 0.5;
    _rstate = corax_random_create(opts.random_seed + ParallelContext::group_id());
  }
}

Optimizer::~Optimizer ()
{
  corax_random_destroy(_rstate);
}

void Optimizer::disable_stopping_rule(){

  _stopping_rule = StoppingRule::none; 
  _criterion = nullptr;
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
  switch(_topology_opt_method)
  {
    case TopologyOptMethod::classic:
      return optimize_topology_standard(treeinfo, cm);
      break;
    case TopologyOptMethod::adaptive:
      if (cm.checkp_file().pythia_score >= 0.)
        return optimize_topology_adaptive(treeinfo, cm);
      else
        return optimize_topology_standard(treeinfo, cm);
      break;
    case TopologyOptMethod::fast:
      if (cm.checkp_file().pythia_score >= 0.)
        return optimize_topology_adaptive(treeinfo, cm);
      else
        return optimize_topology_standard(treeinfo, cm);
      break;
    case TopologyOptMethod::rapidBS:
      return optimize_topology_rbs(treeinfo, cm);
      break;
    case TopologyOptMethod::nniRound:
      return optimize_topology_nni(treeinfo, cm);
      break;
    case TopologyOptMethod::simplified:
      return optimize_topology_adaptive(treeinfo, cm);
      break;
    case TopologyOptMethod::none:
      return evaluate(treeinfo, cm);
      break;
    default:
      assert(0);
  }
}

double Optimizer::optimize_topology_standard(TreeInfo& treeinfo, CheckpointManager& cm)
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
    spr_params.ntopol_keep = _spr_ntopol_keep;
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

double Optimizer::optimize_topology_adaptive(TreeInfo& treeinfo, CheckpointManager& cm){
  
  const double fast_modopt_eps = 10.;
  const double interim_modopt_eps = 3.;
  const double final_modopt_eps = 0.1;

  SearchState local_search_state = cm.search_state();
  auto& search_state = ParallelContext::group_master_thread() ? cm.search_state() : local_search_state;
  ParallelContext::barrier();

  /* set references such that we can work directly with checkpoint values */
  double &loglh = search_state.loglh;
  int& iter = search_state.iteration;
  int& fast_spr_radius = search_state.fast_spr_radius;
  int& slow_spr_radius = search_state.slow_spr_radius;

  // spr round - basics
  spr_round_params& spr_params = search_state.spr_params;
  spr_params.lh_epsilon_brlen_full = _lh_epsilon;
  spr_params.lh_epsilon_brlen_triplet = _lh_epsilon_brlen_triplet;
  
  double br_len_epsilon = _lh_epsilon;
  spr_params.lh_epsilon_brlen_full = _lh_epsilon;
  spr_params.lh_epsilon_brlen_triplet = _lh_epsilon_brlen_triplet;

  /* These parameters are only used in adaptive version */
  const int radius_limit = (int) treeinfo.pll_treeinfo().tip_count - 3;
  
  /* KH multiple testing criterion - init */
  unsigned long int total_moves = 0, increasing_moves = 0;
  spr_params.total_moves = (_stopping_rule == StoppingRule::kh_mult) ? &total_moves : nullptr;
  spr_params.increasing_moves = (_stopping_rule == StoppingRule::kh_mult) ? &increasing_moves : nullptr;
  
  // nni round - basics
  nni_round_params& nni_params = search_state.nni_params;
  nni_params.tolerance = _nni_tolerance;
  nni_params.lh_epsilon = _nni_epsilon;

  double difficulty = cm.checkp_file().pythia_score;
  bool use_kh_test = (_stopping_rule == StoppingRule::kh || _stopping_rule == StoppingRule::kh_mult);
  vector<double *> persite_lnl, persite_lnl_new;

  if(_criterion){
    persite_lnl = _criterion->get_persite_lnl(ParallelContext::group_id(), ParallelContext::local_thread_id()); 
    if (use_kh_test) 
      persite_lnl_new = _criterion->get_persite_lnl_new(ParallelContext::group_id(),  ParallelContext::local_thread_id()); 
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
  string heuristic = (_topology_opt_method == TopologyOptMethod:: adaptive) ?
                      "Adaptive RAxML-NG" :
                      "simplified RAxML-NG (sRAxML-NG)";

  if(_stopping_rule != StoppingRule::none){
    
    switch (_stopping_rule)
    {
      case StoppingRule::sn_rell:
        approach = "Sampling Noise RELL";
        break;
      
      case StoppingRule::sn_normal:
        approach = "Sampling Noise Normal";
        break;

      case StoppingRule::kh:
        approach = "KH";
        break;
      
      case StoppingRule::kh_mult:
        approach = "KH - multiple testing correction";
        break;
      
      default:
        break;
    }
    
    LOG_PROGRESS(loglh) << heuristic << ": Stopping criterion: " << approach << " apporach." << endl;

    /* This is for the SN-based apporaches, since in the KH-based methods the epsilon is recalculated */
    if(resume_step > CheckpointStep::modOpt1) _lh_epsilon = cm.get_epsilon();
    
  } else {

    LOG_PROGRESS(loglh) << heuristic << ": Stopping criteria off, epsilon = "<< _lh_epsilon << endl;  
  }

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

    /* Set FAST SPR radius
      sRAxML-NG: 10
      adaptive: 3*
      fast: 2*
    */
    fast_spr_radius = difficulty >= 0. ? 
        min(3 * adaptive_radius(difficulty), 25) : 10;
    
    if(difficulty >= 0. && _topology_opt_method == TopologyOptMethod::fast)
      fast_spr_radius = 2*adaptive_radius(difficulty);

    // in case the user has specified their own values
    if(_spr_radius > 0){
      fast_spr_radius =_spr_radius;
      LOG_PROGRESS(loglh) << "User specified SPR radius for FAST/SLOW iterations: " << _spr_radius << endl;
    }

    fast_spr_radius = min(fast_spr_radius, radius_limit);

    /* start spr rounds from the beginning */
    iter = 0;
    spr_params.thorough = 0;
    spr_params.radius_min = 1;
    spr_params.radius_max = fast_spr_radius;
    spr_params.ntopol_keep = _spr_ntopol_keep;
    spr_params.subtree_cutoff = _spr_cutoff;
    spr_params.reset_cutoff_info(loglh, _topology_opt_method == TopologyOptMethod::adaptive);

    /* If the selected stopping criterion is either SN-Normal or SN-RELL,
      we have to compute the _lh_epsilon here */
    if(_stopping_rule == StoppingRule::sn_rell || _stopping_rule == StoppingRule::sn_normal){

      _criterion->compute_loglh(treeinfo, persite_lnl, true);
      
      if(ParallelContext::group_master_thread()) 
        _criterion->run_test();
        
      ParallelContext::barrier();

      _lh_epsilon = _criterion->get_epsilon(ParallelContext::group_id());
      //LOG_PROGRESS(loglh) << approach << " apporach. Epsilon = " << _lh_epsilon << endl;
      LOG_DEBUG << approach << " apporach. Epsilon = " << _lh_epsilon << endl;

      if(ParallelContext::group_master_thread())
        cm.set_epsilon(_lh_epsilon);
      
      ParallelContext::barrier();
    }
  }

  double old_loglh, epsilon;
  bool impr = true;
  
  if (do_step(CheckpointStep::fastSPR))
  {
    do
    { 
      epsilon = _lh_epsilon ;
      
      cm.update_and_write(treeinfo);
      ++iter;

      if(use_kh_test)
      {
        _criterion->compute_loglh(treeinfo, persite_lnl, true);
        
        if(spr_params.increasing_moves)
        {
          *(spr_params.increasing_moves) = 0;
          *(spr_params.total_moves) = 0;
        }
      }

      old_loglh = loglh;
      LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
          " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;
      
      loglh = treeinfo.spr_round(spr_params);

      /* optimize ALL branches */
      loglh = treeinfo.optimize_branches(br_len_epsilon, 1);

      if(use_kh_test){
        
        _criterion->compute_loglh(treeinfo,persite_lnl_new, false);
        
        if(_criterion->multi_test_correction()) 
          _criterion->set_increasing_moves((*spr_params.increasing_moves));

        if(ParallelContext::group_master_thread())
          _criterion->run_test();
          
        ParallelContext::barrier();

        if(spr_params.increasing_moves){
          
          double p_value = _criterion->get_pvalue(ParallelContext::group_id());
          epsilon = _criterion->get_epsilon(ParallelContext::group_id()); 
          LOG_DEBUG << "KH multiple-testing epsilon = " << epsilon << endl;
          impr = ((loglh - old_loglh > epsilon) && (p_value < 1));

        } else {

          epsilon = _criterion->get_epsilon(ParallelContext::group_id());
          LOG_DEBUG << "KH criterion epsilon = " << epsilon << endl;
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

    /* Set SLOW SPR radius */
    slow_spr_radius = difficulty >= 0. ? 
        min(adaptive_radius(difficulty),7) : 10;
    
    if(difficulty >= 0. && _topology_opt_method == TopologyOptMethod::fast)
      slow_spr_radius = adaptive_radius(difficulty);
    
    // in case the user has specified their own values
    if(_spr_radius > 0)
      slow_spr_radius =_spr_radius;

    slow_spr_radius = min(slow_spr_radius, radius_limit);
    
    /* init slow SPRs */
    spr_params.thorough = 1;
    spr_params.radius_min = 1;
    spr_params.radius_max = slow_spr_radius;
    spr_params.reset_cutoff_info(loglh, _topology_opt_method == TopologyOptMethod::adaptive);
    iter = 0;
  }

  bool repeat = true;
  int slow_spr_limit = min(2*slow_spr_radius, radius_limit);
  
  if (do_step(CheckpointStep::slowSPR))
  {
    // NNI used only in fast mode
    if(iter == 0 && _topology_opt_method == TopologyOptMethod::fast)
      nni(treeinfo, nni_params, loglh);

    do
    {
      epsilon = _lh_epsilon;

      cm.update_and_write(treeinfo);
      ++iter;
      old_loglh = loglh;

      if(use_kh_test)
      {
        _criterion->compute_loglh(treeinfo, persite_lnl, true);
        
        if(spr_params.increasing_moves)
        {
          *(spr_params.increasing_moves) = 0;
          *(spr_params.total_moves) = 0;
        }
      }

      LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
          " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;
      
      loglh = treeinfo.spr_round(spr_params);
      loglh = treeinfo.optimize_branches(br_len_epsilon, 1);

      if(use_kh_test){
        
        _criterion->compute_loglh(treeinfo, persite_lnl_new, false);

        if(_criterion->multi_test_correction()) 
          _criterion->set_increasing_moves((*spr_params.increasing_moves));

        if(ParallelContext::group_master_thread())
          _criterion->run_test();
          
        ParallelContext::barrier();

        if(spr_params.increasing_moves){
          
          double p_value = _criterion->get_pvalue(ParallelContext::group_id());
          epsilon = _criterion->get_epsilon(ParallelContext::group_id()); 
          LOG_DEBUG << "KH multiple-testing epsilon = " << epsilon << endl;
          impr = ((loglh - old_loglh > epsilon) && (p_value < 1));

        } else {

          epsilon = _criterion->get_epsilon(ParallelContext::group_id());
          LOG_DEBUG << "KH criterion epsilon = " << epsilon << endl;
          impr = (loglh - old_loglh > epsilon);
        }
      } else {

        impr = (loglh - old_loglh > epsilon);
      
      }

      if(_topology_opt_method == TopologyOptMethod::adaptive)
      {
        if (impr)
        {
          spr_params.radius_min = 1;
          spr_params.radius_max = slow_spr_radius;
          repeat = true;
        }
        else
        {
          spr_params.radius_min += slow_spr_radius;
          spr_params.radius_max += slow_spr_radius;
          repeat = spr_params.radius_max <= slow_spr_limit ? true : false;
        }
      }
      else
      {
        repeat = impr;
      }
    }
    while (repeat);
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

double Optimizer::optimize_topology_rbs(TreeInfo& treeinfo, CheckpointManager& cm)
{
  const double fast_modopt_eps = 10.;
  const int max_spr_rounds = 2;

  SearchState local_search_state = cm.search_state();
  auto& search_state = ParallelContext::group_master_thread() ? cm.search_state() : local_search_state;
  ParallelContext::barrier();

  /* set references such that we can work directly with checkpoint values */
  double &loglh = search_state.loglh;
  int& iter = search_state.iteration;
  spr_round_params& spr_params = search_state.spr_params;

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
    spr_params.thorough = 1;
    spr_params.radius_min = 1;
    spr_params.radius_max = 5 + corax_random_getint(_rstate, 11);
    spr_params.ntopol_keep = _spr_ntopol_keep;
    spr_params.subtree_cutoff = _spr_cutoff;
    spr_params.reset_cutoff_info(loglh);
  }

  // do SPRs
  double old_loglh;
  bool impr = true;

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

      impr = (loglh - old_loglh > _lh_epsilon);
    }
    while (impr && iter < max_spr_rounds);
  }

  if (do_step(CheckpointStep::finish))
    cm.update_and_write(treeinfo);

  return loglh;
}

double Optimizer::optimize_topology_nni(TreeInfo& treeinfo, CheckpointManager& cm)
{
  const double modopt_eps = _lh_epsilon;

  SearchState local_search_state = cm.search_state();
  auto& search_state = ParallelContext::group_master_thread() ? cm.search_state() : local_search_state;
  ParallelContext::barrier();

  /* set references such that we can work directly with checkpoint values */
  double &loglh = search_state.loglh;

  CheckpointStep resume_step = search_state.step;

  nni_round_params& nni_params = search_state.nni_params;
  nni_params.tolerance = _nni_tolerance;
  nni_params.lh_epsilon = _nni_epsilon;
  nni_params.max_rounds = 10;

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

  /* Initial fast model optimization */
  if (do_step(CheckpointStep::modOpt1))
  {
    cm.update_and_write(treeinfo);
    LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << modopt_eps << ")" << endl;
    loglh = optimize_model(treeinfo, modopt_eps);
  }

  // do NNIs
  if (do_step(CheckpointStep::radiusDetectOrNNI))
  {
    nni(treeinfo, nni_params, loglh);

    /* optimize ALL branches */
    loglh = treeinfo.optimize_branches(_lh_epsilon, 1);
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

int Optimizer::adaptive_radius(double difficulty){
  
  assert (difficulty >= 0);

  if (difficulty < 0.4) {
    return (int) ( 12.5*difficulty + 5);
  } else if (difficulty <= 0.6){
    return 10;
  } else {
    return (int) ((-12.5)*difficulty + 17.5);
  }
}
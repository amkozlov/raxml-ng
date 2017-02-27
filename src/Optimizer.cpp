#include "Optimizer.hpp"

using namespace std;

Optimizer::Optimizer (const Options &opts) : _lh_epsilon(opts.lh_epsilon),
    _spr_radius(opts.spr_radius), _spr_cutoff(opts.spr_cutoff)
{

}

Optimizer::~Optimizer ()
{
  // TODO Auto-generated destructor stub
}

double Optimizer::optimize(TreeInfo& treeinfo, double lh_epsilon)
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
    assert(cur_loglh - new_loglh < -new_loglh * RAXML_DOUBLE_TOLERANCE);

    DBG("Iteration %d: logLH = %f\n", iter_num, new_loglh);
    iter_num++;
  }
  while (new_loglh - cur_loglh > lh_epsilon);

  return new_loglh;
}

double Optimizer::optimize_topology(TreeInfo& treeinfo)
{
  const double fast_modopt_eps = 10.;
  const double interim_modopt_eps = 3.;
  double loglh;

  /* Compute initial LH of the starting tree */
  loglh = treeinfo.loglh();

  LOG_PROGRESS(loglh) << "Initial branch length optimization" << endl;
  loglh = treeinfo.optimize_branches(fast_modopt_eps, 1);

  /* Initial fast model optimization */
  LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << fast_modopt_eps << ")" << endl;
  loglh = optimize(treeinfo, fast_modopt_eps);
//  print_model_params(treeinfo, useropt);

  // do SPRs
  const int radius_limit = min(22, (int) treeinfo.pll_treeinfo().tip_count - 3 );
  const int radius_step = 5;

//  treeinfo->counter = 0;

  int iter = 0;
  int best_fast_radius;

  if (_spr_radius > 0)
    best_fast_radius = _spr_radius;
  else
  {
    /* auto detect best radius for fast SPRs */

    spr_round_params params;
    params.thorough = 0;
    params.radius_min = 1;
    best_fast_radius = params.radius_max = 5;
    params.ntopol_keep = 0;
    params.subtree_cutoff = 0.;

    double best_loglh = loglh;
    while (params.radius_min < radius_limit)
    {
      ++iter;
      LOG_PROGRESS(best_loglh) << "AUTODETECT spr round " << iter << " (radius: " <<
                     params.radius_max << ")" << endl;
      loglh = treeinfo.spr_round(params);

      if (!loglh)
        throw runtime_error("ERROR in SPR round: " + string(pll_errmsg));

      if (loglh - best_loglh > 0.1)
      {
        /* LH improved, try to increase the radius */
        best_fast_radius = params.radius_max;
        params.radius_min += radius_step;
        params.radius_max += radius_step;
        best_loglh = loglh;
      }
      else
        break;
    }

  }

  LOG_PROGRESS(loglh) << "SPR radius for FAST iterations: " << best_fast_radius << " (" <<
                 (_spr_radius > 0 ? "user-specified" : "autodetect") << ")" << endl;

  /* optimize model parameters a bit more thoroughly */
  LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " <<
                                                          interim_modopt_eps << ")" << endl;
  loglh = optimize(treeinfo, interim_modopt_eps);

  DBG("\nLogLikelihood after intermediate model optimization (eps = %.1f): %f\n",
      interim_modopt_eps, loglh);
//  print_model_params(treeinfo, useropt);

  /* initialize search params */
  spr_round_params spr_params;
  spr_params.thorough = 0;
  spr_params.radius_min = 1;
  spr_params.radius_max = best_fast_radius;
  spr_params.ntopol_keep = 20;
  spr_params.subtree_cutoff = _spr_cutoff;
  spr_params.reset_cutoff_info(loglh);

  double old_loglh, new_loglh = loglh;
  iter = 0;
  do
    {
      ++iter;
      old_loglh = new_loglh;
      LOG_PROGRESS(old_loglh) << (spr_params.thorough ? "SLOW" : "FAST") <<
          " spr round " << iter << " (radius: " << spr_params.radius_max << ")" << endl;
      loglh = treeinfo.spr_round(spr_params);

      /* optimize ALL branches */
      new_loglh = treeinfo.optimize_branches(_lh_epsilon, 1);

      DBG("\nold/new LogLikelihood after %s round %d: %f %f\n\n",
                 spr_params.thorough ? "SLOW" : "FAST", iter, old_loglh, new_loglh);

//      save_utree_to_file(treeinfo->root, result_fname);

      bool impr = (new_loglh - old_loglh > _lh_epsilon);
      if (impr && spr_params.thorough)
      {
        /* got improvement in thorough mode: reset min radius to 1 */
        spr_params.radius_min = 1;
        /* reset max radius to 5; or maybe better keep old value? */
        spr_params.radius_max = radius_step;
      }
      else if (!impr)
      {
        if (!spr_params.thorough)
        {
          spr_params.thorough = 1;
          spr_params.radius_min = 1;
          spr_params.radius_max = radius_step;
          iter = 0;

          LOG_PROGRESS(new_loglh) << "Model parameter optimization (eps = " << 1.0 << ")" << endl;
          new_loglh = optimize(treeinfo, 1.0);
//          print_model_params(treeinfo, useropt);
          DBG("LogLikelihood after FAST iterations: %f\n", new_loglh);
        }
        else
        {
          /* no improvement in thorough mode: set min radius to old max,
           * and increase max radius by the step */
          spr_params.radius_min = spr_params.radius_max + 1;
          spr_params.radius_max += radius_step;
        }
      }
    }
  while (spr_params.radius_min >= 0 && spr_params.radius_min < radius_limit);

  loglh = new_loglh;

  /* Final thorough model optimization */
  LOG_PROGRESS(loglh) << "Model parameter optimization (eps = " << _lh_epsilon << ")" << endl;
  loglh = optimize(treeinfo, _lh_epsilon);

  return loglh;
}

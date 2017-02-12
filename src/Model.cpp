#include "Model.hpp"

using namespace std;

const vector<int> ALL_MODEL_PARAMS = {PLLMOD_OPT_PARAM_FREQUENCIES, PLLMOD_OPT_PARAM_SUBST_RATES,
                                      PLLMOD_OPT_PARAM_PINV, PLLMOD_OPT_PARAM_ALPHA,
                                      PLLMOD_OPT_PARAM_FREE_RATES, PLLMOD_OPT_PARAM_RATE_WEIGHTS};

const unordered_map<DataType,unsigned int,EnumClassHash>  DATATYPE_STATES { {DataType::dna, 4},
                                                                            {DataType::protein, 20},
                                                                            {DataType::binary, 2},
                                                                            {DataType::diploid10, 10}
                                                                          };

const unordered_map<DataType, const unsigned int *,EnumClassHash>  DATATYPE_MAPS {
  {DataType::dna, pll_map_nt},
  {DataType::protein, pll_map_aa},
  {DataType::binary, pll_map_bin},
  {DataType::diploid10, pll_map_diploid10}
};

Model::Model (DataType data_type, const std::string &model_string) :
    _data_type(data_type), _mix_model(nullptr)
{
  init_from_string(model_string);
}

Model::~Model ()
{
  if (_mix_model)
    pllmod_util_model_mixture_destroy(_mix_model);
}

const unsigned int * Model::charmap() const
{
  return DATATYPE_MAPS.at(_data_type);
}

void Model::init_from_string(const std::string &model_string)
{
  size_t pos = model_string.find_first_of("+");
  const string model_name = pos == string::npos ? model_string : model_string.substr(0, pos);
  const string model_opts = pos == string::npos ? "" : model_string.substr(pos);

  /* guess data type */
  autodetect_data_type(model_name);

  /* set number of states based on datatype (unless already set) */
  _num_states = DATATYPE_STATES.at(_data_type);

  init_mix_model(model_name);

  init_model_opts(model_opts);
}


void Model::autodetect_data_type(const std::string &model_name)
{
  if (_data_type == DataType::autodetect)
  {
    if (pllmod_util_model_exists_genotype(model_name.c_str()))
      _data_type = DataType::diploid10;
    else if (pllmod_util_model_exists_protein(model_name.c_str()) ||
             pllmod_util_model_exists_protmix(model_name.c_str()))
    {
      _data_type = DataType::protein;
    }
    else
    {
      _data_type = DataType::dna;
    }
  }
}

void Model::init_mix_model(const std::string &model_name)
{
  const char * model_cstr = model_name.c_str();

  if (pllmod_util_model_exists_protmix(model_cstr))
  {
    _mix_model = pllmod_util_model_info_protmix(model_cstr);
  }
  else
  {
    pllmod_subst_model_t * modinfo =  NULL;

    /* initialize parameters from the model */
    if (_data_type == DataType::protein)
    {
      modinfo =  pllmod_util_model_info_protein(model_cstr);
    }
    else if (_data_type == DataType::dna)
    {
      modinfo =  pllmod_util_model_info_dna(model_cstr);
    }
    else if (_data_type == DataType::diploid10)
    {
      modinfo =  pllmod_util_model_info_genotype(model_cstr);
    }

    /* pre-defined model not found; assume model string encodes rate symmetries */
    if (!modinfo)
      modinfo =  pllmod_util_model_create_custom("USER", _num_states, NULL, NULL, model_cstr, NULL);

    if (!modinfo)
      throw runtime_error("Invalid model name: " + model_name);

    /* create pseudo-mixture with 1 component */
    _mix_model = pllmod_util_model_mixture_create(modinfo->name, 1, &modinfo, NULL, NULL,
                                                  PLLMOD_UTIL_MIXTYPE_FIXED);
  }
}

void Model::init_model_opts(const std::string &model_opts)
{
  _alpha = 1.0;
  _pinv = 0.0;

  /* set rate heterogeneity defaults from model */
  _num_ratecats = _mix_model->ncomp;
  _num_submodels = _mix_model->ncomp;
  _rate_het = _mix_model->mix_type;

  /* allocate space for all subst matrices/base freqs */
  _base_freqs.resize(_num_submodels);
  _subst_rates.resize(_num_submodels);

  /* set default param optimization modes */
  for (auto param: ALL_MODEL_PARAMS)
    _param_mode[param] = ParamValue::undefined;

  _param_mode[PLLMOD_OPT_PARAM_FREQUENCIES] =
      _mix_model->models[0]->freqs ? ParamValue::model : ParamValue::ML;

  _param_mode[PLLMOD_OPT_PARAM_SUBST_RATES] =
      _mix_model->models[0]->rates ? ParamValue::model : ParamValue::ML;

  const char *s = model_opts.c_str();
  const char *tmp;

  /* parse the rest and set additional model params */
  int rate_cats;
  ParamValue param_mode;
  while(*s != '\0')
  {
    // skip "+"
    s++;

    switch(toupper(*s))
    {
      case '\0':
      case '+':
        break;
      case 'F':
        switch (toupper(*(s+1)))
        {
          case '\0':
          case '+':
          case 'C':
            param_mode = ParamValue::empirical;
            break;
          case 'O':
            param_mode = ParamValue::ML;
            break;
          case 'E':
            param_mode = ParamValue::equal;
            break;
          default:
            throw runtime_error(string("Invalid frequencies specification: ") + s);
        }
        _param_mode[PLLMOD_OPT_PARAM_FREQUENCIES] = param_mode;
        break;
      case 'I':
        switch (toupper(*(s+1)))
        {
          case '\0':
          case '+':
          case 'O':
            param_mode = ParamValue::ML;
            break;
          case 'C':
            param_mode = ParamValue::empirical;
            break;
          case '{':
            if (sscanf(s+1, "{%lf}", &_pinv) == 1 && ((tmp = strchr(s, '}')) != NULL))
            {
              param_mode = ParamValue::user;
              s = tmp+1;
            }
            else
              throw runtime_error(string("Invalid p-inv specification: ") + s);
            break;
          default:
            throw runtime_error(string("Invalid p-inv specification: ") + s);
        }
        _param_mode[PLLMOD_OPT_PARAM_PINV] = param_mode;
        break;
      case 'R':
      case 'G':
        /* allow to override mixture ratehet mode for now */
        _rate_het = toupper(*s) == 'R' ? PLLMOD_UTIL_MIXTYPE_FREE : PLLMOD_UTIL_MIXTYPE_GAMMA;
        if (sscanf(s+1, "%d", &rate_cats) == 1)
        {
          _num_ratecats = rate_cats;
        }
        else if (_num_ratecats == 1)
          _num_ratecats = 4;
        break;
      default:
        throw runtime_error("Wrong model specification: " + model_opts);
    }

    // rewind to next term
    while (*s != '+' && *s != '\0')
      s++;
  }

  switch (_param_mode.at(PLLMOD_OPT_PARAM_FREQUENCIES))
  {
    case ParamValue::user:
    case ParamValue::empirical:
      /* nothing to do here */
      break;
    case ParamValue::equal:
    case ParamValue::ML:
      /* use equal frequencies as s a starting value for ML optimization */
      for (size_t i = 0; i < _base_freqs.size(); ++i)
        _base_freqs[i].assign(_num_states, 1.0 / _num_states);
      break;
    case ParamValue::model:
      for (size_t i = 0; i < _base_freqs.size(); ++i)
        _base_freqs[i].assign(_mix_model->models[i]->freqs,
                              _mix_model->models[i]->freqs + _num_states);
      break;
    default:
      assert(0);
  }

  const size_t num_srates = pllmod_util_subst_rate_count(_num_states);
  switch (_param_mode.at(PLLMOD_OPT_PARAM_SUBST_RATES))
  {
    case ParamValue::user:
    case ParamValue::empirical:
      /* nothing to do here */
      break;
    case ParamValue::equal:
    case ParamValue::ML:
      /* use equal rates as s a starting value for ML optimization */
      for (size_t i = 0; i < _subst_rates.size(); ++i)
        _subst_rates[i].assign(num_srates, 1.0);
      break;
    case ParamValue::model:
      for (size_t i = 0; i < _subst_rates.size(); ++i)
        _subst_rates[i].assign(_mix_model->models[i]->rates,
                               _mix_model->models[i]->rates + num_srates);
      break;
    default:
      assert(0);
  }

  /* default: equal rates & weights */
  _ratecat_rates.assign(_num_ratecats, 1.0);
  _ratecat_weights.assign(_num_ratecats, 1.0 / _num_ratecats);
  _ratecat_submodels.assign(_num_ratecats, 0);

  if (_num_ratecats > 1)
  {
    /* init rate & weights according to the selected mode */
    switch (_rate_het)
    {
      case PLLMOD_UTIL_MIXTYPE_FIXED:
        assert(_num_ratecats == _mix_model->ncomp);
        /* set rates and weights from the mixture model definition */
        _ratecat_rates.assign(_mix_model->mix_rates, _mix_model->mix_rates + _num_ratecats);
        _ratecat_weights.assign(_mix_model->mix_weights, _mix_model->mix_weights + _num_ratecats);
        break;

      case PLLMOD_UTIL_MIXTYPE_GAMMA:
        /* compute the discretized category rates from a gamma distribution
           with given alpha shape and store them in rate_cats  */
        pll_compute_gamma_cats(_alpha, _num_ratecats, _ratecat_rates.data());
        if (_param_mode[PLLMOD_OPT_PARAM_ALPHA] == ParamValue::undefined)
          _param_mode[PLLMOD_OPT_PARAM_ALPHA] = ParamValue::ML;
        break;

      case PLLMOD_UTIL_MIXTYPE_FREE:
        /* use GAMMA rates as inital values -> can be changed */
        pll_compute_gamma_cats(_alpha, _num_ratecats, _ratecat_rates.data());
        _param_mode[PLLMOD_OPT_PARAM_FREE_RATES] = ParamValue::ML;
        _param_mode[PLLMOD_OPT_PARAM_RATE_WEIGHTS] = ParamValue::ML;
        break;

      default:
        throw runtime_error("Unknown rate heterogeneity model");
    }

    /* link rate categories to corresponding mixture components (R-matrix + freqs)*/
    if (_mix_model->ncomp == _num_ratecats)
    {
      for (size_t i = 0; i < _num_ratecats; ++i)
        _ratecat_submodels[i] = i;
    }
  }
}

std::string Model::to_string() const
{
  stringstream model_string;
  model_string << name();

  switch(_param_mode.at(PLLMOD_OPT_PARAM_FREQUENCIES))
  {
    case ParamValue::empirical:
      model_string << "+F";
      break;
    case ParamValue::ML:
      model_string << "+FO";
      break;
    case ParamValue::equal:
      model_string << "+FE";
      break;
    default:
      break;
  }

  switch(_param_mode.at(PLLMOD_OPT_PARAM_PINV))
  {
    case ParamValue::empirical:
      model_string << "+IC";
      break;
    case ParamValue::ML:
      model_string << "+I";
      break;
    case ParamValue::user:
      model_string << "+I{" << _pinv << "}";
      break;
    default:
      break;
  }

  if (_num_ratecats > 1)
  {
    if (_rate_het == PLLMOD_UTIL_MIXTYPE_GAMMA)
    {
      model_string << "+G" << _num_ratecats;
      if (_param_mode.at(PLLMOD_OPT_PARAM_ALPHA) == ParamValue::user)
        model_string << "{" << _alpha << "}";
    }
    else if (_rate_het == PLLMOD_UTIL_MIXTYPE_FREE)
    {
      model_string << "+R" << _num_ratecats;
    }
  }

  return model_string.str();
}

int Model::params_to_optimize() const
{
  int params_to_optimize = 0;

  for (auto param: ALL_MODEL_PARAMS)
  {
    if (_param_mode.at(param) == ParamValue::ML)
      params_to_optimize |= param;
  }

  return params_to_optimize;
}

string get_param_mode_str(ParamValue mode)
{
  return ParamValueNames[(size_t) mode];
}

void assign(Model& model, const pllmod_msa_stats_t * stats)
{
  /* either compute empirical P-inv, or set the fixed user-specified value */
  switch (model.param_mode(PLLMOD_OPT_PARAM_PINV))
  {
    case ParamValue::empirical:
      model.pinv(stats->inv_prop);
      break;
    case ParamValue::ML:
      /* use half of empirical pinv as a starting value */
      model.pinv(stats->inv_prop / 2);
      break;
    case ParamValue::user:
    case ParamValue::undefined:
      /* nothing to do here */
      break;
    default:
      assert(0);
  }

   /* assign empirical base frequencies */
  switch (model.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES))
  {
    case ParamValue::empirical:
//      if (_model.data_type == DataType::diploid10)
//        /* for now, use a separate function to compute emp. freqs for diploid10 data*/
//        alloc_freqs = base_freqs = get_diploid10_empirircal_freqs(msa);
//      else
      {
//        base_freqs = pllmod_msa_empirical_frequencies(partition);
        assert(stats->freqs && stats->states == model.num_states());
        model.base_freqs(Model::doubleVector(stats->freqs, stats->freqs + stats->states));
      }
      break;
    case ParamValue::user:
    case ParamValue::equal:
    case ParamValue::ML:
    case ParamValue::model:
      /* nothing to do here */
      break;
    default:
      assert(0);
  }

  /* assign empirical substitution rates */
  switch (model.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES))
  {
    case ParamValue::empirical:
    {
//      double * subst_rates = pllmod_msa_empirical_subst_rates(partition);
      size_t n_subst_rates = pllmod_util_subst_rate_count(stats->states);
      model.subst_rates(Model::doubleVector(stats->subst_rates,
                                            stats->subst_rates + n_subst_rates));
      break;
    }
    case ParamValue::equal:
    case ParamValue::user:
    case ParamValue::ML:
    case ParamValue::model:
      /* nothing to do here */
      break;
    default:
      assert(0);
  }
}

void assign(Model& model, const pll_partition_t * partition)
{
  if (model.num_states() == partition->states &&
      model.num_submodels() == partition->rate_matrices)
  {
    model.pinv(partition->prop_invar[0]);
    for (size_t i = 0; i < model.num_submodels(); ++i)
    {
      model.base_freqs(i, Model::doubleVector(partition->frequencies[i],
                                              partition->frequencies[i] + partition->states));

      size_t n_subst_rates = pllmod_util_subst_rate_count(partition->states);
      model.subst_rates(i, Model::doubleVector(partition->subst_params[i],
                                               partition->subst_params[i] + n_subst_rates));

      if (partition->rate_cats > 1)
      {
        model.ratecat_rates(Model::doubleVector(partition->rates[i],
                                                 partition->rates[i] + partition->rate_cats));
        model.ratecat_weights(Model::doubleVector(partition->rate_weights[i],
                                                  partition->rate_weights[i] + partition->rate_cats));
      }
    }
  }
  else
    throw runtime_error("incompatible partition!");
}

void assign(pll_partition_t * partition, const Model& model)
{
  if (model.num_states() == partition->states &&
      model.num_submodels() == partition->rate_matrices)
  {
    /* set rate categories & weights */
    pll_set_category_rates(partition, model.ratecat_rates().data());
    pll_set_category_weights(partition, model.ratecat_weights().data());

    /* now iterate over rate matrices and set all params */
    for (size_t i = 0; i < partition->rate_matrices; ++i)
    {
      /* set base frequencies */
      assert(!model.base_freqs(i).empty());
      pll_set_frequencies(partition, i, model.base_freqs(i).data());

      /* set substitution rates */
      assert(!model.subst_rates(i).empty());
      pll_set_subst_params(partition, i, model.subst_rates(i).data());

      /* set p-inv value */
      pll_update_invariant_sites_proportion (partition, i, model.pinv());
    }
  }
  else
    throw runtime_error("incompatible partition!");
}

void print_model_info(const Model& m)
{
//  if (treeinfo->brlen_linkage == PLLMOD_TREE_BRLEN_SCALED)
//    print_info("   Speed (%s): %.3f\n",
//               get_param_mode_str(part_info->paramval_brlen_scaler),
//               treeinfo->brlen_scalers[p]);
//
//  print_info("   Branch lengths (%s): %s\n", get_param_mode_str(part_info->paramval_brlen),
//             treeinfo->brlen_linkage == PLLMOD_TREE_BRLEN_SCALED ? "proportional" :
//                 (treeinfo->brlen_linkage == PLLMOD_TREE_BRLEN_UNLINKED ? "unlinked" : "linked"));

//  LOG_INFO << "   Rate heterogeneity: " << get_ratehet_mode_str(part_info);
  if (m.num_ratecats() > 1)
  {
    LOG_INFO << " (" << m.num_ratecats() << " cats)";
    if (m.ratehet_mode() == PLLMOD_UTIL_MIXTYPE_GAMMA)
      LOG_INFO << ",  alpha: " << m.alpha() << " ("  << get_param_mode_str(m.param_mode(PLLMOD_OPT_PARAM_ALPHA))
                 << ")";
    LOG_INFO << ",  weights&rates: ";
    for (size_t i = 0; i < m.num_ratecats(); ++i)
      LOG_INFO << "(" << m.ratecat_weights()[i] << "," << m.ratecat_rates()[i] << ") ";
  }
  LOG_INFO << endl;

  if (m.param_mode(PLLMOD_OPT_PARAM_PINV) != ParamValue::undefined)
    LOG_INFO << "   P-inv (" << get_param_mode_str(m.param_mode(PLLMOD_OPT_PARAM_PINV)) << "): " <<
               m.pinv();

  LOG_INFO << "   Base frequencies (" << get_param_mode_str(m.param_mode(PLLMOD_OPT_PARAM_FREQUENCIES)) << "): ";
  for (size_t i = 0; i < m.num_submodels(); ++i)
  {
    if (m.num_submodels() > 1)
      LOG_INFO << "\nM " << i << ": ";

    for (size_t j = 0; j < m.base_freqs(i).size(); ++j)
      LOG_INFO << m.base_freqs(i)[j] << " ";
  }
  LOG_INFO << endl;

  LOG_INFO << "   Substitution rates (" << get_param_mode_str(m.param_mode(PLLMOD_OPT_PARAM_SUBST_RATES)) << "): ";
  for (size_t i = 0; i < m.num_submodels(); ++i)
  {
    if (m.num_submodels() > 1)
      LOG_INFO << "\nM " << i << ": ";

    for (size_t j = 0; j < m.subst_rates(i).size(); ++j)
      LOG_INFO << m.subst_rates(i)[j] << " ";
  }
  LOG_INFO << endl;
}


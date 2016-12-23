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

Model::Model (DataType data_type, const std::string &model_string) : _data_type(data_type)
{
  init_from_string(model_string);
}

Model::~Model ()
{
  // TODO Auto-generated destructor stub
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
  /* set rate heterogeneity defaults from model */
  _num_ratecats = _mix_model->ncomp;
  _rate_het = _mix_model->mix_type;

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

  if (_num_ratecats > 1)
  {
    if (_rate_het == PLLMOD_UTIL_MIXTYPE_GAMMA)
    {
      if (_param_mode[PLLMOD_OPT_PARAM_ALPHA] == ParamValue::undefined)
        _param_mode[PLLMOD_OPT_PARAM_ALPHA] = ParamValue::ML;
    }
    else
    {
      if (_rate_het == PLLMOD_UTIL_MIXTYPE_FREE)
      {
        _param_mode[PLLMOD_OPT_PARAM_FREE_RATES] = ParamValue::ML;
        _param_mode[PLLMOD_OPT_PARAM_RATE_WEIGHTS] = ParamValue::ML;
      }
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


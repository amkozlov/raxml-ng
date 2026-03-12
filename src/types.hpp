#ifndef RAXML_TYPES_HPP_
#define RAXML_TYPES_HPP_

#include <string>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <random>

#include <corax/corax.h>

/*
 * workaround needed for using enum as std::map key
 * code from: http://stackoverflow.com/a/24847480
 * */
struct EnumClassHash
{
  template <typename T>
  std::size_t operator()(T t) const
  {
      return static_cast<std::size_t>(t);
  }
};


enum class StartingTree
{
  random,
  parsimony,
  user,
  adaptive,
  consensus
};

enum class Command
{
  none = 0,
  help,
  version,
  evaluate,
  search,
  bootstrap,
  all,
  support,
  bsconverge,
  bsmsa,
  terrace,
  check,
  parse,
  start,
  rfdist,
  consense,
  ancestral,
  sitelh,
  pythia,
  modeltest,
  mutmap
};

const std::string CommandNames[] = {"none", "help", "version", "evaluate", "search", "bootstrap",
                                    "all", "support", "bsconverge", "bsmsa", "terrace", "check",
                                    "parse", "start", "rfdist", "consense", "ancestral", "sitelh",
                                    "pythia", "modeltest", "mutmap" };

enum class FileFormat
{
  autodetect = 0,
  fasta,
  fasta_longlabels,
  phylip,
  iphylip,
  vcf,
  catg,
  binary
};

enum class DataType
{
  autodetect = 0,
  dna,
  protein,
  binary,
  multistate,
  genotype10,
  genotype16
};

const std::unordered_map<DataType,unsigned int,EnumClassHash>  DatatypeStates
{
  {DataType::autodetect, 0},
  {DataType::dna, 4},
  {DataType::protein, 20},
  {DataType::binary, 2},
  {DataType::multistate, 0},   // variable
  {DataType::genotype10, 10},
  {DataType::genotype16, 16}
};

const std::unordered_map<DataType,const corax_state_t*,EnumClassHash>  DatatypeCharmaps
{
  {DataType::dna, corax_map_nt},
  {DataType::protein, corax_map_aa},
  {DataType::binary, corax_map_bin},
  {DataType::genotype10, corax_map_gt10},
  {DataType::genotype16, corax_map_gt16}
};

const std::unordered_map<DataType,std::string,EnumClassHash>  DatatypePrefix
{
  {DataType::dna, "DNA"},
  {DataType::protein, "PROT"},
  {DataType::binary, "BIN"},
  {DataType::genotype10, "GT"},
  {DataType::genotype16, "GP"},
  {DataType::multistate, "MULTI"},
  {DataType::autodetect, "AUTO"}
};

enum class ParamValue
{
  undefined = 0,
  equal = 1,
  user = 2,
  model = 3,
  empirical = 4,
  ML = 5
};

enum class AscBiasCorrection
{
  none = 0,
  lewis = CORAX_ATTRIB_AB_LEWIS,
  felsenstein = CORAX_ATTRIB_AB_FELSENSTEIN,
  stamatakis = CORAX_ATTRIB_AB_STAMATAKIS,
};

enum class BootstopCriterion
{
  none = 0,
  autoMRE,
  autoMR,
  autoFC
};

enum class LoadBalancing
{
  naive = 0,
  kassian,
  benoit
};

enum class BranchSupportMetric
{
  fbp = 0,
  tbe,
  rbs,
  sh_alrt,
  ebg,
  ps,
  pbs,
  ic1,
  ica,
  gcf
};

typedef std::set<BranchSupportMetric> SupportMetricSet;
typedef std::map<BranchSupportMetric,unsigned int> SupportMetricMap;

enum class InformationCriterion
{
  aic = 0,
  aicc,
  bic
};

enum class TopologyOptMethod
{
  none = 0,
  classic,
  adaptive,
  rapidBS,
  nniRound,
  simplified,
  adafast
};

enum class StoppingRule
{
  none = 0,
  sn_rell,
  sn_normal,
  kh,
  kh_mult
};

namespace ConsenseCutoff
{
  enum ConsenseCutoff : unsigned int
  {
    MRE = 0,
    MR = 50,
    strict = 100
  };
};

enum class FreerateOptMethod
{
  AUTO = 0,
  EM_BFGS,
  EM_BRENT,
  LBFGSB
};

enum class AbnormalSequenceAction
{
  keep = 0,    /* keep & report */
  regraft,     /* exclude & re-insert into the final tree */
  remove,      /* remove & ignore */
  error        /* exit with error */
};


const std::string ParamValueNames[] = {"undefined", "equal", "user", "model", "empirical", "ML"};

typedef std::vector<double> doubleVector;
typedef std::vector<int> intVector;
typedef std::vector<unsigned int> uintVector;
typedef std::vector<std::string> NameList;
typedef std::pair<size_t,size_t> IdPair;
typedef std::vector<IdPair> IdPairVector;
typedef std::pair<size_t,std::string> IdNamePair;
typedef std::vector<IdNamePair> IdNameVector;
typedef std::unordered_map<size_t,std::string> IdNameMap;
typedef std::unordered_map<std::string,size_t> NameIdMap;
typedef std::unordered_map<std::string,std::string> NameMap;
typedef std::set<size_t> IDSet;
typedef std::vector<size_t> IDVector;
typedef std::queue<size_t> IDQueue;
typedef std::map<StartingTree,size_t> StartingTreeMap;

typedef unsigned int WeightType;
typedef std::vector<WeightType> WeightVector;
typedef std::vector<WeightVector> WeightVectorList;
typedef std::unordered_map<size_t, WeightVector> WeightVectorMap;

typedef std::default_random_engine RandomGenerator;

/* generic exception class */
class RaxmlException : public std::exception
{
public:
  RaxmlException(const std::string& message)
  : _message(message)
  {
  }

  virtual const char* what() const noexcept
  { return message().c_str(); }

  virtual const std::string& message() const
  { update_message(); return _message; };

protected:
  mutable std::string _message;

  virtual void update_message() const { };

  template<typename ... Args>
  std::string format_message(const std::string& fmt, Args ... args) const
  {
    size_t size = std::snprintf(nullptr, 0, fmt.c_str(), args ...) + 1;
    std::string msg;
    msg.resize(size);
    std::snprintf(&msg[0], size, fmt.c_str(), args ...);
    return msg;
  }
};


#endif /* RAXML_TYPES_HPP_ */

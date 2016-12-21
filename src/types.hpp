#ifndef RAXML_TYPES_HPP_
#define RAXML_TYPES_HPP_

enum class StartingTree
{
  random,
  parsimony,
  user
};

enum class Command
{
  none = 0,
  help,
  version,
  evaluate,
  search
};

enum class FileFormat
{
  autodetect = 0,
  fasta,
  phylip,
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
  diploid10
};

enum class ParamValue
{
  undefined = 0,
  equal,
  user,
  model,
  empirical,
  ML
};

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


#endif /* RAXML_TYPES_HPP_ */

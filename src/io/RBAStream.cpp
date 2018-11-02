#include "file_io.hpp"
#include "binary_io.hpp"

using namespace std;

const uint64_t RBA_MAGIC       = *(reinterpret_cast<const uint64_t*>("RBAF\x13\x12\x17\x0A"));
const uint32_t RBA_VERSION     = 2;
const uint32_t RBA_MIN_VERSION = 2;

struct RBAHeader
{
  uint64_t magic;
  uint32_t version;
  unsigned char sizet_size;
  size_t taxon_count;
  size_t pattern_count;
  size_t site_count;
  size_t part_count;

  bool valid() { return magic == RBA_MAGIC; }

  bool supported() { return version >= RBA_MIN_VERSION && version <= RBA_VERSION; }

  RBAHeader() : magic(RBA_MAGIC), version(RBA_VERSION), sizet_size(sizeof(size_t)),
      taxon_count(0), pattern_count(0), site_count(0), part_count(0)
      {}
};

bool RBAStream::rba_file(const std::string& fname, bool check_version)
{
  BinaryFileStream bos(fname, std::ios::in);
  RBAHeader header;

  bos >> header;

  bool valid = header.valid();

  if (check_version)
    valid = valid && header.supported();

  return valid;
}

RBAStream& operator<<(RBAStream& stream, const PartitionedMSA& part_msa)
{
  BinaryFileStream bos(stream.fname(), std::ios::out);

  RBAHeader header{};

  header.taxon_count = part_msa.taxon_count();
  header.site_count = part_msa.total_sites();
  header.pattern_count = part_msa.total_patterns();
  header.part_count = part_msa.part_count();

  bos << header;

  // taxon labels
  for (auto label: part_msa.taxon_names())
  {
    bos << label;
  }

  // models
  for (const auto& pinfo: part_msa.part_list())
  {
    bos << pinfo.name();
    bos << pinfo.range_string();
    bos << pinfo.stats();
    bos << std::make_tuple(std::ref(pinfo.model()), ModelBinaryFmt::full);
  }

  // per-partition alignment blocks
  for (const auto& pinfo: part_msa.part_list())
  {
    bos << pinfo.msa();
  }

  return stream;
}

RBAStream& operator>>(RBAStream& stream, PartitionedMSA& part_msa)
{
  BinaryFileStream bos(stream.fname(), std::ios::in);
  RBAHeader header;

  bos >> header;

  if (!header.valid())
    throw runtime_error("Invalid RBA file header!");

  if (!header.supported())
    throw runtime_error("Unsupported RBA file version: " + to_string(header.version));

  NameList taxon_names(header.taxon_count, "");
  for (auto& taxon: taxon_names)
  {
    bos >> taxon;
//    LOG_INFO << bos.get<std::string>() << endl;
  }
  part_msa = PartitionedMSA(taxon_names);

  for (size_t i = 0; i < header.part_count; ++i)
  {
    PartitionStats pstats;
    std::string pname, prange;
    Model m;
    std::tuple<Model&, ModelBinaryFmt> mtuple = std::make_tuple(std::ref(m), ModelBinaryFmt::full);

    bos >> pname;
    bos >> prange;
    bos >> pstats;

    bos >> mtuple;

//    LOG_INFO << m << endl;

    part_msa.emplace_part_info(pname, pstats, m, prange);
  }

  for (auto& pinfo: part_msa.part_list())
  {
    bos >> pinfo.msa();
  }

//  LOG_INFO << part_msa << endl;

  return stream;
}


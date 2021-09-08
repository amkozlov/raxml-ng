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

  bool valid = bos.good() && header.valid();

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
  for (const auto& label: part_msa.taxon_names())
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
  stream >> RBAStream::RBAOutput(part_msa, RBAStream::RBAElement::all, nullptr);

  return stream;
}

RBAStream& operator>>(RBAStream& stream, RBAStream::RBAOutput out)
{
  BinaryFileStream bos(stream.fname(), std::ios::in);
  RBAHeader header;

  bos >> header;

  if (!bos.good())
    throw runtime_error("Invalid RBA file!");

  if (!header.valid())
    throw runtime_error("Invalid RBA file header!");

  if (!header.supported())
    throw runtime_error("Unsupported RBA file version: " + to_string(header.version));

  auto& part_msa = std::get<0>(out);
  auto& elem = std::get<1>(out);
  auto& pa = std::get<2>(out);

  bool load_meta = (elem == RBAStream::RBAElement::metadata || elem == RBAStream::RBAElement::all);
  bool load_seq = (elem == RBAStream::RBAElement::seqdata || elem == RBAStream::RBAElement::all);

  auto ensure_equal = [](string name, size_t a, size_t b) -> void
      {
        if (a != b)
        {
          throw runtime_error("RBAStream: " + name + " mismatch (" + to_string(a) +
                              " != " + to_string(b) + ")");
        }
      };

  if (!load_meta)
  {
    ensure_equal("taxon count", header.taxon_count, part_msa.taxon_count());
    ensure_equal("partition count", header.part_count, part_msa.part_count());
    ensure_equal("pattern count", header.pattern_count, part_msa.total_patterns());
  }

  NameList taxon_names(header.taxon_count, "");
  for (auto& taxon: taxon_names)
  {
    bos >> taxon;
//    LOG_INFO << bos.get<std::string>() << endl;
  }

  if (load_meta)
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

    if (load_meta)
      part_msa.emplace_part_info(pname, pstats, m, prange);
  }

  if (load_seq)
  {
    if (!pa)
    {
      for (auto& pinfo: part_msa.part_list())
        bos >> pinfo.msa();
    }
    else
    {
      std::vector<RangeList> part_ranges(part_msa.part_count());
      for (const auto& pr: *pa)
        part_ranges[pr.part_id].emplace_back(pr.start, pr.length);

      for (size_t p = 0; p < part_msa.part_count(); ++p)
      {
        auto& pinfo = part_msa.part_list().at(p);
        auto& rlist = part_ranges[p];
        if (rlist.empty())
        {
          // partition not found -> read & ignore
          bos >> NullMSA();
        }
        else
        {
          // load MSA segments
          bos >> MSARange(pinfo.msa(), rlist);
//          printf("LOAD PART: rank %lu, part %lu, len %lu\n",
//                 ParallelContext::rank_id(), p, pinfo.msa().length());
        }
      }
    }
  }

//  LOG_INFO << part_msa << endl;

  return stream;
}


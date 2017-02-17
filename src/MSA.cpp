#include <stdexcept>

#include "MSA.hpp"

using namespace std;

MSA::MSA(const pll_msa_t *pll_msa) :
    _length(pll_msa->length), _num_sites(pll_msa->length), _pll_msa(nullptr)
{
  for (auto i = 0; i < pll_msa->count; ++i)
  {
    append(string(pll_msa->sequence[i], pll_msa->length), pll_msa->label ? pll_msa->label[i] : "");
  }

  update_pll_msa();
}

MSA::MSA(MSA&& other) : _length(other._length), _num_sites(other._num_sites),
    _sequences(move(other._sequences)), _labels(move(other._labels)),
    _label_id_map(move(other._label_id_map)), _weights(move(other._weights)),
    _pll_msa(other._pll_msa), _dirty(other._dirty)
{
  other._length = other._num_sites = 0;
  other._pll_msa = nullptr;
  other._dirty = false;
};

MSA::~MSA()
{
  free_pll_msa();
}

MSA& MSA::operator=(MSA&& other)
{
  if (this != &other)
  {
    // release the current object’s resources
    free_pll_msa();
    _weights.clear();
    _sequences.clear();
    _labels.clear();
    _label_id_map.clear();

    // steal other’s resource
    _length = other._length;
    _num_sites = other._num_sites;
    _pll_msa = other._pll_msa;
    _weights = std::move(other._weights);
    _sequences = std::move(other._sequences);
    _labels = std::move(other._labels);
    _label_id_map = std::move(other._label_id_map);
    _dirty = other._dirty;

    // reset other
    other._length = other._num_sites = 0;
    other._pll_msa = nullptr;
    other._dirty = false;
  }
  return *this;
}

void MSA::free_pll_msa() noexcept
{
  if (_pll_msa)
  {
    free(_pll_msa->sequence);
    if (_pll_msa->label)
      free(_pll_msa->label);
    free(_pll_msa);
    _pll_msa = nullptr;
  }
}

const string& MSA::operator[](const std::string& name)
{
//  if((size_t) i >= sequence_list_.size())
//    throw runtime_error{string("Trying to access MSA entry out of bounds. i = ") + to_string(i) };

  return at(name);
}

void MSA::append(const string& sequence, const string& header)
{
  if(_length && sequence.length() != (size_t) _length)
    throw runtime_error{string("Tried to insert sequence to MSA of unequal length: ") + sequence};

  _sequences.push_back(sequence);

  if (!header.empty())
  {
    _labels.push_back(header);
    _label_id_map[header] = _labels.size() - 1;
  }

  if (!_length)
  {
    _length = sequence.length();
    if (!_num_sites)
      _num_sites = _length;
  }

  _dirty = true;
}

void MSA::compress_patterns(const unsigned int * charmap)
{
  update_pll_msa();

  assert(_pll_msa->count && _pll_msa->length);

  const unsigned int * w = pll_compress_site_patterns(_pll_msa->sequence,
                                                      charmap,
                                                      _pll_msa->count,
                                                      &(_pll_msa->length));

  if (!w)
    throw runtime_error("Pattern compression failed!");

  _length = _pll_msa->length;
  _weights = std::vector<unsigned int>(w, w + _pll_msa->length);

  _dirty = false;
}


const pll_msa_t * MSA::pll_msa() const
{
  update_pll_msa();
  return _pll_msa;
}

void MSA::update_pll_msa() const
{
  if (!_pll_msa)
  {
    _pll_msa = (pll_msa_t *) calloc(1, sizeof(pll_msa_t));
    _dirty = true;
  }

  assert(_labels.empty() || _labels.size() == _sequences.size());

  if (_dirty)
  {
    _pll_msa->count = size();
    _pll_msa->length = length();

    size_t i = 0;
    _pll_msa->sequence = (char **) calloc(_pll_msa->count, sizeof(char *));
    for (const auto& entry : _sequences)
    {
      _pll_msa->sequence[i] = (char *) entry.c_str();
      ++i;
    }
    assert(i == size());

    if (!_labels.empty())
    {
      i = 0;
      _pll_msa->label = (char **) calloc(_pll_msa->count, sizeof(char *));
      for (const auto& entry : _labels)
      {
        _pll_msa->label[i] = (char *) entry.c_str();
        ++i;
      }
      assert(i == size());
    }

    _dirty = false;
  }
}


MSA msa_load_from_fasta(const std::string &filename)
{
  /* open the file */
  auto file = pll_fasta_open(filename.c_str(), pll_map_fasta);
  if (!file)
    throw runtime_error{string("Cannot open file ") + filename};

  char * sequence = NULL;
  char * header = NULL;
  long sequence_length;
  long header_length;
  long sequence_number;

  /* read sequences and make sure they are all of the same length */
  int sites = 0;

  /* read the first sequence separately, so that the MSA object can be constructed */
  pll_fasta_getnext(file, &header, &header_length, &sequence, &sequence_length, &sequence_number);
  sites = sequence_length;

  if (sites == -1 || sites == 0)
    throw runtime_error{"Unable to read MSA file"};

  MSA msa(sites);

  //  MSA&& msa = MSA(sites);
  msa.append(sequence, header);

  free(sequence);
  free(header);

  /* read the rest */
  while (pll_fasta_getnext(file, &header, &header_length, &sequence, &sequence_length, &sequence_number))
  {
    if (sites && sites != sequence_length)
      throw runtime_error{"MSA file does not contain equal size sequences"};

    if (!sites) sites = sequence_length;

    msa.append(sequence, header);
    free(sequence);
    free(header);
  }

  if (pll_errno != PLL_ERROR_FILE_EOF)
    throw runtime_error{string("Error while reading file: ") +  filename};

  pll_fasta_close(file);

  return msa;
}

MSA msa_load_from_phylip(const std::string &filename)
{
  unsigned int sequence_count;
  pll_msa_t * pll_msa = pll_phylip_parse_msa(filename.c_str(), &sequence_count);
  if (pll_msa)
  {
    MSA msa(pll_msa);
    free(pll_msa);
    return msa;
  }
  else
    throw runtime_error{string("Unable to parse PHYLIP file: ") +  filename};
}

MSA msa_load_from_file(const std::string &filename, const FileFormat format)
{
  vector<FileFormat> fmt_list;

  if (format == FileFormat::autodetect)
    fmt_list = {FileFormat::phylip, FileFormat::fasta, FileFormat::catg, FileFormat::vcf, FileFormat::binary};
  else
    fmt_list = {format};

  for (auto fmt: fmt_list)
  {
    try
    {
      switch (fmt)
      {
        case FileFormat::fasta:
          return msa_load_from_fasta(filename);
          break;
        case FileFormat::phylip:
        {
          auto msa = msa_load_from_phylip(filename);
          return msa;
          break;
        }
        default:
          throw runtime_error("Unsupported MSA file format!");
      }
    }
    catch(exception &e)
    {
//      LOG_INFO << "Failed to load as: " << e.what() << endl;
    }
  }

  throw runtime_error("Error loading MSA!");
}

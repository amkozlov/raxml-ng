#include <stdexcept>
#include <algorithm>
#include <map>

#include "file_io.hpp"

using namespace std;

FastaStream& operator>>(FastaStream& stream, MSA& msa)
{
  /* open the file */
  auto file = pll_fasta_open(stream.fname().c_str(), pll_map_generic);
  if (!file)
    libpll_check_error("Unable to parse FASTA file");

  char * sequence = NULL;
  char * header = NULL;
  long sequence_length;
  long header_length;
  long sequence_number;

  /* read sequences and make sure they are all of the same length */
  int sites = 0;

  /* read the rest */
  while (pll_fasta_getnext(file, &header, &header_length, &sequence, &sequence_length, &sequence_number))
  {
    if (!sites)
    {
      /* first sequence, init the MSA object */
      if (sequence_length == -1 || sequence_length == 0)
        throw runtime_error{"Unable to parse FASTA file"};

      sites = sequence_length;

      msa = MSA(sites);
    }
    else
    {
      if (sequence_length != sites)
        throw runtime_error{"FASTA file does not contain equal size sequences"};
    }

    if (!header_length)
    {
      throw runtime_error{"FASTA file contains empty sequence label: " + to_string(msa.size() + 1) };
    }

    if (!sequence_length)
    {
      throw runtime_error{"FASTA file contains empty sequence:" + string(header) };
    }

    /*trim trailing whitespace from the sequence label */
    std::string label(header);
    label.erase(label.find_last_not_of(" \n\r\t")+1);

    msa.append(sequence, label);
    free(sequence);
    free(header);
  }

  if (pll_errno != PLL_ERROR_FILE_EOF)
    libpll_check_error("Error parsing FASTA file: " +  stream.fname() + "\n");

  pll_fasta_close(file);

  libpll_reset_error();

  return stream;
}

PhylipStream& operator>>(PhylipStream& stream, MSA& msa)
{
  pll_phylip_t * fd = pll_phylip_open(stream.fname().c_str(), pll_map_generic);
  if (!fd)
    throw runtime_error(pll_errmsg);

  pll_msa_t * pll_msa = stream.interleaved() ?
      pll_phylip_parse_interleaved(fd) : pll_phylip_parse_sequential(fd);

  pll_phylip_close(fd);

  if (pll_msa)
  {
    msa = MSA(pll_msa);
    pll_msa_destroy(pll_msa);
  }
  else
    libpll_check_error("Unable to parse PHYLIP file: " +  stream.fname() + "\n");

  return stream;
}

PhylipStream& operator<<(PhylipStream& stream, const MSA& msa)
{
  auto retval = pllmod_msa_save_phylip(msa.pll_msa(), stream.fname().c_str());

  if (!retval)
    throw runtime_error{pll_errmsg};

  return stream;
}

PhylipStream& operator<<(PhylipStream& stream, const PartitionedMSAView& msa)
{
  ofstream fs(stream.fname());

  auto taxa = msa.taxon_count();
  auto sites = msa.total_sites();
  fs << taxa << " " << sites << endl;

  for (size_t i = 0; i < taxa; ++i)
  {
    fs << msa.taxon_name(i) << " ";
    for (size_t p = 0; p < msa.part_count(); ++p)
    {
      fs << msa.part_sequence(i, p, true);
    }
    fs << endl;
  }

  return stream;
}

PhylipStream& operator<<(PhylipStream& stream, const PartitionedMSA& msa)
{
  PartitionedMSAView msa_view(msa);

  return stream;
}

PhylipStream& operator<<(PhylipStream& stream, const BootstrapMSA& bs_msa)
{
  ofstream fs(stream.fname());

  const auto& msa = std::get<0>(bs_msa);
  const auto& bsrep = std::get<1>(bs_msa);

  auto taxa = msa.taxon_count();
  auto sites = msa.total_sites();
  fs << taxa << " " << sites << endl;

  for (size_t i = 0; i < taxa; ++i)
  {
    fs << msa.taxon_names().at(i) << " ";
    for (size_t p = 0; p < msa.part_count(); ++p)
    {
      const auto& w = bsrep.site_weights.at(p);
      const auto& m = msa.part_info(p).msa();
      const auto& seq = m.at(i);

      assert(w.size() == seq.size());

      size_t wsum = 0;
      for (size_t j = 0; j < seq.length(); ++j)
      {
        wsum += w[j];
        for (size_t k = 0; k < w[j]; ++k)
          fs << seq[j];
      }

      assert(wsum == m.num_sites());
    }
    fs << endl;
  }

  return stream;
}

CATGStream& operator>>(CATGStream& stream, MSA& msa)
{
  ifstream fs;
  fs.open(stream.fname());

  /* read alignment dimensions */
  size_t taxa_count, site_count;

  try
  {
    fs >> taxa_count >> site_count;
  }
  catch(exception& e)
  {
    LOG_DEBUG << e.what() << endl;
    taxa_count = site_count = 0;
  }

  if (!taxa_count || !site_count)
    throw runtime_error("Invalid alignment dimensions!");

  LOG_DEBUG << "CATG: taxa: " << taxa_count << ", sites: " << site_count << endl;

  string dummy(site_count, '*');

  /* read taxa names */
  try
  {
    string taxon_name;
    for (size_t i = 0; i < taxa_count; ++i)
    {
      fs >> taxon_name;
      msa.append(dummy, taxon_name);
      LOG_DEBUG << "CATG: taxon " << i << ": " << taxon_name << endl;
    }
  }
  catch (exception& e)
  {
    LOG_DEBUG << e.what() << endl;
  }

  if (msa.size() != taxa_count)
    throw runtime_error("Wrong number of taxon labels!");

  /* this is mapping for DNA: CATG -> ACGT, for other datatypes we assume 1:1 mapping */
  std::vector<size_t> state_map({1, 0, 3, 2});

  string cons_str, prob_str;

  /* read alignment, remember that the matrix is transposed! */
  for (size_t i = 0; i < msa.num_sites(); ++i)
  {
    /* read consensus sequences */
    fs >> cons_str;

    LOG_DEBUG << "CATG: site " << i << " consesus seq: " << cons_str << endl;

    if (cons_str.length() != msa.size())
      throw runtime_error("Wrong length of consensus sequence for site " + to_string(i+1) + "!");

    std::vector<double> probs;

    for (size_t j = 0; j < msa.size(); ++j)
    {
      msa[j][i] = cons_str[j];

      fs >> prob_str;

      if (msa.states() == 0)
      {
        auto states = std::count_if(prob_str.cbegin(), prob_str.cend(),
                                    [](char c) -> bool { return c == ','; }) + 1;
        msa.states(states);

        /* see above: for datatypes other than DNA we assume 1:1 mapping */
        if (states != 4)
          state_map.clear();

        LOG_DEBUG << "CATG: number of states: " << states << endl;
      }

      auto site_probs = msa.probs(j, i);

      istringstream ss(prob_str);
      size_t k = 0;
      for (string token; getline(ss, token, ','); ++k)
      {
        if (state_map.empty())
          site_probs[k] = stod(token);
        else
          site_probs[state_map[k]] = stod(token);
      }

      if (k != msa.states())
        throw runtime_error("Wrong number of state probabilities for site " + to_string(i+1) + "!");
    }
  }

#ifdef CATG_DEBUG
  {
    PhylipStream ps("catgout.phy");
    ps << msa;
  }
#endif

  return stream;
}

VCFStream& operator>>(VCFStream& stream, MSA& msa)
{
#ifndef _RAXML_VCF
  throw runtime_error("RAxML-NG was build without VCF support");
#else
  const auto fname = stream.fname().c_str();
  htsFile *fp    = hts_open(fname, "rb");

  if (!fp)
    throw runtime_error("Cannot open VCF file: " + stream.fname());

  const htsFormat *fmt = hts_get_format(fp);

  if (fmt->category != variant_data)
    throw runtime_error("Invalid VCF file type");

  bcf_hdr_t *hdr = bcf_hdr_read(fp);
  bcf1_t *rec    = bcf_init1();

  size_t taxa_count = bcf_hdr_nsamples(hdr);

  // This is an ugly workaround, but there seems to be no better way to get
  // the number of SNPs from the stupid VCF
  size_t site_count = 0;
  while (bcf_read1(fp, hdr, rec) >=0)
    site_count++;
  bcf_hdr_destroy(hdr);
  hts_close(fp);
  fp = hts_open(fname,"rb");
  hdr = bcf_hdr_read(fp);

  LOG_DEBUG << "VCF samples: " << taxa_count << ", variants: " << site_count << endl;

  msa = MSA(site_count);

  string dummy(site_count, '*');

  /* read taxa names */
  try
  {
    for (size_t i = 0; i < taxa_count; ++i)
    {
      string taxon_name = hdr->samples[i];
      msa.append(dummy, taxon_name);
      LOG_DEBUG << "VCF: sample " << i << ": " << taxon_name << endl;
    }
  }
  catch (exception& e)
  {
    LOG_DEBUG << e.what() << endl;
  }

  // TODO hardcoded for now: diploid unphased
  msa.states(10);

  /* allocate memory */
  char inv_charmap[PLL_ASCII_SIZE] = {0};
  for (unsigned int i = 0; i < PLL_ASCII_SIZE; ++i)
    if (pll_map_nt[i] && !inv_charmap[pll_map_nt[i]])
      inv_charmap[pll_map_nt[i]] = (char)i;

  //       0  1  2  3  4  5  6  7  8  9
  // VCF: AA AC AG AT CC CG CT GG GT TT
  // RAX: AA CC GG TT AC AG AT CG CT GT
                                      /* AA AC AG AT CC CG CT GG GT TT */
  static const int vcf_to_rax_map[10] = {0, 4, 5, 6, 1, 7, 8, 2, 9, 3 };

  char gt_to_char[4][4];
  for (size_t i = 0; i < 4; ++i)
  {
    for (size_t j = 0; j < 4; ++j)
    {
      gt_to_char[i][j] = inv_charmap[ (1u << i) | (1u << j)];
    }
  }

  int gl_num = 0;
  float * gt_pl = NULL;

  size_t j = 0;
  while ( bcf_read1(fp, hdr, rec)>=0 )
    {
      bcf_unpack(rec, BCF_UN_ALL);

      assert(strlen(rec->d.allele[0]) == 1 && strlen(rec->d.allele[1]));

      int als[4] = {'-'};
      for (size_t i = 0; i < rec->n_allele; ++i)
        als[i] = rec->d.allele[i][0];

//      printf("alleles: %c %c %c %c\n", als[0], als[1], als[2], als[3]);

      int cals[4] = {0};
      for (size_t i = 0; i < rec->n_allele; ++i)
        cals[i] = pll_map_nt[als[i]];

//      printf("encoded alleles: %d %d %d %d\n", cals[0], cals[1], cals[2], cals[3]);

      bcf_fmt_t * gt = bcf_get_fmt(hdr, rec, "GT");

      assert(gt);

//      bcf_fmt_t * gl = bcf_get_fmt(hdr, rec, "GL");
      bcf_fmt_t * gl10 = bcf_get_fmt(hdr, rec, "G10");

      /* assume 10 genotypes for now */
      assert(gl10->n == 10);

      if (!bcf_get_format_float(hdr, rec ,"G10", &gt_pl, &gl_num))
        throw runtime_error("Invalid VCF file format: field GL not found");

      assert(gl_num == (int) taxa_count * gl10->n);

      for (size_t i = 0; i < taxa_count; ++i)
      {
        const int al1 = bcf_gt_allele(gt->p[i * 2]);
        const int al2 = bcf_gt_allele(gt->p[i * 2 + 1]);

        char c = '-';
        if (al1 >= 0 && al2 >= 0)
        {
          auto gt1 = PLL_CTZ32(cals[al1]);
          auto gt2 = PLL_CTZ32(cals[al2]);
          c = gt_to_char[gt1][gt2];
        }

        msa[i][j] = c;

//        if (!i)
//          printf("als: %d %d, char: %c\n", al1, al2, c);

        /* probs */
        auto site_probs = msa.probs(i, j);

        if (al1 >= 0 && al2 >= 0)
        {
          for (unsigned int k = 0; k < 10; ++k)
          {
            // TODO remap
            auto pl = gt_pl[i * 10 + k];
            auto s = vcf_to_rax_map[k];
            site_probs[s] = isfinite(pl) ? exp10(pl) : 0.;
//            site_probs[k] = isfinite(pl) ? exp10(-0.1 * pl) : 0.;
//            if (!i)
//              printf("prob %u: %lf / %f \n", s, site_probs[s], pl);
          }
        }
        else
        {
          /* gap / missing data */
          for (size_t k = 0; k < 10; ++k)
          {
            site_probs[k] = 1.;
          }
        }
      }

      j++;

      if (j > site_count-1)
        break;
    }

  assert(j == site_count);

  free(gt_pl);
  bcf_hdr_destroy(hdr);

  int ret;
  if ( (ret = hts_close(fp)) )
  {
      fprintf(stderr,"hts_close(%s): non-zero status %d\n", fname, ret);
      exit(ret);
  }

//  pllmod_msa_save_phylip(msa.pll_msa(), "vcfout.phy");
#endif

  return stream;
}

MSA msa_load_from_file(const std::string &filename, const FileFormat format)
{
  MSA msa;

  typedef pair<FileFormat, string> FormatNamePair;
  static vector<FormatNamePair> msa_formats = { {FileFormat::iphylip, "IPHYLIP"},
                                                {FileFormat::phylip, "PHYLIP"},
                                                {FileFormat::fasta, "FASTA"},
                                                {FileFormat::catg, "CATG"},
                                                {FileFormat::vcf, "VCF"},
                                                {FileFormat::binary, "RAxML-binary"} };

  auto fmt_begin = msa_formats.cbegin();
  auto fmt_end = msa_formats.cend();

  if (!sysutil_file_exists(filename))
    throw runtime_error("File not found: " + filename);

  if (format != FileFormat::autodetect)
  {
    fmt_begin = std::find_if(msa_formats.begin(), msa_formats.end(),
                             [format](const FormatNamePair& p) { return p.first == format; });
    assert(fmt_begin != msa_formats.cend());
    fmt_end = fmt_begin + 1;
  }

  for (; fmt_begin != fmt_end; fmt_begin++)
  {
    try
    {
      switch (fmt_begin->first)
      {
        case FileFormat::fasta:
        {
          FastaStream s(filename);
          s >> msa;
          return msa;
          break;
        }
        case FileFormat::iphylip:
        {
          PhylipStream s(filename, true);
          s >> msa;
          return msa;
          break;
        }
        case FileFormat::phylip:
        {
          PhylipStream s(filename, false);
          s >> msa;
          return msa;
          break;
        }
        case FileFormat::vcf:
        {
          VCFStream s(filename);
          s >> msa;
          return msa;
          break;
        }
        case FileFormat::catg:
        {
          CATGStream s(filename);
          s >> msa;
          return msa;
          break;
        }
        default:
          throw runtime_error("Unsupported MSA file format!");
      }
    }
    catch(exception &e)
    {
      libpll_reset_error();
      if (format == FileFormat::autodetect)
        LOG_DEBUG << "Failed to load as " << fmt_begin->second << ": " << e.what() << endl;
      else
        throw runtime_error("Error loading MSA: " + string(e.what()));
    }
  }

  throw runtime_error("Error loading MSA: cannot parse any format supported by RAxML-NG!\n"
      "Please re-run with --msa-format <FORMAT> and/or --log debug to get more information.");
}




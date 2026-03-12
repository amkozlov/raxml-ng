#include "file_io.hpp"

#include <htslib/hts.h>
#include <htslib/vcf.h>

//#define _RAXML_VCF_DEBUG

#define _RAXML_VCF_MINGL -75

#ifdef __APPLE__
#define EXP10(x) pow(10, x)
#else
#define EXP10(x) exp10(x)
#endif

using namespace std;

class vcf_parse_errpr: public runtime_error
{
public:
  vcf_parse_errpr (const string& msg) : runtime_error(msg) {}
};

struct SNVRecord
{
  string err_coord;
  string snv_name;

  unsigned int al_count;
  int al_names[4];
  corax_state_t al_states[4];

  unsigned int pl_per_sample;
  int pl_d10_map[10];

  int gt_count;
  int max_ploidy;
  int32_t * sample_gt;
  float * sample_lh;
  int sample_lh_size;
  int * sample_plh;
  int sample_plh_size;

  size_t lh_underflow;

  void error(const string& msg)
  {
    throw vcf_parse_errpr(err_coord + msg);
  }
};

//       0  1  2  3  4  5  6  7  8  9
// VCF: AA AC AG AT CC CG CT GG GT TT
// RAX: AA CC GG TT AC AG AT CG CT GT
                                    /* AA AC AG AT CC CG CT GG GT TT */
static const int vcf_to_rax_map[10] = {0, 4, 5, 6, 1, 7, 8, 2, 9, 3 };

char gt10_to_char[4][4];
char gt16_to_char[4][4];

                            /* A   C   G   T  */
int gt16_to_stateid[4][4] =  { {0,  4,  5,  6},    /* A  */
                               {10, 1,  7,  8},    /* C  */
                               {11, 13, 2,  9},    /* G  */
                               {12, 14, 15, 3},    /* T  */
                             };


#ifdef _RAXML_VCF_DEBUG
static const char gt4_inv_map[][3] = {"A", "C", "G", "T"};
static const char gt10_inv_map[][3] = {"AA", "CC", "GG", "TT", "AC", "AG", "AT", "CG", "CT", "GT"};
static const char gt16_inv_map[][3] = {"AA", "CC", "GG", "TT", "AC", "AG", "AT", "CG", "CT", "GT",
                                                               "CA", "GA", "TA", "GC", "TC", "TG"};
#endif

static const char vcf_lh_field[][6] = {"NONE", "GL", "PL", "FPL", "G10", "G10N"};

static const char gap_char = '-';

bool VCFStream::vcf_file(const std::string& fname)
{
  htsFile * fp    = hts_open(fname.c_str(), "rb");

  if (!fp)
    return false;

  const htsFormat * fmt = hts_get_format(fp);

  bool res = (fmt->category == variant_data);

  hts_close(fp);

  return res;
}


static VCFLikelihoodMode detect_likelihood_mode(VCFStream& stream, bcf_hdr_t *hdr)
{
  VCFLikelihoodMode lh_mode = VCFLikelihoodMode::none;

  bcf_hrec_t * hrec = NULL;
  if (stream.use_normalized_gl() && (hrec = bcf_hdr_get_hrec(hdr, BCF_HL_FMT, "ID", "G10N", NULL)) != NULL)
  {
    lh_mode = VCFLikelihoodMode::g10n;
  }
  else if ((hrec = bcf_hdr_get_hrec(hdr, BCF_HL_FMT, "ID", "G10", NULL)) != NULL)
    lh_mode = VCFLikelihoodMode::g10;
  else if ((hrec = bcf_hdr_get_hrec(hdr, BCF_HL_FMT, "ID", "PL", NULL)) != NULL)
    lh_mode = VCFLikelihoodMode::pl;
  else if ((hrec = bcf_hdr_get_hrec(hdr, BCF_HL_FMT, "ID", "FPL", NULL)) != NULL)
    lh_mode = VCFLikelihoodMode::fpl;
  else if ((hrec = bcf_hdr_get_hrec(hdr, BCF_HL_FMT, "ID", "GL", NULL)) != NULL)
    lh_mode = VCFLikelihoodMode::gl;
  else
    lh_mode = VCFLikelihoodMode::none;

  LOG_DEBUG << "VCF: uncertainty type = " <<  vcf_lh_field[(int) lh_mode] << endl;

  return lh_mode;
}

static size_t get_snv_count(const char * fname)
{
  // This is an ugly workaround, but there seems to be no better way to get
  // the number of SNPs from the stupid VCF
  size_t snv_count = 0;
  htsFile * fp = hts_open(fname, "rb");
  if (fp)
  {
    bcf_hdr_t * hdr = bcf_hdr_read(fp);
    bcf1_t    * rec = bcf_init1();
    while (bcf_read1(fp, hdr, rec) >= 0)
      snv_count++;
    bcf_destroy1(rec);
    bcf_hdr_destroy(hdr);
    hts_close(fp);
  }
  return snv_count;
}

static void set_sample_names(MSA& msa, bcf_hdr_t * hdr)
{
  size_t sample_count = bcf_hdr_nsamples(hdr);
  string dummy(msa.num_sites(), '*');

  /* read sample names from VCF, and add respective taxa to MSA */
  try
  {
    for (size_t i = 0; i < sample_count; ++i)
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
}

static void init_maps()
{
  char inv_charmap10[CORAX_ASCII_SIZE] = {0};
  char inv_charmap16[CORAX_ASCII_SIZE] = {0};
  for (unsigned int i = 0; i < CORAX_ASCII_SIZE; ++i)
  {
    if (corax_map_nt[i] && !inv_charmap10[corax_map_nt[i]])
      inv_charmap10[corax_map_nt[i]] = (char)i;

    if (corax_map_gt16[i] && CORAX_STATE_POPCNT(corax_map_gt16[i]) == 1)
    {
      int state_id = CORAX_STATE_CTZ(corax_map_gt16[i]);
      if (!inv_charmap16[state_id])
        inv_charmap16[state_id] = (char)i;
    }
  }

  for (size_t i = 0; i < 4; ++i)
  {
    for (size_t j = 0; j < 4; ++j)
    {
      gt10_to_char[i][j] = inv_charmap10[ (1u << i) | (1u << j)];

      size_t state_id = gt16_to_stateid[i][j];
      gt16_to_char[i][j] = inv_charmap16[state_id];
    }
  }
}

static void init_snv_rec(SNVRecord& snv)
{
  snv.sample_lh_size = 0;
  snv.sample_plh_size = 0;
  snv.sample_gt = NULL;
  snv.sample_plh = NULL;
  snv.sample_lh = NULL;
  snv.lh_underflow = 0;
}

static void free_snv_rec(SNVRecord& snv)
{
  free(snv.sample_gt);
  free(snv.sample_lh);
  free(snv.sample_plh);
}

static void init_pl_d10_map(SNVRecord& snv)
{
  unsigned int i, k;
  unsigned int g = 0;

  for (i = 0; i < 10; ++i)
    snv.pl_d10_map[i] = -1;

  /* - genotype order in PL field differs for every line and depends on REF/ALT alleles
   * - hence, we build a mapping between PL field index and genotype state index used in raxml-ng
   * - eg. if REF=A and ALT=T,C -> pl_d10_map = [ 0 6 3 4 8 1 -1 -1 -1 -1 ]  */
  for (i = 0; i < snv.al_count; ++i)
  {
    for (k = 0; k <= i; ++k)
    {
      int c1 = CORAX_STATE_CTZ(snv.al_states[k]);
      int c2 = CORAX_STATE_CTZ(snv.al_states[i]);
      int d10 = CORAX_STATE_CTZ(corax_map_gt10[(int) gt10_to_char[c1][c2]]);
      snv.pl_d10_map[g++] = d10;
#ifdef _RAXML_VCF_DEBUG
      printf("%s ", gt10_inv_map[d10]);
#endif
    }
  }

  assert(g == snv.pl_per_sample);
}

static void read_snv_fixed(SNVRecord& snv, bcf_hdr_t * hdr, bcf1_t * rec)
{
  unsigned int i, k;
  const char * supported_alleles = "ACGTN";

  auto chr = bcf_hdr_id2name(hdr, rec->rid);
  auto pos = rec->pos+1;
  snv.err_coord = "[chr " + string(chr) + ", pos " + to_string(pos) +  "] ";

  snv.al_count = rec->n_allele;
  snv.pl_per_sample = snv.al_count * (snv.al_count + 1) / 2;
  if (snv.al_count > 4)
   snv.error("Wrong number of alleles (" + to_string(snv.al_count) + ")");

  snv.snv_name = strlen(rec->d.id) > 1 ? rec->d.id : string(chr) + ":" + to_string(pos);
#ifdef _RAXML_VCF_DEBUG
  LOG_DEBUG << "SNV: " << snv.snv_name << endl;
#endif

  for (i = 0; i < 4; ++i)
    snv.al_names[i] = '-';
  for (i = 0; i < rec->n_allele; ++i)
  {
    if (strlen(rec->d.allele[i]) != 1 || !strchr(supported_alleles, rec->d.allele[i][0]))
      snv.error("Unsupported allele name: " + string(rec->d.allele[i]));

    snv.al_names[i] = rec->d.allele[i][0];
  }

// printf("alleles: %c %c %c %c\n", snv.al_names[0], snv.al_names[1], snv.al_names[2], snv.al_names[3]);

  for (i = 0; i < 4; ++i)
    snv.al_states[i] = 0;
  for (i = 0; i < snv.al_count; ++i)
    snv.al_states[i] = corax_map_nt[snv.al_names[i]];

  /* sanity-check alleles */
  for (i = 0; i < snv.al_count-1; ++i)
  {
    for (k = i+1; k < snv.al_count; ++k)
    {
      if (((snv.al_states[i] & snv.al_states[k]) != 0) && snv.al_names[i] != 'N' && snv.al_names[k] != 'N')
      {
        snv.error("Wrong REF/ALT alleles: " +
                  to_string(char(snv.al_names[i])) + " / " + char(snv.al_names[k]));
      }
    }
  }

#ifdef _RAXML_VCF_DEBUG
  printf("chrom: %s, pos: %ld, REF: %c, ALT: %c,%c,%c  GT: ",
         chr, pos, snv.al_names[0], snv.al_names[1], snv.al_names[2], snv.al_names[3]);
#endif

  init_pl_d10_map(snv);

#ifdef _RAXML_VCF_DEBUG
  printf("\n");
#endif
}

static void read_snv_sample_data(SNVRecord& snv, bcf_hdr_t * hdr, bcf1_t * rec,
                                 VCFLikelihoodMode lh_mode)
{
   int sample_count = bcf_hdr_nsamples(hdr);
   int32_t ngt_arr = 0;

   snv.gt_count = bcf_get_genotypes(hdr, rec, &snv.sample_gt, &ngt_arr);
   if (!snv.gt_count)
     snv.error("Field GT not found");
   snv.max_ploidy = snv.gt_count / sample_count;

#ifdef _RAXML_VCF_DEBUG
   printf("gt_count: %d, max_ploidy: %d\n", snv.gt_count, snv.max_ploidy);
#endif

  if (lh_mode == VCFLikelihoodMode::none)
    return;

  const char * lh_field_name = vcf_lh_field[(int) lh_mode];

  bcf_fmt_t * lh_field = bcf_get_fmt(hdr, rec, lh_field_name);

  if (!lh_field)
    snv.error("Field " + string(lh_field_name) + " not found in FORMAT");

#ifdef _RAXML_VCF_DEBUG
  LOG_DEBUG << "Found " << lh_field_name << " field with "
            << lh_field->n << " genotypes..." << endl;
#endif

  int lh_per_sample = 0;
  switch (lh_mode)
  {
    case VCFLikelihoodMode::g10:
    case VCFLikelihoodMode::g10n:
      lh_per_sample = 10;
      break;
    case VCFLikelihoodMode::pl:
    case VCFLikelihoodMode::gl:
      lh_per_sample = snv.pl_per_sample;
      break;
    case VCFLikelihoodMode::fpl:
      lh_per_sample = 4;
      break;
    case VCFLikelihoodMode::none:
    case VCFLikelihoodMode::autodetect:
      assert(0);
      break;
  }

  if (lh_field->n != lh_per_sample)
  {
    snv.error("Invalid size of " + string(lh_field_name) + " format: " +
              to_string(lh_field->n) + " (expected: " + to_string(lh_per_sample) + ")");
  }

  int n_read = 0;
  switch (lh_mode)
  {
    case VCFLikelihoodMode::g10:
    case VCFLikelihoodMode::g10n:
    case VCFLikelihoodMode::gl:
      n_read = bcf_get_format_float(hdr, rec, lh_field_name, &snv.sample_lh, &snv.sample_lh_size);
      break;
    case VCFLikelihoodMode::pl:
    case VCFLikelihoodMode::fpl:
      n_read = bcf_get_format_int32(hdr, rec, lh_field_name, &snv.sample_plh, &snv.sample_plh_size);
      break;
    case VCFLikelihoodMode::none:
    case VCFLikelihoodMode::autodetect:
      assert(0);
      break;
  }

#ifdef _RAXML_VCF_DEBUG
      LOG_DEBUG << "Loaded " << string(lh_field_name) << ": " << n_read << " entries" << endl;
#endif

  if (!n_read)
    snv.error("No data entries found for the field: " + string(lh_field_name));

  int n_expected = bcf_hdr_nsamples(hdr) * lh_field->n;
  if (n_read != n_expected)
  {
    snv.error("Invalid number of entries in " + string(lh_field_name) + " field: " +
              to_string(n_read) + " (expected:  " + to_string(n_expected) + ")");
  }
}

void set_g10_probs(MSA& msa, SNVRecord& snv, size_t snv_id, size_t sample_id)
{
  auto site_probs = msa.probs(sample_id, snv_id);
  auto gt_g10 = snv.sample_lh + sample_id * 10;

  if (msa.states() < 10)
  {
    snv.error("Wrong number of model states: " + to_string(msa.states()) + "\n " +
              "Try using a different model (GT10 or GT16) or genotype likelihood type.");
  }

  /* G10 field: all 10 genotype likelihoods are defined */
  int gl_underflow = 1;
  for (unsigned int k = 0; k < 10; ++k)
  {
      auto gl = gt_g10[k];
      auto s = vcf_to_rax_map[k];

      if (gl > 0.)
      {
        snv.error("[" + msa.label(sample_id) +
                  "] G10 field contains a positive value: " + to_string(gl));
      }

      site_probs[s] = isfinite(gl) ? EXP10(gl) : 0.;
      gl_underflow &= (gl < _RAXML_VCF_MINGL);
  }

  /* if *all* genotype likelihoods are below threshold, convert this SNV to gap */
  if (gl_underflow)
  {
#ifdef _RAXML_VCF_DEBUG
    printf("taxon: %s, SNV: %lu, GL: ", msa.label(sample_id).c_str(), snv_id);
    for (size_t k = 0; k < 10; ++k)
      printf("%lf ", gt_g10[k]);
    printf("\n");
#endif

    snv.lh_underflow++;
    for (size_t k = 0; k < 10; ++k)
      site_probs[k] = 1.;
    msa[sample_id][snv_id] = '-';
  }
}

void set_gl_probs(MSA& msa, SNVRecord& snv, size_t snv_id, size_t sample_id)
{
  unsigned int k;
  auto site_probs = msa.probs(sample_id, snv_id);
  auto gt_gl = snv.sample_lh + sample_id * snv.pl_per_sample;

  for (size_t k = 0; k < msa.states(); ++k)
    site_probs[k] = 0.;

#ifdef _RAXML_VCF_DEBUG
  printf("GL: ");
  for (k = 0; k < snv.pl_per_sample; ++k)
    printf("%f ", gt_gl[k]);
  printf("\n");
#endif

  for (k = 0; k < snv.pl_per_sample; ++k)
  {
    auto gl = gt_gl[k];
    if (gl != bcf_float_missing && isfinite(gl))
    {
      if (gl > 0.)
      {
        snv.error("[" + msa.label(sample_id) +
                  "] GL field contains a positive value: " + to_string(gl));
      }
      else
        site_probs[snv.pl_d10_map[k]] = EXP10(gl);
    }
    else
      site_probs[snv.pl_d10_map[k]] = 0.;
  }
}

void set_pl_probs(MSA& msa, SNVRecord& snv, size_t snv_id, size_t sample_id)
{
  unsigned int k;
  auto site_probs = msa.probs(sample_id, snv_id);
  auto gt_pl = snv.sample_plh + sample_id * snv.pl_per_sample;

  for (size_t k = 0; k < msa.states(); ++k)
    site_probs[k] = 0.;

#ifdef _RAXML_VCF_DEBUG
  printf("PL: ");
  for (k = 0; k < snv.pl_per_sample; ++k)
    printf("%d ", gt_pl[k]);
  printf("\n");
#endif

  int min_pl = INT_MAX;
  for (k = 0; k < snv.pl_per_sample; ++k)
  {
    if (gt_pl[k] != bcf_int32_missing)
      min_pl = std::min(min_pl, gt_pl[k]);
  }

  if (min_pl < 0.)
  {
    snv.error("[" + msa.label(sample_id) +
              "] PL field contains a negative value: " + to_string(min_pl));
  }

  for (k = 0; k < snv.pl_per_sample; ++k)
  {
    auto pl = gt_pl[k];
    site_probs[snv.pl_d10_map[k]] = pl == bcf_int32_missing ? 0 : EXP10(-0.1 * pl);
  }
}

void set_fpl_probs(MSA& msa, SNVRecord& snv, size_t snv_id, size_t sample_id)
{
  auto site_probs = msa.probs(sample_id, snv_id);
  auto gt_fpl = snv.sample_plh + sample_id * 4;

  for (unsigned int k = 0; k < 10; ++k)
    site_probs[k] = 0.;

  int pl_ref = std::min(gt_fpl[0], gt_fpl[1]);
  double p_ref = EXP10(-0.1 * pl_ref);
  double p_het = EXP10(-0.1 * gt_fpl[2]);
  double p_alt = EXP10(-0.1 * gt_fpl[3]);

  int min_pl = std::min({pl_ref, gt_fpl[2], gt_fpl[3]});

  if (min_pl < 0.)
  {
    snv.error("[" + msa.label(sample_id) +
              "] FPL field contains negative value: " + to_string(min_pl));
  }

  site_probs[snv.pl_d10_map[0]] = p_ref;
  site_probs[snv.pl_d10_map[1]] = p_het;
  site_probs[snv.pl_d10_map[2]] = p_alt;
}

void set_sample_probs(MSA& msa, SNVRecord& snv, size_t snv_id, size_t sample_id,
                      VCFLikelihoodMode lh_mode)
{
  const size_t msa_states = msa.states();
  bool msa_phased = (msa_states == 16);

  int32_t *gt_ptr = snv.sample_gt + sample_id * snv.max_ploidy;

  bool haploid = (snv.max_ploidy == 1 || gt_ptr[1] == bcf_int32_vector_end);

  const int al1 = bcf_gt_allele(gt_ptr[0]);
  const int al2 = haploid ? al1 : bcf_gt_allele(gt_ptr[1]);

//  printf("sample_id: %d, haploid: %d, al1: %d, al2: %d \n", sample_id, haploid, al1, al2);

  bool gt_phased = haploid ? false : bcf_gt_is_phased(gt_ptr[1]);

  /* VCF genotype likelihood fields do not support phasing now, but this might change later */
  bool pr_phased = (lh_mode == VCFLikelihoodMode::none);
  bool phased = msa_phased && gt_phased && pr_phased;

  auto gt1 = CORAX_STATE_CTZ(snv.al_states[al1]);
  auto gt2 = CORAX_STATE_CTZ(snv.al_states[al2]);

  char c = gap_char;
  auto site_probs = msa.probs(sample_id, snv_id);

  if (al1 >= 0 && al2 >= 0)
  {
    c = phased ? gt16_to_char[gt1][gt2] : gt10_to_char[gt1][gt2];

    switch (lh_mode)
    {
      case VCFLikelihoodMode::g10:
      case VCFLikelihoodMode::g10n:
        set_g10_probs(msa, snv, snv_id, sample_id);
        break;
      case VCFLikelihoodMode::pl:
        set_pl_probs(msa, snv, snv_id, sample_id);
        break;
      case VCFLikelihoodMode::gl:
        set_gl_probs(msa, snv, snv_id, sample_id);
        break;
      case VCFLikelihoodMode::fpl:
        set_fpl_probs(msa, snv, snv_id, sample_id);
        break;
      case VCFLikelihoodMode::none:
      {
        // no uncertainty specified, called genotype gets likelihood 1.0
        corax_state_t ml_state = phased ? corax_map_gt16[(int) c] : corax_map_gt10[(int) c];
        corax_state_t state = 1;
        for (unsigned int k = 0; k < msa_states; ++k, state <<= 1)
          site_probs[k] = (state & ml_state) ? 1.0 : 0.0;
      }
        break;
      case VCFLikelihoodMode::autodetect:
        assert(0);
    }
  }
  else
  {
    /* gap / missing data */
    for (size_t k = 0; k < msa_states; ++k)
      site_probs[k] = 1.;
  }

  /* convert unphased 10-state genotype into phased 16-state model: pYX = pXY */
  if (msa_states == 16 && !pr_phased)
  {
    for (size_t k = 10; k < 16; ++k)
      site_probs[k] = site_probs[k-6];
  }

  /* set ML genotype */
  msa[sample_id][snv_id] = c;

#ifdef _RAXML_VCF_DEBUG
  if (sample_id < 4)
  {
    printf("site: %lu, sample: %lu, gt: %c  phased: %d,  probs: ", snv_id, sample_id, c, phased);
    for (unsigned int k = 0; k < msa_states; ++k)
      printf("%s=%lf ", haploid ? gt4_inv_map[k] : gt16_inv_map[k], site_probs[k]);
    printf("\n");
  }
#endif
}

void set_allgap_snv(MSA& msa, size_t snv_id)
{
  for (size_t i = 0; i < msa.size(); ++i)
  {
    msa[i][snv_id] = gap_char;
    if (msa.probabilistic())
    {
      auto site_probs = msa.probs(i, snv_id);
      for (size_t k = 0; k < msa.states(); ++k)
        site_probs[k] = 1.;
    }
  }
}

VCFStream& operator>>(VCFStream& stream, MSA& msa)
{
  const char * fname = stream.fname().c_str();

  size_t site_count = get_snv_count(fname);

  htsFile * fp    = hts_open(fname, "rb");

  if (!fp)
    throw runtime_error("Cannot open VCF file: " + stream.fname());

  const htsFormat * fmt = hts_get_format(fp);

  if (fmt->category != variant_data)
    throw runtime_error("Invalid VCF file type");

  bcf_hdr_t * hdr = bcf_hdr_read(fp);
  bcf1_t * rec    = bcf_init1();

  /* autodetect genotype likelihood fields */
  auto lh_mode = stream.gt_likelihood_mode() == VCFLikelihoodMode::autodetect ?
                     detect_likelihood_mode(stream, hdr) : stream.gt_likelihood_mode();

  size_t sample_count = bcf_hdr_nsamples(hdr);

  LOG_DEBUG << "VCF samples: " << sample_count << ", variants: " << site_count << endl;

  if (!sample_count || !site_count)
    throw runtime_error("VCF file is empty or corrupted!");

  msa = MSA(site_count);

  set_sample_names(msa, hdr);

  assert(msa.size() == sample_count);

  msa.states(stream.num_states());
  assert(msa.states() > 0);

  LOG_DEBUG << "MSA states: " << msa.states() << endl;

  init_maps();

  SNVRecord snv_rec;
  init_snv_rec(snv_rec);

  /* iterate over VCF lines, ie SNVs */
  size_t j = 0;
  size_t invalid_lines = 0;
  while (bcf_read1(fp, hdr, rec) >= 0)
  {
    bcf_unpack(rec, BCF_UN_ALL);

    try
    {
      /* read fixed portion of VCF line -> eg REF/ALT allele names */
      read_snv_fixed(snv_rec, hdr, rec);

      msa.site_name(j, snv_rec.snv_name);

      /* load per-sample genotype likelihoods into intermediate array  */
      read_snv_sample_data(snv_rec, hdr, rec, lh_mode);

      /* iterate over per-sample records and set genotype likelihoods to MSA*/
      for (size_t i = 0; i < sample_count; ++i)
        set_sample_probs(msa, snv_rec, j, i, lh_mode);
    }
    catch (vcf_parse_errpr& e)
    {
      if (stream.skip_invalid_snvs())
      {
        LOG_WARN << "ERROR: " << e.what() << " -> data line ignored!" << endl;
        set_allgap_snv(msa, j);
        invalid_lines++;
      }
      else
        throw e;
    }

    j++;

    if (j > site_count-1)
      break;
  }

  assert(j == site_count);

  if (invalid_lines > 0)
  {
    LOG_WARN << endl << "WARNING: VCF data lines with parsing errors: " << invalid_lines << endl << endl;
    if (invalid_lines == site_count)
      throw runtime_error("No valid VCF data lines found!");
  }

  if (snv_rec.lh_underflow > 0)
  {
    LOG_WARN << endl << "WARNING: Some low-confidence SNVs were converted to gaps to prevent underflow: " << snv_rec.lh_underflow
             << " (" << (100.*snv_rec.lh_underflow/(site_count*sample_count)) << "%)" << endl << endl;
  }

  free_snv_rec(snv_rec);
  bcf_destroy1(rec);
  bcf_hdr_destroy(hdr);

  int ret;
  if ( (ret = hts_close(fp)) )
    throw runtime_error("hts_close() returned non-zero status: " + to_string(ret));

#ifdef _RAXML_VCF_DEBUG
  corax_phylip_save("vcfout.phy", msa.pll_msa());
#endif

  return stream;
}




#include "IcSupportTree.hpp"

#include "corax/tree/utree_split.h"

IcSupportTree::IcSupportTree(const Tree& tree, bool icAll) :  SupportTree(tree),
  _ic_all(icAll), _ica_filter(RAXML_ICTC_SPLIT_FILTER), _ica_cutoff(RAXML_ICTC_SPLIT_CUTOFF)
{
  _ref_splits_only = false;
}

bool IcSupportTree::compute_support()
{
  auto ref_split_count = num_splits();
  auto tot_split_count = _pll_splits_hash->entry_count;
  double min_alt_support = _ica_cutoff * _num_bs_trees;
  std::vector<bool> conflict_split;

  _support.resize(ref_split_count);

  bitv_hash_entry_t ** sorted_splits = corax_utree_split_hashtable_sorted(_pll_splits_hash, CORAX_TRUE);

  if (!sorted_splits)
    return false;

  doubleVector alt_support_vec;
  alt_support_vec.reserve(1);
  for (unsigned int i = 0; i < tot_split_count; i++)
  {
    bitv_hash_entry_t * e_ref = sorted_splits[i];
    double ic = 0.;
    double n = 1.0;
    double alt_support = 0.;
    double ref_support = 0.;
    bool negative_ic = false;

    // non-reference split -> ignore
    if (e_ref->bip_number >= ref_split_count)
      continue;

    ref_support = e_ref->support;

    if ((size_t) ref_support == _num_bs_trees)
    {
      // special case: full support
      _support[e_ref->bip_number] = 1.0;
      continue;
    }

    if (_ica_filter)
      conflict_split.assign(tot_split_count, false);

    for (unsigned int j = 0; j < tot_split_count; j++)
    {
      bitv_hash_entry_t * e_alt = sorted_splits[j];

      // reference split -> ignore
      if (e_alt->bip_number < ref_split_count)
        continue;

      // ginore splits with frequency below threshold
      if (_ic_all && alt_support > 0. && e_alt->support < min_alt_support)
        break;

      // check compatibility
      if (!corax_utree_split_compatible(e_ref->bit_vector,
                                        e_alt->bit_vector,
                                        _pll_splits_hash->bitv_len,
                                        _pll_splits_hash->bit_count))
      {
        bool add_alt_split = true;

        // Split filter as in RAXML8, for description and rationale see:
        // https://cme.h-its.org/exelixis/resource/download/NewManual.pdf#page=49
        if (_ica_filter && alt_support > 0.)
        {
          for (unsigned int k = 0; k < j; k++)
          {
            bitv_hash_entry_t * e_old = sorted_splits[k];

             // not in the set of accepted conflict splits -> ignore
             if (!conflict_split[k])
               continue;

             // if current split is compatible with one of the splits already
             // in the conflict split set, ignore it
             if (corax_utree_split_compatible(e_old->bit_vector,
                                              e_alt->bit_vector,
                                              _pll_splits_hash->bitv_len,
                                              _pll_splits_hash->bit_count))
             {
               add_alt_split = false;
               break;
             }
          }
        }

        if (add_alt_split)
        {
          alt_support_vec.push_back(e_alt->support);
          alt_support += e_alt->support;
          n += 1.;

          // if *any* alternative conflicting split has higher frequency
          // than the reference split, then IC/ICA value will be negative
          if (e_alt->support > ref_support)
            negative_ic = true;

          // for IC, consider only one conflicting split with the highest frequency
          if (!_ic_all)
            break;

          //  mark this split as belonging to the alternative conflicting set
          if (_ica_filter)
            conflict_split[j] = true;
        }
      }
    }

    double tot_support = ref_support + alt_support;

    if (tot_support > 0.)
    {
      double ref_freq = ref_support / tot_support;

      if (ref_freq > 0.)
        ic += ref_freq * log(ref_freq);

      for(auto s: alt_support_vec)
      {
        assert(s > 0.);

        double alt_freq =  s / tot_support;

        if(alt_freq > 0.)
          ic += alt_freq * log(alt_freq);
      }

      ic += log(n);

      // the original formula has log_n(X), so we use a small math trick...
      ic /= log(n);

      if (negative_ic)
        ic *= -1;
    }
    else
    {
      //neither support for the actual bipartition, nor for the conflicting ones
      //I am not sure that this will happen, but anyway
      ic = 0.;
    }

    alt_support_vec.clear();

//    printf("split %d, REF = %lf, ALT = %lf, IC = %lf\n", e_ref->bip_number, ref_support, alt_support, ic);

    _support[e_ref->bip_number] = ic;
  }

  free(sorted_splits);

  return true;
}

IcSupportTree::~IcSupportTree ()
{
}


#include "ParsimonyMSA.hpp"

ParsimonyMSA::ParsimonyMSA (std::shared_ptr<PartitionedMSA> parted_msa, unsigned int attributes)
{
  init_pars_msa(parted_msa);
  create_pll_partitions(attributes);
}

void ParsimonyMSA::init_pars_msa(std::shared_ptr<PartitionedMSA> orig_msa)
{
  if (orig_msa->part_count() == 1)
  {
    _pars_msa = orig_msa;
    return;
  }

  // create 1 partition per datatype
  auto pars_msa = new PartitionedMSA(orig_msa->taxon_names());
  _pars_msa.reset(pars_msa);

  NameIdMap datatype_pinfo_map;
  for (const auto& pinfo: orig_msa->part_list())
  {
    const auto& model = pinfo.model();
    auto data_type_name = model.data_type_name();

    auto iter = datatype_pinfo_map.find(data_type_name);
    if (iter == datatype_pinfo_map.end())
    {
      pars_msa->emplace_part_info(data_type_name, model.data_type(), model.to_string());
      auto& pars_pinfo = pars_msa->part_list().back();
      pars_pinfo.msa(MSA(pinfo.msa().num_sites()));
      datatype_pinfo_map[data_type_name] = pars_msa->part_count()-1;
    }
    else
    {
      auto& msa = pars_msa->part_list().at(iter->second).msa();
      msa.num_sites(msa.num_sites() + pinfo.msa().num_sites());
    }
  }

  // set_per-datatype MSA
  for (size_t j = 0; j < orig_msa->taxon_count(); ++j)
  {
    for (auto& pars_pinfo: pars_msa->part_list())
    {
      auto pars_datatype = pars_pinfo.model().data_type_name();
      std::string sequence;
      sequence.resize(pars_pinfo.msa().num_sites());
      size_t offset = 0;

      for (const auto& pinfo: orig_msa->part_list())
      {
        // different datatype -> skip for now
        if (pinfo.model().data_type_name() != pars_datatype)
          continue;

        const auto w = pinfo.msa().weights();
        const auto s = pinfo.msa().at(j);

        if (w.empty())
        {
          for (size_t k = 0; k < s.size(); ++k)
            sequence[offset++] = s[k];
        }
        else
        {
          for (size_t k = 0; k < w.size(); ++k)
          {
            auto wk = w[k];
            while(wk-- > 0)
              sequence[offset++] = s[k];
          }
        }
      }

      assert(offset == sequence.size());

      pars_pinfo.msa().append(sequence);
    }
  }

  /* Currently, parsimony computation can not use pattern compression */
//  if (instance.opts.use_pattern_compression)
//  {
//    for (auto& pinfo: pars_msa->part_list())
//    {
//      pinfo.compress_patterns();
//    }
//  }

}

void ParsimonyMSA::create_pll_partitions(unsigned int attributes)
{
  free_pll_partitions();

  for (const auto& pinfo: _pars_msa->part_list())
  {
    const auto& model = pinfo.model();
    const auto& msa = pinfo.msa();

    auto partition = corax_partition_create(_pars_msa->taxon_count(),
                                             0,   /* number of CLVs */
                                             model.num_states(),
                                             msa.length(),
                                             1,
                                             1, /* pmatrix count */
                                             1,  /* rate_cats */
                                             0,  /* scale buffers */
                                             attributes);

    /* set pattern weights */
    if (!msa.weights().empty())
      corax_set_pattern_weights(partition, msa.weights().data());

    /* set tip states */
    for (size_t j = 0; j < msa.size(); ++j)
    {
      corax_set_tip_states(partition, j, model.charmap(), msa.at(j).c_str());
    }

    _pll_partitions.push_back(partition);
  }
  assert(_pll_partitions.size() == _pars_msa->part_count());
}

void ParsimonyMSA::free_pll_partitions()
{
  for (auto p: _pll_partitions)
    corax_partition_destroy(p);
  _pll_partitions.clear();
}

size_t ParsimonyMSA::memsize_estimate() const
{
  size_t nodes = 4;  // nodes per taxon (1 tip + 4 inner)
  size_t vec_size = 0;

  for (const auto& pinfo: _pars_msa->part_list())
  {
    vec_size += pinfo.length() * pinfo.model().num_states();
  }

  auto memsize = vec_size * _pars_msa->taxon_count() * nodes / 8;
  return memsize;
}


ParsimonyMSA::~ParsimonyMSA ()
{
  free_pll_partitions();
}


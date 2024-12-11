#include "PartitionedMSA.hpp"

using namespace std;

PartitionedMSA::PartitionedMSA(): _auto_part (new AutoPartitioner()), _difficulty_score(-1.)
{}

PartitionedMSA::PartitionedMSA(const NameList& taxon_names) : PartitionedMSA()
{
  set_taxon_names(taxon_names);
}

PartitionedMSA& PartitionedMSA::operator=(PartitionedMSA&& other)
{
  _part_list = std::move(other._part_list);
  _full_msa = std::move(other._full_msa);
  _taxon_names = std::move(other._taxon_names);
  _taxon_id_map = std::move(other._taxon_id_map);
   return *this;
}

void PartitionedMSA::init_single_model(DataType data_type, const std::string &model_string)
{
  _auto_part->init_from_string(*this, data_type, model_string);
}

ModelCRefMap PartitionedMSA::models() const
{
  ModelCRefMap mmap;
  for (size_t p = 0; p < part_count(); ++p)
    mmap.emplace(p, _part_list.at(p).model());

  return mmap;
}

void PartitionedMSA::set_taxon_names(const NameList& taxon_names)
{
  _taxon_names.assign(taxon_names.cbegin(), taxon_names.cend());
  for (size_t i = 0; i < _taxon_names.size(); ++i)
    _taxon_id_map[_taxon_names[i]] = i;

  assert(_taxon_names.size() == taxon_names.size() && _taxon_id_map.size() == taxon_names.size());
}

uintVector PartitionedMSA::get_site_part_assignment() const
{
  const size_t full_len = _full_msa.length();
  uintVector spa(full_len);

  size_t p = 0;
  for (auto& pinfo: _part_list)
  {
    try
    {
      pinfo.mark_partition_sites(p+1, spa);
    }
    catch (MultiplePartitionForSiteException& e)
    {
      e.pinfo2(_part_list.at(spa[e.site()-1]-1));
      throw e;
    }
    p++;
  }

  /* check if all sites were assigned to partitions */
  MissingPartitionForSiteException e_unassinged;
  for (size_t i = 0; i < full_len; ++i)
  {
    if (!spa[i])
      e_unassinged.add_unassigned_site(i+1);
  }

  if (e_unassinged.count() > 0)
    throw e_unassinged;

  return spa;
}

const uintVector& PartitionedMSA::site_part_map() const
{
  if (_site_part_map.empty() && part_count() > 1)
    _site_part_map = get_site_part_assignment();

  return _site_part_map;
}

size_t PartitionedMSA::full_msa_site(size_t index, size_t site) const
{
  if (part_count() == 1)
    return site;
  else
  {
    size_t cur_site = site;
    auto index_map = site_part_map();

    // TODO: this can be optimized
    for (size_t i = 0; i < index_map.size(); ++i)
    {
      if (index_map[i] == index+1)
      {
        if (!cur_site)
          return i;

        cur_site--;
      }
    }

    throw runtime_error("Site " + to_string(site+1) +
                        " not found in partition " +  to_string(index+1));
  }
}

/*
 *  This function returns a pair (partition_id, local_site_id) for each site in
 *  the original, full, uncompressed MSA file.
 */
IdPairVector PartitionedMSA::full_to_parted_sitemap() const
{
  auto total_sites = this->total_sites();
  assert(site_part_map().empty() || site_part_map().size() == total_sites);

  IdPairVector sitemap(total_sites);
  IDVector part_site_idx(part_count(), 0);
  for (size_t i = 0; i < total_sites; ++i)
  {
    auto pid = site_part_map().empty() ? 0 : site_part_map()[i] - 1;
    auto sid = part_site_idx[pid]++;
    auto& spmap = part_info(pid).msa().site_pattern_map();
    sitemap[i].first = pid;
    sitemap[i].second = spmap.empty() ? sid : spmap[sid];
  }

  return sitemap;
}


void PartitionedMSA::full_msa(MSA&& msa)
{
  _full_msa = std::move(msa);

  set_taxon_names(_full_msa.labels());
}

void PartitionedMSA::split_msa()
{
  bool need_split;
  string full_range = "1-" + to_string(_full_msa.length());

  if (part_count() == 0)
    return;

  _auto_part->update_partition_ranges(*this);

  if (part_count() == 1)
  {
    const string& first_range = _part_list[0].range_string();
    need_split = !first_range.empty() && first_range != full_range && first_range != "all";
  }
  else
    need_split = true;

  if (need_split)
  {
    /* split MSA into partitions */
    corax_msa_t ** part_msa_list =
        corax_msa_split(_full_msa.pll_msa(), site_part_map().data(), part_count());

    for (size_t p = 0; p < part_count(); ++p)
    {
      part_msa(p, part_msa_list[p]);
      corax_msa_destroy(part_msa_list[p]);

      /* distribute external site weights to per-partition MSAs */
      if (!_full_msa.weights().empty())
      {
        auto& msa = _part_list[p].msa();
        WeightVector w(msa.length());
        const auto full_weights = _full_msa.weights();
        assert(full_weights.size() == site_part_map().size());

        size_t pos = 0;
        for (size_t i = 0; i < site_part_map().size(); ++i)
        {
          if (_site_part_map[i] == p+1)
            w[pos++] = full_weights[i];
        }
        assert(pos == msa.length());
        msa.weights(w);
      }
    }
    free(part_msa_list);
  }
  else
  {
    if (_part_list[0].range_string().empty())
      _part_list[0].range_string(full_range);
    part_msa(0, std::move(_full_msa));
  }
}

void PartitionedMSA::compress_patterns(bool store_backmap)
{
  for (PartitionInfo& pinfo: _part_list)
  {
    pinfo.compress_patterns(store_backmap);
  }
}

size_t PartitionedMSA::total_length() const
{
  size_t sum = 0;

  for (const auto& pinfo: _part_list)
  {
    sum += pinfo.length();
  }

  return sum;
}

size_t PartitionedMSA::total_sites() const
{
  size_t sum = 0;

  for (const auto& pinfo: _part_list)
  {
    sum += pinfo.stats().site_count;
  }

  return sum;
}

size_t PartitionedMSA::total_patterns() const
{
  size_t sum = 0;

  for (const auto& pinfo: _part_list)
  {
    sum += pinfo.stats().pattern_count;
  }

  return sum;
}

size_t PartitionedMSA::total_free_model_params() const
{
  size_t sum = 0;

  for (const auto& pinfo: _part_list)
  {
    sum += pinfo.model().num_free_params();
  }

  return sum;
}

size_t PartitionedMSA::taxon_clv_size() const
{
  size_t clv_size = 0;

  for (const auto& pinfo: _part_list)
  {
    clv_size += pinfo.taxon_clv_size();
  }

  return clv_size;
}

void PartitionedMSA::set_model_empirical_params()
{
  for (PartitionInfo& pinfo: _part_list)
  {
    pinfo.set_model_empirical_params();
  }
}

std::ostream& operator<<(std::ostream& stream, const PartitionedMSA& part_msa)
{
  for (size_t p = 0; p < part_msa.part_count(); ++p)
  {
    const PartitionInfo& pinfo = part_msa.part_info(p);
    const auto pstats = pinfo.stats();
    stream << "Partition " << p << ": " << pinfo.name() << endl;
    stream << "Model: " << pinfo.model().to_string() << endl;
    if (pinfo.msa().num_patterns())
    {
      stream << "Alignment sites / patterns: " << pstats.site_count <<
          " / " << pstats.pattern_count << endl;
    }
    else
      stream << "Alignment sites: " << pinfo.msa().num_sites() << endl;

//    stream << fixed;
    stream << "Gaps: " << setprecision(2) << (pstats.gap_prop * 100) << " %" << endl;
    stream << "Invariant sites: " << setprecision(2) << (pstats.inv_prop * 100) << " %" << endl;
    stream << endl;
  }

  return stream;
}



void AutoPartitioner::init_from_string(PartitionedMSA& part_msa, DataType data_type, const std::string &model_string)
{
  // TODO proper parsing, we look for the last "/" outside of curly brackets
  size_t pos = model_string.find_last_of("/");
  size_t pos2 = model_string.find_last_of("}");
  if (pos2 != string::npos && pos < pos2) pos = string::npos;
  const string model_def = pos == string::npos ? model_string : model_string.substr(0, pos);
  const string part_def = pos == string::npos ? "" : model_string.substr(pos+1);

  if (!part_def.empty())
  {
    /* automatic partitioning */
    istringstream ss(part_def);
    if (toupper(ss.get()) != 'P')
      throw runtime_error(string("Invalid auto-partition specification: ") + part_def);

    size_t num_part = 4;
    if (isdigit(ss.peek()))
    {
      ss >> num_part;
    }

    std::string ap_name = "ap";
    for (size_t i = 0; i < num_part; ++i)
    {
      part_msa.emplace_part_info(ap_name + std::to_string(i+1), data_type, model_def, "auto");
    }
  }
  else
    part_msa.emplace_part_info("noname", data_type, model_def);
}

void AutoPartitioner::update_partition_ranges(PartitionedMSA& part_msa)
{
  auto column_entropies = get_column_entropies(part_msa);
//  double binw = log2(mod.num_states())  / 4.;
  double maxe = column_entropies.empty() ? 0. :
                                          *std::max_element(column_entropies.cbegin(), column_entropies.cend());
  double binw = maxe  / part_msa.part_count() + 1e-9;
//  printf("maxe : %lf, binw : %lf\n", maxe, binw);

  size_t p = 0;
  for (auto& pinfo: part_msa.part_list())
  {
    if (pinfo.range_string() == "auto")
    {
      auto new_range = resolve_auto_range(column_entropies, p, binw);
//      printf("p%lu : %s\n", p, new_range.c_str());
      pinfo.range_string(new_range);
    }
    p++;
  }

  if (part_msa.part_count() > 1)
  {
    for (std::vector<PartitionInfo>::iterator it = part_msa.part_list().begin(); it != part_msa.part_list().end();)
    {
        if (it->range_string() == "")
            it = part_msa.part_list().erase(it);
        else
            ++it;
    }
  }
}

std::string AutoPartitioner::resolve_auto_range(const doubleVector& col_entropies, size_t part_num, double binw)
{
  ostringstream range;

  size_t sites_assigned = 0;
  part_num++;
  double ub = binw * part_num;
  double lb = part_num > 1 ? binw * (part_num-1) : -1;
  for (size_t i = 0; i < col_entropies.size(); ++i)
  {
    if (col_entropies[i] > ub || col_entropies[i] <= lb)
      continue;
    range << (sites_assigned ? "," : "") << (i+1);
    sites_assigned++;
  }

  return range.str();
}

doubleVector AutoPartitioner::get_column_entropies(const PartitionedMSA& part_msa)
{
  auto full_len = part_msa.full_msa().length();
  doubleVector column_entropies(full_len);

  // TODO support multiple partitions / data types
  const auto& mod = part_msa.model(0);
  double * e = corax_msa_column_entropies(part_msa.full_msa().pll_msa(),
                                          mod.num_states(), mod.charmap());

  libpll_check_error("ERROR computing column entropies");
  assert(e);

//  printf("Site entropy: ");
//  for (size_t i = 0; i < full_len; ++i)
//    if (i == 110) printf("%.3f ", e[i]);
//  printf("\n\n");

  column_entropies.assign(e, e + full_len);

  free(e);

  return column_entropies;
}

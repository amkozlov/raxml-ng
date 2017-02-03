#include "PartitionInfo.hpp"

PartitionInfo::~PartitionInfo ()
{
  // TODO Auto-generated destructor stub
}

size_t PartitionInfo::mark_partition_sites(unsigned int part_num, std::vector<unsigned int>& site_part)
{
  size_t start, end, stride;
  size_t i;
  size_t sites_assigned = 0;
  const char * range = _range_string.c_str();

  do
  {
    while(*range == ',')
      range++;

    int read = 0;
    /* try to parse strided format first */
    read = sscanf(range, "%lu-%lu\\%lu", &start, &end, &stride);
    if (read != 3)
    {
      /* try to parse contiguous range format first */
      stride = 1;
      read = sscanf(range, "%lu-%lu", &start, &end);
      if (read != 2)
      {
        /* finally, check if we have a single column */
        read = sscanf(range, "%lu", &start);
        end = start;
      }
    }
    if (read && start >= 1 && end <= site_part.size() && start <= end)
    {
      /* remember indices are 1-based in the partition file! */
      for (i = start-1; i <= end-1; ++i)
      {
        if ((i - start + 1) % stride == 0)
        {
          if (!site_part[i])
          {
            site_part[i] = part_num;
            sites_assigned++;
          }
          else
            throw MultiplePartitionForSiteException(*this, i+1);
        }
      }
    }
    else
      throw InvalidPartitionRangeException(*this);
  }
  while ((range = strchr(range, ',')) != NULL);

  return sites_assigned;
}

void PartitionInfo::compress_patterns()
{
  _msa.compress_patterns(model().charmap());
}


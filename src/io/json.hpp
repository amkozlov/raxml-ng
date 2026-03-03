#ifndef RAXML_IO_JSON_HPP_
#define RAXML_IO_JSON_HPP_

#include "../Options.hpp"
#include "../PartitionedMSA.hpp"
#include "../modeltest/ModelTest.hpp"
#include "../Checkpoint.hpp"
#include "../version.h"

void print_json(const Options& opts, const PartitionedMSA *msa, const CheckpointFile& checkp, const ModelTest *modeltest, double used_wh);

#endif

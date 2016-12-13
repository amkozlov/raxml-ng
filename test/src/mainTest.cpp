#include <gtest/gtest.h>
#include <string>
#include <iostream>

#include "RaxmlTest.hpp"

RaxmlTest* env;

int main(int argc, char** argv)
{
  env = new RaxmlTest();

  // Set data dir using the program path.
  std::string call = argv[0];
  std::size_t found = call.find_last_of("/\\");
  if (found != std::string::npos) {
      env->data_dir = call.substr(0,found) + "/../data/";
  }

//  env->tree_file = std::string(env->data_dir);
//  env->tree_file += "ref.tre";

//  env->out_dir  = std::string("/tmp/epatest/");
//  std::string cmd("mkdir ");
//  cmd += env->out_dir.c_str();
//  system(cmd.c_str());

  ::testing::InitGoogleTest(&argc, argv);
//  MPI_INIT(&argc, &argv);
  ::testing::AddGlobalTestEnvironment(env);
  auto result = RUN_ALL_TESTS();
//  MPI_FINALIZE();
  return result;
}

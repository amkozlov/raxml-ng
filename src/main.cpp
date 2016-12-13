/*
    Copyright (C) 2016 Alexey Kozlov, Alexandros Stamatakis, Diego Darriba, Tomas Flouri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact: Alexey Kozlov <Alexey.Kozlov@h-its.org>,
    Heidelberg Institute for Theoretical Studies,
    Schloss-Wolfsbrunnenweg 35, D-69118 Heidelberg, Germany
*/
#include <algorithm>
#include <chrono>

//#include <cxxopts.hpp>
//
//#include "mpihead.hpp"
//#include "epa.hpp"

#include "common.h"
#include "Options.hpp"
#include "CommandLineParser.hpp"

using namespace std;

void print_banner()
{
  LOG_INFO << "RAxML-NG v. 0.1alpha (c) 2016 The Exelixis Lab" << endl;
  LOG_INFO << endl <<
      "WARNING: This is an EXPERIMENTAL version of RAxML which has not been released yet!"
      << endl << endl;
}

int main(int argc, char** argv)
{
  print_banner();

  Options opts;
  CommandLineParser cmdline;

  try
  {
    cmdline.parse_options(argc, argv, opts);
  }
  catch (OptionException &e)
  {
    LOG_INFO << "ERROR: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  switch (opts.command)
  {
    case Command::help:
      cmdline.print_help();
      return EXIT_SUCCESS;
    case Command::version:
      return EXIT_SUCCESS;
    case Command::evaluate:
    case Command::search:
      // parse model string & init partitions
      LOG_INFO << "Not implemented!" << endl;
      print_options(opts);
      return EXIT_SUCCESS;
    case Command::none:
    default:
      LOG_INFO << "Unknown command!" << endl;
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

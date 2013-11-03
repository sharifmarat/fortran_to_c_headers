#include <string>
#include <iostream>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include "program.h"
#include "parse.h"

namespace f2h
{

int program(int argc, char **argv)
{
  std::string inputFile;
  std::string ouputFile;

  boost::program_options::options_description options("Program to automatic generation of C headers from Fortran 2003 bindings. Options");
  options.add_options()
      ("help,h", "prints this help")
      ("input,i", boost::program_options::value<std::string>(&inputFile), "input fortran file")
      ("output,o", boost::program_options::value<std::string>(&ouputFile), "generated header file");

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options), vm);
  boost::program_options::notify(vm);

  if (vm.count("help"))
  {
    std::cout << options << std::endl;
    return SUCCESS;
  }

  if (!vm.count("input"))
  {
    std::cerr << "Input is required" << std::endl;
    std::cerr << options << std::endl;
    return MISSING_ARGUMENTS;
  }

  if (!vm.count("output"))
  {
    std::cerr << "Output is required" << std::endl;
    std::cerr << options << std::endl;
    return MISSING_ARGUMENTS;
  }

  std::cout << "From " << inputFile << " to " << ouputFile << std::endl;

  return SUCCESS;
}

}

#include "program.h"

#include <string>
#include <iostream>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include "parser.h"
#include "generator.h"

namespace f2h
{

ProgramResult program(int argc, char **argv)
{
  std::string input_file_name;
  std::string output_file_name;

  boost::program_options::options_description options("Program to automatic generation of C headers from Fortran 2003 bindings. Options");
  options.add_options()
      ("help,h", "prints this help")
      ("input,i", boost::program_options::value<std::string>(&input_file_name), "input fortran file")
      ("output,o", boost::program_options::value<std::string>(&output_file_name), "generated header file");

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

  return program(input_file_name, output_file_name);
}


ProgramResult program(const std::string &input_file_name, const std::string &output_file_name)
{
  Parser parser(input_file_name);
  parser.Parse();

  Generator generator(output_file_name);
  generator.Generate(parser.GetAst());

  return SUCCESS;
}

}

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
  namespace po = boost::program_options;

  std::string input_file_name;
  std::string output_file_name;
  std::string define_name;
  std::vector<std::string> custom_typedefs_input;
  custom_typedefs_t custom_typedefs;

  po::options_description options("Program to automatic generation of C headers from Fortran 2003 bindings. Options");
  options.add_options()
      ("help,h", po::bool_switch()->default_value(false), "prints this help")
      ("input,i", po::value<std::string>(&input_file_name)->required(), "input fortran file")
      ("output,o", po::value<std::string>(&output_file_name)->required(), "generated header file")
      ("dllexport", po::bool_switch()->default_value(false), "adds __declspec(dllexport) to the generated header file")
      ("custom-typedefs", po::value<std::vector<std::string> >(&custom_typedefs_input)->multitoken(),
                          "Allows to specify typedefs for a variable.  Example: `--custom-typedefs var1=var1_t var2=var2_t'"
                          "will change the type of variable var1 to var1_t and var2 to var2_t.")
      ("define_name,d", po::value<std::string>(&define_name)->default_value("RESULT_H"), "define name of generated header")
  ;

  po::variables_map vm;

  try
  {
    po::store(po::parse_command_line(argc, argv, options), vm);
  }
  catch (const po::error& ex)
  {
    std::cerr << "Error: " << ex.what() << std::endl;
    std::cerr << "Try --help for more information." << std::endl;
    return ERROR_PARSING_COMMAND_OPTIONS;
  }

  if (vm["help"].as<bool>())
  {
    std::cout << options << std::endl;
    return SUCCESS;
  }

  try
  {
    po::notify(vm);
  }
  catch (const po::error& ex)
  {
    std::cerr << "Error: " << ex.what() << std::endl;
    std::cerr << "Try --help for more information." << std::endl;
    return MISSING_ARGUMENTS;
  }

  bool add_dll_export = vm["dllexport"].as<bool>();

  BOOST_FOREACH(const std::string& custom_typedef, custom_typedefs_input)
  {
    size_t pos = custom_typedef.find('=');
    if (pos == std::string::npos || pos == custom_typedef.size() -1)
    {
      std::cerr << "Error: custom typedefs have to be in the format `var=var_t'." << std::endl;
      std::cerr << "Try --help for more information." << std::endl;
      return MISSING_ARGUMENTS;
    }
    custom_typedefs.insert(std::pair<std::string, std::string>(custom_typedef.substr(0, pos), custom_typedef.substr(pos+1)));
  }

  if (define_name.length() == 0)
  {
    std::cerr << "Define name cannot be empty" << std::endl;
    std::cerr << "Try --help for more information." << std::endl;
    return MISSING_ARGUMENTS;
  }

  return program(input_file_name, output_file_name, define_name, add_dll_export, custom_typedefs);
}


ProgramResult program(const std::string &input_file_name, const std::string &output_file_name, const std::string &define_name, bool add_dll_export, const custom_typedefs_t& typedefs)
{
  Parser parser(input_file_name);
  parser.Parse();

  Generator generator(output_file_name);
  generator.Generate(parser.GetAst(), define_name, add_dll_export, typedefs);

  return SUCCESS;
}

}

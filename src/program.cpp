#include "program.h"

#include <string>
#include <iostream>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include "parser.h"
#include "generator.h"
#include "version.h"

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
      ("define_name,d", po::value<std::string>(&define_name)->default_value("RESULT_H"), "define name of generated header")
      ("add-dllimport", po::bool_switch()->default_value(false), "adds __declspec(dllimport) to the generated header file")
      ("add-extern", po::bool_switch()->default_value(false), "adds extern for all variables and functions to the generated header file")
      ("custom-typedefs", po::value<std::vector<std::string> >(&custom_typedefs_input)->multitoken(),
                          "Allows to specify typedefs for a variable.  Example: `--custom-typedefs var1=var1_t var2=var2_t'"
                          "will change the type of variable var1 to var1_t and var2 to var2_t.")
      ("omit-comments", po::bool_switch()->default_value(false), "Omits comments on the top of generated header")
      ("version,v", po::bool_switch()->default_value(false), "prints the version")
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

  if (vm["version"].as<bool>())
  {
    std::cout << GetVersionString() << std::endl;
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

  bool add_dll_import = vm["add-dllimport"].as<bool>();
  bool ommit_comments = vm["omit-comments"].as<bool>();
  bool add_extern = vm["add-extern"].as<bool>();

  return program(input_file_name, output_file_name, define_name, add_dll_import, custom_typedefs, ommit_comments, add_extern);
}


ProgramResult program(const std::string &input_file_name, const std::string &output_file_name, const std::string &define_name, bool add_dll_import, const custom_typedefs_t& typedefs, bool ommit_comments, bool add_extern)
{
  Parser parser(input_file_name);
  parser.Parse();

  Generator generator(output_file_name);
  generator.Generate(parser.GetAst(), define_name, add_dll_import, typedefs, ommit_comments, add_extern);

  return SUCCESS;
}

}

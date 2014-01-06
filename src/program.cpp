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
  typedef std::map<std::string, std::string> custom_typedefs_t;

  std::string input_file_name;
  std::string output_file_name;
  std::string define_name;
  std::vector<std::string> custom_typedefs_input;
  custom_typedefs_t custom_typedefs;

  boost::program_options::options_description options("Program to automatic generation of C headers from Fortran 2003 bindings. Options");
  options.add_options()
      ("help,h", "prints this help")
      ("input,i", boost::program_options::value<std::string>(&input_file_name)->required(), "input fortran file")
      ("output,o", boost::program_options::value<std::string>(&output_file_name)->required(), "generated header file")
      ("dllexport", "adds __declspec(dllexport) to the generated header file")
      ("custom-typedefs", boost::program_options::value<std::vector<std::string> >(&custom_typedefs_input)->multitoken(),
                          "Allows to specify typedefs for a variable.  Example: `--custom-typedefs var1=var1_t var2=var2_t'"
                          "will change the type of variable var1 to var1_t and var2 to var2_t.")
      ("define_name,d", boost::program_options::value<std::string>(&define_name)->default_value("RESULT_H"), "define name of generated header")
  ;

  boost::program_options::variables_map vm;

  try
  {
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options), vm);
  }
  catch (std::exception &ex)
  {
    std::cerr << "Error: " << ex.what() << std::endl;
    std::cerr << "Try --help for more information." << std::endl;
    return ERROR_PARSING_COMMAND_OPTIONS;
  }

  if (vm.count("help"))
  {
    std::cout << options << std::endl;
    return SUCCESS;
  }

  try
  {
    boost::program_options::notify(vm);
  }
  catch (std::exception &ex)
  {
    std::cerr << "Error: " << ex.what() << std::endl;
    std::cerr << "Try --help for more information." << std::endl;
    return MISSING_ARGUMENTS;
  }

  bool add_dll_export = vm.count("dllexport") ? true : false;

  std::cout << "custom_typedefs_input.size = " << custom_typedefs_input.size() << std::endl;

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

  BOOST_FOREACH(const custom_typedefs_t::value_type& custom_typedef, custom_typedefs)
  {
    std::cout << custom_typedef.first << "--->" << custom_typedef.second << std::endl;
  }

  if (define_name.length() == 0)
  {
    std::cerr << "Define name cannot be empty" << std::endl;
    std::cerr << options << std::endl;
    return MISSING_ARGUMENTS;
  }

  return program(input_file_name, output_file_name, define_name, add_dll_export);
}


ProgramResult program(const std::string &input_file_name, const std::string &output_file_name, const std::string &define_name, bool add_dll_export)
{
  Parser parser(input_file_name);
  parser.Parse();

  Generator generator(output_file_name);
  generator.Generate(parser.GetAst(), define_name, add_dll_export);

  return SUCCESS;
}

}

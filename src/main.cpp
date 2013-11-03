#include <string>
#include <iostream>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

int main(int argc, char **argv)
{
  boost::program_options::options_description options("Program to automatic generation of C headers from Fortran 2003 bindings. Options");
  options.add_options()
      ("help,h", "prints this help")
      ("input,i", boost::program_options::value<std::string>(), "input fortran file")
      ("output,o", boost::program_options::value<std::string>(), "generated header file");

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options), vm);

  boost::program_options::notify(vm);

  if (vm.count("help"))
  {
    std::cout << options << std::endl;
    return 0;
  }

  if (!vm.count("input"))
  {
    std::cerr << "Input is required" << std::endl;
    std::cerr << options << std::endl;
    return 1;
  }

  if (!vm.count("output"))
  {
    std::cerr << "Output is required" << std::endl;
    std::cerr << options << std::endl;
    return 2;
  }

  return 0;
}

#ifndef F2H_PROGRAM_H
#define F2H_PROGRAM_H

#include <string>
#include <map>

namespace f2h
{

typedef std::map<std::string, std::string> custom_typedefs_t;

enum ProgramResult
{
  SUCCESS = 0,
  MISSING_ARGUMENTS,
  ERROR_PARSING_COMMAND_OPTIONS,
};

ProgramResult program(int argc, char **argv);

ProgramResult program(const std::string &input_file_name, const std::string &output_file_name, const std::string &define_name, bool add_dll_export, const custom_typedefs_t& typedefs, bool ommit_comments, bool add_extern);

}

#endif

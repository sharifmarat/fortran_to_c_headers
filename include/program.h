#ifndef F2H_PROGRAM_H
#define F2H_PROGRAM_H

#include <string>

namespace f2h
{

enum ProgramResult
{
  SUCCESS = 0,
  MISSING_ARGUMENTS
};

ProgramResult program(int argc, char **argv);

ProgramResult program(const std::string &input_file_name, const std::string &output_file_name);

}

#endif

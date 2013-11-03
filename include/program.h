#ifndef F2H_PROGRAM_H
#define F2H_PROGRAM_H


namespace f2h
{

enum ProgramResult
{
  SUCCESS = 0,
  MISSING_ARGUMENTS
};

int program(int argc, char **argv);

}

#endif

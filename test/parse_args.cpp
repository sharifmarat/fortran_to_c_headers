#include "gtest/gtest.h"
#include "program.h"

TEST(ParseArgs, NoArguments)
{
  const int argc = 1;
  const char *argv[] = {"program"};
  f2h::ProgramResult result = f2h::program(argc, (char **)argv);
  EXPECT_EQ(f2h::MISSING_ARGUMENTS, result) << "expecting error if no arguments are provided";
}

TEST(ParseArgs, NoOutput)
{
  const int argc = 3;
  const char *argv[] = {"program", "-i", "in.f90"};
  f2h::ProgramResult result = f2h::program(argc, (char **)argv);
  EXPECT_EQ(f2h::MISSING_ARGUMENTS, result) << "expecting error if output file is not provided";
}

TEST(ParseArgs, NoInput)
{
  const int argc = 3;
  const char *argv[] = {"program", "-o", "out.h"};
  f2h::ProgramResult result = f2h::program(argc, (char **)argv);
  EXPECT_EQ(f2h::MISSING_ARGUMENTS, result) << "expecting error if input file is not provided";
}

TEST(ParseArgs, Help)
{
  const int argc = 2;
  const char *argv[] = {"program", "-h"};
  f2h::ProgramResult result = f2h::program(argc, (char **)argv);
  EXPECT_EQ(f2h::SUCCESS, result) << "success on help message";
}

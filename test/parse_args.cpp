#include <algorithm>

#include "gtest/gtest.h"
#include "program.h"

TEST(ParseArgs, NoArguments)
{
  const int argc = 1;
  const char *argv[] = {"program"};
  int result = f2h::program(argc, (char **)argv);
  EXPECT_EQ(f2h::MISSING_ARGUMENTS, result);
}

TEST(ParseArgs, OnlyInput)
{
  const int argc = 3;
  const char *argv[] = {"program", "-i", "in.f90"};
  int result = f2h::program(argc, (char **)argv);
  EXPECT_EQ(f2h::MISSING_ARGUMENTS, result);
}

TEST(ParseArgs, OnlyOutput)
{
  const int argc = 3;
  const char *argv[] = {"program", "-o", "out.h"};
  int result = f2h::program(argc, (char **)argv);
  EXPECT_EQ(f2h::MISSING_ARGUMENTS, result);
}

TEST(ParseArgs, Help)
{
  const int argc = 2;
  const char *argv[] = {"program", "-h"};
  int result = f2h::program(argc, (char **)argv);
  EXPECT_EQ(f2h::SUCCESS, result);
}

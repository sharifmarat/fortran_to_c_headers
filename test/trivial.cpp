#include "gtest/gtest.h"
#include "program.h"

TEST(Trivial, EmptyFile)
{
  const int argc = 1;
  const char *argv[] = {"program"};
  int result = f2h::program(argc, (char **)argv);
  EXPECT_EQ(f2h::MISSING_ARGUMENTS, result);
}

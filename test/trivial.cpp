#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(Trivial, EmptyFile)
{
  f2h_test::run_program_and_compare_files("resources/trivial/in.f90", "resources/trivial/out.h");
}

#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(Functions, SimpleFunction)
{
  f2h_test::run_program_and_compare_files("resources/functions/in.f90", "resources/functions/out.h");
}


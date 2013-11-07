#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(SimpleSubroutine, SimpleSubroutine)
{
  f2h_test::run_program_and_compare_files("resources/simple_subroutine/in.f90", "resources/simple_subroutine/out.h");
}

TEST(SimpleSubroutine, TwoSimpleSubroutines)
{
  f2h_test::run_program_and_compare_files("resources/simple_subroutine/in2.f90", "resources/simple_subroutine/out2.h");
}

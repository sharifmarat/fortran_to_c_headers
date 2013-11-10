#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(SubroutineWithArgs, SubroutineWithArgs)
{
  f2h_test::run_program_and_compare_files("resources/subroutine_with_args/in.f90", "resources/subroutine_with_args/out.h");
}

TEST(SubroutineWithArgs, SubroutineWithArgsPtr)
{
  f2h_test::run_program_and_compare_files("resources/subroutine_with_args/in2.f90", "resources/subroutine_with_args/out2.h");
}

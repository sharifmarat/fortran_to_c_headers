#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(LineContinuation, LineContinuation)
{
  f2h_test::run_program_and_compare_files("resources/line_continuation/in.f90", "resources/line_continuation/out.h");
}


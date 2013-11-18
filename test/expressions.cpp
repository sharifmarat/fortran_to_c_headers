#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(Expressions, Expressions)
{
  f2h_test::run_program_and_compare_files("resources/expressions/in.f90", "resources/expressions/out.h");
}

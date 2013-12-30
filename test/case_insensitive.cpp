#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(CaseInsensitive, CaseInsensitive)
{
  f2h_test::run_program_and_compare_files("resources/case_insensitive/in.f90", "resources/case_insensitive/out.h");
}

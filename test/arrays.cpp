#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(Arrays, Arrays)
{
  f2h_test::run_program_and_compare_files("resources/arrays/in.f90", "resources/arrays/out.h");
}

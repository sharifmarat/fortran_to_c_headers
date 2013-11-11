#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(Comments, Comments)
{
  f2h_test::run_program_and_compare_files("resources/comments/in.f90", "resources/comments/out.h");
}


#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(Types, Types)
{
  f2h_test::run_program_and_compare_files("resources/types/in.f90", "resources/types/out.h");
}


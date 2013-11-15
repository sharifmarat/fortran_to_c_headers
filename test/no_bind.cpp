#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(NoBind, NoBind)
{
  f2h_test::run_program_and_compare_files("resources/no_bind/in.f90", "resources/no_bind/out.h");
}

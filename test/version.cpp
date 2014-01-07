#include "gtest/gtest.h"
#include "utils.h"

TEST(Version, Version)
{
  f2h_test::run_program_and_compare_files("resources/version/in.f90", "resources/version/out.h", false, f2h::custom_typedefs_t(), false);
}


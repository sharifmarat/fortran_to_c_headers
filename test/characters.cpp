#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(Characters, Characters)
{
  f2h_test::run_program_and_compare_files("resources/characters/in.f90", "resources/characters/out.h");
}

#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(NoEol, NoEol)
{
  f2h_test::run_program_and_compare_files("resources/noeol/in.f90", "resources/noeol/out.h");
}


#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(BindVars, BindVars)
{
  f2h_test::run_program_and_compare_files("resources/bind_vars/in.f90", "resources/bind_vars/out.h");
}

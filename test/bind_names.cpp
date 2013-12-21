#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(BindNames, BindNames)
{
  f2h_test::run_program_and_compare_files("resources/bind_names/in.f90", "resources/bind_names/out.h");
}

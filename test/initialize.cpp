#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(Initialize, Initialize)
{
  f2h_test::run_program_and_compare_files("resources/initialize/in.f90", "resources/initialize/out.h");
}

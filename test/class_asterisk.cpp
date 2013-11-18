#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(ClassAsterisk, ClassAsterisk)
{
  f2h_test::run_program_and_compare_files("resources/class_asterisk/in.f90", "resources/class_asterisk/out.h");
}

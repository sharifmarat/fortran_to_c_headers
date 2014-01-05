#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(DllExports, DllExports)
{
  f2h_test::run_program_and_compare_files("resources/dll_exports/in.f90", "resources/dll_exports/out.h", true);
}

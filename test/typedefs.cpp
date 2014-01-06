#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(Typedefs, Typedefs)
{
  f2h::custom_typedefs_t typedefs;
  typedefs.insert(f2h::custom_typedefs_t::value_type("some_ptr", "some_ptr_t"));
  typedefs.insert(f2h::custom_typedefs_t::value_type("val", "val_t"));
  f2h_test::run_program_and_compare_files("resources/typedefs/in.f90", "resources/typedefs/out.h", true, typedefs);
}

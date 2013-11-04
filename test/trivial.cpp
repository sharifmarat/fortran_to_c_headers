#include "gtest/gtest.h"
#include "program.h"
#include "utils.h"

TEST(Trivial, EmptyFile)
{
  std::string data_dir = "resources/trivial/";
  std::string in_file = data_dir + "in.f90";
  std::string expected_file = data_dir + "out.h";
  std::string actual_file = data_dir + "result.h";

  f2h::ProgramResult result = f2h::program(in_file, actual_file);
  ASSERT_EQ(f2h::SUCCESS, result) << "program has not been successfully completed";

  f2h_test::compare_files(expected_file, actual_file);
}

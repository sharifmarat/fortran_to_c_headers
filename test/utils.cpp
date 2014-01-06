#include "utils.h"
#include "program.h"
#include "gtest/gtest.h"

#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>


namespace f2h_test
{

void compare_files(const std::string &file_name_1, const std::string &file_name_2)
{
  std::ifstream in1;
  in1.open(file_name_1.c_str());

  ASSERT_TRUE(in1.is_open()) << "Can't open file " << file_name_1;

  std::ifstream in2;
  in2.open(file_name_2.c_str());

  ASSERT_TRUE(in2.is_open()) << "Can't open file " << file_name_2;

  std::string line1, line2;

  while (true)
  {
    bool status1 = std::getline(in1, line1);
    bool status2 = std::getline(in2, line2);
    ASSERT_EQ(status1, status2) << "Different statuses when comparing " << file_name_1 << " and " << file_name_2;
    if (!status1 || !status2)
    {
      break;
    }
    ASSERT_STREQ(line1.c_str(), line2.c_str()) << "Different lines when comparing " << file_name_1 << " and " << file_name_2;
  }

  ASSERT_TRUE(in1.eof()) << "Finished reading " << file_name_1;
  ASSERT_TRUE(in2.eof()) << "Finished reading " << file_name_2;

  in1.close();
  in2.close();
}

void run_program_and_compare_files(const std::string &in_file, const std::string &expected_out_file, bool add_dll_export, const f2h::custom_typedefs_t& typedefs)
{
  boost::filesystem::path actual_out_file = boost::filesystem::path(expected_out_file).parent_path() / "result.h";
  f2h::ProgramResult result = f2h::program(in_file, actual_out_file.string(), "RESULT_H", add_dll_export, typedefs);
  ASSERT_EQ(f2h::SUCCESS, result) << "program has not been successfully completed";

  compare_files(expected_out_file, actual_out_file.string());
}

void run_program_and_compare_files(const std::string &in_file, const std::string &expected_out_file, bool add_dll_export)
{
  run_program_and_compare_files(in_file, expected_out_file, add_dll_export, f2h::custom_typedefs_t());
}

void run_program_and_compare_files(const std::string &in_file, const std::string &expected_out_file)
{
  run_program_and_compare_files(in_file, expected_out_file, false);
}


};

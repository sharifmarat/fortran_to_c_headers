#ifndef F2H_TEST_UTILS_H
#define F2H_TEST_UTILS_H

#include <string>

#include "program.h"

namespace f2h_test
{

void compare_files(const std::string &fileName1, const std::string &fileName2);

void run_program_and_compare_files(const std::string &in_file, const std::string &expected_out_file, bool add_dll_export, const f2h::custom_typedefs_t& typedefs);

void run_program_and_compare_files(const std::string &in_file, const std::string &expected_out_file, bool add_dll_export);

void run_program_and_compare_files(const std::string &in_file, const std::string &expected_out_file);

};

#endif

#ifndef F2H_PARSER_H
#define F2H_PARSER_H

#include <string>
#include <iostream>
#include <fstream>

namespace f2h
{

class Parser
{
public:
  Parser(const std::string &in_file_name);
  void Parse();
private:
private:
  std::string in_file_name_;
  std::ifstream in_;
};

}


#endif

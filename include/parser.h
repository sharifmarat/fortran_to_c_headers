#ifndef F2H_PARSER_H
#define F2H_PARSER_H

#include <string>
#include <iostream>
#include <fstream>

#include "grammar.hpp"
#include "function.hpp"
#include "ast.hpp"

namespace f2h
{

class Parser
{
public:
  Parser(const std::string &in_file_name);
  void Parse();
  const f2h::ast::Program &GetAst() const { return ast_; }
private:
private:
  std::string in_file_name_;
  std::ifstream in_;

  boost::spirit::ascii::space_type space_;
  Grammar<std::string::const_iterator> grammar_;
  f2h::ast::Program ast_;
};

}


#endif

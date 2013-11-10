#ifndef F2H_GENERATOR_H
#define F2H_GENERATOR_H

#include <string>
#include <iostream>
#include <fstream>

#include "ast.hpp"

namespace f2h
{

class Generator
{
public:
  typedef bool result_type;

  explicit Generator(const std::string &out_file_name);
  void Generate(ast::Program const& x);

  bool operator()(ast::Nil) { BOOST_ASSERT(0); return false; }
  bool operator()(ast::Identifier const& x);
  bool operator()(ast::VariableDeclaration const& x);
  bool operator()(ast::Expression const& x);
  bool operator()(ast::Function const& x);
  bool operator()(ast::Program const& x);

private:

  void DumpHeaderStart() const;
  void DumpHeaderEnd() const;
  std::string GetDefineName() const;

private:
  Generator();

private:
  std::string out_file_name_;
  std::string body_;
  mutable std::ofstream out_;
};


}


#endif

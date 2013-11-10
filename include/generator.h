#ifndef F2H_GENERATOR_H
#define F2H_GENERATOR_H

#include <string>
#include <map>
#include <list>
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
  bool operator()(ast::Other const& x);
  bool operator()(ast::Function const& x);
  bool operator()(ast::VariableDeclaration const& x);
  bool operator()(ast::VariableDeclarationSimple const& x);
  bool operator()(ast::VariableDeclarationExtended const& x);
  bool operator()(ast::Program const& x);

private:

  void DumpHeaderStart() const;
  void DumpHeaderEnd() const;
  std::string GetDefineName() const;

  struct Argument
  {
    std::string name;
    std::string type;
  };

  struct Function
  {
    std::string return_value;
    std::string name;
    std::list<Argument> argument_list;
    std::list<Argument>::iterator find_argument(const std::string& name)
    {
      for (std::list<Argument>::iterator it = argument_list.begin(); it != argument_list.end(); ++it)
      {
        if ((*it).name == name) return it;
      }
      return argument_list.end();
    }
  };


private:
  Generator();

private:
  std::string out_file_name_;
  std::string body_;
  mutable std::ofstream out_;
  std::list<Function> functions_;
};


}


#endif

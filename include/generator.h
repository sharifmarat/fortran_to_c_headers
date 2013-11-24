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
  void Generate(ast::Program const& x, const std::string& define_name);

  bool operator()(ast::Nil) { BOOST_ASSERT(0); return false; }
  bool operator()(ast::Identifier const& x);
  bool operator()(ast::Other const& x);
  bool operator()(ast::Function const& x);
  bool operator()(ast::VariableDeclaration const& x);
  bool operator()(ast::VariableDeclarationAttribute const& x);
  bool operator()(ast::VariableDeclarationSimple const& x);
  bool operator()(ast::VariableDeclarationExtended const& x);
  bool operator()(ast::Program const& x);

private:

  void DumpHeaderStart(const std::string& define_name) const;
  void DumpHeaderEnd(const std::string& define_name) const;
  std::string GetDefineName() const;

  struct TypeSpecToCType : boost::static_visitor<std::string>
  {
    std::string operator()(ast::Nil const&) const { BOOST_ASSERT(0); return ""; }
    std::string operator()(ast::TypeSpecIntrinsic const& type_spec) const;
    std::string operator()(ast::TypeSpecType const& type_spec) const;
  };

  struct Argument
  {
    std::string name;
    std::string type;
    bool pointer;
    bool constant;
    bool has_c_bind;
    Argument() : type("void"), pointer(true), constant(false), has_c_bind(false) { }
    Argument(const std::string& name) : type("void"), pointer(true), constant(false), name(name), has_c_bind(false) { }
    std::string ToCType() const { return std::string("") + (constant&&pointer?"const ":"") + type + (pointer?"*":""); }
    std::string ToCTypeWithName() const { return ToCType() + " " + name; }
    void SetArgumentType(const ast::TypeSpec& type_spec);
    void SetArgumentAttribute(const std::string& attribute);
    bool operator==(const std::string& name) { return this->name == name; }
  };

  struct Function
  {
    std::string name;
    Argument return_value;
    std::list<Argument> argument_list;
    std::list<Argument>::iterator find_argument(const std::string& name)
    {
      for (std::list<Argument>::iterator it = argument_list.begin(); it != argument_list.end(); ++it)
      {
        if ((*it).name == name) return it;
      }
      return argument_list.end();
    }
    void SetArgumentType(const std::string& argument_name, const ast::TypeSpec& type_spec);
    void SetArgumentAttribute(const std::string& argument_name, const std::string& attribute);
  };

  Argument& GetOrAddGlobalArgument(const std::string& name);

private:
  Generator();

private:
  std::string out_file_name_;
  mutable std::ofstream out_;
  std::list<Function> functions_;
  std::list<Argument> globals_;
};


}


#endif

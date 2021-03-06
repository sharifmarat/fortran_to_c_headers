#ifndef F2H_GENERATOR_H
#define F2H_GENERATOR_H

#include <string>
#include <map>
#include <list>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "ast.hpp"

namespace f2h
{

typedef std::map<std::string, std::string> custom_typedefs_t;

class Generator
{
public:
  typedef bool result_type;

  explicit Generator(const std::string &out_file_name);
  void Generate(ast::Program const& x, const std::string& define_name, bool add_dll_import, const custom_typedefs_t& typedefs, bool omit_comments, bool add_extern);

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

  static std::string ExtractBindName(const std::string& bind_attribute)
  {
    const std::string bind_prefix = "bind=";
    return bind_attribute.length() > bind_prefix.length() ? bind_attribute.substr(bind_prefix.length()) : "";
  }

  void DumpHeaderStart(const std::string& define_name, bool omit_comments) const;
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
    std::string bind_name;
    std::string type;
    bool pointer;
    bool constant;
    bool parameter;
    bool has_c_bind;

    Argument() : type("void"), pointer(true), constant(false), has_c_bind(false), parameter(false) { }
    Argument(const std::string& name) : type("void"), pointer(true), constant(false), name(name), has_c_bind(false), parameter(false) { }
    std::string ToCType() const { return std::string("") + (constant&&pointer||parameter?"const ":"") + type + (pointer?"*":""); }
    std::string ToCTypeWithName() const { return ToCType() + " " + CName(); }
    std::string CName() const { return has_c_bind&&bind_name.length()>0 ? bind_name : name; }
    void SetArgumentType(const ast::TypeSpec& type_spec);
    void SetArgumentAttribute(const std::string& attribute);
    bool operator==(const std::string& name) { return boost::iequals(this->name, name); }
  };

  struct Function
  {
    std::string name;
    std::string bind_name;
    Argument return_value;
    std::list<Argument> argument_list;
    bool has_c_bind;

    Function() : has_c_bind(false) { }

    const std::string& GetName() const { return bind_name.length() > 0 ? bind_name : name; }

    std::list<Argument>::iterator find_argument(const std::string& name)
    {
      for (std::list<Argument>::iterator it = argument_list.begin(); it != argument_list.end(); ++it)
      {
        if (boost::iequals((*it).name, name)) return it;
      }
      return argument_list.end();
    }
    void SetArgumentType(const std::string& argument_name, const ast::TypeSpec& type_spec);
    void SetArgumentAttribute(const std::string& argument_name, const std::string& attribute);
  };

  Argument& GetOrAddGlobalArgument(const std::string& name);

  struct Typedef
  {
    std::string variable_name;
    std::string real_type_name;
    std::string alias;

    Typedef(const std::string& variable_name, const std::string& real_type_name, const std::string& alias)
      : variable_name(variable_name), real_type_name(real_type_name), alias(alias)
    { }
    bool operator==(const std::string& name) { return boost::iequals(this->variable_name, name); }
  };

  inline std::list<Typedef>::iterator RegisterTypedef(const Typedef& t) { return registered_typedefs_.insert(registered_typedefs_.end(), t); }

  void ResolveTypedef(Argument& arg, const custom_typedefs_t::value_type& typedef_input);

private:
  Generator();

private:
  std::string out_file_name_;
  mutable std::ofstream out_;
  std::list<Function> functions_;
  std::list<Argument> globals_;
  std::list<Typedef> registered_typedefs_;
};


}


#endif

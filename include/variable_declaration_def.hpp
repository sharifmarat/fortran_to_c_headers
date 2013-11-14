#include "variable_declaration.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{

unsigned int ParameterToUInt(ast::Identifier id)
{
  //TODO search among global parameters
  return 4;
}

template <typename Iterator>
VariableDeclaration<Iterator>::VariableDeclaration()
  : VariableDeclaration::base_type(var_decl)
{
  qi::char_type char_;
  qi::alnum_type alnum;
  qi::alpha_type alpha;
  qi::string_type string;
  qi::raw_type raw;
  qi::lexeme_type lexeme;
  qi::uint_type uint_;

  variable_name = primary_expression.identifier;
  variable_list = variable_name % ',';

  attribute =   string("allocatable")
              | string("asynchronous")
              | string("automatic")
              | string("bind") //TODO (C [, NAME=ext-name])
              | string("codimension")
              | string("contiguous")
              | string("dimension") //TODO, add (a-spec) Is an array specification. It can be any of the following: a(10,10), a(:), a(:,:), a(10,*)
              | string("external")
              | (string("intent") >> '(' >> (string("in") | string("out") | string("inout")) >> ')')
              | string("external")
              | string("intrinsic")
              | string("optional")
              | string("parameter")
              | string("pointer")
              | string("private")
              | string("protected")
              | string("public")
              | string("save")
              | string("static")
              | string("target")
              | string("value")
              | string("volatile")
              ;

  attribute_list = attribute % ',';

  var_decl_attribute = attribute >> -(string("::")) > variable_list;

  var_decl_simple = type_spec >> -(string("::")) > variable_list;

  var_decl_extended = type_spec >> ',' > attribute_list >> string("::") > variable_list;

  var_decl = (var_decl_extended | var_decl_simple | var_decl_attribute) > qi::eol;

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (attribute)
  //    (variable_name)
  //    (type_spec)
  //    (attribute_list)
  //    (variable_list)
  //    (var_decl_simple)
  //    (var_decl_extended)
  //    (var_decl)
  //    );
}







}

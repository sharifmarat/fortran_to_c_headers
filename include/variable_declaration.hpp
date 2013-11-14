#ifndef F2H_VARIABLE_DECLARATION_HPP
#define F2H_VARIABLE_DECLARATION_HPP

#include <boost/spirit/include/qi.hpp>
#include <vector>

#include "skipper.hpp"
#include "primary_expression.hpp"
#include "type_spec.hpp"
#include "ast.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct VariableDeclaration : qi::grammar<Iterator, ast::VariableDeclaration(), Skipper<Iterator> >
{   
  VariableDeclaration();

  qi::rule<Iterator, ast::VariableDeclarationSimple(), Skipper<Iterator> > var_decl_simple;

  qi::rule<Iterator, ast::VariableDeclarationAttribute(), Skipper<Iterator> > var_decl_attribute;

  qi::rule<Iterator, ast::VariableDeclarationExtended(), Skipper<Iterator> > var_decl_extended;

  qi::rule<Iterator, ast::VariableDeclaration(), Skipper<Iterator> > var_decl;

  //qi::rule<Iterator, Skipper<Iterator> > attr_decl;

  qi::rule<Iterator, ast::Identifier(), Skipper<Iterator> > variable_name;

  qi::rule<Iterator, std::string(), Skipper<Iterator> > attribute;

  qi::rule<Iterator, std::list<std::string>(), Skipper<Iterator>  > attribute_list;

  qi::rule<Iterator, std::list<ast::Identifier>(), Skipper<Iterator>  > variable_list;

  PrimaryExpression<Iterator> primary_expression;

  TypeSpec<Iterator> type_spec;

};


}


#endif //F2H_VARIABLE_DECLARATION_HPP

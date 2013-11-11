#ifndef F2H_VARIABLE_DECLARATION_HPP
#define F2H_VARIABLE_DECLARATION_HPP

#include <boost/spirit/include/qi.hpp>
#include <vector>

#include "skipper.hpp"
#include "ast.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct VariableDeclaration : qi::grammar<Iterator, ast::VariableDeclaration(), Skipper<Iterator> >
{   
  VariableDeclaration();

  qi::rule<Iterator, ast::Kind(), Skipper<Iterator> > kind;

  qi::rule<Iterator, ast::VariableDeclarationSimple(), Skipper<Iterator> > var_decl_simple;

  qi::rule<Iterator, ast::VariableDeclarationExtended(), Skipper<Iterator> > var_decl_extended;

  qi::rule<Iterator, ast::VariableDeclaration(), Skipper<Iterator> > var_decl;

  qi::rule<Iterator, Skipper<Iterator> > attr_decl;

  qi::rule<Iterator, std::string(), Skipper<Iterator> > type_name;

  qi::rule<Iterator, ast::Identifier(), Skipper<Iterator> > identifier;

  qi::rule<Iterator, std::string(), Skipper<Iterator> > variable_name;

  qi::rule<Iterator, std::string(), Skipper<Iterator> > type_spec;

  qi::rule<Iterator, std::string(), Skipper<Iterator> > attribute;

  qi::rule<Iterator, std::list<std::string>(), Skipper<Iterator>  > attribute_list;

  qi::rule<Iterator, std::list<std::string>(), Skipper<Iterator>  > variable_list;

};


}


#endif //F2H_VARIABLE_DECLARATION_HPP

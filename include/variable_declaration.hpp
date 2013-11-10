#ifndef F2H_VARIABLE_DECLARATION_HPP
#define F2H_VARIABLE_DECLARATION_HPP

#include <boost/spirit/include/qi.hpp>
#include <vector>

#include "ast.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct VariableDeclaration : qi::grammar<Iterator, ast::VariableDeclaration(), ascii::space_type>
{   
  VariableDeclaration();

  qi::rule<Iterator, ast::VariableDeclaration(), ascii::space_type> var_decl;

  qi::symbols<char> keywords;
};


}


#endif //F2H_VARIABLE_DECLARATION_HPP

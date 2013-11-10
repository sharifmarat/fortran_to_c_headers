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
//struct VariableDeclaration : qi::grammar<Iterator, ascii::space_type>
{   
  VariableDeclaration();

  qi::rule<Iterator, ast::Kind(), ascii::space_type> kind;

  qi::rule<Iterator, ast::VariableDeclarationSimple(), ascii::space_type> var_decl_simple;

  qi::rule<Iterator, ast::VariableDeclarationExtended(), ascii::space_type> var_decl_extended;

  qi::rule<Iterator, ast::VariableDeclaration(), ascii::space_type> var_decl;
  //qi::rule<Iterator, ascii::space_type> var_decl;

  qi::rule<Iterator, ascii::space_type> attr_decl;

  qi::rule<Iterator, std::string(), ascii::space_type> type_name;

  qi::rule<Iterator, ast::Identifier(), ascii::space_type> identifier;

  qi::rule<Iterator, std::string(), ascii::space_type> variable_name;

  qi::rule<Iterator, std::string(), ascii::space_type> type_spec;

  qi::rule<Iterator, std::string(), ascii::space_type> attribute;

  qi::rule<Iterator, std::list<std::string>(), ascii::space_type > attribute_list;

  qi::rule<Iterator, std::list<std::string>(), ascii::space_type > variable_list;

};


}


#endif //F2H_VARIABLE_DECLARATION_HPP

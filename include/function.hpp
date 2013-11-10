#ifndef F2H_FUNCTION_HPP
#define F2H_FUNCTION_HPP

#include "ast.hpp"
#include "expression.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct Function : qi::grammar<Iterator, ast::Function(), ascii::space_type>
{   
  Function();

  qi::rule<Iterator, ast::Function(), ascii::space_type> start;

  qi::rule<Iterator, std::string(), ascii::space_type> name;

  qi::rule<Iterator, ast::Identifier(), ascii::space_type> identifier;

  qi::rule<Iterator, std::list<ast::Identifier>(), ascii::space_type > argument_list;

  qi::rule<Iterator, std::string(), ascii::space_type> const_char_expr;

  Expression<Iterator> expr;
  
  // TODO statements
};


}


#endif //F2H_FUNCTION_HPP

#ifndef F2H_FUNCTION_HPP
#define F2H_FUNCTION_HPP

#include "ast.hpp"
#include "expression.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct Function : qi::grammar<Iterator, ast::function(), ascii::space_type>
{   
  Function();

  qi::rule<Iterator, ast::function(), ascii::space_type> start;

  qi::rule<Iterator, std::string(), ascii::space_type> name;

  qi::rule<Iterator, ast::identifier(), ascii::space_type> identifier;

  Expression<Iterator> expr;
  
  // TODO statements
};


}


#endif //F2H_FUNCTION_HPP

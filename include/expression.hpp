#ifndef F2H_EXPRESSION_HPP
#define F2H_EXPRESSION_HPP

#include <boost/spirit/include/qi.hpp>
#include <vector>

#include "ast.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct Expression : qi::grammar<Iterator, ast::expression(), ascii::space_type>
{   
  Expression();

  qi::rule<Iterator, ast::expression(), ascii::space_type> expr;

  qi::symbols<char> keywords;
};


}


#endif //F2H_EXPRESSION_HPP

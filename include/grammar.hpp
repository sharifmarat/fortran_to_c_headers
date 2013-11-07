#ifndef F2H_GRAMMAR_HPP
#define F2H_GRAMMAR_HPP

#include "expression.hpp"
#include "function.hpp"
#include "ast.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct Grammar : qi::grammar<Iterator, ast::program(), ascii::space_type>
{
  Grammar();

  Function<Iterator> function;
  Expression<Iterator> expr;

  qi::rule<Iterator, ast::operand(), ascii::space_type> operand;
  qi::rule<Iterator, ast::program(), ascii::space_type> program;
};



}


#endif //F2H_GRAMMAR_HPP

#ifndef F2H_GRAMMAR_HPP
#define F2H_GRAMMAR_HPP

#include "expression.hpp"
#include "function.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct Grammar : qi::grammar<Iterator, ascii::space_type>
{
  Grammar();

  qi::rule<Iterator, ascii::space_type> program;
  Function<Iterator> function;
  Expression<Iterator> expr;
};



}


#endif //F2H_GRAMMAR_HPP

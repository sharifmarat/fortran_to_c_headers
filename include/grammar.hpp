#ifndef F2H_GRAMMAR_HPP
#define F2H_GRAMMAR_HPP

#include "expression.hpp"
#include "function.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
class Grammar : public qi::grammar<Iterator, ascii::space_type>
{
public:
  Grammar();
private:
  qi::rule<Iterator, ascii::space_type> program;
  Function<Iterator> function;
  Expression<Iterator> expr;
};



}


#endif //F2H_GRAMMAR_HPP

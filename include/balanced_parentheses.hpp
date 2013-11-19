#ifndef F2H_BALANCED_PARENTHESES_HPP
#define F2H_BALANCED_PARENTHESES_HPP

#include "error_handler.hpp"
#include "skipper.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct BalancedParentheses : qi::grammar<Iterator, Skipper<Iterator> >
{
  BalancedParentheses(ErrorHandler<Iterator>& error_handler);

  qi::rule<Iterator, Skipper<Iterator> > inner_parentheses;

  qi::rule<Iterator, Skipper<Iterator> > outer_parentheses;

  qi::rule<Iterator, Skipper<Iterator> > text;
};



}


#endif //F2H_BALANCED_PARENTHESES_HPP

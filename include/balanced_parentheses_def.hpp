#include "balanced_parentheses.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{

template <typename Iterator>
BalancedParentheses<Iterator>::BalancedParentheses(ErrorHandler<Iterator>& error_handler)
  : BalancedParentheses::base_type(outer_parentheses)
{
  qi::char_type char_;

  text = +(char_ - ')' - '(');

  inner_parentheses %=  text
                      | ('(' >> inner_parentheses >> ')')
                      | (char_('(') >> char_(')'))
                      ;

  outer_parentheses = '(' >> -(*inner_parentheses) >> ')';

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (text)
  //    (inner_parentheses)
  //    (outer_parentheses)
  //    );

}

}

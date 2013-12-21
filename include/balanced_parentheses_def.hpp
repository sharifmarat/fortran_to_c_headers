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
  qi::_1_type _1;
  qi::_2_type _2;
  qi::_3_type _3;
  qi::_4_type _4;
  typedef boost::phoenix::function<ErrorHandler<Iterator> > ErrorHandlerFunction;

  text = +(char_ - ')' - '(' - qi::eol);

  inner_parentheses %=  text 
                      | 
                        (    *text 
                          >> ('(' >> *inner_parentheses >> ')') 
                          >> *text
                        )
                      ;

  outer_parentheses = '(' >> -(*inner_parentheses) >> ')';

  qi::on_error<qi::fail>(outer_parentheses,
      ErrorHandlerFunction(error_handler)(
        "Error! Expecting ", _4, _3));

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (text)
  //    (inner_parentheses)
  //    (outer_parentheses)
  //    );

}

}

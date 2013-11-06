#include "expression.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>



namespace f2h
{

template <typename Iterator>
Expression<Iterator>::Expression()
  : Expression::base_type(expr)
{
  qi::char_type char_;
  qi::alnum_type alnum;

  keywords.add
    ("function")
    ("subroutine")
    ;

  expr =
    !qi::lexeme[keywords >> !(alnum | '_')] >> +char_;
    ;

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (expr)
  //    );
}







}

#include "other.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>



namespace f2h
{

template <typename Iterator>
Other<Iterator>::Other(ErrorHandler<Iterator> & error_handler)
  : Other::base_type(expr)
{
  qi::char_type char_;
  qi::alnum_type alnum;

  keywords.add
    //("function")
    //("subroutine")
    //("integer")
    //("real")
    //("complex")
    //("logical")
    //("character")
    //("byte")
    ;

  expr =
      ((!qi::lexeme[keywords >> !(alnum | '_')] >> +(char_ - qi::eol)) > qi::eol) | qi::eol
    ;

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (expr)
  //    );
}







}

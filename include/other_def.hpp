#include "other.hpp"
#include <boost/spirit/include/qi_no_case.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>



namespace f2h
{

template <typename Iterator>
Other<Iterator>::Other(ErrorHandler<Iterator> & error_handler)
  : Other::base_type(expr)
{
  using boost::spirit::ascii::no_case;
  qi::char_type char_;
  qi::alnum_type alnum;
  qi::_1_type _1;
  qi::_2_type _2;
  qi::_3_type _3;
  qi::_4_type _4;
  typedef boost::phoenix::function<ErrorHandler<Iterator> > ErrorHandlerFunction;

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
        ((!qi::lexeme[no_case[keywords] >> !(alnum | '_')] >> +(char_ - qi::eol - qi::eoi)) > (qi::eol | qi::eoi))
      | qi::eol 
    ;

  qi::on_error<qi::fail>(expr,
      ErrorHandlerFunction(error_handler)(
        "Error! Expecting ", _4, _3));

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (expr)
  //    );
}







}

#include "function.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>

namespace f2h
{

template <typename Iterator>
Function<Iterator>::Function(ErrorHandler<Iterator>& error_handler)
  : Function::base_type(start), type_spec(error_handler), primary_expression(error_handler)
{
  qi::alpha_type alpha;
  qi::alnum_type alnum;
  qi::string_type string;
  qi::raw_type raw;
  qi::lexeme_type lexeme;
  qi::char_type char_;
  qi::_1_type _1;
  qi::_2_type _2;
  qi::_3_type _3;
  qi::_4_type _4;
  typedef boost::phoenix::function<ErrorHandler<Iterator> > ErrorHandlerFunction;

  argument_list = -(primary_expression.identifier % ',');

  result_prefix = string("result");

  result = result_prefix > '(' > primary_expression.identifier > ')';

  start =  -(type_spec)
        >> qi::raw[qi::lexeme[(string("subroutine") | string("function")) >> !(alnum | '_')]]
        >  primary_expression.identifier
        >  -('(' > argument_list > ')')
        >  -(result)
        >  -(string("bind") > '(' > 'c' > -(',' > string("name") > '=' > primary_expression.const_char_expr) > ')')
        >  qi::eol
        ;

  qi::on_error<qi::fail>(start,
      ErrorHandlerFunction(error_handler)(
        "Error! Expecting ", _4, _3));


  //BOOST_SPIRIT_DEBUG_NODES(
  //    (start)
  //    (primary_expression.identifier)
  //    (result)
  //    (primary_expression.const_char_expr)
  //    (argument_list)
  //    );

}

}

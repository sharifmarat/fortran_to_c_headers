#include "function.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{


template <typename Iterator>
Function<Iterator>::Function()
  : Function::base_type(start)
{
  qi::alpha_type alpha;
  qi::alnum_type alnum;
  qi::string_type string;
  qi::raw_type raw;
  qi::lexeme_type lexeme;
  qi::char_type char_;

  argument_list = -(primary_expression.identifier % ',');

  result_prefix = string("result");

  result = result_prefix > '(' > primary_expression.identifier > ')';

  start =  -(type_spec)
        >> qi::raw[qi::lexeme[(string("subroutine") | string("function")) >> !(alnum | '_')]]
        >  primary_expression.identifier
        >  '(' > argument_list > ')'
        >  -(result)
        >  -(string("bind") > '(' > 'c' > -(',' > string("name") > '=' > primary_expression.const_char_expr) > ')')
        >  qi::eol
        ;

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (start)
  //    (primary_expression.identifier)
  //    (result)
  //    (primary_expression.const_char_expr)
  //    (argument_list)
  //    );

}

}

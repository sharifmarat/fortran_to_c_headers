#include "primary_expression.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{


template <typename Iterator>
PrimaryExpression<Iterator>::PrimaryExpression()
  : PrimaryExpression::base_type(primary_expression)
{
  qi::alpha_type alpha;
  qi::alnum_type alnum;
  qi::string_type string;
  qi::raw_type raw;
  qi::lexeme_type lexeme;
  qi::char_type char_;
  qi::uint_type uint_;
  qi::bool_type bool_;

  name = raw[lexeme[(alpha | '_') >> *(alnum | '_')]];
  identifier = name;

  argument_list = -(primary_expression % ',');

  const_char_expr =   ('"' >> +(char_ - '"') >> '"')
                    | ('\'' >> +(char_ - '\'') >> '\'')
                    ;

  function_call =   (identifier >> '(')
                  > argument_list
                  > ')'
                  ;
  primary_expression =  uint_
                      | function_call
                      | identifier
                      | bool_   //TODO change to .true. or .false.
                      // TODO identifier(array_spec)
                      | const_char_expr
                      ;


  //BOOST_SPIRIT_DEBUG_NODES(
  //    (primary_expression)
  //    (uint_)
  //    (function_call)
  //    (argument_list)
  //    (identifier)
  //    (bool_)
  //    (const_char_expr)
  //    );

}

}

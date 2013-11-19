#include "primary_expression.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{


template <typename Iterator>
PrimaryExpression<Iterator>::PrimaryExpression(ErrorHandler<Iterator> & error_handler)
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
  qi::_1_type _1;
  qi::_2_type _2;
  qi::_3_type _3;
  qi::_4_type _4;
  typedef boost::phoenix::function<ErrorHandler<Iterator> > ErrorHandlerFunction;

  name = raw[lexeme[(alpha | '_') >> *(alnum | '_')]];
  identifier = name;

  argument_list = -(primary_expression % ',');

  const_char_expr =   ('"' >> +(char_ - '"') >> '"')
                    | ('\'' >> +(char_ - '\'') >> '\'')
                    ;

  primary_expression =  uint_
                      | identifier
                      | const_char_expr
                      ;

  qi::on_error<qi::fail>(primary_expression,
      ErrorHandlerFunction(error_handler)(
        "Error! Expecting ", _4, _3));

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (primary_expression)
  //    (uint_)
  //    (argument_list)
  //    (identifier)
  //    (bool_)
  //    (const_char_expr)
  //    );

}

}

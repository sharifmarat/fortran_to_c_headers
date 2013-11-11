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

  name = !other.keywords >> raw[lexeme[(alpha | '_') >> *(alnum | '_')]];

  identifier = name;

  argument_list = -(identifier % ',');

  const_char_expr =   ('"' >> +(char_ - '"') >> '"')
                    | ('\'' >> +(char_ - '\'') >> '\'')
                    ;
  
  start = qi::lexeme[(string("subroutine") | string("function")) >> !(alnum | '_')]
        > identifier
        > '(' > argument_list > ')'
        > string("bind") > '(' > 'c' > -(',' > string("name") > '=' > const_char_expr) > ')'
        > qi::eol
        ;

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (start)
  //    (identifier)
  //    (const_char_expr)
  //    (argument_list)
  //    );

}

}

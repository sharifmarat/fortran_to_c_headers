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

  name = !expr.keywords >> raw[lexeme[(alpha | '_') >> *(alnum | '_')]];

  identifier = name;

  start = qi::lexeme[(string("subroutine") | string("function")) >> !(alnum | '_')]  // make sure we have whole words
        > identifier
        > expr;

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (start)
  //    );

}

}

#include "grammar.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{

template <typename Iterator>
Grammar<Iterator>::Grammar()
  : Grammar::base_type(program)
{

  program = +(function | expr);

  //expression = implicit | id;
  //implicit = "implicit none";
  //id = qi::lexeme[ (qi::alpha | '_') >> *(qi::alnum | '_') ];

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (program)
  //);
}

}

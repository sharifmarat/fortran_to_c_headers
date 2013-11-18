#include "grammar.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{

template <typename Iterator>
Grammar<Iterator>::Grammar(ErrorHandler<Iterator>& error_handler)
  : Grammar::base_type(program), function(error_handler), other(error_handler), var_decl(error_handler)
{
  program_block = (modificator | function | var_decl | other);

  program = *program_block;

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (program_block)
  //    );

}

}

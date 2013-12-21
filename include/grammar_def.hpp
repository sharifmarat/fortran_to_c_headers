#include "grammar.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{

template <typename Iterator>
Grammar<Iterator>::Grammar(ErrorHandler<Iterator>& error_handler)
  : Grammar::base_type(program), function(error_handler), other(error_handler), var_decl(error_handler)
{
  qi::_1_type _1;
  qi::_2_type _2;
  qi::_3_type _3;
  qi::_4_type _4;
  typedef boost::phoenix::function<ErrorHandler<Iterator> > ErrorHandlerFunction;

  program_block = (modificator | function | var_decl | other);

  program = *program_block;

  qi::on_error<qi::fail>(program,
      ErrorHandlerFunction(error_handler)(
        "Error! Expecting ", _4, _3));

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (program_block)
  //    );

}

}

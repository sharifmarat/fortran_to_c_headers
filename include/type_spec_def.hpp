#include "type_spec.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{

template <typename Iterator>
TypeSpec<Iterator>::TypeSpec(ErrorHandler<Iterator>& error_handler)
  : TypeSpec::base_type(type_spec), primary_expression(error_handler)
{
  qi::alpha_type alpha;
  qi::alnum_type alnum;
  qi::string_type string;
  qi::raw_type raw;
  qi::lexeme_type lexeme;
  qi::char_type char_;
  qi::uint_type uint_;
  qi::_1_type _1;
  qi::_2_type _2;
  qi::_3_type _3;
  qi::_4_type _4;
  typedef boost::phoenix::function<ErrorHandler<Iterator> > ErrorHandlerFunction;

  char_len_param = primary_expression | '*' | ':';

  // kind is a subset of char_or_kind_selector
  char_or_kind_selector =   (    '('
                              >> -(string("len") > '=')
                              >> char_len_param
                              >> -(',' >> string("kind") > '=' > primary_expression)
                              >> ')'
                            )
                          | (    '('
                              >> char_len_param
                              >> ','
                              >> -(string("kind") > '=')
                               > primary_expression
                               > ')'
                            )
                          | (    '('
                              >> string("kind") > '=' > primary_expression
                              >> -(',' > string("len") > '=' > char_len_param)
                               > ')'
                            )
                          | (    '*'
                              >> uint_
                            )
                          | (    '*'
                              >> char_('(')
                               > char_len_param
                               > char_(')')
                            )
                          ;

  type_spec_intrinsic = (  string("integer")
                         | string("real")
                         | string("character")
                        )
                        >> -(char_or_kind_selector)
                        ; 

  type_spec_type = (  string("type")
                    | string("class")
                   )
                   >> '('
                   >  (primary_expression.name | string("*"))
                   >  ')'
                   ;


  type_spec = type_spec_intrinsic | type_spec_type;

  qi::on_error<qi::fail>(type_spec,
      ErrorHandlerFunction(error_handler)(
        "Error! Expecting ", _4, _3));
  
  //BOOST_SPIRIT_DEBUG_NODES(
  //    (type_spec)
  //    (type_spec_type)
  //    (type_spec_intrinsic)
  //    (char_or_kind_selector)
  //    (char_len_param)
  //    );

}

}

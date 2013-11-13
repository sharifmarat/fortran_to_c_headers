#include "type_spec.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{

template <typename Iterator>
TypeSpec<Iterator>::TypeSpec()
  : TypeSpec::base_type(type_spec)
{
  qi::alpha_type alpha;
  qi::alnum_type alnum;
  qi::string_type string;
  qi::raw_type raw;
  qi::lexeme_type lexeme;
  qi::char_type char_;
  qi::uint_type uint_;

  //type_spec_intrinsic
 
  kind_prefix = '(' >> -(string("kind") >> '=');

  kind =   ('*' > uint_)
         | (kind_prefix > primary_expression > ')');

  type_spec_intrinsic = (  string("integer")
                         | string("real")
                        )
                        >> -(kind)
                        ; 

  type_spec_type = (  string("type")
                    | string("class")
                   )
                   > '('
                   > primary_expression.name
                   > ')'
                   ;


  type_spec = type_spec_intrinsic | type_spec_type;
  
  //BOOST_SPIRIT_DEBUG_NODES(
  //    (type_spec)
  //    );

}

}

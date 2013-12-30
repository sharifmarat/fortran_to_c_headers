#include "variable_declaration.hpp"
#include <boost/spirit/include/qi_no_case.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{

unsigned int ParameterToUInt(ast::Identifier id)
{
  //TODO search among global parameters
  return 4;
}

template <typename Iterator>
VariableDeclaration<Iterator>::VariableDeclaration(ErrorHandler<Iterator>& error_handler)
  : VariableDeclaration::base_type(var_decl), primary_expression(error_handler), type_spec(error_handler),
    balanced_parentheses(error_handler), bind_attribute(error_handler)
{
  using boost::spirit::ascii::no_case;
  using qi::lit;
  qi::char_type char_;
  qi::alnum_type alnum;
  qi::alpha_type alpha;
  qi::string_type string;
  qi::raw_type raw;
  qi::lexeme_type lexeme;
  qi::uint_type uint_;
  qi::_1_type _1;
  qi::_2_type _2;
  qi::_3_type _3;
  qi::_4_type _4;
  typedef boost::phoenix::function<ErrorHandler<Iterator> > ErrorHandlerFunction;

  initialize_spec = '=' > +(char_ - qi::eol);
  variable_name = primary_expression.identifier >> -(balanced_parentheses) >> -(initialize_spec);
  variable_list = variable_name % ',';

  attribute =   no_case[string("allocatable")]
              | no_case[string("asynchronous")]
              | no_case[string("automatic")]
              | bind_attribute
              | no_case[string("codimension")]
              | no_case[string("contiguous")]
              | (no_case[string("dimension")] >> -(balanced_parentheses))
              | no_case[string("external")]
              | (no_case[string("intent")] >> '(' >> (no_case[string("in")] | no_case[string("out")] | no_case[string("inout")]) >> ')')
              | no_case[string("external")]
              | no_case[string("intrinsic")]
              | no_case[string("optional")]
              | no_case[string("parameter")]
              | no_case[string("pointer")]
              | no_case[string("private")]
              | no_case[string("protected")]
              | no_case[string("public")]
              | no_case[string("save")]
              | no_case[string("static")]
              | no_case[string("target")]
              | no_case[string("value")]
              | no_case[string("volatile")]
              ;

  attribute_list = attribute % ',';

  var_decl_attribute = attribute >> -lit("::") > variable_list;

  var_decl_simple = type_spec >> -lit("::") > variable_list;

  var_decl_extended = type_spec >> ',' > attribute_list >> lit("::") > variable_list;

  var_decl = (var_decl_extended | var_decl_simple | var_decl_attribute) > qi::eol;

  qi::on_error<qi::fail>(var_decl,
      ErrorHandlerFunction(error_handler)(
        "Error! Expecting ", _4, _3));

  //BOOST_SPIRIT_DEBUG_NODES(
  //    (attribute)
  //    (initialize_spec)
  //    (variable_name)
  //    (attribute_list)
  //    (variable_list)
  //    (var_decl_simple)
  //    (var_decl_extended)
  //    (var_decl)
  //    );
}







}

#ifndef F2H_BIND_ATTRIBUTE_HPP
#define F2H_BIND_ATTRIBUTE_HPP

#include "error_handler.hpp"
#include "primary_expression.hpp"
#include "skipper.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct BindAttribute : qi::grammar<Iterator, std::string(), Skipper<Iterator> >
{   
  BindAttribute(ErrorHandler<Iterator>& error_handler)
    : BindAttribute::base_type(bind_attribute), primary_expression(error_handler)
  {
    using qi::lit;
    qi::string_type string;
    qi::char_type char_;
    qi::_3_type _3;
    qi::_4_type _4;

    typedef boost::phoenix::function<ErrorHandler<Iterator> > ErrorHandlerFunction;

    bind_attribute =   string("bind") 
                     > '(' 
                     > 'c' 
                     > -(  ',' 
                          > lit("name") 
                          > char_('=')
                          > primary_expression.const_char_expr
                        ) 
                     > ')';

    qi::on_error<qi::fail>(bind_attribute, 
        ErrorHandlerFunction(error_handler)(
          "Error! Expecting ", _4, _3));
  }

  qi::rule<Iterator, std::string(), Skipper<Iterator> > bind_attribute;

  PrimaryExpression<Iterator> primary_expression;
};


}


#endif //F2H_BIND_ATTRIBUTE_HPP


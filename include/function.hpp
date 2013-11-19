#ifndef F2H_FUNCTION_HPP
#define F2H_FUNCTION_HPP

#include "ast.hpp"
#include "error_handler.hpp"
#include "type_spec.hpp"
#include "primary_expression.hpp"
#include "skipper.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct Function : qi::grammar<Iterator, ast::Function(), Skipper<Iterator> >
{   
  Function(ErrorHandler<Iterator>& error_handler);

  qi::rule<Iterator, ast::Function(), Skipper<Iterator> > start;

  qi::rule<Iterator, Skipper<Iterator> > result_prefix;

  qi::rule<Iterator, ast::Identifier(), Skipper<Iterator> > result;

  qi::rule<Iterator, std::list<ast::Identifier>(), Skipper<Iterator>  > argument_list;

  TypeSpec<Iterator> type_spec;

  PrimaryExpression<Iterator> primary_expression;

  qi::symbols<char> function_attributes;
};


}


#endif //F2H_FUNCTION_HPP

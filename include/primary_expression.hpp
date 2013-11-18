#ifndef F2H_PRIMARY_EXPRESSION_HPP
#define F2H_PRIMARY_EXPRESSION_HPP

#include "error_handler.hpp"
#include "ast.hpp"
#include "skipper.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct PrimaryExpression : qi::grammar<Iterator, ast::PrimaryExpression(), Skipper<Iterator> >
{   
  PrimaryExpression(ErrorHandler<Iterator>& error_handler);

  qi::rule<Iterator, ast::PrimaryExpression(), Skipper<Iterator> > primary_expression;

  qi::rule<Iterator, std::string(), Skipper<Iterator> > name;

  qi::rule<Iterator, ast::Identifier(), Skipper<Iterator> > identifier;

  qi::rule<Iterator, std::string(), Skipper<Iterator> > const_char_expr;

  qi::rule<Iterator, std::list<ast::PrimaryExpression>(), Skipper<Iterator> > argument_list;

  qi::rule<Iterator, ast::FunctionCall(), Skipper<Iterator> > function_call;
};


}


#endif //F2H_PRIMARY_EXPRESSION_HPP

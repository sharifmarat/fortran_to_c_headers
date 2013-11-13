#ifndef F2H_TYPE_SPEC_HPP
#define F2H_TYPE_SPEC_HPP

#include "ast.hpp"
#include "skipper.hpp"
#include "primary_expression.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;


template <typename Iterator>
struct TypeSpec : qi::grammar<Iterator, ast::TypeSpec(), Skipper<Iterator> >
{   
  TypeSpec();

  PrimaryExpression<Iterator> primary_expression;

  qi::rule<Iterator, Skipper<Iterator> > kind_prefix;

  qi::rule<Iterator, ast::PrimaryExpression(), Skipper<Iterator> > kind;

  qi::rule<Iterator, ast::TypeSpecIntrinsic(), Skipper<Iterator> > type_spec_intrinsic;

  qi::rule<Iterator, ast::TypeSpecType(), Skipper<Iterator> > type_spec_type;

  qi::rule<Iterator, ast::TypeSpec(), Skipper<Iterator> > type_spec;
};


}


#endif //F2H_TYPE_SPEC_HPP

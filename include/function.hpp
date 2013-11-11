#ifndef F2H_FUNCTION_HPP
#define F2H_FUNCTION_HPP

#include "ast.hpp"
#include "other.hpp"
#include "skipper.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct Function : qi::grammar<Iterator, ast::Function(), Skipper<Iterator> >
{   
  Function();

  qi::rule<Iterator, ast::Function(), Skipper<Iterator> > start;

  qi::rule<Iterator, std::string(), Skipper<Iterator> > name;

  qi::rule<Iterator, ast::Identifier(), Skipper<Iterator> > identifier;

  qi::rule<Iterator, std::list<ast::Identifier>(), Skipper<Iterator>  > argument_list;

  qi::rule<Iterator, std::string(), Skipper<Iterator> > const_char_expr;

  Other<Iterator> other;
  
  // TODO statements
};


}


#endif //F2H_FUNCTION_HPP

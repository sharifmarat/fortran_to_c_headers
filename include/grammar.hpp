#ifndef F2H_GRAMMAR_HPP
#define F2H_GRAMMAR_HPP

#include "other.hpp"
#include "skipper.hpp"
#include "variable_declaration.hpp"
#include "function.hpp"
#include "ast.hpp"
#include "modificator.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct Grammar : qi::grammar<Iterator, ast::Program(), Skipper<Iterator> >
{
  Grammar();

  Function<Iterator> function;
  Other<Iterator> other;
  VariableDeclaration<Iterator> var_decl;
  Modificator<Iterator> modificator;

  qi::rule<Iterator, ast::ProgramBlock(), Skipper<Iterator> > program_block;

  qi::rule<Iterator, ast::Program(), Skipper<Iterator> > program;
};



}


#endif //F2H_GRAMMAR_HPP

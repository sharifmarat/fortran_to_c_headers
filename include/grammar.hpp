#ifndef F2H_GRAMMAR_HPP
#define F2H_GRAMMAR_HPP

#include "expression.hpp"
#include "variable_declaration.hpp"
#include "function.hpp"
#include "ast.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct Grammar : qi::grammar<Iterator, ast::Program(), ascii::space_type>
{
  Grammar();

  Function<Iterator> function;
  Expression<Iterator> expr;
  VariableDeclaration<Iterator> var_decl;

  qi::rule<Iterator, ast::ProgramBlock(), ascii::space_type> program_block;

  qi::rule<Iterator, ast::Program(), ascii::space_type> program;
};



}


#endif //F2H_GRAMMAR_HPP

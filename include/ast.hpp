#ifndef F2H_AST_HPP
#define F2H_AST_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <list>


namespace f2h
{
namespace ast
{

struct tagged
{
  int id; // Used to annotate the AST with the iterator position.
          // This id is used as a key to a map<int, Iterator>
          // (not really part of the AST.)
};

struct nil {};
struct unary;
struct expression;

struct identifier : tagged
{
  identifier(std::string const& name = "") : name(name) {}
  std::string name;
};

struct expression
{
  std::string value;
};

struct function
{
  std::string prefix;
  identifier function_name;
  expression expr;
};

typedef std::list<function> function_list;

// print functions for debugging
inline std::ostream& operator<<(std::ostream& out, nil)
{
  out << "nil"; return out;
}

inline std::ostream& operator<<(std::ostream& out, identifier const& id)
{
  out << id.name; return out;
}


}
}

BOOST_FUSION_ADAPT_STRUCT(
  f2h::ast::expression,
  (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
  f2h::ast::function,
  (std::string, prefix)
  (f2h::ast::identifier, function_name)
  (f2h::ast::expression, expr)
)


#endif //F2H_AST_HPP

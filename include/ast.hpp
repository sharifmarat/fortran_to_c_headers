#ifndef F2H_AST_HPP
#define F2H_AST_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <list>


namespace f2h
{
namespace ast
{

struct Tagged
{
  int id; // Used to annotate the AST with the iterator position.
          // This id is used as a key to a map<int, Iterator>
          // (not really part of the AST.)
};

struct Nil {};
struct Expression;
struct Function;
struct VariableDeclaration;

struct Identifier : Tagged
{
  Identifier(std::string const& name = "") : name(name) {}
  std::string name;
};

typedef boost::variant<
      Nil
    , Expression
    , Function
    , VariableDeclaration
  >
ProgramBlock;

struct Expression
{
  std::string value;
};

struct VariableDeclaration
{
  std::list<Identifier> variables;
};

struct Function
{
  std::string prefix;
  Identifier function_name;
  std::list<Identifier> argument_list;
  std::string bind_name;
};

typedef std::list<ProgramBlock> Program;

// print functions for debugging
inline std::ostream& operator<<(std::ostream& out, Nil)
{
  out << "nil"; return out;
}

inline std::ostream& operator<<(std::ostream& out, Identifier const& id)
{
  out << id.name; return out;
}


}
}

BOOST_FUSION_ADAPT_STRUCT(
  f2h::ast::Expression,
  (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
  f2h::ast::VariableDeclaration,
  (std::list<f2h::ast::Identifier>, variables)
)

BOOST_FUSION_ADAPT_STRUCT(
  f2h::ast::Function,
  (std::string, prefix)
  (f2h::ast::Identifier, function_name)
  (std::list<f2h::ast::Identifier>, argument_list)
  (std::string, bind_name)
)

#endif //F2H_AST_HPP

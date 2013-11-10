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
struct Other;
struct Function;
struct VariableDeclarationSimple;
struct VariableDeclarationExtended;

struct Identifier : Tagged
{
  Identifier(std::string const& name = "") : name(name) {}
  std::string name;
};

typedef boost::variant<
      VariableDeclarationSimple
    , VariableDeclarationExtended
  >
VariableDeclaration;

typedef boost::variant<
      Nil
    , Other
    , Function
    , VariableDeclaration
  >
ProgramBlock;

typedef unsigned int Kind;

struct Other
{
  std::string value;
};

struct VariableDeclarationSimple
{
  std::string keyword;
  std::list<Identifier> variables;
};

struct VariableDeclarationExtended
{
  std::string keyword;
  std::list<std::string> attributes;
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
  f2h::ast::Other,
  (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
  f2h::ast::VariableDeclarationSimple,
  (std::string, keyword)
  (std::list<f2h::ast::Identifier>, variables)
)

BOOST_FUSION_ADAPT_STRUCT(
  f2h::ast::VariableDeclarationExtended,
  (std::string, keyword)
  (std::list<std::string>, attributes)
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

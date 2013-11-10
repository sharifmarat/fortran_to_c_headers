#include "generator.h"

#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/variant/apply_visitor.hpp>

#include "exception.h"

namespace f2h
{

Generator::Generator(const std::string &out_file_name)
  : out_file_name_(out_file_name)
{
}

void Generator::Generate(ast::Program const& x)
{
  // process grammar
  (*this)(x);

  // dump to file
  out_.open(out_file_name_.c_str(), std::ios_base::out | std::ios_base::trunc);

  if (!out_.is_open())
  {
    throw UnableToOpenFileForWritingException();
  }

  DumpHeaderStart();

  if (!body_.empty()) out_ << body_;
  
  DumpHeaderEnd();

  out_.close();
}

bool Generator::operator()(ast::Identifier const& x)
{
  body_ += x.name;
  return true;
}
  
bool Generator::operator()(ast::Other const& x)
{
  return true;
}
  
bool Generator::operator()(ast::VariableDeclaration const& x)
{
  return true;
}

bool Generator::operator()(ast::Function const& x)
{
  body_ += "void " + x.function_name.name + "(";
  for (std::list<ast::Identifier>::const_iterator it = x.argument_list.begin(); it != x.argument_list.end(); ++it)
  {
    if (it != x.argument_list.begin()) body_ += ", ";
    if (!(*this)(*it))
    {
      return false;
    }
  }
  body_ += ");\n\n";
  return true;
}

bool Generator::operator()(ast::Program const& x)
{

  BOOST_FOREACH(ast::ProgramBlock const& o, x)
  {
    if (!boost::apply_visitor(*this, o))
    {
      return false;
    }
  }
  return true;
}
  

void Generator::DumpHeaderStart() const
{
  out_ << "#ifndef " << GetDefineName() << "\n";
  out_ << "#define " << GetDefineName() << "\n\n";
  out_ << "#ifdef __cplusplus\n";
  out_ << "extern \"C\"\n";
  out_ << "{\n";
  out_ << "#endif\n\n";
}


void Generator::DumpHeaderEnd() const
{
  out_ << "#ifdef __cplusplus\n";
  out_ << "}\n";
  out_ << "#endif\n\n";
  out_ << "#endif //" << GetDefineName() << "\n";
}
  
std::string Generator::GetDefineName() const
{
  std::string basename = boost::filesystem::basename(out_file_name_);
  boost::replace_all(basename, " ", "_");
  boost::replace_all(basename, "\"", "_");
  boost::replace_all(basename, "\'", "_");
  boost::to_upper(basename);
  basename = basename + "_H";
  return basename;
}

}

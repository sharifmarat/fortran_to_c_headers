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

  for (std::list<Function>::const_iterator it = functions_.begin(); it != functions_.end(); ++it)
  {
    const Function& function = *it;
    body_ += function.return_value + " " + function.name + "(";
    for (std::list<Argument>::const_iterator argument_it = function.argument_list.begin(); argument_it != function.argument_list.end(); ++argument_it)
    {
      if (argument_it != function.argument_list.begin()) body_ += ", ";
      const Argument& argument = *argument_it;
      body_ += argument.type + " " + argument.name;
    }
    body_ += ");\n\n";
  }

  out_ << body_;
  
  DumpHeaderEnd();

  out_.close();
}

bool Generator::operator()(ast::Identifier const& x)
{
  return true;
}
  
bool Generator::operator()(ast::Other const& x)
{
  return true;
}
  
bool Generator::operator()(ast::Function const& x)
{
  Function new_function;
  new_function.return_value = "void";
  new_function.name = x.function_name.name;
  for (std::list<ast::Identifier>::const_iterator it = x.argument_list.begin(); it != x.argument_list.end(); ++it)
  {
    Argument arg;
    arg.type = "void";
    arg.name = (*it).name;
    new_function.argument_list.push_back(arg);
    std::cout << "pushing " << (*it).name << " into " << x.function_name.name << "\n";
  }

  functions_.push_back(new_function);
  return true;
}
  
bool Generator::operator()(ast::VariableDeclaration const& x)
{
  if (!boost::apply_visitor(*this, x))
  {
    return false;
  }
  return true;
}

bool Generator::operator()(ast::VariableDeclarationSimple const& x)
{
  std::cout << "ast::VariableDeclarationSimple " << x.keyword << " vars = \n";
  for (std::list<ast::Identifier>::const_iterator it = x.variables.begin(); it != x.variables.end(); ++it)
  {
    std::cout << (*it).name << "\n";

    if (!functions_.empty())
    {
      Function& current_function = functions_.back();
      std::list<Argument>::iterator argument_it = current_function.find_argument((*it).name);
      if (argument_it != current_function.argument_list.end())
      {
        if (x.keyword.find("integer") == 0)
        {
          (*argument_it).type = "int";
        }
        else if (x.keyword.find("real") == 0)
        {
          (*argument_it).type = "double";
        }
        else
        {
          //TODO
          std::cout << "!!! unable to map keyword = `" << x.keyword << "'\n";
        }
      }
      else
      {
        std::cout << "!!! unable to find " << (*it).name << "\n";
      }
    }
  }
  std::cout << "\n";



  return true;
}

bool Generator::operator()(ast::VariableDeclarationExtended const& x)
{
  std::cout << "ast::VariableDeclarationExtended " << x.keyword << " attrs = ";
  for (std::list<std::string>::const_iterator it = x.attributes.begin(); it != x.attributes.end(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << " vars = \n";
  for (std::list<ast::Identifier>::const_iterator it = x.variables.begin(); it != x.variables.end(); ++it)
  {
    std::cout << (*it).name << "\n";

    if (!functions_.empty())
    {
      Function& current_function = functions_.back();
      std::list<Argument>::iterator argument_it = current_function.find_argument((*it).name);
      if (argument_it != current_function.argument_list.end())
      {
        if (x.keyword.find("integer") == 0)
        {
          (*argument_it).type = "int";
        }
        else if (x.keyword.find("real") == 0)
        {
          (*argument_it).type = "double";
        }
        else
        {
          //TODO
          std::cout << "!!! unable to map keyword = `" << x.keyword << "'\n";
        }
      }
      else
      {
        std::cout << "!!! unable to find " << (*it).name << "\n";
      }
    }
  }
  std::cout << "\n";
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

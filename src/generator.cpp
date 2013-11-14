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

void Generator::Generate(ast::Program const& x, const std::string& define_name)
{
  // process grammar
  (*this)(x);

  // dump to file
  out_.open(out_file_name_.c_str(), std::ios_base::out | std::ios_base::trunc);

  if (!out_.is_open())
  {
    throw UnableToOpenFileForWritingException();
  }

  DumpHeaderStart(define_name);

  for (std::list<Function>::const_iterator it = functions_.begin(); it != functions_.end(); ++it)
  {
    const Function& function = *it;
    body_ += function.return_value.ToCType() + " " + function.name + "(";
    for (std::list<Argument>::const_iterator argument_it = function.argument_list.begin(); argument_it != function.argument_list.end(); ++argument_it)
    {
      if (argument_it != function.argument_list.begin()) body_ += ", ";
      const Argument& argument = *argument_it;
      body_ += argument.ToCTypeWithName();
    }
    body_ += ");\n\n";
  }

  out_ << body_;
  
  DumpHeaderEnd(define_name);

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
  new_function.name = x.function_name.name;
  for (std::list<ast::Identifier>::const_iterator it = x.argument_list.begin(); it != x.argument_list.end(); ++it)
  {
    Argument arg;
    arg.type = "void";
    arg.name = (*it).name;
    new_function.argument_list.push_back(arg);
    std::cout << "pushing " << (*it).name << " into " << x.function_name.name << "\n";
  }

  // set return value
  new_function.return_value.type = (x.type_spec_prefix) ? boost::apply_visitor(TypeSpecToCType(), *x.type_spec_prefix) : "void";
  new_function.return_value.name = (x.result) ? (*x.result).name : x.function_name.name;
  new_function.return_value.pointer = false;
  new_function.return_value.constant = false;

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
  
bool Generator::operator()(ast::VariableDeclarationAttribute const& x)
{
  if (functions_.empty()) return true;
  Function& current_function = functions_.back();
  for (std::list<ast::Identifier>::const_iterator it = x.variables.begin(); it != x.variables.end(); ++it)
  {
    current_function.SetArgumentAttribute((*it).name, x.keyword);
  }
  return true;
}

bool Generator::operator()(ast::VariableDeclarationSimple const& x)
{
  if (functions_.empty()) return true;
  Function& current_function = functions_.back();
  for (std::list<ast::Identifier>::const_iterator it = x.variables.begin(); it != x.variables.end(); ++it)
  {
    current_function.SetArgumentType((*it).name, x.type_spec);
  }

  return true;
}

bool Generator::operator()(ast::VariableDeclarationExtended const& x)
{
  if (functions_.empty()) return true;
  Function& current_function = functions_.back();
  for (std::list<ast::Identifier>::const_iterator it = x.variables.begin(); it != x.variables.end(); ++it)
  {
    current_function.SetArgumentType((*it).name, x.type_spec);

    for (std::list<std::string>::const_iterator attribute_it = x.attributes.begin(); attribute_it != x.attributes.end(); ++attribute_it)
    {
      current_function.SetArgumentAttribute((*it).name, *attribute_it);
    }
  }

  return true;
}
  
void Generator::Function::SetArgumentType(const std::string& argument_name, const ast::TypeSpec& type_spec)
{
  std::list<Argument>::iterator argument_it = this->find_argument(argument_name);
  if (argument_it != this->argument_list.end()) (*argument_it).SetArgumentType(type_spec);
  if (this->return_value.name == argument_name) this->return_value.SetArgumentType(type_spec);
}
    
void Generator::Function::SetArgumentAttribute(const std::string& argument_name, const std::string& attribute)
{
  std::list<Argument>::iterator argument_it = this->find_argument(argument_name);
  if (argument_it != this->argument_list.end()) (*argument_it).SetArgumentAttribute(attribute);
  if (this->return_value.name == argument_name) this->return_value.SetArgumentAttribute(attribute);
}

void Generator::Argument::SetArgumentType(const ast::TypeSpec& type_spec)
{
  this->type = boost::apply_visitor(TypeSpecToCType(), type_spec);
}

void Generator::Argument::SetArgumentAttribute(const std::string& attribute)
{
  if (attribute.find("value") == 0) this->pointer = false;
  else if (attribute.find("intentin") == 0) this->constant = true;
  else if (attribute.find("intentout") == 0) this->constant = false;
  else if (attribute.find("dimension") == 0) this->pointer = true;
  else std::cout << "!!! ignored attribute " << attribute << std::endl;
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

std::string Generator::TypeSpecToCType::operator()(ast::TypeSpecIntrinsic const& type_spec) const
{
  std::string result = "unknown_intinsic_type";
  if (type_spec.keyword == "integer") result = "int";
  else if (type_spec.keyword == "real") result = "double";
  return result;
}

std::string Generator::TypeSpecToCType::operator()(ast::TypeSpecType const& type_spec) const
{
  std::string result = "unknown_derived_type";
  if (type_spec.type_name == "c_ptr") result = "void*";
  else result = type_spec.type_name;
  return result;
}

void Generator::DumpHeaderStart(const std::string& define_name) const
{
  out_ << "#ifndef " << define_name << "\n";
  out_ << "#define " << define_name << "\n\n";
  out_ << "#ifdef __cplusplus\n";
  out_ << "extern \"C\"\n";
  out_ << "{\n";
  out_ << "#endif\n\n";
}


void Generator::DumpHeaderEnd(const std::string& define_name) const
{
  out_ << "#ifdef __cplusplus\n";
  out_ << "}\n";
  out_ << "#endif\n\n";
  out_ << "#endif //" << define_name << "\n";
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

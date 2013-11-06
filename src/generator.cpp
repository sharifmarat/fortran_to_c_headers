#include "generator.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include "exception.h"

namespace f2h
{

Generator::Generator(const std::string &out_file_name)
  : out_file_name_(out_file_name)
{
}

void Generator::Generate()
{
  out_.open(out_file_name_.c_str(), std::ios_base::out | std::ios_base::trunc);

  if (!out_.is_open())
  {
    throw UnableToOpenFileForWritingException();
  }

  DumpHeaderStart();

  //TODO
  
  DumpHeaderEnd();

  out_.close();
}

bool Generator::operator()(ast::identifier const& x)
{
}

bool Generator::operator()(ast::function const& x)
{
  std::cout << "Generator::operator() with ast::function" << std::endl;
  body_ += "void" + x.function_name.name + "();\n";
}

bool Generator::operator()(ast::function_list const& x)
{
  std::cout << "Generator::operator() with ast::function_list, size = " << x.size()  << std::endl;
  for (std::list<ast::function>::const_iterator it = x.begin(); it != x.end(); ++it)
  {
    std::cout << "Generator::operator() with ast::function_list in cycle" << std::endl;
    if (!(*this)(*it))
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

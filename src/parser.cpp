#include "parser.h"

#include <boost/spirit/include/classic.hpp>

#include "exception.h"

namespace f2h
{

Parser::Parser(const std::string &in_file_name)
  : in_file_name_(in_file_name)
{
}
  
void Parser::Parse()
{
  in_.open(in_file_name_.c_str());

  if (!in_.is_open())
  {
    throw UnableToOpenFileForReadingException();
  }

  in_.close();
}

}


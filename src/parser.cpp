#include "parser.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/algorithm/string.hpp>

#include "error_handler.hpp"
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

  std::string code;
  in_.unsetf(std::ios::skipws);
  std::copy(
      std::istream_iterator<char>(in_),
      std::istream_iterator<char>(),
      std::back_inserter(code));

  typedef std::string::const_iterator iterator_type;
  iterator_type iter = code.begin();
  iterator_type end = code.end();

  Skipper<iterator_type> skipper;
  ErrorHandler<iterator_type> error_handler(iter, end);
  Grammar<iterator_type> grammar(error_handler);

  bool parse_status = phrase_parse(iter, end, grammar, skipper, ast_);
  if (!parse_status || iter != end)
  {
    std::cerr << "parsing error" << std::endl;
    std::cerr << "please submit an error, if code compiles by fortran compiler" << std::endl;
  }

  in_.close();
}

}


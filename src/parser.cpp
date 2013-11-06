#include "parser.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/algorithm/string.hpp>

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

  std::string line;

  while (std::getline(in_, line))
  {
    //TODO: make sure empty lines are skipped in the skipper
    boost::trim(line);
    if (line.length() == 0) continue;

    std::string::const_iterator iter = line.begin();
    std::string::const_iterator end = line.end();
    //bool parse_status = phrase_parse(iter, end, grammar_, space_, ast_);
    bool parse_status = phrase_parse(iter, end, +grammar_, space_, ast_);
    std::cout << "!!!!!!!!!!\n ast size = " << ast_.size() << "\n";

    if (!parse_status || iter != end)
    {
      std::cerr << "parsing error" << std::endl;
    }
  }

  in_.close();
}

}


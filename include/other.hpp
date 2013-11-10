#ifndef F2H_OTHER_HPP
#define F2H_OTHER_HPP

#include <boost/spirit/include/qi.hpp>
#include <vector>

#include "ast.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct Other : qi::grammar<Iterator, ast::Other(), ascii::space_type>
{   
  Other();

  qi::rule<Iterator, ast::Other(), ascii::space_type> expr;

  qi::symbols<char> keywords;
};


}


#endif //F2H_OTHER_HPP

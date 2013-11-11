#ifndef F2H_OTHER_HPP
#define F2H_OTHER_HPP

#include <boost/spirit/include/qi.hpp>
#include <vector>

#include "skipper.hpp"
#include "ast.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct Other : qi::grammar<Iterator, ast::Other(), Skipper<Iterator> >
{   
  Other();

  qi::rule<Iterator, ast::Other(), Skipper<Iterator> > expr;

  qi::symbols<char> keywords;
};


}


#endif //F2H_OTHER_HPP

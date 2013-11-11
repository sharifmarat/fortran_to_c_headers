#ifndef F2H_SKIPPER_HPP
#define F2H_SKIPPER_HPP

#include <boost/spirit/include/qi.hpp>

namespace f2h
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct Skipper : qi::grammar<Iterator>
{   
  Skipper();

  qi::rule<Iterator> comment;

  qi::rule<Iterator> skip;
};


}


#endif //F2H_SKIPPER_HPP

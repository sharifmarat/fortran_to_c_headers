#ifndef F2H_MODIFICATOR_HPP
#define F2H_MODIFICATOR_HPP

#include <boost/spirit/include/qi_no_case.hpp>

#include "ast.hpp"
#include "skipper.hpp"

namespace f2h
{

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct Modificator : qi::grammar<Iterator, ast::Other(), Skipper<Iterator> >
{   
  Modificator()
    : Modificator::base_type(modificator)
  {
    using boost::spirit::ascii::no_case;
    qi::string_type string;
    modificator = (no_case[string("public")] | no_case[string("private")] | no_case[string("protected")]) >> qi::eol;
  }

  qi::rule<Iterator, ast::Other(), Skipper<Iterator> > modificator;
};


}


#endif //F2H_MODIFICATOR_HPP


#ifndef F2H_MODIFICATOR_HPP
#define F2H_MODIFICATOR_HPP

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
    qi::string_type string;
    modificator = (string("public") | string("private") | string("protected")) >> qi::eol;
  }

  qi::rule<Iterator, ast::Other(), Skipper<Iterator> > modificator;
};


}


#endif //F2H_MODIFICATOR_HPP


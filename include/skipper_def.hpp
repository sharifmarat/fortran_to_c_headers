#include "skipper.hpp"
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi_no_case.hpp>


namespace f2h
{


template <typename Iterator>
Skipper<Iterator>::Skipper()
  : Skipper::base_type(skip)
{
  ascii::space_type space;
  qi::char_type char_;
  

  comment = ('!' >> *(char_ - qi::eol));

  skip =   ascii::blank
         | comment
         | ('&' >> *space >> comment >> qi::eol)
         | ('&' >> *space)
         ;

}

}

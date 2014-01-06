#ifndef F2H_EXCEPTION_H
#define F2H_EXCEPTION_H

#include <exception>

namespace f2h
{

class NotImplementedException : public std::exception
{
};   

class UnableToOpenFileForWritingException : public std::exception
{
};

class UnableToOpenFileForReadingException : public std::exception
{
};

class AmbiguousTypedefException : public std::exception
{
};

}


#endif

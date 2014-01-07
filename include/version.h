#ifndef F2H_VERSION_H
#define F2H_VERSION_H

#include <string>

namespace f2h
{

#define TO_STR_HELPER(x) #x
#define TO_STR(x) TO_STR_HELPER(x)

#define F2H_VERSION_MAJOR 0
#define F2H_VERSION_MINOR 1

#define F2H_VERSION_STRING TO_STR(F2H_VERSION_MAJOR) "." TO_STR(F2H_VERSION_MINOR)


inline std::string GetVersionString() { return F2H_VERSION_STRING; }


}

#endif //F2H_VERSION_H


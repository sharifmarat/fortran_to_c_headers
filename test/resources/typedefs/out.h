#ifndef RESULT_H
#define RESULT_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef void* some_ptr_t;

typedef double val_t;

__declspec(dllexport) double dbl1;

__declspec(dllexport) double dbl2;

__declspec(dllexport) int int1;

__declspec(dllexport) void* ptr1;

__declspec(dllexport) int SimpleFunction1();

__declspec(dllexport) double SimpleFunction2(some_ptr_t some_ptr, val_t val);

__declspec(dllexport) void* SimpleFunction3(some_ptr_t some_ptr, val_t val);

#ifdef __cplusplus
}
#endif

#endif //RESULT_H

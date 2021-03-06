#ifndef _CFFIX_H_
#define _CFFIX_H_

#include "nore.h"
#include <stddef.h>

/* make: CFLAGS=-DSHARED=1 */
#if (MSVC)
#  if (1 == EXPORT)
#    define CFFIX_API __declspec(dllexport) __stdcall
#  elif (0 == EXPORT)
#    define CFFIX_API __declspec(dllimport) __stdcall
#  endif /* end of EXPORT */
#else
#  define CFFIX_API
#endif /* end of MSVC */


#ifdef __cplusplus
extern "C" {
#endif

  int CFFIX_API inc(int);
  size_t CFFIX_API str_len(const char *ss);

#ifdef __cplusplus
}
#endif


#endif /* _CFFIX_H_ */

#ifndef _STRS_H_
#define _STRS_H_

#if (LINUX)
#  if !(__USE_POSIX_POSIX_C_SOURCE)
#    define __USE_POSIX
#  endif
#endif

#if (WINNT) && (MSVC)
#  define strerror_r(errno, buf, len) strerror_s(buf, len, errno)
#  define strtok_r                    strtok_s
#endif


#endif /* end of _STRS_H_ */


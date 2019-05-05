#ifndef SAPPHIRE_COMPILER_STATUS_H
#define SAPPHIRE_COMPILER_STATUS_H

/**
 * The following tells us what kind of C
 * features are available to us. Also informs
 * of specific requirements to the OS
 */
#if defined(__STDC__)
# define SAPPHIRE_STD_C_1989
# if defined(__STDC_VERSION__)
#  define SAPPHIRE_STD_C_1990
#  if (__STDC_VERSION__ >= 199409L)
#   define SAPPHIRE_STD_C_1994
#  endif
#  if (__STDC_VERSION__ >= 199901L)
#   define SAPPHIRE_STD_C_1999
#  endif
#  if (__STDC_VERSION__ >= 201112L)
#   define SAPPHIRE_STD_C_2011
#  endif
# endif
#endif

#if defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
#  define SAPPHIRE_OS_UNIX
#endif

#ifdef _WIN32
#  define SAPPHIRE_OS_WIN32
#endif

#ifdef SAPPHIRE_STD_C_1999
#  define SAPPHIRE_HAS_VARIADIC_ARGS
#  define SAPPHIRE_HAS_INLINE_FUNC
#endif

#ifdef WIN32_UTF16_PATHNAMES
#  ifndef SAPPHIRE_STD_C_1994
#     include <stddef.h>
#  else
#     include <wchar.h>
#  endif // SAPPHIRE_STD_C_1994
   typedef wchar_t ospath_ch_t;
#  define OSPATH_CON(expr) L##expr
#else
   typedef char ospath_ch_t;
#  define OSPATH_CON(expr) expr
#endif // WIN32_UTF16_PATHNAMES

#endif // SAPPHIRE_COMPILER_STATUS_H

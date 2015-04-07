/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// "liveMedia"
// Copyright (c) 1996-2015 Live Networks, Inc.  All rights reserved.
// Support for temporarily setting the locale (e.g., to "C" or "POSIX") for (e.g.) parsing or printing
// floating-point numbers in protocol headers, or calling toupper()/tolower() on human-input strings.
// C++ header

#ifndef _LOCALE_HH
#define _LOCALE_HH

// If you're on a system that (for whatever reason) doesn't have either the "setlocale()" or the "newlocale()" function, then
// add "-DLOCALE_NOT_USED" to your "config.*" file.

// If you're on a system that (for whatever reason) has "setlocale()" but not "newlocale()", then
// add "-DXLOCALE_NOT_USED" to your "config.*" file.
// (Note that -DLOCALE_NOT_USED implies -DXLOCALE_NOT_USED; you do not need both.)
// Also, for Windows systems, we define "XLOCALE_NOT_USED" by default, because at least some Windows systems
// (or their development environments) don't have "newlocale()".  If, however, your Windows system *does* have "newlocale()",
// then you can override this by defining "XLOCALE_USED" before #including this file.

#ifdef XLOCALE_USED
#undef LOCALE_NOT_USED
#undef XLOCALE_NOT_USED
#else
#if defined(__WIN32__) || defined(_WIN32)
#define XLOCALE_NOT_USED 1
#endif
#endif

//libScreenShare Fix as android doesn't have this shit
#define __LC_CTYPE       0
#define __LC_NUMERIC         1
#define __LC_TIME        2
#define __LC_COLLATE         3
#define __LC_MONETARY        4
#define __LC_MESSAGES        5
#define __LC_ALL         6
#define __LC_PAPER       7
#define __LC_NAME        8
#define __LC_ADDRESS         9
#define __LC_TELEPHONE      10
#define __LC_MEASUREMENT    11
#define __LC_IDENTIFICATION 12
typedef struct __locale_struct
{
  /* Note: LC_ALL is not a valid index into this array.  */
  struct __locale_data *__locales[13]; /* 13 = __LC_LAST. */

  /* To increase the speed of this solution we add some special members.  */
  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;

  /* Note: LC_ALL is not a valid index into this array.  */
  const char *__names[13];
} *__locale_t;

/* POSIX 2008 makes locale_t official.  */
typedef __locale_t locale_t;

# define LC_CTYPE_MASK      (1 << __LC_CTYPE)
# define LC_NUMERIC_MASK    (1 << __LC_NUMERIC)
# define LC_TIME_MASK       (1 << __LC_TIME)
# define LC_COLLATE_MASK    (1 << __LC_COLLATE)
# define LC_MONETARY_MASK   (1 << __LC_MONETARY)
# define LC_MESSAGES_MASK   (1 << __LC_MESSAGES)
# define LC_PAPER_MASK      (1 << __LC_PAPER)
# define LC_NAME_MASK       (1 << __LC_NAME)
# define LC_ADDRESS_MASK    (1 << __LC_ADDRESS)
# define LC_TELEPHONE_MASK  (1 << __LC_TELEPHONE)
# define LC_MEASUREMENT_MASK    (1 << __LC_MEASUREMENT)
# define LC_IDENTIFICATION_MASK (1 << __LC_IDENTIFICATION)
# define LC_ALL_MASK        (LC_CTYPE_MASK \
                 | LC_NUMERIC_MASK \
                 | LC_TIME_MASK \
                 | LC_COLLATE_MASK \
                 | LC_MONETARY_MASK \
                 | LC_MESSAGES_MASK \
                 | LC_PAPER_MASK \
                 | LC_NAME_MASK \
                 | LC_ADDRESS_MASK \
                 | LC_TELEPHONE_MASK \
                 | LC_MEASUREMENT_MASK \
                 | LC_IDENTIFICATION_MASK \
                 )
extern __locale_t newlocale (int __category_mask, const char *__locale,__locale_t __base);
extern __locale_t uselocale (__locale_t __dataset);
extern void freelocale (__locale_t __dataset) ;
//libScreenShare fix end

#ifndef LOCALE_NOT_USED
#include <locale.h>
#ifndef XLOCALE_NOT_USED
//#include <xlocale.h> // because, on some systems, <locale.h> doesn't include <xlocale.h>; this makes sure that we get both
#endif
#endif


enum LocaleCategory { All, Numeric }; // define and implement more categories later, as needed

class Locale {
public:
  Locale(char const* newLocale, LocaleCategory category = All);
  virtual ~Locale();

private:
#ifndef LOCALE_NOT_USED
#ifndef XLOCALE_NOT_USED
  locale_t fLocale, fPrevLocale;
#else
  int fCategoryNum;
  char* fPrevLocale;
#endif
#endif
};

#endif

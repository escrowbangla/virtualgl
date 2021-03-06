/*
 * "$Id: Fl_Export.H,v 1.1 2007-09-01 23:40:01 dcommander Exp $"
 *
 * WIN32 DLL export definitions for the Fast Light Tool Kit (FLTK).
 *
 * Copyright 1998-2005 by Bill Spitzak and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301
 * USA.
 *
 * Please report all bugs and problems on the following page:
 *
 *     http://www.fltk.org/str.php
 */

#ifndef Fl_Export_H
#  define Fl_Export_H

/*
 * The following is only used when building DLLs under WIN32...
 */

#  if defined(FL_DLL) && (defined(_MSC_VER) || defined(__MWERKS__) || defined(__BORLANDC__) || __GNUC__ >= 3)
#    ifdef FL_LIBRARY
#      define FL_EXPORT	__declspec(dllexport)
#    else
#      define FL_EXPORT	__declspec(dllimport)
#    endif /* FL_LIBRARY */
#  else
#    define FL_EXPORT
#  endif /* FL_DLL */

#endif /* !Fl_Export_H */

/*
 * End of "$Id: Fl_Export.H,v 1.1 2007-09-01 23:40:01 dcommander Exp $".
 */

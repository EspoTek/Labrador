// Copyright (C) 2018, 2019 Christopher Paul Esposito
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef LIBRADOR_GLOBAL_H
#define LIBRADOR_GLOBAL_H

#ifdef FORCE_COMPILATION_FOR_QT5
    #include <QtCore/qglobal.h>
#else
    #ifdef _WIN32 | _WIN64
        #define Q_DECL_EXPORT __declspec(dllexport)
        #define Q_DECL_IMPORT __declspec(dllimport)
    #else
        #define Q_DECL_EXPORT
        #define Q_DECL_IMPORT
    #endif
#endif

#if defined(LIBRADOR_LIBRARY)
#  define LIBRADORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBRADORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBRADOR_GLOBAL_H

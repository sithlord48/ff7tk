//    SPDX-FileCopyrightText: 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QtCore/qglobal.h>
#include <QMetaType>
#ifdef _MSC_VER
#   define PACK(structure)          \
    __pragma(pack(push, 1))     \
    structure                   \
    __pragma(pack(pop))
#elif defined(__MINGW32__)
#define PACK(structure) structure __attribute__ ((gcc_struct, __packed__))
#else
#define PACK(structure) structure Q_PACKED
#endif
#include <ff7tkdata_export.h>
/*! \struct materia
 *  \brief materia format saved in materia list or on a character
 *
 * Total Size 4 Bytes 100% known!
 */
PACK(
struct FF7TKDATA_EXPORT materia{// sizeof 4
    quint8 id;      /**< materias id */
    quint8 ap[3];   /** Ap Storage is done as a 24bit int. */
});
Q_DECLARE_METATYPE(materia)

//    SPDX-FileCopyrightText: 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once
#include <QtCore/qglobal.h>
#include <ff7tkdata_export.h>

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

/*! \struct FF7CHOCOBO
 *  \brief a chocobo in save game
 *
 *  16 Bytes total size 15 known 1 Byte Unknown
 *  \todo Research The Personality byte
 *  \todo Research the pcount byte
 */
PACK(
struct FF7TKDATA_EXPORT FF7CHOCOBO {
    quint16 sprintspd = 0;      /**< [0x0000] Speed */
    quint16 maxsprintspd = 0;   /**< [0x0002] Max Speed*/
    quint16 speed = 0;          /**< [0x0004] Sprint speed*/
    quint16 maxspeed = 0;       /**< [0x0006] Max Sprint speed*/
    quint8 accel = 0;           /**< [0x0008] acceleration*/
    quint8 coop = 0;            /**< [0x0009] cooperation*/
    quint8 intelligence = 0;    /**< [0x000A] Intelligence*/
    quint8 personality = 0;     /**< [0x000B] personality Type - THIS NEED TO HAVE A RANGE FOUND!*/
    quint8 pcount = 0;          /**< [0x000C] P count ??*/
    quint8 raceswon = 0;        /**< [0x000D] Number of races won*/
    quint8 sex = 0;             /**< [0x000E] Sex (0=male,1=female)*/
    quint8 type = 0;            /**< [0x000F] Type (Yellow,Green,Blue,Black,Gold)*/
});

/****************************************************************************/
//    copyright 2009 - 2021  Jérôme Arzel <myst6re@gmail.com>               //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#pragma once

#include <QtCore>
#include <QRgb>
#include <ff7tkutils_export.h>

#define COEFF_COLOR    8.2258064516129032258064516129032 // 255/31

#define psColorAlphaBit(color) \
    ((color >> 15) & 1)
#define setPsColorAlphaBit(color, alpha) \
    ((color & 0x7FFF) | (alpha << 15))

class FF7TKUTILS_EXPORT PsColor
{
public:
    static quint16 toPsColor(const QRgb &color);
    static QRgb fromPsColor(quint16 color, bool useAlpha = false);
};

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
#include <PsColor.h>

quint16 PsColor::toPsColor(const QRgb &color)
{
    return quint16((qRound(qRed(color) / COEFF_COLOR) & 31) | ((qRound(qGreen(color) / COEFF_COLOR) & 31) << 5)
           | ((qRound(qBlue(color) / COEFF_COLOR) & 31) << 10) | ((qAlpha(color)==255) << 15));
}

QRgb PsColor::fromPsColor(quint16 color, bool useAlpha)
{
    quint8 r = color & 31,
           g = (color >> 5) & 31,
           b = (color >> 10) & 31;

    return qRgba((r << 3) + (r >> 2), (g << 3) + (g >> 2), (b << 3) + (b >> 2), color == 0 && useAlpha ? 0 : 255);
}

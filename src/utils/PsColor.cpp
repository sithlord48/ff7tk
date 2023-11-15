//    SPDX-FileCopyrightText: 2009 - 2021 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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

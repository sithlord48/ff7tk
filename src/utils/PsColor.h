//    SPDX-FileCopyrightText: 2009 - 2021 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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

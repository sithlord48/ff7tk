//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QtCore>
#include <ff7tkformats_export.h>

class FF7TKFORMATS_EXPORT Akao
{
public:
    Akao();
private:
    quint16 _musicID, _length, _reverbMode;
    QMap<quint8, QByteArray> _data;
};

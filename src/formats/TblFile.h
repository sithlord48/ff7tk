//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QtCore>
#include <ff7tkformats_export.h>

struct FF7TKFORMATS_EXPORT WorldToField
{
    qint16 x;
    qint16 y;
    qint16 z;
    quint16 fieldId;
    quint8 dir;
    quint8 _pad;
};

struct FF7TKFORMATS_EXPORT TblFileEntry
{
    WorldToField wm2Field[2]; // 0= default, 1= alternate
};

class FF7TKFORMATS_EXPORT TblFile
{
public:
    TblFile();
    bool open(const QByteArray &data);
    QByteArray save() const;
    QString toString() const;
private:
    QList<TblFileEntry> _entries;
};

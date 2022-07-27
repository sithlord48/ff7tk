/****************************************************************************/
//    copyright 2009 - 2022  Arzel Jérôme <myst6re@gmail.com>               //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
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

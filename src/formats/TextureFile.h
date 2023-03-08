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

#include <QImage>
#include <ff7tkformats_export.h>

class FF7TKFORMATS_EXPORT TextureFile
{
public:
    TextureFile();
    explicit TextureFile(const QImage &image);
    TextureFile(const QImage &image, const QList<QList<QRgb> > &colorTables);
    bool isValid() const;
    void clear();
    const QImage &image() const;
    QImage *imagePtr();
    bool isPaletted() const;
    const QList< QList<QRgb> > &colorTables() const;
    qsizetype currentColorTable() const;
    QList<QRgb> colorTable(qsizetype id) const;
    void setCurrentColorTable(qsizetype id);
    void setColorTable(qsizetype id, const QList<QRgb> &colorTable);
    qsizetype colorTableCount() const;
    void debug() const;
protected:
    QImage _image;
    QList< QList<QRgb> > _colorTables;
    qsizetype _currentColorTable;
};

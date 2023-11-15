//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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

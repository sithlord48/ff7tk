//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later
#pragma once

#include <QImage>
#include <TextureFile>
#include <ff7tkformats_export.h>

class FF7TKFORMATS_EXPORT TimFile : public TextureFile
{
public:
    TimFile() : TextureFile(), bpp(0), palX(0), palY(0), palW(0), palH(0), imgX(0), imgY(0) {}
    explicit TimFile(const QByteArray &data);
    TimFile(const TextureFile &texture, quint8 bpp, quint16 palX, quint16 palY, quint16 palW, quint16 palH, quint16 imgX, quint16 imgY);
    bool open(const QByteArray &data);
    bool save(QByteArray &data) const;
private:
    quint8 bpp;
    quint32 sizeImgSection;
    quint16 palX, palY;
    quint16 palW, palH;
    quint16 imgX, imgY;
    QList<QBitArray> _alphaBits;
};

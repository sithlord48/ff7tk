//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QImage>
#include <TextureFile>
#include <ff7tkformats_export.h>

struct FF7TKFORMATS_EXPORT TexStruct {
    // Header
    quint32 version; // 1=FF7 | 2=FF8
    quint32 unknown1; // 0
    quint32 hasColorKey;
    quint32 unknown2; // 0
    quint32 unknown3; // 7
    quint32 minBitsPerColor;
    quint32 maxBitsPerColor;
    quint32 minAlphaBits;
    quint32 maxAlphaBits;
    quint32 minBitsPerPixel;
    quint32 maxBitsPerPixel;
    quint32 unknown4; // 0
    quint32 nbPalettes;
    quint32 nbColorsPerPalette1;
    quint32 bitDepth;
    quint32 imageWidth;
    quint32 imageHeight;
    quint32 pitch; // 0
    quint32 unknown5; // 0
    quint32 hasPal;
    quint32 bitsPerIndex;
    quint32 indexedTo8bit;
    quint32 paletteSize;
    quint32 nbColorsPerPalette2;// may be 0 sometimes
    quint32 runtimeData1;
    quint32 bitsPerPixel;
    quint32 bytesPerPixel;
    // Pixel format
    quint32 nbRedBits1;
    quint32 nbGreenBits1;
    quint32 nbBlueBits1;
    quint32 nbAlphaBits1;
    quint32 redBitmask;
    quint32 greenBitmask;
    quint32 blueBitmask;
    quint32 alphaBitmask;
    quint32 redShift;
    quint32 greenShift;
    quint32 blueShift;
    quint32 alphaShift;
    quint32 nbRedBits2;// Always 8 - Unused
    quint32 nbGreenBits2;// Always 8 - Unused
    quint32 nbBlueBits2;// Always 8 - Unused
    quint32 nbAlphaBits2;// Always 8 - Unused
    quint32 redMax;
    quint32 greenMax;
    quint32 blueMax;
    quint32 alphaMax;
    // /Pixel format
    quint32 hasColorKeyArray;
    quint32 runtimeData2;
    quint32 referenceAlpha;
    quint32 runtimeData3;
    quint32 unknown6;
    quint32 paletteIndex;
    quint32 runtimeData4;
    quint32 runtimeData5;
    quint32 unknown7;
    quint32 unknown8;
    quint32 unknown9;
    quint32 unknown10;
    quint32 unknown11; // only on ff8!
};

class FF7TKFORMATS_EXPORT TexFile : public TextureFile
{
public:
    enum Version {
        None, FF7, FF8
    };

    TexFile() : TextureFile() {}
    explicit TexFile(const QByteArray &data);
    TexFile(const TextureFile &textureFile, const TexStruct &header,
            const QList<quint8> &colorKeyArray = QList<quint8>());
    ~TexFile() {}
    bool open(const QByteArray &data);
    bool save(QByteArray &data);
    TexFile scaled(const QSize &size) const;
    void setVersion(Version version);
    void debug();
private:
    void updateHeader();
    TexStruct header;
    QList<quint8> colorKeyArray;
};

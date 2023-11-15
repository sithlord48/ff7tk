//    SPDX-FileCopyrightText: 2012 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later
/***************************************************************
    4/6/1989 Haruhiko Okumura
    Use, distribute, and modify this program freely.
    Please send me your improved versions.
        PC-VAN      SCIENCE
        NIFTY-Serve PAF01022
        CompuServe  74050,1022
**************************************************************/
#pragma once

#include <QtCore>
#include <ff7tkutils_export.h>

class FF7TKUTILS_EXPORT LZS
{
public:
    // Theses functions are limited to "small" data sizes
    static const QByteArray &decompress(const QByteArray &data, int max);
    static const QByteArray &decompress(const char *data, int fileSize, int max);
    static const QByteArray &decompressAll(const QByteArray &data);
    static const QByteArray &decompressAll(const char *data, int fileSize);
    static const QByteArray &decompressAllWithHeader(const QByteArray &data);
    static const QByteArray &decompressAllWithHeader(const char *data, int size);
    static const QByteArray &compress(const QByteArray &fileData);
    static const QByteArray &compress(const char *data, int sizeData);
    static const QByteArray &compressWithHeader(const QByteArray &fileData);
    static const QByteArray &compressWithHeader(const char *data, int sizeData);
    // To reset the cache
    static void clear();
private:
    static void InsertNode(qint32 r);
    static void DeleteNode(qint32 p);
    static qint32 match_length; // of longest match. These are set by the InsertNode() procedure.
    static qint32 match_position;
    static qint32 lson[4097]; // left & right children & parents -- These constitute binary search trees.
    static qint32 rson[4353];
    static qint32 dad[4097];
    static unsigned char text_buf[4113]; // ring buffer of size 4096, with extra 17 bytes to facilitate string comparison
    static QByteArray result;
};

//    SPDX-FileCopyrightText: 2012 - 2021 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QtCore>
#include <ff7tkutils_export.h>

class FF7TKUTILS_EXPORT GZIP
{
public:
    enum Strategy {
        StrategyDefault,
        StrategyFiltered,
        StrategyHuffmanOnly,
        StrategyRle,
        StrategyFixed
    };

    static QByteArray decompress(const QByteArray &data, int decSize, Strategy strategy = StrategyDefault);
    static QByteArray compress(const QByteArray &ungzip, int level = -1, Strategy strategy = StrategyDefault);
    static QByteArray decompress(const char *data, int size, int decSize, Strategy strategy = StrategyDefault);
    static QByteArray compress(const char *ungzip, int size, int level = -1, Strategy strategy = StrategyDefault);
    static QByteArray decompress(const QString &path, int decSize, Strategy strategy = StrategyDefault);
    static QByteArray decompressNoHeader(const char *data, int size);
    static QByteArray compressNoHeader(const char *data, int size, int level = -1);
    static ulong crc(const char *data, int size);
private:
    static char strategyToChar(Strategy strategy);
    static QString gzMode(const char *mode, int level = -1, Strategy strategy = StrategyDefault);
};

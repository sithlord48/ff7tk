/****************************************************************************/
//    copyright 2012 - 2021  Jérôme Arzel <myst6re@gmail.com>               //
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
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#pragma once

#include <QtCore>
#include "ff7tkutils_export.h"

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

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

#include <GZIP.h>
#include <ff7tkutils_export.h>

#define GZIPPS_HEADER_SIZE      8

class FF7TKUTILS_EXPORT GZIPPS
{
public:
    inline static QByteArray decompress(const QByteArray &data)
    {
        return decompress(data.constData(), data.size());
    }
    inline static QByteArray compress(const QByteArray &ungzip, const QByteArray &header, int level = -1)
    {
        return compress(ungzip.constData(), ungzip.size(), header, level);
    }
    inline static QByteArray compress(const QByteArray &ungzip, quint32 header, int level = -1)
    {
        return compress(ungzip.constData(), ungzip.size(), header, level);
    }
    static QByteArray decompress(const char *data, int size);
    static QByteArray compress(const char *ungzip, int size, const QByteArray &header, int level = -1);
    inline static QByteArray compress(const char *ungzip, int size, quint32 header, int level = -1)
    {
        return compress(ungzip, size, QByteArray((char *)&header, 4), level);
    }
};

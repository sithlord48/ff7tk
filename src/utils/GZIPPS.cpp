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
#include <GZIPPS.h>

QByteArray GZIPPS::decompress(const char *data, int size)
{
    if (size <= GZIPPS_HEADER_SIZE) {
        return QByteArray();
    }

    quint32 decSize;
    memcpy(&decSize, data, 4);
    return GZIP::decompress(data + GZIPPS_HEADER_SIZE, size - GZIPPS_HEADER_SIZE, decSize);
}

QByteArray GZIPPS::compress(const char *ungzip, int size, const QByteArray &header, int level)
{
    Q_ASSERT(header.size() == 4);

    QByteArray ret;
    ret.append((char *)&size, 4); // = decSize
    ret.append(header);
    return ret.append(GZIP::compress(ungzip, size, level));
}

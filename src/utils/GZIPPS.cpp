//    SPDX-FileCopyrightText: 2012 - 2021 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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

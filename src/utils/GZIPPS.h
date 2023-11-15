//    SPDX-FileCopyrightText: 2012 - 2021 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <GZIP>
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

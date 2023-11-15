//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QtCore>
#include <ff7tkutils_export.h>

class FF7TKUTILS_EXPORT IO
{
public:
    explicit IO(QIODevice *device);
    virtual ~IO();
    inline void setDevice(QIODevice *device) { _device = device; }
    inline QIODevice *device() const { return _device; }
    bool canRead() const;
    bool canWrite() const;
private:
    QIODevice *_device;
};

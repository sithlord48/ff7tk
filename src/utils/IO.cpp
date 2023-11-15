//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <IO.h>

IO::IO(QIODevice *device)
    : _device(device)
{
}

IO::~IO()
{
}

bool IO::canRead() const
{
    if (!_device)
        return false;
    if (!_device->isOpen())
        return _device->open(QIODevice::ReadOnly);
    return _device->isReadable();
}

bool IO::canWrite() const
{
    if (!_device)
        return false;
    if (!_device->isOpen())
        return _device->open(QIODevice::WriteOnly);
    return _device->isWritable();
}

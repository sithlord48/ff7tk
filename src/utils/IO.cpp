/****************************************************************************/
//    copyright 2009 - 2022  Arzel Jérôme <myst6re@gmail.com>               //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
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

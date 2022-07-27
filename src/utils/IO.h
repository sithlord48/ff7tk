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

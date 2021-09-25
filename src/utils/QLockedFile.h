/****************************************************************************/
//    copyright 2009 - 2021  Jérôme Arzel <myst6re@gmail.com>               //
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
#ifdef Q_OS_WIN
#include <windows.h>
#include <winbase.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#endif
#include "ff7tkutils_export.h"
class FF7TKUTILS_EXPORT QLockedFile : public QFile
{
    Q_OBJECT
public:
    QLockedFile();
    explicit QLockedFile(const QString &name);
    explicit QLockedFile(QObject *parent);
    QLockedFile(const QString &name, QObject *parent);
    virtual ~QLockedFile();
    virtual void close();
    virtual bool open(OpenMode mode);
signals:

public slots:
private:
#ifdef Q_OS_WIN
    HANDLE handle;
#endif
};

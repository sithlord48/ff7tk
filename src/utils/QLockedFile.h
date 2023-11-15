//    SPDX-FileCopyrightText: 2009 - 2021 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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
#include <ff7tkutils_export.h>

class FF7TKUTILS_EXPORT QLockedFile : public QFile
{
    Q_OBJECT
public:
    QLockedFile();
    explicit QLockedFile(const QString &name);
    explicit QLockedFile(QObject *parent);
    QLockedFile(const QString &name, QObject *parent);
    ~QLockedFile();
    void close();
    bool open(OpenMode mode);
signals:

public slots:
private:
#ifdef Q_OS_WIN
    HANDLE handle;
#endif
};

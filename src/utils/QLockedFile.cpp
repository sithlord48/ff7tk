//    SPDX-FileCopyrightText: 2009 - 2021 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <QLockedFile.h>

QLockedFile::QLockedFile()
{
}

QLockedFile::QLockedFile(const QString &name) :
    QFile(name)
{
}

QLockedFile::QLockedFile(QObject *parent) :
    QFile(parent)
{
}

QLockedFile::QLockedFile(const QString &name, QObject *parent) :
    QFile(name, parent)
{
}

QLockedFile::~QLockedFile()
{
    if (isOpen())
        close();
}

void QLockedFile::close()
{
    // Unlock file
#ifdef Q_OS_WIN
    CloseHandle(handle);
#else
    ::flock(handle(), LOCK_UN);
#endif
    QFile::close();
}

bool QLockedFile::open(OpenMode mode)
{
    if (!mode.testFlag(QIODevice::ReadOnly)) {
        qWarning() << "QLockedFile::open must be opened in ReadOnly mode";
        return false;
    }

    // Lock file
#ifdef Q_OS_WIN
    handle = CreateFileA(QDir::toNativeSeparators(fileName()).toLatin1().data(),
                         GENERIC_READ,
                         FILE_SHARE_READ,
                         nullptr,
                         OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL,
                         nullptr);
    if (handle == INVALID_HANDLE_VALUE) {
        qWarning() << "QLockedFile::open error lock";
        return false;
    }

    return QFile::open(mode);
#else
    bool isOpen = QFile::open(mode);

    if (isOpen && ::flock(handle(), LOCK_SH) < 0) {
        qWarning() << "QLockedFile::open error flock";
        return false;
    }

    return isOpen;
#endif
}

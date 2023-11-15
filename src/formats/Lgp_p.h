//    SPDX-FileCopyrightText: 2009 - 2021 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-FileCopyrightText: 2019 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later
/*
 * This file may contains some code (especially the conflict part)
 * inspired from LGP/UnLGP tool written by Aali.
 * http://forums.qhimm.com/index.php?topic=8641.0
*/
#pragma once

#include <QIODevice>
#include <QString>
#include <QMultiHash>

#include <ff7tkformats_export.h>

#define LGP_COMPANY_NAME_SIZE    12
#define LGP_PRODUCT_NAME_SIZE    14

#define LOOKUP_VALUE_MAX 30
#define LOOKUP_TABLE_ENTRIES LOOKUP_VALUE_MAX * LOOKUP_VALUE_MAX

#define MAX_CONFLICTS 4096

#ifdef _MSC_VER
#   define PACK(structure)      \
        __pragma(pack(push, 1)) \
        structure               \
        __pragma(pack(pop))
#else
#   define PACK(structure) structure Q_PACKED
#endif

PACK(
struct FF7TKFORMATS_EXPORT LgpLookupTableEntry {
    quint16 tocOffset;
    quint16 fileCount;
});

struct FF7TKFORMATS_EXPORT LgpConflictEntry {
    LgpConflictEntry() : fileDir(QString()), tocIndex(0) {}
    LgpConflictEntry(const QString &fileDir, quint16 tocIndex = 0) :
        fileDir(fileDir), tocIndex(tocIndex) {}
    QString fileDir;
    quint16 tocIndex;
};

struct FF7TKFORMATS_EXPORT LgpTocEntry {
    LgpTocEntry() : conflict(0), tocIndex(0) {}
    LgpTocEntry(quint16 tocIndex, quint16 conflict = 0) :
        conflict(conflict), tocIndex(tocIndex) {}
    quint16 conflict;
    quint16 tocIndex;
};

class FF7TKFORMATS_EXPORT LgpHeaderEntry
{
public:
    LgpHeaderEntry(const QString &fileName, quint32 filePosition);
    virtual ~LgpHeaderEntry();
    const QString &fileName() const;
    const QString &fileDir() const;
    QString filePath() const;
    quint32 filePosition() const;
    qint64 fileSize() const;
    void setFileName(const QString &fileName);
    void setFileDir(const QString &fileDir);
    void setFilePath(const QString &filePath);
    void setFilePosition(quint32 filePosition);
    void setFileSize(quint32 fileSize);
    QIODevice *file(QIODevice *lgp);
    QIODevice *modifiedFile(QIODevice *lgp);
    void setFile(QIODevice *io);
    void setModifiedFile(QIODevice *io);
private:
    QIODevice *createFile(QIODevice *lgp);
    QString _fileName;
    QString _fileDir;
    quint32 _filePosition;
    quint32 _fileSize;
    bool _hasFileSize;
    QIODevice *_io;
    QIODevice *_newIO;
};

class FF7TKFORMATS_EXPORT LgpIO : public QIODevice
{
public:
    LgpIO(QIODevice *lgp, const LgpHeaderEntry *header, QObject *parent = nullptr);
    bool open(OpenMode mode) override;
    qint64 size() const override;
    bool canReadLine() const override;
protected:
    qint64 readData(char *data, qint64 maxSize) override;
    qint64 writeData(const char *data, qint64 maxSize) override;
private:
    QIODevice *_lgp;
    const LgpHeaderEntry *_header;
};

class LgpIterator;

class FF7TKFORMATS_EXPORT LgpToc
{
public:
    LgpToc();
    LgpToc(const LgpToc &other);
    virtual ~LgpToc();
    bool addEntry(LgpHeaderEntry *entry);
    LgpHeaderEntry *entry(const QString &filePath) const;
    QList<LgpHeaderEntry *> entries(quint16 id) const;
    const QMultiHash<quint16, LgpHeaderEntry *> &table() const;
    bool hasEntries(quint16 id) const;
    bool removeEntry(const QString &filePath);
    static bool isNameValid(const QString &filePath);
    bool renameEntry(const QString &filePath, const QString &newFilePath);
    bool contains(const QString &filePath) const;
    void clear();
    bool isEmpty() const;
    int size() const;
    QList<const LgpHeaderEntry *> filesSortedByPosition() const;
    LgpToc &operator=(const LgpToc &other);
private:
    LgpHeaderEntry *entry(const QString &filePath, quint16 id) const;
    static qint16 lookupValue(const QString &filePath);
    static qint8 lookupValue(const QChar &qc);
    QMultiHash<quint16, LgpHeaderEntry *> _header;
};

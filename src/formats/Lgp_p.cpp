//    SPDX-FileCopyrightText: 2009 - 2021 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-FileCopyrightText: 2019 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later
/*
 * This file may contains some code (especially the conflict part)
 * inspired from LGP/UnLGP tool written by Aali.
 * http://forums.qhimm.com/index.php?topic=8641.0
*/
#include <Lgp_p.h>
#include <QDebug>

LgpHeaderEntry::LgpHeaderEntry(const QString &fileName, quint32 filePosition) :
    _fileName(fileName), _filePosition(filePosition),
    _hasFileSize(false), _io(nullptr), _newIO(nullptr)
{
}

LgpHeaderEntry::~LgpHeaderEntry()
{
    if (_io != nullptr) {
        _io->deleteLater();
    }
    if (_newIO != nullptr) {
        _newIO->deleteLater();
    }
}

const QString &LgpHeaderEntry::fileName() const
{
    return _fileName;
}

const QString &LgpHeaderEntry::fileDir() const
{
    return _fileDir;
}

QString LgpHeaderEntry::filePath() const
{
    return _fileDir.isEmpty()
           ? _fileName
           : _fileDir + '/' + _fileName;
}

quint32 LgpHeaderEntry::filePosition() const
{
    return _filePosition;
}

qint64 LgpHeaderEntry::fileSize() const
{
    if (_hasFileSize) {
        return _fileSize;
    }
    return -1;
}

void LgpHeaderEntry::setFileName(const QString &fileName)
{
    if (fileName.size() > 20) {
        _fileName = fileName.left(20);
    } else {
        _fileName = fileName;
    }
}

void LgpHeaderEntry::setFileDir(const QString &fileDir)
{
    if (fileDir.size() > 128) {
        _fileDir = fileDir.left(128);
    } else {
        _fileDir = fileDir;
    }
}

void LgpHeaderEntry::setFilePath(const QString &filePath)
{
    int index = filePath.lastIndexOf('/');

    if (index < 0) {
        setFileName(filePath);
    } else {
        setFileDir(filePath.left(index));
        setFileName(filePath.mid(index + 1));
    }
}

void LgpHeaderEntry::setFilePosition(quint32 filePosition)
{
    _filePosition = filePosition;
}

void LgpHeaderEntry::setFileSize(quint32 fileSize)
{
    _fileSize = fileSize;
    _hasFileSize = true;
}

QIODevice *LgpHeaderEntry::file(QIODevice *lgp)
{
    if (_io) {
        _io->close();
        return _io;
    } else {
        return createFile(lgp);
    }
}

QIODevice *LgpHeaderEntry::modifiedFile(QIODevice *lgp)
{
    if (_newIO) {
        _newIO->close();
        return _newIO;
    } else {
        return file(lgp);
    }
}

void LgpHeaderEntry::setFile(QIODevice *io)
{
    _io = io;
}

void LgpHeaderEntry::setModifiedFile(QIODevice *io)
{
    _newIO = io;
}

QIODevice *LgpHeaderEntry::createFile(QIODevice *lgp)
{
    if (!lgp->seek(filePosition())) {
        return nullptr;
    }
    QByteArray name = lgp->read(20);
    if (name.size() != 20) {
        return nullptr;
    }
    QString nameStr = QString::fromLatin1(name.constData(), qstrnlen(name.constData(), 20));
    if (nameStr.compare(fileName(), Qt::CaseInsensitive) != 0) {
        qWarning() << "different name";
        return nullptr;
    }

    quint32 size;
    if (lgp->read(reinterpret_cast<char *>(&size), 4) != 4) {
        return nullptr;
    }

    setFileSize(size);
    setFileName(nameStr);
    QIODevice *io = new LgpIO(lgp, this);
    setFile(io);
    return io;
}

LgpIO::LgpIO(QIODevice *lgp, const LgpHeaderEntry *header, QObject *parent) :
    QIODevice(parent), _lgp(lgp), _header(header)
{
}

bool LgpIO::open(OpenMode mode)
{
    if (mode.testFlag(QIODevice::Append)
            || mode.testFlag(QIODevice::Truncate)) {
        return false;
    }
    return QIODevice::open(mode);
}

qint64 LgpIO::size() const
{
    return _header->fileSize();
}

qint64 LgpIO::readData(char *data, qint64 maxSize)
{
    if (_lgp->seek(_header->filePosition() + 24 + pos())) {
        qint64 size = this->size();
        if (size < 0) {
            return -1;
        }
        return _lgp->read(data, qMin(maxSize, size - pos()));
    }
    return -1;
}

/*!
 * You cannot write more than the initial file size.
 */
qint64 LgpIO::writeData(const char *data, qint64 maxSize)
{
    if (_lgp->seek(_header->filePosition() + 24 + pos())) {
        qint64 size = this->size();
        if (size < 0) {
            return -1;
        }
        return _lgp->write(data, qMin(maxSize, size - pos()));
    }
    return -1;
}

bool LgpIO::canReadLine() const
{
    return pos() < size();
}

LgpToc::LgpToc()
{
}

LgpToc::LgpToc(const LgpToc &other)
{
    for (LgpHeaderEntry *headerEntry : other.table()) {
        addEntry(new LgpHeaderEntry(*headerEntry));
    }
}

LgpToc::~LgpToc()
{
    qDeleteAll(_header);
}

bool LgpToc::addEntry(LgpHeaderEntry *entry)
{
    qint16 v = lookupValue(entry->fileName());
    if (v < 0) {
        return false;
    }

    if (contains(entry->fileName())) {
        return false;
    }

    _header.insert(quint16(v), entry);

    return true;
}

LgpHeaderEntry *LgpToc::entry(const QString &filePath) const
{
    qint16 v = lookupValue(filePath);
    if (v < 0) {
        qDebug() << "LgpToc::entry invalid lookup" << filePath;
        return nullptr; // invalid file name
    }
    
    return entry(filePath, quint16(v));
}

QList<LgpHeaderEntry *> LgpToc::entries(quint16 id) const
{
    return _header.values(id);
}

const QMultiHash<quint16, LgpHeaderEntry *> &LgpToc::table() const
{
    return _header;
}

bool LgpToc::hasEntries(quint16 id) const
{
    return _header.contains(id);
}

LgpHeaderEntry *LgpToc::entry(const QString &filePath, quint16 id) const
{
    for (LgpHeaderEntry *entry : entries(id)) {
        if (filePath.compare(entry->filePath(), Qt::CaseInsensitive) == 0) {
            return entry;
        }
    }

    return nullptr; // file not found
}

bool LgpToc::removeEntry(const QString &filePath)
{
    qint16 v = lookupValue(filePath);
    if (v < 0) {
        return false; // invalid file name
    }

    LgpHeaderEntry *e = entry(filePath);
    if (e == nullptr) {
        return false; // file not found
    }
    
    bool ok = _header.remove(quint16(v), e) > 0;

    delete e;

    return ok;
}

bool LgpToc::isNameValid(const QString &filePath)
{
    return lookupValue(filePath) >= 0;
}

bool LgpToc::renameEntry(const QString &filePath, const QString &newFilePath)
{
    // Get file

    qint16 v = lookupValue(filePath);
    if (v < 0) {
        qWarning() << "LgpToc::renameEntry invalid filename" << filePath;
        return false; // invalid file name
    }
    
    LgpHeaderEntry *e = entry(filePath, quint16(v));
    if (e == nullptr) {
        qWarning() << "LgpToc::renameEntry file not found" << filePath;
        return false; // file not found
    }

    // Get new file

    qint16 newV = lookupValue(newFilePath);
    if (newV < 0) {
        qWarning() << "LgpToc::renameEntry invalid new filename" << newFilePath;
        return false; // invalid file name
    }

    if (entry(newFilePath, quint16(newV)) != nullptr) {
        qWarning() << "LgpToc::renameEntry new file exists" << newFilePath;
        return false; // file found
    }

    // Move file

    if (_header.remove(v, e) <= 0) {
        qWarning() << "LgpToc::renameEntry cannot remove entry";
        return false;
    }

    e->setFilePath(newFilePath);
    _header.insert(newV, e);

    return true;
}

bool LgpToc::contains(const QString &filePath) const
{
    return entry(filePath) != nullptr;
}

void LgpToc::clear()
{
    qDeleteAll(_header);

    _header.clear();
}

bool LgpToc::isEmpty() const
{
    return _header.isEmpty();
}

int LgpToc::size() const
{
    return _header.size();
}

QList<const LgpHeaderEntry *> LgpToc::filesSortedByPosition() const
{
    QMultiMap<quint32, const LgpHeaderEntry *> ret;

    for (const LgpHeaderEntry *entry : _header) {
        ret.insert(entry->filePosition(), entry);
    }

    return ret.values();
}

LgpToc &LgpToc::operator=(const LgpToc &other)
{
    if (this != &other) {
        clear();
        for (LgpHeaderEntry *headerEntry : other.table()) {
            addEntry(new LgpHeaderEntry(*headerEntry));
        }
    }

    return *this;
}

qint16 LgpToc::lookupValue(const QString &filePath)
{
    int index = filePath.lastIndexOf('/');

    if (index != -1) {
        index++;
    } else {
        index = 0;
    }

    if (filePath.size() < index + 2) {
        return -1;
    }

    qint16 ret = lookupValue(filePath.at(index)) * LOOKUP_VALUE_MAX;

    QChar secondChar = filePath.at(index + 1);

    if (secondChar != '.') {
        ret += lookupValue(secondChar) + 1;
    }

    return ret >= LOOKUP_TABLE_ENTRIES ? -1 : ret;
}

qint8 LgpToc::lookupValue(const QChar &qc)
{
    char c = qc.toLower().toLatin1();

    if (c >= '0' && c <= '9') {
        return qint8(c - '0'); // Returns 0 to 9
    }
    if (c == '_') {
        return 10;
    }
    if (c == '-') {
        return 11;
    }

    // Returns -97 to 158, only 0 ('a') to 25 ('z') and 26 ('{'), 27 ('|'), 28 ('}') and 29 ('~') are valid
    return qint8(c - 'a');
}

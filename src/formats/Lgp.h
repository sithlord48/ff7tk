//    SPDX-FileCopyrightText: 2009 - 2021 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-FileCopyrightText: 2019 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later
/*
 * This file may contains some code (especially the conflict part)
 * inspired from LGP/UnLGP tool written by Aali.
 * http://forums.qhimm.com/index.php?topic=8641.0
*/
#pragma once

#include <Archive>
#include <ff7tkformats_export.h>

class LgpHeaderEntry;
class LgpToc;
class Lgp;

class FF7TKFORMATS_EXPORT LgpIterator
{
    friend class Lgp;
public:
    explicit LgpIterator(const Lgp &lgp);
    bool hasNext() const;
    void next();
    void toBack();
    void toFront();
    QIODevice *file();
    QIODevice *modifiedFile();
    const QString &fileName() const;
    const QString &fileDir() const;
    QString filePath() const;
private:
    LgpIterator(LgpToc *toc, QFile *lgp);
    QMultiHashIterator<quint16, LgpHeaderEntry *> it;
    QFile *_lgp;
};

class FF7TKFORMATS_EXPORT Lgp : public Archive
{
    friend class LgpIterator;
public:
    enum LgpError {
        NoError,
        ReadError,
        WriteError,
        OpenError,
        OpenTempError,
        AbortError,
        RemoveError,
        RenameError,
        PositionError,
        ResizeError,
        PermissionsError,
        CopyError,
        InvalidError,
        FileNotFoundError
    };

    Lgp();
    explicit Lgp(const QString &name);
    explicit Lgp(QFile *device);
    virtual ~Lgp() override;
    void clear() override;
    QStringList fileList() const override;
    int fileCount() const override;
    LgpIterator iterator();
    bool fileExists(const QString &filePath) const override;
    QIODevice *file(const QString &filePath) override;
    QIODevice *modifiedFile(const QString &filePath) override;
    bool setFile(const QString &filePath, QIODevice *data) override;
    bool addFile(const QString &filePath, QIODevice *data) override;
    bool removeFile(const QString &filePath) override;
    bool isNameValid(const QString &filePath) const override;
    bool renameFile(const QString &filePath, const QString &newFilePath) override;
    const QString &companyName();
    void setCompanyName(const QString &companyName);
    const QString &productName();
    void setProductName(const QString &productName);
    bool pack(const QString &destination=QString(), ArchiveObserver *observer = nullptr) override;
    LgpError error() const;
    void unsetError();
private:
    Q_DISABLE_COPY(Lgp)
    bool openHeader() override;
    bool openCompanyName();
    bool openProductName();
    LgpHeaderEntry *headerEntry(const QString &filePath) const;
    void setError(LgpError error, const QString &errorString = QString());
    static QByteArray readAll(QIODevice *d, bool *ok);

    QString _companyName;
    LgpToc *_files;
    QString _productName;
    LgpError _error;

};

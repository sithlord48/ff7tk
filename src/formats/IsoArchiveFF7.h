//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <IsoArchive>
#include <ff7tkformats_export.h>

class FF7TKFORMATS_EXPORT IsoArchiveFF7 : public IsoArchive
{
public:
    enum Compression {
        None, LZS, GZIP
    };

    enum Country {
        NoCountry, Jp, Us, Uk, Fr, De, Es
    };

    explicit IsoArchiveFF7(const QString &name);
    virtual ~IsoArchiveFF7() override;

    bool open(QIODevice::OpenMode mode) override;
    const QByteArray &fileLzs(const QString &path, quint32 maxSize=0) const;
    const QByteArray &modifiedFileLzs(const QString &path, quint32 maxSize=0) const;
    Country country() const;
    IsoFile *exe() const;
    bool isDisc(int num) const;
    QByteArray windowBinData() const;
    IsoDirectory *fieldDirectory() const;
    IsoDirectory *initDirectory() const;
    bool isDemo() const;
    QMap<int, QString> maplist();
private:
    Q_DISABLE_COPY(IsoArchiveFF7)
    bool updateBin(IsoFile *isoBin, const QList<IsoFile *> &filesRefByBin, int startOffset = 0);
    IsoFile *updateFieldBin();
    IsoFile *updateWorldBin();
    IsoFile *updateYamadaBin();
    bool reorganizeModifiedFilesAfter(QMap<quint32, const IsoFile *> &writeToTheMain, QList<const IsoFile *> &writeToTheEnd) override;
    IsoFile *searchExe() const;
    Country searchCountry() const;
    QList<QIODevice *> _devicesToDelete;
    IsoFile *_exe;
    Country _country;
};

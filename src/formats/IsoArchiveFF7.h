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

//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QtCore>
#include <ff7tkutils_export.h>

class FF7TKUTILS_EXPORT PsfTags
{
public:
    PsfTags();
    explicit PsfTags(const QString &lib);
    bool open(const QString &config);
    QString save() const;
    PsfTags &setLengthS(quint32 seconds);
    inline PsfTags &setLib(const QString &lib) {return setCustom(QStringLiteral("_lib"), lib);}
    inline PsfTags &setAuthor(const QString &author) {return setCustom(QStringLiteral("psfby"), author);}
    inline PsfTags &setFade(int fade) {return setCustom(QStringLiteral("fade"), fade);}
    inline PsfTags &setVolume(int volume) {return setCustom(QStringLiteral("volume"), volume);}
    inline PsfTags &setTitle(const QString &title) {return setCustom(QStringLiteral("title"), title);}
    inline PsfTags &setArtist(const QString &artist) {return setCustom(QStringLiteral("artist"), artist);}
    inline PsfTags &setGame(const QString &game) {return setCustom(QStringLiteral("game"), game);}
    inline PsfTags &setGenre(const QString &genre) {return setCustom(QStringLiteral("genre"), genre);}
    inline PsfTags &setComment(const QString &comment) {return setCustom(QStringLiteral("comment"), comment);}
    inline PsfTags &setYear(int year) {return setCustom(QStringLiteral("year"), year);}
    inline PsfTags &setCopyright(const QString &copyright) {return setCustom(QStringLiteral("copyright"), copyright);}
    inline PsfTags &setReplayGainTrack(double gain_db, double peak) {return setReplayGain(QStringLiteral("track"), gain_db, peak);}
    inline PsfTags &setReplayGainAlbum(double gain_db, double peak) {return setReplayGain(QStringLiteral("album"), gain_db, peak);}
    inline PsfTags &setCustom(const QString &name, int value) {return setCustom(name, QString::number(value));}
    inline PsfTags &setCustom(const QString &name, const QString &value) {
        _tags.insert(name, value);
        return *this;
    }
private:
    PsfTags &setReplayGain(const QString &type, double gain_db, double peak);
    QMap<QString, QString> _tags;
};

class FF7TKUTILS_EXPORT PsfFile
{
public:
    PsfFile();
    PsfFile(const QByteArray &data, const PsfTags &tags);
    static PsfFile fromAkao(const QByteArray &akaoData, const PsfTags &tags);
    bool open(const QByteArray &data);
    QByteArray save() const;
    inline const QByteArray &data() const {
        return _data;
    }
    inline QByteArray &data() {
        return _data;
    }
    inline const QByteArray &special() const {
        return _special;
    }
    inline const PsfTags &tags() const {
        return _tags;
    }
    inline PsfTags &tags() {
        return _tags;
    }
    QByteArray akao() const;
private:
    QByteArray _special, _data;
    PsfTags _tags;
};

//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <FF7Text.h>

#if QT_VERSION < QT_VERSION_CHECK(6, 5, 0)
#include <QRegularExpressionMatch>
#endif

/*~~~~~~~~TEXT CLASS~~~~~~~~~*/
// the PC function is modified from Makou Reactor (thanks Myst6re)
FF7Text *FF7Text::get()
{
    static FF7Text m;
    return &m;
}

FF7Text::FF7Text(QObject *parent) :
    QObject(parent)
    , d(new FF7TextPrivate)
{
}

FF7Text::~FF7Text()
{
    delete d;
}

void FF7Text::setJapanese(bool japanese)
{
    if(japanese == get()->d->in_ja)
        return;
    get()->d->in_ja = japanese;
    Q_EMIT get()->languageChanged();
}

bool FF7Text::isJapanese()
{
    return get()->d->in_ja;
}

QString FF7Text::toPC(QByteArray text)
{
    QString str;
    for (quint16 i = 0 ; i < text.size() ; ++i) {
        quint8 index = quint8(text.at(i));
        if (index == 0xFF) {
            break;
        } else if (index == 0xFE) {
            if (i + 1 >= text.size())
                continue;
            ++i;
            switch (quint8(text.at(i))) {
                case 0xDD:
                    if (text.size() <= i + 1) {
                        break;
                    }
                    ++i;
                    str.append(QString("{PAUSE%1}").arg(quint8(text.at(i)), 3, 10, QChar('0')));
                    continue;
                case 0xE2:
                    if (i + 4 <= text.size() && quint8(text.at(i + 4)) == 0) {
                        quint8 bank = 0;
                        switch (quint8(text.at(i + 2))) {
                            case 0:     bank = 1;     break; // 1 & 2
                            case 1:     bank = 3;     break; // 3 & 4
                            case 2:     bank = 11;    break; // 11 & 12
                            case 3:     bank = 13;    break; // 13 & 14
                            case 4:     bank = 15;    break; // 7 & 15
                            default:    break; // Error Bank;
                        }
                        str.append(QString("{MEMORY:var[%2][%1];size=%3}")
                                        .arg(quint8(text.at(i + 1)))
                                        .arg(bank)
                                        .arg(quint8(text.at(i + 3))));
                        i += 4;
                    } else { // Skip the FEE2
                        i += 2;
                    }
                    continue;
                default:
                    str.append((get()->isJapanese() || quint8(text.at(i)) >= 0xD2) ? character(text.at(i), 6) : QString());
                    continue;
            }
        }

        if (!get()->isJapanese()) {
            str.append(character(text.at(i), 0));
        } else {
            switch (index) {
            case 0xFA:
                ++i;
                str.append(character(text.at(i), 2));
                break;
            case 0xFB:
                ++i;
                str.append(character(text.at(i), 3));
                break;
            case 0xFC:
                ++i;
                str.append(character(text.at(i), 4));
                break;
            case 0xFD:
                ++i;
                str.append(character(text.at(i), 5));
                break;
            case 0xFE: break; //FE is handled above.
            default:
                str.append(character(text.at(i), 1));
                break;
            }
        }
    }
    return str;
}

QByteArray FF7Text::toFF7(const QString &string)
{
    QByteArray ff7str;
    int c = 0;
    while (c < string.length()) {
        //Match Pause
        QRegularExpressionMatch match = get()->d->pauseEXP.match(string.mid(c, 10));
        if (match.hasMatch()) {
            int num = string.mid(c + 6, 3).toInt();
            ff7str.append("\xFE\xDD").append(num);
            c += 10;
            continue;
        }

        //Match Mem Command
        if (string.mid(c, 12).startsWith(QStringLiteral("{MEMORY:var["), Qt::CaseInsensitive)) {
            match = get()->d->memoryEXP.match(string.mid(c));
            if(match.hasMatch()) {
                quint8 bank;
                switch (match.captured(1).toInt()) {
                    case 3: case 4: bank = 1; break;
                    case 11: case 12: bank = 2; break;
                    case 13: case 14: bank = 3; break;
                    case 7: case 15: bank = 4; break;
                    default: bank = 0; break;
                }
                ff7str.append("\xFE\xE2")
                    .append(match.captured(2).toInt())
                    .append(bank)
                    .append(match.captured(3).toInt())
                    .append('\x00');
                c += match.capturedLength();
                continue;
            }
        }

        //Normal Characters
        int j = 1;
        bool isSpecial = false;
        QString comp = string.mid(c);
        for(auto & sChar : get()->d->specialChars) {
            if(comp.startsWith(sChar, Qt::CaseInsensitive)) {
                j = sChar.length();
                isSpecial = true;
                break;
            }
        }

        comp = string.mid(c, j);
        if (isSpecial)
            comp = comp.toUpper();

        if (!get()->d->in_ja) {
            for (int i = 0 ; i <= 0xFF ; ++i) {
                if (!comp.compare(character(quint8(i), 0))) {
                    ff7str.append(i);
                    break;
                }
                if (i >= 0xD2) {
                    if (!comp.compare(character(quint8(i), 6))) {
                        ff7str.append('\xFE')
                              .append(i);
                        break;
                    }
                }
            }
        } else {
            for (int table = 1 ; table < 7 ; ++table) {
                for (int i = 0 ; i <= 0xFF ; ++i) {
                    if (!comp.compare(character(quint8(i), quint8(table)))) {
                        switch (table) {
                            case 2: ff7str.append('\xFA'); break;
                            case 3: ff7str.append('\xFB'); break;
                            case 4: ff7str.append('\xFC'); break;
                            case 5: ff7str.append('\xFD'); break;
                            case 6: ff7str.append('\xFE'); break;
                            default: break;
                        }
                        ff7str.append(quint8(i));
                        break;
                    }
                }
            }
        }
        c += j;
    }
    return ff7str;
}

QString FF7Text::character(quint8 ord, quint8 table)
{
    switch (table) {
    case 1:
        return get()->d->jap.at(ord);
    case 2:
        if(ord > get()->d->jap_fa.count() -1)
            return QString();
        return get()->d->jap_fa.at(ord);
    case 3:
        if(ord > get()->d->jap_fb.count() -1)
            return QString();
        return get()->d->jap_fb.at(ord);
    case 4:
        if(ord > get()->d->jap_fc.count() -1)
            return QString();
        return get()->d->jap_fc.at(ord);
    case 5:
        if(ord > get()->d->jap_fd.count() -1)
            return QString();
        return get()->d->jap_fd.at(ord);
    case 6:
        if(ord > get()->d->jap_fe.count() -1)
            return QString();
        return get()->d->jap_fe.at(ord);
    default:
        return get()->d->eng.at(ord);
    }
}

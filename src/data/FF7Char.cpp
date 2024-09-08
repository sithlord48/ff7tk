//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <FF7Char.h>

#include <QIcon>
#include <QRandomGenerator>
#include <QStringList>

FF7Char *FF7Char::get()
{
    static FF7Char m;
    return &m;
}

FF7Char::FF7Char(QObject *parent) :
    QObject(parent)
    , d(new FF7CharPrivate)
{
}

FF7Char::~FF7Char()
{
    delete d;
}

const FF7Char::Character &FF7Char::character(int who)
{
    if (!validID(who))
        return FF7Char::get()->d->_emptyChar;
    return FF7Char::get()->d->_charData.at(who);
}

quint32 FF7Char::totalExpForLevel(int who, int level)
{
    if (!validID(who))
        return 0;
    level = std::clamp(level, 0, int(character(who)._charlvls.size()) - 1);
    return character(who)._charlvls.at(level);
}

quint32 FF7Char::tnlForLevel(int who, int level)
{
    if (!validID(who))
        return 0;
    level = std::clamp(level, 0, int(character(who)._charlvls.size()) - 1);
    return character(who)._chartnls.at(level);
}

quint8 FF7Char::id(int who)
{
    if (!validID(who))
        return FF7Char::Empty;
    return character(who)._id;
}

bool FF7Char::validID(int id)
{
    return !((id < 0) || (id > 11));
}

int FF7Char::numberOfWeapons(int who)
{
    if (!validID(who))
        return 0;
    return character(who)._num_weapons;
}

int FF7Char::weaponStartingId(int who)
{
    if (!validID(who))
        return 0;
    return character(who)._starting_weapon_id;
}

int FF7Char::weaponOffset(int who)
{
    if (!validID(who))
        return 0;
    return character(who)._weapon_offset;
}

QString FF7Char::defaultName(int who)
{
    if (!validID(who))
        return QString();
    return tr(FF7Char::get()->d->_charData.at(who)._def_name.toUtf8());
}

QImage FF7Char::image(int who)
{
    if (!validID(who))
        return QImage();
    return QImage(character(who)._avatarString);
}

QIcon FF7Char::icon(int who)
{
    if (!validID(who))
        return QIcon();
    return QIcon(pixmap(who));
}

QPixmap FF7Char::pixmap(int who)
{
    if (!validID(who))
        return QPixmap();
    return QPixmap(character(who)._avatarString);
}

QStringList FF7Char::limits(int who)
{
    if (!validID(who))
        return FF7Char::get()->d->_emptyChar._limits;
    QStringList translated_list;
    for (const QString &limit : std::as_const(FF7Char::get()->d->_charData.at(who)._limits)) {
        translated_list.append(tr(limit.toUtf8()));
    }
    return translated_list;
}
int FF7Char::limitBitConvert(int bit)
{
    bit = std::clamp(bit, 0, 7);
    return FF7Char::get()->d->_limitbitarray.at(bit);
}

QByteArray FF7Char::toByteArray(FF7CHAR ff7char)
{
    QByteArray temp;
    temp.setRawData(reinterpret_cast<char *>(&ff7char), 132);
    temp.detach();
    return temp;
}

FF7CHAR FF7Char::fromByteArray(const QByteArray &ba)
{
    if (ba.size() != 132)
        return FF7CHAR();
    FF7CHAR temp;
    memcpy(&temp, ba, 132);
    return temp;
}

int FF7Char::stat_grade(int who, int stat)
{
    if (!validID(who))
        return 0;
    return character(who)._stat_grade.at(stat);
}

int FF7Char::mp_base(int who, int lvl_bracket)
{
    if (!validID(who))
        return 0;
    return character(who)._mp_base.at(lvl_bracket);
}

int FF7Char::mp_gradent(int who, int lvl_bracket)
{
    if (!validID(who))
        return 0;
    return character(who)._mp_gradent.at(lvl_bracket);
}

int FF7Char::hp_base(int who, int lvl_bracket)
{
    if (!validID(who))
        return 0;
    return character(who)._hp_base.at(lvl_bracket);
}

int FF7Char::hp_gradent(int who, int lvl_bracket)
{
    if (!validID(who))
        return 0;
    return character(who)._hp_gradent.at(lvl_bracket);
}

int FF7Char::luck_base(int who, int lvl_bracket)
{
    if (!validID(who))
        return 0;
    return character(who)._luck_base.at(lvl_bracket);
}

int FF7Char::luck_gradent(int who, int lvl_bracket)
{
    if (!validID(who))
        return 0;
    return character(who)._luck_gradent.at(lvl_bracket);
}

int FF7Char::stat_base(int rank, int lvl_bracket)
{
    return FF7Char::get()->d->_stat_base.at(rank).at(lvl_bracket);
}

int FF7Char::stat_gradent(int rank, int lvl_bracket)
{
    return FF7Char::get()->d->_stat_gradent.at(rank).at(lvl_bracket);
}

int FF7Char::statGain(int who, int stat, int stat_amount, int current_lvl, int next_lvl)
{
    if (!validID(who))
        return 0;
    who = std::clamp(who, 0, 10);
    stat = std::clamp(stat, 0, 7);
    stat_amount = std::clamp(stat_amount, 1, 255); // the stat must be at least one
    current_lvl = std::clamp(current_lvl, 0, 99);
    next_lvl = std::clamp(next_lvl, 0, 99);
    int randomNumber = QRandomGenerator::system()->bounded(1,9);
    int gain = 0; //return this
    int diff = 0; //holds our diff
    //0:str; 1:vit; 2:mag; 3:spi; 4:dex; 5:luck; 6:hp; 7:mp
    int baseline_stat = 0; // holds our baseline_stat calculation.
    bool levelUp = (current_lvl < next_lvl);

    int lvl_bracket = 0;
    if (next_lvl >= 12 && next_lvl <= 21) {
        lvl_bracket = 1;
    } else if (next_lvl >= 22 && next_lvl <= 31) {
        lvl_bracket = 2;
    } else if (next_lvl >= 32 && next_lvl <= 41) {
        lvl_bracket = 3;
    } else if (next_lvl >= 42 && next_lvl <= 51) {
        lvl_bracket = 4;
    } else if (next_lvl >= 52 && next_lvl <= 61) {
        lvl_bracket = 5;
    } else if (next_lvl >= 62 && next_lvl <= 81) {
        lvl_bracket = 6;
    } else if (next_lvl >= 82 && next_lvl <= 99) {
        lvl_bracket = 7;
    }

    //Get the baseline
    if (stat < 5) {
        //calculating str,vit,mag,spi or dex
        int grade = stat_grade(who, stat);
        baseline_stat = stat_base(grade, lvl_bracket) + ((stat_gradent(grade, lvl_bracket) * next_lvl) / 100);
    } else if (stat == 5) {
        baseline_stat = luck_base(who, lvl_bracket) + ((luck_gradent(who, lvl_bracket)) / 100);
    } else if (stat == 6) {
        baseline_stat = hp_base(who, lvl_bracket) + (next_lvl - 1) * hp_gradent(who, lvl_bracket);
    } else if (stat == 7) {
        baseline_stat = mp_base(who, lvl_bracket) + ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10);
    }

    //now calc the diff, so we can send back a gain based on type
    if (stat < 6) {
        //str, vit,mag, spr,dex or luck all calculated the same
        diff = (levelUp) ? randomNumber + (baseline_stat - stat_amount) : randomNumber - baseline_stat + stat_amount;
        if (diff < 4) {
            gain = 0;
        } else if (diff < 7) {
            gain = 1;
        } else if (diff < 10) {
            gain = 2;
        } else {
            gain = 3;
        }
    } else if (stat == 6) {
        // Base HP Gain
        //Vegeta_Ss4 lv down mod
        if (levelUp) {
            diff = randomNumber + (100 * baseline_stat / stat_amount) - 100;   //is lv up
        } else if (baseline_stat != 0) {
            diff = randomNumber + (100 * stat_amount / baseline_stat) - 100;   //lv down
        }
        diff = std::clamp(diff, 0 , 11);
        gain = int(hp_gradent(who, lvl_bracket) * FF7Char::get()->d->_hp_diff_modifier.at(diff));
    } else if (stat == 7) {
        // Base MP Gain
        //Vegeta_Ss4 lv down mod
        if (levelUp) {
            diff = randomNumber + (100 * baseline_stat / stat_amount) - 100;   //is lv up
        } else if (baseline_stat != 0) {
            diff = randomNumber + (100 * stat_amount / baseline_stat) - 100;   //lv down
        }
        diff = std::clamp(diff, 0 , 11);
        gain = int(((next_lvl * mp_gradent(who, lvl_bracket) / 10) - ((next_lvl - 1) * mp_gradent(who, lvl_bracket) / 10)) * FF7Char::get()->d->_mp_diff_modifier.at(diff));
    }
    return gain;
}

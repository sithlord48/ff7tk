//    SPDX-FileCopyrightText: 2013 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <FF7Achievements.h>

#include <QFile>

bool FF7Achievements::openFile(const QString &fileName)
{
    if (fileName.isEmpty())
        return false;

    QFile data(fileName);
    if (!data.open(QIODevice::ReadOnly))
        return false;

    _achievements = data.readAll();
    data.close();
    return true;
}

bool FF7Achievements::saveFile(const QString &fileName)
{
    if (fileName.isEmpty())
        return false;

    QFile data(fileName);
    if (!data.open(QIODevice::WriteOnly))
        return false;

    data.seek(0);
    data.write(_achievements.data(), 8);
    data.close();
    return true;
}

bool FF7Achievements::achievementUnlocked(int bit)
{
    bit = std::clamp(bit, 28, 63);
    return (_achievements.at(bit / 8) & (1 << (7 - (bit % 8))));
}

void FF7Achievements::setAchievementUnlocked(int bit, bool unlocked)
{
    bit = std::clamp(bit, 28, 63);
    char temp = _achievements.at(bit / 8);
    if (unlocked)
        temp |= (1 << (7 - (bit % 8)));
    else
        temp &= ~(1 << (7 - (bit % 8)));
    _achievements[bit / 8] = temp;
}

QString FF7Achievements::name(int bit)
{
    QString temp;
    if (bit >=28 && bit <=63)
        temp = tr(_names.at(bit - 28).toUtf8());
    return temp;
}


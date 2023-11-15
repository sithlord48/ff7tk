//    SPDX-FileCopyrightText: 2013 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QObject>
#include <ff7tkdata_export.h>

/*!
 * \class FF7Achievements
 * \todo need more icons for the achievements.
 * \brief Work with achievements.dat
 *
 * Open Edit and Save achievements.dat found with the 2012 Square and 2013 Steam Releases of Final Fantasy VII
*/
class FF7TKDATA_EXPORT FF7Achievements : public QObject
{
    Q_OBJECT
public:
    FF7Achievements() = default;
    ~FF7Achievements() = default;
    /*! \brief Attempt to Open a file.
    * Open a file and replace data with its contents.
    * \param fileName file you want to open
    * \return True is successful
    * \sa saveFile()
    */
    Q_INVOKABLE bool openFile(const QString &fileName);

    /*! \brief Attempt to save a file.
     * Write data to a file
     * \param fileName file you want to open
     * \return TRUE if successful
     * \sa openFile()
    */
    Q_INVOKABLE bool saveFile(const QString &fileName);

    /*! \brief is Achievement @ bit unlocked?
     *   \param bit (28-63 are valid)
     *   \return TRUE for Achievement unlocked
     *  \sa setAchievementUnlocked()
    */
    Q_INVOKABLE bool achievementUnlocked(int bit);

    /*! \brief set Achievement @ bit to unlocked
        \param bit (28-63 are valid)
        \param unlocked  True for Achievement Unlocked
        \sa achievmentUnlocked()
    */
    Q_INVOKABLE void setAchievementUnlocked(int bit, bool unlocked);

    /*! \brief Translate name for Achievement bit
        \param bit (28-63 are valid)
        \return Translated QString of Achievement Name.
    */
    Q_INVOKABLE QString name(int bit);
private:
    QByteArray _achievements = QByteArray(8, '\x00');/**< Hold our Achievements.dat */
    inline static const QStringList _names{
        QT_TR_NOOP("Dice")
        , QT_TR_NOOP("Sled Fang")
        , QT_TR_NOOP("Greased Lightning")
        , QT_TR_NOOP("Beat Rush")
        , QT_TR_NOOP("Boost Jump")
        , QT_TR_NOOP("Healing Wind")
        , QT_TR_NOOP("Galian Beast")
        , QT_TR_NOOP("Big Shot")
        , QT_TR_NOOP("Braver")
        , QT_TR_NOOP("First Battle")
        , QT_TR_NOOP("Gold Chocobo")
        , QT_TR_NOOP("Battle Square")
        , QT_TR_NOOP("Materia Overlord")
        , QT_TR_NOOP("Yuffie")
        , QT_TR_NOOP("Vincent")
        , QT_TR_NOOP("Emerald Weapon")
        , QT_TR_NOOP("Ruby Weapon")
        , QT_TR_NOOP("Diamond Weapon")
        , QT_TR_NOOP("Ultimate Weapon")
        , QT_TR_NOOP("Bahamut Zero")
        , QT_TR_NOOP("Slots")
        , QT_TR_NOOP("Cosmo Memory")
        , QT_TR_NOOP("All Creation")
        , QT_TR_NOOP("Final Heaven")
        , QT_TR_NOOP("Highwind")
        , QT_TR_NOOP("Great Gospel")
        , QT_TR_NOOP("Chaos")
        , QT_TR_NOOP("Catastrophe")
        , QT_TR_NOOP("Omnislash")
        , QT_TR_NOOP("Knights of the Round")
        , QT_TR_NOOP("Top Level")
        , QT_TR_NOOP("Master of Gil")
        , QT_TR_NOOP("Master Materia")
        , QT_TR_NOOP("End of Game")
        , QT_TR_NOOP("End of Part II")
        , QT_TR_NOOP("End of Part I")
    };
};

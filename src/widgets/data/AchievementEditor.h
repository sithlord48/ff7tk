//    SPDX-FileCopyrightText: 2013 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QWidget>
#include <ff7tkwidgets_export.h>
#include <FF7Achievements>

class QListWidget;

/*! \class AchievementEditor
 *  \brief A QWidget editor for achievements.dat file from 2012 and 2013 release of Final Fantasy 7.
 *
 *  This widget uses FF7Achievements to do everything for us we only need to tell it what file to open and what file to save.
 *  The list will contain icons for each achievement so be sure to include achievements.qrc in your projects resources
 *  The end user only ever needs to see a list the rest should be set to signals/slots in the host application
 */
class FF7TKWIDGETS_EXPORT AchievementEditor : public QWidget
{
    Q_OBJECT
public:
    explicit AchievementEditor(QWidget *parent = nullptr); /**< \brief create a new AchievementEditor */
    ~AchievementEditor() = default;
public slots:
    /*! \brief open a file.
     *  \param fileName an achievements.dat file that you want to open
     *  \return TRUE if successful while attempting to open the file
     */
    bool openFile(const QString &fileName);

    /*! \brief saves a file.
     *  \param fileName an achievements.dat file that you want to save
     *  \return TRUE if successful while attempting to write the file
     */
    bool saveFile(const QString &fileName);
private slots:
    /*! \brief an item has been toggled
     *  \param index QModeIndex from where the change occurred
     */
    void itemToggled(const QModelIndex &index);
private:
    void initDisplay(); /**< \brief create this items widgets*/
    FF7Achievements achievements; /**< \brief data class for widget*/
    QListWidget *achievementList = nullptr; /**< \brief QListWidget that will contain the list of achievements.*/
};

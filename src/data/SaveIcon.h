//    SPDX-FileCopyrightText: 2010 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QObject>
#include <QPixmap>
#include <ff7tkdata_export.h>

/** \class SaveIcon
 *  \brief PSX icon data as a QPixmap
 */
class FF7TKDATA_EXPORT SaveIcon : public QObject
{
    Q_OBJECT
public:
    /** \brief create a new Save icon*/
    SaveIcon();

    /**
     * \brief create a new Save icon with data
     * \param data psx saveicon data
     * \param nbFrames number of frames icon has (1-3)
     * */
    SaveIcon(const QByteArray &data, quint8 nbFrames = 1);

    /**
     * \brief create a new Save icon with data
     * \param data psx saveicon one frame pre list item
    */
    SaveIcon(const QList<QByteArray> &data);

    /**
     * \brief fill SaveIcon with data
     * \param data psx saveicon data
     * \param nbFrames number of frames in icon (1-3)
    */
    void setAll(const QByteArray &data, quint8 nbFrames = 1);

    /** \brief fill SaveIcon with data
     * \param data psx saveicon one frame pre list item.
     */
    void setAll(const QList<QByteArray> &data);

    /*!
     * \brief Save the icon.
     * \return Icon Data as QByteArray
     */
    const QByteArray &save();

    /** \brief pixmap of your icon
     * \param chocobo_world_icon is this an icon for chocoboworld?
     * \return psx SaveIcon as A QPixmap
    */
    QPixmap icon(bool chocobo_world_icon = false);
signals:
    void nextIcon(QPixmap); /**< \brief Emit Signal: Time to update your QPixmap. connect to object your displaying on to tell it time for a new icon.*/
private:

    /** \brief Helper function for chocobo World Icons.
     * \return chocobo World Icon as A QPixmap
    */
    QPixmap chocoWorldIcon();

    /** \brief Helper function for psx SaveIcons
     * \return psx SaveIcon as A QPixmap
    */
    void nextFrame(); /**< \brief get get next icon if more then one frame */
    QPixmap psxIcon();
    QByteArray m_data; /**< \brief hold our icon data */
    quint8 m_nbFrames;/**< \brief number of frames */
    quint8 m_curFrame = 0; /**< \brief current Frame*/
    static QTimer m_timer; /**< \brief frame change timer.*/
};

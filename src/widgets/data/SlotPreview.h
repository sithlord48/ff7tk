//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QLabel>
#include <ff7tkwidgets_export.h>

class QHBoxLayout;
class QToolButton;
class QVBoxLayout;
class SaveIcon;

/** \class SlotPreview
 *  \brief Preview a Single Slot on a Psx memory card or FF7 Save file.
 *
 * Currently will display the "description" of FF7 Save or a preview of what psx save is in that slot. More games could be added by extending the modes
 */
class FF7TKWIDGETS_EXPORT SlotPreview : public QLabel
{
    Q_OBJECT
public:
    /** \enum MODE */
    enum MODE {
        EMPTY,/**< \brief Empty Slot*/
        PSXGAME, /**< \brief PSX Game or linked block */
        FF7SAVE /**< \brief FF7 Save in slot*/
    };
    Q_ENUM(MODE)
    SlotPreview(int index = 0, QWidget *parent = nullptr);
    int index(void);
    void setParty(QPixmap p1, QPixmap p2, QPixmap p3);
    void setName(QString);
    void setLevel(int);
    void setLocation(QString);
    void setGil(int);
    void setTime(int hour, int min);
    void setPsxIcon(const QByteArray &icon_data, quint8 frames = 1);
    void setPsxIcon(const QList<QByteArray> &icon_data);
    void setMode(SlotPreview::MODE mode);
    void setBackground(const QImage &image);
    void setPSXText(const QString &text);

signals:
    /**
     *  \brief Signal: User Clicked on preview, returns index of click
     */
    void clicked(int);

    /**
     *  \brief Signal: User Clicked on remove, returns index of click
    */
    void remove(int);
    [[ deprecated ("will be removed in ff7tk 2.0, Use SlotPreview::remove") ]]void btn_remove_clicked(int);

    /**
      *  \brief Signal: User Clicked on copy, returns index of click
     */
    void copy(int);
    [[ deprecated ("will be removed in ff7tk 2.0, Use SlotPreview::copy") ]]void btn_copy_clicked(int);

    /**
     *  \brief Signal: User Clicked on paste, returns index of click
    */
    void paste(int);
    [[ deprecated ("will be removed in ff7tk 2.0, Use SlotPreview::paste") ]]void btn_paste_clicked(int);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *);

private:
    QToolButton *btn_copy = nullptr;
    QToolButton *btn_paste = nullptr;
    QToolButton *btn_remove = nullptr;
    SaveIcon *m_psxIcon = nullptr;

    int m_index;
    int m_lineHeight;

    MODE m_mode = EMPTY;
    QString m_psxText = QString();
    QImage m_background = QImage();
    QPixmap m_p1 = QPixmap();
    QPixmap m_p2 = QPixmap();
    QPixmap m_p3 = QPixmap();
    QString m_name = QString();
    QString m_time = QString();
    QString m_level = QString();
    QString m_gil = QString();
    QString m_location = QString();
};

//    SPDX-FileCopyrightText: 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QWidget>
#include <ff7tkwidgets_export.h>

class QGroupBox;
class QHBoxLayout;
class QLabel;
class QListWidget;

class FF7TKWIDGETS_EXPORT ItemPreview : public QWidget
{
    Q_OBJECT
public:
    ItemPreview(QFlags<Qt::WindowType> WindowFlags = Qt::Widget, QWidget *parent = nullptr);
    int id(void);//return shown id.
public slots:
    void setItem(quint16);
    void setItem(int);
private:
    void setName(QString);
    void setDesc(QString);
    void setIcon(QPixmap);
    void elemental_info(int);
    void status_info(int);
    QHBoxLayout *makeMateriaPair(QLabel *slot1, QLabel *slot2 , QLabel *link);
    bool eventFilter(QObject *obj, QEvent *ev);
    QLabel *lbl_name = nullptr;
    QLabel *lbl_desc = nullptr;
    QLabel *lbl_icon = nullptr;
    QList<QLabel *> slotLabels;
    QList<QLabel *> slotLinks;
    QGroupBox *materia_slot_box = nullptr;
    QGroupBox *elemental_box = nullptr;
    QGroupBox *status_box = nullptr;
    QListWidget *elemental_effects = nullptr;
    QListWidget *status_effects = nullptr;
    int _id;
    QSize slotSize;
    QSize linkSize;
};

//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QWidget>
#include <ff7tkwidgets_export.h>

class QComboBox;
class QPushButton;
class QSpinBox;

class FF7TKWIDGETS_EXPORT ItemSelector : public QWidget
{
    Q_OBJECT
public:
    explicit ItemSelector(QWidget *parent = nullptr);
    int id();// current id
    int combo_item_width();//width of the item box.
    int combo_type_width();//width of the type box.
    int qty_width();//width of qty area.
    void setFixedHeight(int h);
    void setFixedWidth(int w);
    quint16 currentItem();
signals:
    void itemChanged(quint16);//return selected rawitem
public slots:
    void setCurrentItem(quint16 ff7item);
    void setCurrentItem(int id, int qty);
    void setMaximumQty(int maxQty);
    void setEditableItemCombo(bool editable);
    void setShowPlaceholderItems(bool showPlaceholderItems);
private slots:
    void setFilter(int type);
    void comboItem_changed(int index);
    void sb_qty_changed(int qty);
    void btn_remove_clicked();
private:
    void init_display();
    void init_connections();
    void init_data();
    int type_offset(int type);
    QComboBox *combo_type = nullptr;
    QComboBox *combo_item = nullptr;
    QSpinBox  *sb_qty = nullptr;
    QPushButton *btn_remove = nullptr;
    quint16 current_item = 0;
    bool _showPlaceholderItems;
};

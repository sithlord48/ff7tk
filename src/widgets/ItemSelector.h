/****************************************************************************/
//    copyright 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#pragma once

#include <QWidget>

#ifndef ff7tkwidgets_export_h
    #include <ff7tkwidgets_export.h>
#endif

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
signals:
    void itemChanged(quint16);//return selected rawitem
public slots:
    void setCurrentItem(quint16 ff7item);
    void setCurrentItem(int id, int qty);
    void setMaximumQty(int maxQty);
    void setEditableItemCombo(bool editable);
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
};

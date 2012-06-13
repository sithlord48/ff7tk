/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
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
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#ifndef EquipmentSelector_H
#define EquipmentSelector_H

//Besure to set FF7Item Path!
#include "static_data/FF7Item.h"
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QComboBox>

class EquipmentSelector : public QWidget
{
Q_OBJECT
  public:
    EquipmentSelector(QWidget *parent=0);

   public slots:
    void setMode(int);
    void ItemChange(int);
  private:
    void setItem(int);
    void setRange (int min ,int max);
 //   void setName(QString);
 //   void setIcon(QPixmap);
    void setDesc(QString);
    void elemental_info(int);
    void status_info(int);
    QComboBox *combo_selector;
    //QLabel *lbl_name;
    //QLabel *lbl_icon;
    QLabel *lbl_desc;

    QLabel *lbl_slot_1;
    QLabel *lbl_slot_2;
    QLabel *lbl_slot_3;
    QLabel *lbl_slot_4;
    QLabel *lbl_slot_5;
    QLabel *lbl_slot_6;
    QLabel *lbl_slot_7;
    QLabel *lbl_slot_8;
    QLabel *lbl_m_link_1;
    QLabel *lbl_m_link_2;
    QLabel *lbl_m_link_3;
    QLabel *lbl_m_link_4;

    QGroupBox *materia_slot_box;
    QGroupBox *elemental_box;
    QGroupBox *status_box;
    QListWidget *elemental_effects;
    QListWidget *status_effects;
    FF7Item data;
    int min;
    int max;
};
#endif//EquipmentSelector_H

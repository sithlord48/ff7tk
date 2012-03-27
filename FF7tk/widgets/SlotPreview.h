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
#ifndef SLOTPREVIEW_H
#define SLOTPREVIEW_H

#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QHBoxLayout>
//#include <QtGil/QVBoxLayout>

class SlotPreview : public QWidget
{
    Q_OBJECT
public:
    SlotPreview(QWidget *parent = 0);
    void setParty(QPixmap p1,QPixmap p2,QPixmap p3);
    void setParty(QString p1_style,QString p2_style,QString p3_style);
    void setName(QString);
    void set_Button_Label(QString);
    void setLevel(int);
    void setLocation(QString);
    void setGil(int);
    void setTime(int hour,int min);

private slots:
    //raw pix map for labels
    void set_Party1(QPixmap);
    void set_Party2(QPixmap);
    void set_Party3(QPixmap);

    void set_Party1(QString style);
    void set_Party2(QString style);
    void set_Party3(QString style);
private:
    QLabel *party1;
    QLabel *party2;
    QLabel *party3;
    QLabel *gil_amount;
    QLabel *name;
    QLabel *time_hour;
    QLabel *time_min;
    QLabel *level_amount;
    QLabel *location;
    QLabel *GIL_LABEL;
    QLabel *TIME_LABEL;
    QLabel *TIME_SEP;
    QLabel *LEVEL_LABEL;
    QPushButton *btn_select;
    QSpacerItem *spacer1;
};

#endif

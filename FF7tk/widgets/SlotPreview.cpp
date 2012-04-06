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
#include "SlotPreview.h"
//Slot Preview Widget is for display of the previewed save data.
SlotPreview::SlotPreview(QWidget *parent) :
    QWidget(parent)
{
party1 = new QLabel();
party2 = new QLabel();
party3 = new QLabel();
GIL_LABEL = new QLabel(tr("Gil:"),this,0);
gil_amount = new QLabel(this,0);
name = new QLabel(this,0);
TIME_LABEL = new QLabel(tr("Time:"),this,0);
TIME_SEP = new QLabel(":",this,0);
time_hour = new QLabel(this,0);
time_min = new QLabel(this,0);
LEVEL_LABEL = new QLabel(tr("Level"),this,0);
level_amount = new QLabel(this,0);
location = new QLabel(this,0);
btn_select = new QPushButton(this);

party1->setMinimumSize(96,100);
party1->setMaximumSize(100,100);
party1->setScaledContents(1);
party2->setMinimumSize(96,100);
party2->setMaximumSize(100,100);
party2->setScaledContents(1);
party3->setMinimumSize(96,100);
party3->setMaximumSize(100,100);
party3->setScaledContents(1);
name->setMinimumSize(48,31);
name->setMaximumSize(96,31);
name->setFrameStyle(1);
location->setMaximumHeight(24);

QHBoxLayout *partybox = new QHBoxLayout;
partybox->addWidget(party1);
partybox->addWidget(party2);
partybox->addWidget(party3);

party1->setScaledContents(1);
party2->setScaledContents(1);
party3->setScaledContents(1);

QHBoxLayout *timebox = new QHBoxLayout;
timebox->addWidget(TIME_LABEL);
timebox->addWidget(time_hour);
timebox->addWidget(TIME_SEP);
timebox->addWidget(time_min);

QHBoxLayout *gilbox = new QHBoxLayout;
gilbox->addWidget(GIL_LABEL);
gilbox->addWidget(gil_amount);

QVBoxLayout *timegilbox = new QVBoxLayout;
timegilbox->addLayout(timebox);
timegilbox->addLayout(gilbox);

QHBoxLayout *levelbox =new QHBoxLayout;
levelbox->addWidget(LEVEL_LABEL);
levelbox->addWidget(level_amount);

QVBoxLayout *namelevelbox =new QVBoxLayout;
namelevelbox->addWidget(name);
namelevelbox->addLayout(levelbox);


QHBoxLayout *upperhalf = new QHBoxLayout;
upperhalf->addLayout(namelevelbox);
upperhalf->addLayout(timegilbox);

QVBoxLayout *locbox = new QVBoxLayout;
locbox->addLayout(upperhalf);
locbox->addWidget(location);
location->setFrameStyle(1);

QHBoxLayout *midbox = new QHBoxLayout;
midbox->addLayout(partybox);
midbox->addLayout(locbox);

QVBoxLayout *finished = new QVBoxLayout;
finished->addWidget(btn_select);
finished->addLayout(midbox);

connect(btn_select,SIGNAL(clicked()),this,SLOT(selected()));

this->setLayout(finished);
this->setMinimumSize(581,150);
this->setMaximumSize(581,150);
}

void SlotPreview::setParty(QPixmap p1,QPixmap p2,QPixmap p3)
{
    this->set_Party1(p1);
    this->set_Party2(p2);
    this->set_Party3(p3);
}

void SlotPreview::setParty(QString p1_style,QString p2_style,QString p3_style)
{
    this->set_Party1(p1_style);
    this->set_Party2(p2_style);
    this->set_Party3(p3_style);
}

void SlotPreview::set_Party1(QPixmap pix){this->party1->setPixmap(pix);}
void SlotPreview::set_Party1(QString style){this->party1->setStyleSheet(style);}

void SlotPreview::set_Party2(QPixmap pix){this->party2->setPixmap(pix);}
void SlotPreview::set_Party2(QString style){this->party2->setStyleSheet(style);}

void SlotPreview::set_Party3(QPixmap pix){this->party3->setPixmap(pix);}
void SlotPreview::set_Party3(QString style){this->party3->setStyleSheet(style);}


void SlotPreview::setName(QString Name){this->name->setText(Name);}
void SlotPreview::setLevel(int lvl){this->level_amount->setText(QString::number(lvl));}
void SlotPreview::setLocation(QString loc){this->location->setText(loc);}
void SlotPreview::setGil(int gil){this->gil_amount->setText(QString::number(gil));}
void SlotPreview::setTime(int hr,int min){this->time_hour->setText(QString::number(hr));this->time_min->setText(QString::number(min));}
void SlotPreview::set_Button_Label(QString lbl){this->btn_select->setText(lbl);}
void SlotPreview::selected(void){emit button_clicked();}

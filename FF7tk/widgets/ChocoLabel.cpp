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
#include "ChocoLabel.h"
// Pull in Icons, Be Sure Paths Are Correct
#include"../static_data/icons/Chocobo_Icons/black_choco.xpm"
#include"../static_data/icons/Chocobo_Icons/blue_choco.xpm"
#include"../static_data/icons/Chocobo_Icons/green_choco.xpm"
#include"../static_data/icons/Chocobo_Icons/yellow_choco.xpm"
#include"../static_data/icons/Chocobo_Icons/gold_choco.xpm"
bool ChocoLabel::event(QEvent *ev)
{
    if (ev->type()==QEvent::MouseButtonPress){emit(clicked());return true;}
    else{return false;}
}
ChocoLabel::ChocoLabel(QWidget *parent) :
    QWidget(parent)
{
    lblType = new QLabel("");
    lblName = new QLabel("Empty");
    lblSex = new QLabel("");
    lblRank = new QLabel("Rank:-");

    lblType->setFixedSize(48,48);
    lblType->setScaledContents(true);
    QHBoxLayout *NameSexLayout = new QHBoxLayout;
    NameSexLayout->setContentsMargins(0,0,0,0);
    NameSexLayout->addWidget(lblName);
    NameSexLayout->addWidget(lblSex);
    NameSexLayout->setSpacing(1);

    QVBoxLayout *rightSideLayout = new QVBoxLayout;
    rightSideLayout->setContentsMargins(0,0,0,0);
    rightSideLayout->addLayout(NameSexLayout);
    rightSideLayout->addWidget(lblRank);

    QHBoxLayout *innerFinalLayout = new QHBoxLayout;
    innerFinalLayout->addWidget(lblType);
    innerFinalLayout->addLayout(rightSideLayout);

    this->setLayout(innerFinalLayout);
}
void ChocoLabel::setType(int type)
{
    if((type<0) || (type>4)) {lblType->setPixmap (QPixmap ( QString("") ) );return;}
    else if (type==0){lblType->setPixmap(QPixmap(yellow_choco_xpm));}
    else if (type==1){lblType->setPixmap(QPixmap(green_choco_xpm));}
    else if (type==2){lblType->setPixmap(QPixmap(blue_choco_xpm));}
    else if (type==3){lblType->setPixmap(QPixmap(black_choco_xpm));}
    else {lblType->setPixmap(QPixmap(gold_choco_xpm));}
}
void ChocoLabel::setName(QString decodedName){lblName->setText(decodedName);}
void ChocoLabel::setSex(bool male)
{
    if(male){lblSex->setText(QString::fromUtf8("♂"));}
    else{lblSex->setText(QString::fromUtf8("♀"));}
}
void ChocoLabel::setRank(int wins)
{
    if(wins<0){lblRank->setText("");}
    else if(wins<3){lblRank->setText(tr("Rank:C"));}
    else if(wins<6){lblRank->setText(tr("Rank:B"));}
    else if(wins<9){lblRank->setText(tr("Rank:A"));}
    else{lblRank->setText(tr("Rank:S"));}
}

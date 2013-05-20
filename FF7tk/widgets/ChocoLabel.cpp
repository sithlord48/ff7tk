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
#include"../static_data/icons/Common_Icons/copy.xpm"
#include"../static_data/icons/Common_Icons/paste.xpm"
#include"../static_data/icons/Common_Icons/delete.xpm"

bool ChocoLabel::event(QEvent *ev)
{
    if (ev->type()==QEvent::MouseButtonPress){emit(clicked());return true;}
    else{return false;}
}
ChocoLabel::ChocoLabel(QWidget *parent,QString titleText,bool occupied) :
    QWidget(parent)
{
    lblType = new QLabel("");   
    lblType->setFixedSize(48,48);
    lblType->setScaledContents(true);

    lblName = new QLabel("");
    lblSex = new QLabel("");
    lblRank = new QLabel("");

    chkOccupied = new QCheckBox();
    chkOccupied->setText(titleText);
    chkOccupied->setMaximumHeight(20);

    btnCopy = new QPushButton();
    btnCopy->setFixedSize(16,16);
    btnCopy->setIconSize(QSize(16,16));
    btnCopy->setToolTip(QString(tr("Copy")));
    btnCopy->setIcon(QIcon(QPixmap(copy_xpm).scaled(QSize(16,16),Qt::KeepAspectRatio,Qt::SmoothTransformation)));

    btnPaste = new QPushButton();
    btnPaste->setIconSize(QSize(16,16));
    btnPaste->setFixedSize(16,16);
    btnPaste->setToolTip(QString(tr("Paste")));
    btnPaste->setIcon(QIcon(QPixmap(paste_xpm).scaled(QSize(16,16),Qt::KeepAspectRatio,Qt::SmoothTransformation)));

    btnRemove = new QPushButton();
    btnRemove->setIconSize(QSize(16,16));
    btnRemove->setFixedSize(16,16);
    btnRemove->setToolTip(QString(tr("Remove")));
    btnRemove->setIcon(QIcon(QPixmap(delete_xpm).scaled(QSize(16,16),Qt::KeepAspectRatio,Qt::SmoothTransformation)));

    QString fontStyle =QString("font-size:14pt;");
    lblName->setStyleSheet(fontStyle);
    lblSex->setStyleSheet(fontStyle);
    lblRank->setStyleSheet(fontStyle);
    chkOccupied->setChecked(occupied);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setContentsMargins(0,0,0,0);
    btnLayout->addWidget(chkOccupied);
    btnLayout->addWidget(btnCopy);
    btnLayout->addWidget(btnPaste);
    btnLayout->addWidget(btnRemove);
    btnLayout->setSpacing(1);

    QHBoxLayout *NameSexLayout = new QHBoxLayout;
    NameSexLayout->setContentsMargins(0,0,0,0);
    NameSexLayout->addWidget(lblName);
    NameSexLayout->addWidget(lblSex);
    QSpacerItem *spacer1 = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Preferred);
    NameSexLayout->addSpacerItem(spacer1);
    NameSexLayout->setSpacing(1);

    QVBoxLayout *rightSideLayout = new QVBoxLayout;
    rightSideLayout->setContentsMargins(0,0,0,0);
    rightSideLayout->addLayout(NameSexLayout);
    rightSideLayout->addWidget(lblRank);

    QHBoxLayout *innerFinalLayout = new QHBoxLayout;
    innerFinalLayout->addWidget(lblType);
    innerFinalLayout->addLayout(rightSideLayout);

    QVBoxLayout *finalLayout= new QVBoxLayout;
    finalLayout->setContentsMargins(0,0,0,0);
    finalLayout->addLayout(btnLayout);
    finalLayout->addLayout(innerFinalLayout);

    this->setLayout(finalLayout);
    this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    enable(occupied);
    connect(chkOccupied,SIGNAL(toggled(bool)),this,SLOT(chkOccupiedToggled(bool)));
    connect(btnCopy,SIGNAL(clicked()),this,SLOT(copyPushed()));
    connect(btnPaste,SIGNAL(clicked()),this,SLOT(pastePushed()));
    connect(btnRemove,SIGNAL(clicked()),this,SLOT(removePushed()));
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
void ChocoLabel::setTitle(QString title){chkOccupied->setText(title);}
void ChocoLabel::setName(QString decodedName){lblName->setText(decodedName);}
void ChocoLabel::setSex(bool male)
{
    if(male){lblSex->setText(QString::fromUtf8("♂"));}
    else{lblSex->setText(QString::fromUtf8("♀"));}
}
void ChocoLabel::setSex(int sex)
{
    if (sex==0){lblSex->setText(QString::fromUtf8("♂"));}
    else if(sex==1){lblSex->setText(QString::fromUtf8("♀"));}
    else{lblSex->setText("");}
}
void ChocoLabel::setRank(int wins)
{
    if(wins<0){lblRank->setText("");}
    else if(wins<3){lblRank->setText(tr("Rank:C"));}
    else if(wins<6){lblRank->setText(tr("Rank:B"));}
    else if(wins<9){lblRank->setText(tr("Rank:A"));}
    else{lblRank->setText(tr("Rank:S"));}
}
void ChocoLabel::setOccupied(bool occupied)
{
    chkOccupied->blockSignals(true);
    chkOccupied->setChecked(occupied);
    chkOccupied->blockSignals(false);
    enable(occupied);
}
void ChocoLabel::chkOccupiedToggled(bool occupied)
{
    emit occupiedToggled(occupied);
    enable(occupied);
}
void ChocoLabel::copyPushed(void){emit copy();}
void ChocoLabel::pastePushed(void){emit paste();}
void ChocoLabel::removePushed(void)
{
    emit remove();
    setType(-1);
    setRank(-1);
    setName("");
    setSex(-1);
    chkOccupied->setChecked(false);
}
void ChocoLabel::setFontSize(int fontSize)
{
    QString fontStyle =QString("font-size:%1pt;").arg(fontSize);
    lblName->setStyleSheet(fontStyle);
    lblSex->setStyleSheet(fontStyle);
    lblRank->setStyleSheet(fontStyle);
}
void ChocoLabel::enable(bool enabled)
{
    lblName->setEnabled(enabled);
    lblType->setEnabled(enabled);
    lblSex->setEnabled(enabled);
    lblRank->setEnabled(enabled);
}
void ChocoLabel::setCheckBoxStyle(QString styleSheet){chkOccupied->setStyleSheet(styleSheet);}

/****************************************************************************/
//    copyright 2012 - 2018  Chris Rizzitello <sithlord48@gmail.com>        //
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

#include "DoubleCheckBox.h"
DoubleCheckBox::DoubleCheckBox(qreal scale,QWidget *parent) :
	QWidget(parent)
{
    init_display(scale);
}

DoubleCheckBox::DoubleCheckBox(const QString &text,qreal scale,QWidget *parent ) :
    QWidget(parent)
{
    init_display(scale);
    setText(text);
}
void DoubleCheckBox::init_display(qreal scale)
{
    cb_one = new QCheckBox(this);
    cb_one->setMaximumSize(int(22*scale), int(22*scale));
    connect(cb_one, &QCheckBox::toggled, this, &DoubleCheckBox::box1_toggled);

    cb_two = new QCheckBox(this);
    cb_two->setMaximumSize(int(22*scale), int(22*scale));
    connect(cb_two, &QCheckBox::toggled, this, &DoubleCheckBox::box2_toggled);
    label = new QLabel(this);

    auto boxLayout = new QHBoxLayout;
    boxLayout->addWidget(cb_one);
	boxLayout->addWidget(cb_two);
	boxLayout->setContentsMargins(0,0,0,0);
	boxLayout->setSpacing(2);

    auto Final = new QHBoxLayout;
    Final->addWidget(label);
	Final->addLayout(boxLayout);
	Final->setContentsMargins(0,0,0,0);
	this->setLayout(Final);
}

void DoubleCheckBox::setText(const QString& text)
{
    label->setText(text);
}

void DoubleCheckBox::setChecked(int box, bool checked)
{
	switch(box)
	{
		case 1: cb_one->setChecked(checked); break;
		case 2: cb_two->setChecked(checked); break;
		default: break;
	}
}
bool DoubleCheckBox::isChecked(int box)
{
	switch(box)
	{
        case 1: return cb_one->isChecked();
        case 2: return cb_two->isChecked();
        default: return false;
	}
}

void DoubleCheckBox::setBoxToolTip(int box, const QString& text)
{
	switch(box)
	{
		case 1: cb_one->setToolTip(text); break;
		case 2: cb_two->setToolTip(text); break;
		default: break;
	}
}
void DoubleCheckBox::setToolTip(const QString& text)
{
    label->setToolTip(text);
}

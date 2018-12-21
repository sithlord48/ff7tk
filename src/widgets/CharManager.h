/****************************************************************************/
//    copyright 2015- 2016  Chris Rizzitello <sithlord48@gmail.com>         //
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
#ifndef CHARMANAGER_H
#define CHARMANAGER_H

#include "qglobal.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	#include <QtWidgets>
#else
	#include <QtGui>
#endif

#include "CharEditor.h"
#include "../data/FF7Char.h"

class CharManager : public QWidget
{
	Q_OBJECT
public:
	explicit CharManager(qreal Scale=1,QWidget *parent=0);

signals:
	void comboParty1_changed(qint8);
	void comboParty2_changed(qint8);
	void comboParty3_changed(qint8);

public slots:
    void setParty(qint8 member1,qint8 member2,qint8 member3);

private slots:
	void party1Changed(int);
	void party2Changed(int);
	void party3Changed(int);
private:
	void initDisplay(void);
	void connectAll(void);
	void disconnectAll(void);
	FF7Char *charData;
	CharEditor *charEditor;
	QComboBox *comboParty[3];
	bool load;
	qreal scale;
};

#endif // CHARMANAGER_H

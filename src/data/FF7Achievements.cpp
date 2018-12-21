/****************************************************************************/
//    copyright 2013 - 2016 Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//   FF7tk is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#include "FF7Achievements.h"
#include <QFile>
#include <QCoreApplication>

FF7Achievements::FF7Achievements(QObject *parent) :
	QObject(parent)
{
	Achievements = QByteArray("\x00\x00\x00\x00\x00\x00\x00\x00");
}

bool FF7Achievements::openFile(QString fileName)
{
	if(!fileName.isEmpty())
	{
		QFile data(fileName);
		if(data.open(QIODevice::ReadOnly))
		{
			Achievements = data.readAll();
			data.close();
		}
		else{return false;}
		return true;
	}
	return false;
}

bool FF7Achievements::saveFile(QString fileName)
{
	if(!fileName.isEmpty())
	{
		QFile data(fileName);
		if(data.open(QIODevice::WriteOnly))
		{
			data.seek(0);
			data.write(Achievements.data(),8);
			data.close();
		}
		else{return false;}
		return true;
	}
	return false;
}

bool FF7Achievements::achievmentUnlocked(int bit){return (Achievements.at(bit/8) &(1<< (7-(bit%8))));}

void FF7Achievements::setAchievementUnlocked(int bit,bool unlocked)
{
	char temp = Achievements.at(bit/8);
	if(unlocked){ temp |= (1<< (7-(bit%8)));}
	else{temp &= ~(1<< (7-(bit%8)));}
	Achievements[bit/8]=temp;
}

QString FF7Achievements::name(int bit)
{
	switch(bit)
	{
        case 63: return qApp->translate("Achievement_Names","End of Part I");
        case 62: return qApp->translate("Achievement_Names","End of Part II");
        case 61: return qApp->translate("Achievement_Names","End of Game");
        case 60: return qApp->translate("Achievement_Names","Master Materia");
        case 59: return qApp->translate("Achievement_Names","Master of Gil");
        case 58: return qApp->translate("Achievement_Names","Top Level");
        case 57: return qApp->translate("Achievement_Names","Knights of the Round");
        case 56: return qApp->translate("Achievement_Names","Omnislash");
        case 55: return qApp->translate("Achievement_Names","Catastrophe");
        case 54: return qApp->translate("Achievement_Names","Chaos");
        case 53: return qApp->translate("Achievement_Names","Great Gospel");
        case 52: return qApp->translate("Achievement_Names","Highwind");
        case 51: return qApp->translate("Achievement_Names","Final Heaven");
        case 50: return qApp->translate("Achievement_Names","All Creation");
        case 49: return qApp->translate("Achievement_Names","Cosmo Memory");
        case 48: return qApp->translate("Achievement_Names","Slots");
        case 47: return qApp->translate("Achievement_Names","Bahamut Zero");
        case 46: return qApp->translate("Achievement_Names","Ultimate Weapon");
        case 45: return qApp->translate("Achievement_Names","Diamond Weapon");
        case 44: return qApp->translate("Achievement_Names","Ruby Weapon");
        case 43: return qApp->translate("Achievement_Names","Emerald Weapon");
        case 42: return qApp->translate("Achievement_Names","Vincent");
        case 41: return qApp->translate("Achievement_Names","Yuffie");
        case 40: return qApp->translate("Achievement_Names","Materia Overlord");
        case 39: return qApp->translate("Achievement_Names","Battle Square");
        case 38: return qApp->translate("Achievement_Names","Gold Chocobo");
        case 37: return qApp->translate("Achievement_Names","First Battle");
        case 36: return qApp->translate("Achievement_Names","Braver");
        case 35: return qApp->translate("Achievement_Names","Big Shot");
        case 34: return qApp->translate("Achievement_Names","Galian Beast");
        case 33: return qApp->translate("Achievement_Names","Healing Wind");
        case 32: return qApp->translate("Achievement_Names","Boost Jump");
        case 31: return qApp->translate("Achievement_Names","Beat Rush");
        case 30: return qApp->translate("Achievement_Names","Greased Lightning");
        case 29: return qApp->translate("Achievement_Names","Sled Fang");
        case 28: return qApp->translate("Achievement_Names","Dice");
        default: return QString("");
	}
}

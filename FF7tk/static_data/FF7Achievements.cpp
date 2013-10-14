/****************************************************************************/
//    copyright 2013  Chris Rizzitello <sithlord48@gmail.com>               //
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
#include "FF7Achievements.h"
#include <QFile>
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
        FileName=fileName;
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
    else
    {
        saveFile(FileName);
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
    case 63: return QString(tr("End of Part I")); break;
    case 62: return QString(tr("End of Part II")); break;
    case 61: return QString(tr("End of Game")); break;
    case 60: return QString(tr("Master Materia")); break;
    case 59: return QString(tr("Master of Gil")); break;
    case 58: return QString(tr("Top Level")); break;
    case 57: return QString(tr("Knights of the Round")); break;
    case 56: return QString(tr("Onmislash")); break;
    case 55: return QString(tr("Catastrophe")); break;
    case 54: return QString(tr("Chaos")); break;
    case 53: return QString(tr("Great Gospel")); break;
    case 52: return QString(tr("Highwind")); break;
    case 51: return QString(tr("Final Heaven")); break;
    case 50: return QString(tr("All Creation")); break;
    case 49: return QString(tr("Cosmo Memory")); break;
    case 48: return QString(tr("Slots")); break;
    case 47: return QString(tr("Bahamut Zero")); break;
    case 46: return QString(tr("Ultimate Weapon")); break;
    case 45: return QString(tr("Diamond Weapon")); break;
    case 44: return QString(tr("Ruby Weapon")); break;
    case 43: return QString(tr("Emerald Weapon")); break;
    case 42: return QString(tr("Vincent")); break;
    case 41: return QString(tr("Yuffie")); break;
    case 40: return QString(tr("Materia Overlord")); break;
    case 39: return QString(tr("Battle Square")); break;
    case 38: return QString(tr("Gold Chocobo")); break;
    case 37: return QString(tr("First Battle")); break;
    case 36: return QString(tr("Braver")); break;
    case 35: return QString(tr("Big Shot")); break;
    case 34: return QString(tr("Galian Beast")); break;
    case 33: return QString(tr("Healing Wind")); break;
    case 32: return QString(tr("Boost Jump")); break;
    case 31: return QString(tr("Beat Rush")); break;
    case 30: return QString(tr("Greased Lightning")); break;
    case 29: return QString(tr("Sled Fang")); break;
    case 28: return QString(tr("Dice")); break;
    default: return QString(""); break;
    }
}

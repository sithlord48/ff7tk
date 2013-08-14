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
//
#ifndef FF7FIELDITEMLIST_H
#define FF7FIELDITEMLIST_H

#include<QStringList>

struct FieldItemList
{
  QList<quint16> Offset;
  QList<quint8> Bit;
  QStringList Maps;
  QString Text;
};


class FF7FieldItemList
{
public:
    FF7FieldItemList();
    QList<quint16> offset(int index);
    QList<quint8> bit(int index);
    QStringList maps(int index);
    QString text(int index);
};

static FieldItemList FILIST[]=
{
    {QList<quint16>()<<0xFC4,QList<quint8>()<<0,QStringList()<<"md1stin",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0xFC4,QList<quint8>()<<1,QStringList()<<"md1stin",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0xFC4,QList<quint8>()<<2,QStringList()<<"nmkin_3",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0xFC4,QList<quint8>()<<3,QStringList()<<"nmkin_1",QT_TRANSLATE_NOOP("Items","Phoenix Down")},
    {QList<quint16>()<<0xFC4,QList<quint8>()<<4,QStringList()<<"blin67_1",QT_TRANSLATE_NOOP("Materia_Names","Poison")},
    {QList<quint16>()<<0xFC4,QList<quint8>()<<5,QStringList()<<"colne_b1",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0xFC4,QList<quint8>()<<6,QStringList()<<"",""},
    {QList<quint16>()<<0xFC4,QList<quint8>()<<7,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("Items","Potion")},

    {QList<quint16>()<<0xFC5,QList<quint8>()<<0,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0xFC5,QList<quint8>()<<1,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0xFC5,QList<quint8>()<<2,QStringList()<<"blin68_1",QT_TRANSLATE_NOOP("Items","Potion")},
    {QList<quint16>()<<0xFC5,QList<quint8>()<<3,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("Items","Bolt Armlet")},
    {QList<quint16>()<<0xFC5,QList<quint8>()<<4,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("Items","HypnoCrown")}, // add var[5][58] == 1 to this.
    {QList<quint16>()<<0xFC5,QList<quint8>()<<5,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("Items","Megalixir")},
    {QList<quint16>()<<0xFC5,QList<quint8>()<<6,QStringList()<<"smkin_1",QT_TRANSLATE_NOOP("Items","Ether")},
    {QList<quint16>()<<0xFC5,QList<quint8>()<<7,QStringList()<<"slfrst_2",QT_TRANSLATE_NOOP("Materia_Names","Kujata")},

    {QList<quint16>()<<0xFC6<<0xFC6,QList<quint8>()<<0<<1,QStringList()<<"sininb42",QT_TRANSLATE_NOOP("Materia_Names","Destruct")},
    {QList<quint16>()<<0xFC6<<0xFC6,QList<quint8>()<<2<<3,QStringList()<<"blin68_1"<<"blin68_2",QT_TRANSLATE_NOOP("Materia_Names","Enemy Skill")},
    {QList<quint16>()<<0xFC6<<0xFC6,QList<quint8>()<<4<<5,QStringList()<<"sinin2_1",QT_TRANSLATE_NOOP("Materia_Names","Odin")},
    {QList<quint16>()<<0xFC6,QList<quint8>()<<6,QStringList()<<"nvdun1",QT_TRANSLATE_NOOP("Materia_Names","Counter")},
    {QList<quint16>()<<0xFC6,QList<quint8>()<<7,QStringList()<<"sandun_1",QT_TRANSLATE_NOOP("Materia_Names","Magic Plus")}
};
#endif // FF7FIELDITEMLIST_H

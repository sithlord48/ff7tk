/****************************************************************************/
//    copyright 2013 - 2023 Chris Rizzitello <sithlord48@gmail.com>         //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include <FF7FieldItemList.h>

#include<QStringList>


FF7FieldItemList *FF7FieldItemList::get()
{
    static FF7FieldItemList m;
    return &m;
}

FF7FieldItemList::FF7FieldItemList(QObject *parent)
    : QObject(parent)
    , d(new FF7FieldItemListPrivate)
{
}

FF7FieldItemList::~FF7FieldItemList()
{
    delete d;
}
const QList<quint16> &FF7FieldItemList::offset(int index)
{
    index = std::clamp(index, 0, size() - 1);
    return get()->d->_fieldItemList.at(index).Offset;
}

const QList<quint8> &FF7FieldItemList::bit(int index)
{
    index = std::clamp(index, 0, size() - 1);
    return get()->d->_fieldItemList.at(index).Bit;
}

const QStringList &FF7FieldItemList::maps(int index)
{
    index = std::clamp(index, 0, size() - 1);
    return get()->d->_fieldItemList.at(index).Maps;
}

QString FF7FieldItemList::text(int index)
{
    index = std::clamp(index, 0, size() -1);
    return tr(get()->d->_fieldItemList.at(index).Text.toLocal8Bit());
}

const QList<FieldItem> &FF7FieldItemList::fieldItemList()
{
    return get()->d->_fieldItemList;
}

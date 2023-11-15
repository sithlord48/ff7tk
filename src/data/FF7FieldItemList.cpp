//    SPDX-FileCopyrightText: 2013 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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
    return tr(get()->d->_fieldItemList.at(index).Text.toUtf8());
}

const QList<FieldItem> &FF7FieldItemList::fieldItemList()
{
    return get()->d->_fieldItemList;
}

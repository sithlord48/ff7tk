/****************************************************************************/
//    copyright 2022         Chris Rizzitello <sithlord48@gmail.com>        //
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
#pragma once

#include <QAbstractTableModel>
#include <ff7tk_export.h>
#include <FF7Item.h>

class FF7TK_EXPORT FF7ItemModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QList<quint16> items READ allItems WRITE setItems NOTIFY itemsChanged);
public:
    explicit FF7ItemModel(QObject *parent = nullptr, const QList<quint16> &initialItems = QList<quint16>(320, FF7Item::EmptyItemData));
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index = QModelIndex(), int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index =  QModelIndex(), const QVariant &value = QVariant(), int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setItems(const QList<quint16> &newItems = {});
    QList<quint16> allItems();
signals:
    void itemsChanged(QList<quint16>);
private:
    QList<quint16> items;
};

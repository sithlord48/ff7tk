//    SPDX-FileCopyrightText: 2022 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QAbstractTableModel>
#include <ff7tkdata_export.h>
#include <FF7Item>

class FF7TKDATA_EXPORT FF7ItemModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QList<quint16> items READ allItems WRITE setItems NOTIFY itemsChanged)
public:
    explicit FF7ItemModel(QObject *parent = nullptr, const QList<quint16> &initialItems = QList<quint16>(320, FF7Item::EmptyItemData));
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index = QModelIndex(), int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index =  QModelIndex(), const QVariant &value = QVariant(), int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    /**
     * Set Items
     * Emits Items Changed
     * Returns True (and Emits) if successful
     */
    bool setItems(const QList<quint16> &newItems = {});
    /** Resets Initial Items
     *  Does not Emit Items Changed
     *  Returns True When successful
    */
    bool resetItems(const QList<quint16> &newItems = {});
    QList<quint16> allItems();
signals:
    void itemsChanged(QList<quint16>);
private:
    QList<quint16> items;
};

#include <FF7ItemModel.h>
#include <FF7Item>
#include <QIcon>
#include <QModelIndex>

FF7ItemModel::FF7ItemModel(QObject *parent, const QList<quint16> &initialItems)
    : QAbstractTableModel{parent}
    , items(initialItems)
{
}

int FF7ItemModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 320;
}

int FF7ItemModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return 3;
}

QVariant FF7ItemModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if( (role != Qt::EditRole && role != Qt::ToolTipRole && index.column() != 1 && role != FF7Item::ItemNameRole) && items.at(index.row()) == FF7Item::EmptyItemData)
        return QVariant();

    if(role == Qt::EditRole)
        return items.at(index.row());

    int id = FF7Item::itemId(items.at(index.row()));
    if (role == Qt::ToolTipRole)
        return id;

    if((role == Qt::DecorationRole && index.column() == 0) || role == FF7Item::ItemTypeRole)
        return FF7Item::icon(id);
    if((role == Qt::DisplayRole && index.column() == 1) || role == FF7Item::ItemNameRole) {
        if(id == FF7Item::EmptyItem)
            return tr("-------EMPTY--------");
        return FF7Item::name(id);
    }
    if((role == Qt::DisplayRole && index.column() == 2) || role == FF7Item::ItemQtyRole)
        return FF7Item::itemQty(items.at(index.row()));
    return QVariant();
}

bool FF7ItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;
    if(role == FF7Item::ChangeMaxQtyRole) {
        QAbstractItemModel::beginResetModel();
        for(int i = 0; i < items.count(); i ++) {
            quint16 item = items.at(i);
            if( item == FF7Item::EmptyItemData)
                continue;
            if(FF7Item::itemQty(item) > value.toInt())
                setData(index.model()->index(i, 0), value.toInt(), FF7Item::ItemQtyRole);
        }
        QAbstractItemModel::endResetModel();
        return true;
    }
    if(index.row() < 0 || index.row() > rowCount() || index.column() < 0 || index.column() > columnCount())
        return false;
    if(role == Qt::EditRole) {
        items.replace(index.row(), FF7Item::itemEncode(FF7Item::itemId(value.toUInt()), FF7Item::itemQty(value.toUInt())));
        Q_EMIT itemsChanged(items);
        return true;
    }
    quint16 itemtmp = items.at(index.row());
    if(index.column() == 1 || role == FF7Item::ItemNameRole) {
        items.replace(index.row(), FF7Item::itemEncode(value.toUInt(), FF7Item::itemQty(itemtmp)));
        return true;
    }
    if(index.column() == 2 || role == FF7Item::ItemQtyRole) {
        items.replace(index.row(), FF7Item::itemEncode(FF7Item::itemId(itemtmp), value.toUInt()));
        return true;
    }
    return false;
}

Qt::ItemFlags FF7ItemModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return QAbstractItemModel::flags(index);
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable ;
}

QVariant FF7ItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal) {
        if(section == 0)
            return tr("Type");
        if(section == 1)
            return tr("Name");
        if(section == 2)
            return tr("Qty");
        return QVariant();
    } else {
        return QString::number(section);
    }
}

bool FF7ItemModel::setItems(const QList<quint16> &newItems)
{
    if(!resetItems(newItems))
        return false;
    Q_EMIT itemsChanged(items);
    return true;
}

bool FF7ItemModel::resetItems(const QList<quint16> &newItems)
{
    if(newItems.count() != 320)
        return false;
    if(items == newItems)
        return false;
    beginResetModel();
    items = newItems;
    endResetModel();
    return true;
}

QList<quint16> FF7ItemModel::allItems()
{
    return items;
}

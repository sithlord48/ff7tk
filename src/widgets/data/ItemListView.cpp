/****************************************************************************/
//    copyright 2022  Chris Rizzitello <sithlord48@gmail.com>               //
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
#include <ItemListView.h>

#include <QEvent>
#include <QHeaderView>
#include <QScrollBar>
#include <FF7Item.h>
#include <ItemPreview.h>
#include <ItemSelector.h>
#include <ItemSelectionDelegate.h>

ItemListView::ItemListView(QWidget *parent)
    : QTableView(parent)
{
    setSelectionMode(QAbstractItemView::NoSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::AllEditTriggers);
    setItemDelegate(new ItemSelectionDelegate(this));
    ItemSelector itemSelector;

    verticalHeader()->setDefaultSectionSize(itemSelector.height());
    verticalHeader()->close();

    setFixedWidth(itemSelector.width() + verticalScrollBar()->sizeHint().width() + 3 );
    itemSelector.close();
    itemSelector.deleteLater();

}

void ItemListView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);

    ItemSelector itemSelector;
    setColumnWidth(0, itemSelector.combo_type_width());
    setColumnWidth(1, itemSelector.combo_item_width());
    setColumnWidth(2, itemSelector.qty_width());
}

bool ItemListView::viewportEvent(QEvent *event)
{
    if(event->type() != QEvent::ToolTip)
        return QTableView::viewportEvent(event);

    int row = indexAt(mapFromGlobal(viewport()->cursor().pos())).row() - 1;
    int itemID = model()->data(model()->index(row, 0, QModelIndex()), Qt::ToolTipRole).toInt();

    if(m_createdTooltip)
        destroyTooltip();

    if(row == -1)
        return true;

    if (mapFromGlobal(cursor().pos()).x() > viewport()->width() || mapFromGlobal(cursor().pos()).y() > viewport()->height())
        return true;

    if (itemID != FF7Item::EmptyItem) {
        itemPreview = new ItemPreview(Qt::ToolTip);
        itemPreview->setItem(FF7Item::itemId(itemID));
        itemPreview->setGeometry(QRect(cursor().pos(), itemPreview->contentsRect().size()));
        itemPreview->show();
        m_createdTooltip = true;
    }
    return true;
}

void ItemListView::destroyTooltip()
{
    itemPreview->close();
    m_createdTooltip = false;
}

void ItemListView::setMaximumItemQty(int itemQtyLimit)
{
    if(m_itemQtyLimit == itemQtyLimit)
        return;

    auto itemSelector = static_cast<ItemSelectionDelegate*>(itemDelegate());
    if(itemSelector)
        itemSelector->setMaximumQty(m_itemQtyLimit);
    m_itemQtyLimit = itemQtyLimit;
    model()->setData(model()->index(0,0), m_itemQtyLimit, FF7Item::ChangeMaxQtyRole);
    setCurrentIndex(QModelIndex());
}

void ItemListView::setEditableItemCombo(bool editable)
{
    if(m_editableItemCombo == editable)
        return;

    auto itemSelector = static_cast<ItemSelectionDelegate*>(itemDelegate());
    if(itemSelector) {
        m_editableItemCombo = editable;
        itemSelector->setEditableItemCombo(m_editableItemCombo);
    }
    setCurrentIndex(QModelIndex());
}

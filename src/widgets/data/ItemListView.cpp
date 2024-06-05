//    SPDX-FileCopyrightText: 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <ItemListView.h>

#include <QEvent>
#include <QHeaderView>
#include <QScrollBar>
#include <FF7Item>
#include <ItemPreview>
#include <ItemSelector>
#include <ItemSelectionDelegate>

ItemListView::ItemListView(QWidget *parent)
    : QTableView(parent)
{
    setSelectionMode(QAbstractItemView::NoSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::AllEditTriggers);
    setItemDelegate(new ItemSelectionDelegate(this));

    ItemSelector itemSelector;
    m_columnWidth[0] = itemSelector.combo_type_width();
    m_columnWidth[1] = itemSelector.combo_item_width();
    m_columnWidth[2] = itemSelector.qty_width();

    verticalHeader()->setDefaultSectionSize(itemSelector.height());
    verticalHeader()->close();

    setFixedWidth(itemSelector.sizeHint().width() + verticalScrollBar()->sizeHint().width());
    itemSelector.close();
    itemSelector.deleteLater();

}

void ItemListView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);
    for(int i=0; i<3; i++)
        setColumnWidth(i, sizeHintForColumn(i));
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

int ItemListView::sizeHintForColumn(int column)
{
    if(column < 0 || column > 2)
        return -1;
    return m_columnWidth[column];
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

void ItemListView::setShowPlaceholderItems(bool showPlaceholderItems)
{
    if(m_showPlaceholderItems == showPlaceholderItems)
        return;

    auto itemSelector = static_cast<ItemSelectionDelegate*>(itemDelegate());
    if(itemSelector) {
        m_showPlaceholderItems = showPlaceholderItems;
        itemSelector->setShowPlaceholderItems(m_showPlaceholderItems);
    }
    setCurrentIndex(QModelIndex());
}

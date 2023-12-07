//    SPDX-FileCopyrightText: 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QTableView>
#include <ff7tkwidgets_export.h>

class ItemPreview;

class FF7TKWIDGETS_EXPORT ItemListView : public QTableView
{
public:
    explicit ItemListView(QWidget *parent = nullptr);
    void setMaximumItemQty(int itemQtyLimit);
    int maximumItemQty() {return m_itemQtyLimit;}
    void setEditableItemCombo(bool editable);
    bool editableItemCombo() {return m_editableItemCombo;}
    void setShowPlaceholderItems(bool showPlaceholderItems);
    bool showPlaceholderItems() {return m_showPlaceholderItems;}
    void setModel(QAbstractItemModel* model);
    bool viewportEvent(QEvent *event);
    void destroyTooltip();
    int sizeHintForColumn(int column);
private:
    int m_itemQtyLimit = 127;
    bool m_editableItemCombo = false;
    bool m_createdTooltip = false;
    bool m_showPlaceholderItems = false;
    ItemPreview *itemPreview = nullptr;
    int m_columnWidth[3];
};

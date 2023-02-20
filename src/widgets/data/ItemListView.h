/****************************************************************************/
//    copyright 2022 Chris Rizzitello <sithlord48@gmail.com>                //
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
private:
    int m_itemQtyLimit = 127;
    bool m_editableItemCombo = false;
    bool m_createdTooltip = false;
    bool m_showPlaceholderItems = false;
    ItemPreview *itemPreview = nullptr;
};

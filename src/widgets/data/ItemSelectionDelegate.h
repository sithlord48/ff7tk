/****************************************************************************/
//    copyright 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>         //
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

#include <QStyledItemDelegate>
#include <ff7tkwidgets_export.h>

class FF7TKWIDGETS_EXPORT ItemSelectionDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ItemSelectionDelegate(QObject * parent = nullptr);
    QWidget *createEditor (QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index = QModelIndex()) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setMaximumQty(int maxQty);
    void setEditableItemCombo(bool editable);
    void setShowPlaceholderItems(bool showPlaceholderItems);
protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
signals:
    void commitData(QWidget *editor) const;
private:
    int m_maxQty = 127;
    bool m_editableItemCombo = false;
    bool m_showPlaceholderItems = false;
};


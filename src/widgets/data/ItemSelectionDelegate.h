//    SPDX-FileCopyrightText: 2022 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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


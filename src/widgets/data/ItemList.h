//    SPDX-FileCopyrightText: 2012 - 2022 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QTableWidget>
#include <QEvent>
#include <ff7tkwidgets_export.h>

class ItemPreview;
class ItemSelector;

class FF7TKWIDGETS_DEPRECATED_EXPORT ItemList : public QTableWidget
{
    Q_OBJECT
public:
    explicit ItemList(QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject *, QEvent *);
    void changeEvent(QEvent *e);
signals:
    void itemsChanged(QList<quint16> items);
public slots:
    void setItems(const QList<quint16> &items);
    void setMaximumItemQty(int maxQty);
    void setEditableItemCombo(bool);
private slots:
    void listSelectionChanged(int row, int colum, int prevRow, int prevColum);
    void itemSelector_changed(quint16);
private:
    void itemupdate();
    void updateItem(int row);
    void destroyTooltip();
    void destroySelector();
    ItemSelector *itemSelector = nullptr;
    ItemPreview *itemPreview = nullptr;
    QList<quint16> itemlist;
    int itemQtyLimit;
    bool createdSelector;
    bool createdTooltip;
    bool editableItemCombo = false;
};

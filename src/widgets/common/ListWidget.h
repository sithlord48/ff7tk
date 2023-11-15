//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-FileCopyrightText: 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QWidget>
#include <QToolBar>
#include <QListWidget>
#include <QEvent>

#include <ff7tkqtwidgets_export.h>

class FF7TKQTWIDGETS_EXPORT ListWidget : public QWidget
{
    Q_OBJECT
public:
    enum ActionType {
        Add, Remove, Up, Down, Cut, Copy, Paste
    };

    explicit ListWidget(QWidget *parent = nullptr);
    void addSeparator(bool invisible = false);
    QAction *addAction(ActionType type, const QString &overrideText = QString(), bool visible = true);

    QToolBar *toolBar() const;
    QListWidget *listWidget() const;
signals:
    void addTriggered();
    void removeTriggered();
    void cutTriggered();
    void copyTriggered();
    void pasteTriggered();
    void upTriggered();
    void downTriggered();
protected:
    void changeEvent(QEvent *e);
private:
    QToolBar *_toolBar;
    QListWidget *_listWidget;
};

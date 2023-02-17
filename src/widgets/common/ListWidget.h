/****************************************************************************/
//    Copyright (C) 2009-2022 Arzel Jérôme <myst6re@gmail.com>              //
//    Copyright (C) 2023 Chris Rizzitello <sithlord48@gmail.com>            //
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

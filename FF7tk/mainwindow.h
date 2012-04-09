/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
/****************************************************************************/
//    This Demo Program Just Shows Widgets For Easier Testing               //

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgets/DialogPreview.h"
#include "widgets/SlotPreview.h"

#include "widgets/MateriaEditor.h"
#include "widgets/ItemPreview.h"
#include "widgets/CharEditor.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_set_item_clicked();
    void on_combo_widget_currentIndexChanged(int index);
    void on_sb_materia_editor_setStarSize_valueChanged(int arg1);
    void on_cb_materia_editor_setEditable_toggled(bool checked);

private:

    Ui::MainWindow *ui;
    DialogPreview *dialog_preview;
    MateriaEditor *materia_editor;
    ItemPreview *item_preview;
    CharEditor *char_editor;
};

#endif // MAINWINDOW_H

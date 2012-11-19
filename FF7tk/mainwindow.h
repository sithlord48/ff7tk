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

//Include FF7Save for slot preview.

//#include"static_data/FF7Save.h"

#include "widgets/DialogPreview.h"
#include "widgets/MateriaEditor.h"
#include "widgets/CharEditor.h"
#include "widgets/ChocoboEditor.h"
#include "widgets/ItemList.h"
#include "widgets/MetadataCreator.h"
#include "widgets/SlotSelect.h"

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
    void on_combo_widget_currentIndexChanged(int index);
    void on_sb_materia_editor_setStarSize_valueChanged(int arg1);
    void on_cb_materia_editor_setEditable_toggled(bool checked);
    void on_cb_charEditor_clicked(bool checked);
    void on_pushButton_clicked();
    void on_checkBox_toggled(bool checked);
    void on_btn_showmetaData_clicked();
    void on_btn_slotSelect_clicked();

private:

    Ui::MainWindow *ui;
    FF7Save *ff7save;
    DialogPreview *dialog_preview;
    MateriaEditor *materia_editor;
    CharEditor *char_editor;
    ChocoboEditor *choco_editor;
    ItemList *item_list;
    SlotSelect *slotSelect;
};

#endif // MAINWINDOW_H

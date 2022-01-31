/****************************************************************************/
//    copyright 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>         //
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
#pragma once
#include <QtWidgets/QMainWindow>

#include <MateriaEditor.h>
#include <CharEditor.h>
#include <ItemList.h>
#include <MetadataCreator.h>
#include <SlotSelect.h>
#include <PhsListWidget.h>
#include <MenuListWidget.h>
#include <OptionsWidget.h>
#include <LocationViewer.h>
#include <ChocoboManager.h>
#include <AchievementEditor.h>

#include <Lgp.h>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void hideAllBoxes(void);
    void on_combo_widget_currentIndexChanged(int index);
    void on_sb_materia_editor_setStarSize_valueChanged(int arg1);
    void on_cb_materia_editor_setEditable_toggled(bool checked);
    void on_cb_charEditor_clicked(bool checked);
    void on_pushButton_clicked();
    void on_checkBox_toggled(bool checked);
    void on_btn_showmetaData_clicked();
    void on_btn_slotSelect_clicked();
    void on_btn_lgpSelect_clicked();
    void on_btnExtractLgp_clicked();
    void on_btn_loadAchievement_clicked();
    void on_btn_saveAchievement_clicked();
    void on_checkBox_2_toggled(bool checked);
    void on_checkBox_3_clicked(bool checked);
    void on_cbEditableMateriaCombos_clicked(bool checked);
    void on_checkBox_4_clicked(bool checked);

    void on_comboRegion_currentIndexChanged(const QString &arg1);

private:

    Ui::MainWindow *ui;
    qreal scale;
    MateriaEditor *materia_editor;
    CharEditor *char_editor;
    ItemList *item_list;
    MetadataCreator *metadataCreator;
    PhsListWidget *ListPHS;
    MenuListWidget *ListMenu;
    Lgp *lgpFile;
    LocationViewer *locViewer;
    OptionsWidget *optionsWidget;
    ChocoboManager *chocoboManager;
    AchievementEditor *achievementEditor;
};

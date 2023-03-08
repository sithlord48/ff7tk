/****************************************************************************/
//    copyright 2012 - 2021 Chris Rizzitello <sithlord48@gmail.com>         //
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
#include <MetadataCreator.h>
#include <SlotSelect.h>
#include <PhsListWidget.h>
#include <MenuListWidget.h>
#include <OptionsWidget.h>
#include <LocationViewer.h>
#include <ChocoboManager.h>
#include <AchievementEditor.h>
#include <ItemListView.h>
#include <HexLineEdit.h>

#include <EncounterTableWidget>
#include <OrientationWidget>
#include <Lgp>

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

    void on_comboRegion_currentTextChanged(const QString &arg1);

    void on_cb_itemSelectionDeleageEditable_toggled(bool checked);
    void on_sb_itemListViewMaxQty_editingFinished();

    void on_sb_hexEditLine_maxlen_valueChanged(double arg1);

    void on_sb_orientationWidget_value_valueChanged(int arg1);

    void on_cb_materiaEditor_showPlaceHolderMateria_toggled(bool checked);

    void on_cb_itemSelection_showPlaceHolders_toggled(bool checked);

private:

    Ui::MainWindow *ui = nullptr;
    MateriaEditor *materia_editor = nullptr;
    CharEditor *char_editor = nullptr;
    MetadataCreator *metadataCreator = nullptr;
    PhsListWidget *ListPHS = nullptr;
    MenuListWidget *ListMenu = nullptr;
    Lgp *lgpFile = nullptr;
    LocationViewer *locViewer = nullptr;
    OptionsWidget *optionsWidget = nullptr;
    ChocoboManager *chocoboManager = nullptr;
    AchievementEditor *achievementEditor = nullptr;
    ItemListView *itemlistView = nullptr;
    HexLineEdit *hexLineEdit = nullptr;
    OrientationWidget *orientationWidget = nullptr;
    EncounterTableWidget *encounterTableWidget = nullptr;
};

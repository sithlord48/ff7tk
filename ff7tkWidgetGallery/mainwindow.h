/****************************************************************************/
//    copyright 2012 - 2016 Chris Rizzitello <sithlord48@gmail.com>         //
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

#include <QtWidgets/QMainWindow>

#include "../src/widgets/MateriaEditor.h"
#include "../src/widgets/CharEditor.h"
#include "../src/widgets/ItemList.h"
#include "../src/widgets/MetadataCreator.h"
#include "../src/widgets/SlotSelect.h"
#include "../src/widgets/PhsListWidget.h"
#include "../src/widgets/MenuListWidget.h"
#include "../src/widgets/OptionsWidget.h"
#include "../src/widgets/LocationViewer.h"
#include "../src/widgets/ChocoboManager.h"
#include "../src/widgets/AchievementEditor.h"
#include "../src/widgets/CharManager.h"

#include "../src/formats/Lgp.h"

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

private:

	Ui::MainWindow *ui;
	qreal scale;
	MateriaEditor *materia_editor;
	CharEditor *char_editor;
	ItemList *item_list;
	MetadataCreator *metadataCreator;
	//SlotSelect *slotSelect;
	PhsListWidget *ListPHS;
	MenuListWidget *ListMenu;
	Lgp *lgpFile;
	LocationViewer *locViewer;
	OptionsWidget *optionsWidget;
	ChocoboManager *chocoboManager;
	AchievementEditor *achievementEditor;
	CharManager *charManager;
};

#endif // MAINWINDOW_H

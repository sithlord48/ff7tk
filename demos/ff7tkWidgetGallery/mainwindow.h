//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later
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
    void combo_currentWidget_currentIndexChanged(int index);
    void slotSelect_show();
    void selectLgpFile();
    void extractLgp();

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
    void initUiConnections();
};

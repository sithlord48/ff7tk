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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dialog_preview_box->setHidden(1);
    ui->materia_editor_box->setHidden(1);
    ui->char_editor_box->setHidden(1);
    ui->choco_editor_box->setHidden(1);
    ui->item_list_box->setHidden(1);
    ui->metadata_box->setHidden(1);
    ui->slotSelect_Box->setHidden(1);
    ui->phsListBox->setHidden(1);
    ui->menuListBox->setHidden(1);

    ListPHS = new PhsListWidget(0);
    QHBoxLayout *listLayout = new QHBoxLayout;
    listLayout->addWidget(ListPHS);
    ui->phsListBox->setLayout(listLayout);

    ListMenu = new MenuListWidget(0);
    QHBoxLayout *list2Layout = new QHBoxLayout;
    list2Layout->addWidget(ListMenu);
    ui->menuListBox->setLayout(list2Layout);

    dialog_preview= new DialogPreview();
    QHBoxLayout *dialog_preview_layout = new QHBoxLayout();
    dialog_preview_layout->addWidget(dialog_preview);
    ui->dialog_preview_box->setLayout(dialog_preview_layout);

    materia_editor = new MateriaEditor(this);
    QHBoxLayout *materia_editor_layout= new QHBoxLayout();
    materia_editor_layout->addWidget(materia_editor);
    ui->editor_box->setLayout(materia_editor_layout);

    char_editor = new CharEditor();
    QHBoxLayout * char_editor_layout = new QHBoxLayout();
    char_editor_layout->addWidget(char_editor);
    ui->charEditor_box->setLayout(char_editor_layout);

    choco_editor = new ChocoboEditor();
    QHBoxLayout *choco_editor_layout = new QHBoxLayout();
    choco_editor_layout->addWidget(choco_editor);
    ui->choco_editor_box->setLayout(choco_editor_layout);

    item_list = new ItemList();
    QHBoxLayout *item_list_layout = new QHBoxLayout;
    item_list_layout->addWidget(item_list);
    ui->item_list_box->setLayout(item_list_layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_combo_widget_currentIndexChanged(int index)
{
    ui->dialog_preview_box->setVisible(0);
    ui->materia_editor_box->setVisible(0);
    ui->char_editor_box->setVisible(0);
    ui->choco_editor_box->setVisible(0);
    ui->item_list_box->setVisible(0);
    ui->metadata_box->setVisible(0);
    ui->slotSelect_Box->setVisible(0);
    ui->phsListBox->setVisible(0);
    ui->menuListBox->setVisible(0);

    switch(index)
    {
        case 1:ui->dialog_preview_box->setVisible(1); break;
        case 2:ui->materia_editor_box->setVisible(1); break;
        case 3:ui->item_list_box->setVisible(1);break;
        case 4:ui->char_editor_box->setVisible(1); break;
        case 5:ui->choco_editor_box->setVisible(1); break;
        case 6:ui->metadata_box->setVisible(1);break;
        case 7:ui->slotSelect_Box->setVisible(1);break;
        case 8:ui->phsListBox->setVisible(1);break;
        case 9:ui->menuListBox->setVisible(1);break;
    };
    this->adjustSize();
}

void MainWindow::on_sb_materia_editor_setStarSize_valueChanged(int size){materia_editor->setStarsSize(size);}
void MainWindow::on_cb_materia_editor_setEditable_toggled(bool checked){materia_editor->setEditable(checked);}
void MainWindow::on_cb_charEditor_clicked(bool checked){char_editor->setEditable(checked);}
void MainWindow::on_checkBox_toggled(bool checked){char_editor->setDebug(checked);}

void MainWindow::on_pushButton_clicked()
{
    QByteArray temp;
    temp.fill(0x00,132);
    FF7CHAR c_data;
    memcpy(&c_data,temp,132);
    char_editor->setChar(c_data,QString("Cloud"));
}


void MainWindow::on_btn_showmetaData_clicked()
{
    FF7Save *ff7save = new FF7Save;
    metadataCreator = new MetadataCreator(this,ff7save);
    metadataCreator->exec();
}

void MainWindow::on_btn_slotSelect_clicked()
{
    FF7Save *ff7save = new FF7Save;
    QString fileFilter("Multi Slot Save Types (*.ff7 *.vmp *.vgs *.mem *.gme *.mcr *.mcd *.mci *.mc *.ddf *.ps *.psm *.VM1 *.bin);;PC FF7 SaveGame (*.ff7);;Raw PSX FF7 SaveGame (*-S*);;MC SaveGame (*.mcr *.mcd *.mci *.mc *.ddf *.ps *.psm *.VM1 *.bin);;PSP SaveGame (*.vmp);;VGS SaveGame(*.vgs *.mem);;Dex-Drive SaveGame(*.gme)");
    QString filename = QFileDialog::getOpenFileName(this,"Select A Save To Preview",QDir::homePath(),fileFilter);
    if(!filename.isEmpty())
    {
        ff7save->loadFile(filename);
        slotSelect = new SlotSelect(this,ff7save);
        slotSelect->exec();
    }
}

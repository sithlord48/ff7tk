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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dialog_preview_box->setHidden(1);
    ui->materia_editor_box->setHidden(1);
    ui->item_selector_box->setHidden(1);
    ui->item_preview_box->setHidden(1);
    ui->char_editor_box->setHidden(1);
    ui->choco_editor_box->setHidden(1);

    dialog_preview= new DialogPreview();
    QHBoxLayout *dialog_preview_layout = new QHBoxLayout();
    dialog_preview_layout->addWidget(dialog_preview);
    ui->dialog_preview_box->setLayout(dialog_preview_layout);

    materia_editor = new MateriaEditor(this);
    QHBoxLayout *materia_editor_layout= new QHBoxLayout();
    materia_editor_layout->addWidget(materia_editor);
    ui->editor_box->setLayout(materia_editor_layout);

    item_preview =new ItemPreview();
    QHBoxLayout *item_preview_layout =new QHBoxLayout();
    item_preview_layout->addWidget(item_preview);
    ui->item_box->setLayout(item_preview_layout);

    char_editor = new CharEditor();
    QHBoxLayout * char_editor_layout = new QHBoxLayout();
    char_editor_layout->addWidget(char_editor);
    ui->charEditor_box->setLayout(char_editor_layout);

    choco_editor = new ChocoboEditor();
    QHBoxLayout *choco_editor_layout = new QHBoxLayout();
    choco_editor_layout->addWidget(choco_editor);
    ui->choco_editor_box->setLayout(choco_editor_layout);

    item_selector = new ItemSelector();
    QHBoxLayout *item_selector_layout = new QHBoxLayout;
    item_selector_layout->addWidget(item_selector);
    ui->item_selector_box->setLayout(item_selector_layout);

    connect(this->item_selector,SIGNAL(item_changed(quint16)),item_preview,SLOT(setItem(quint16)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_combo_widget_currentIndexChanged(int index)
{
    ui->dialog_preview_box->setVisible(0);
    ui->materia_editor_box->setVisible(0);
    ui->item_preview_box->setVisible(0);
    ui->char_editor_box->setVisible(0);
    ui->choco_editor_box->setVisible(0);
    ui->item_selector_box->setVisible(0);

    switch(index)
    {
        case 1:ui->dialog_preview_box->setVisible(1); break;
        case 2:ui->materia_editor_box->setVisible(1); break;
        case 3:ui->item_preview_box->setVisible(1); ui->item_selector_box->setVisible(1);break;
        case 4:ui->char_editor_box->setVisible(1); break;
        case 5:ui->choco_editor_box->setVisible(1); break;
    };
    this->adjustSize();
}

void MainWindow::on_sb_materia_editor_setStarSize_valueChanged(int size){materia_editor->setStarsSize(size);}
void MainWindow::on_cb_materia_editor_setEditable_toggled(bool checked){materia_editor->setEditable(checked);}

void MainWindow::on_cb_charEditor_clicked(bool checked){char_editor->setEditable(checked);}

void MainWindow::on_pushButton_clicked()
{
    QByteArray temp;
    temp.fill(0x00,132);
    FF7CHAR c_data;
    memcpy(&c_data,temp,132);
    char_editor->setChar(c_data,QString("Cloud"));
}

void MainWindow::on_checkBox_toggled(bool checked){char_editor->setDebug(checked);}
void MainWindow::on_sb_item_id_valueChanged(int arg1){item_preview->setItem(arg1);}

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
    ui->materia_preview_box->setHidden(1);
    ui->materia_editor_box->setHidden(1);
    ui->item_preview_box->setHidden(1);

    dialog_preview= new DialogPreview();
    QHBoxLayout *dialog_preview_layout = new QHBoxLayout();
    dialog_preview_layout->addWidget(dialog_preview);
    ui->dialog_preview_box->setLayout(dialog_preview_layout);

    materia_preview=new MateriaPreview();
    QHBoxLayout *materia_preview_layout =new QHBoxLayout();
    materia_preview_layout->addWidget(materia_preview);
    ui->materia_box->setLayout(materia_preview_layout);

    materia_editor = new MateriaEditor();
    QHBoxLayout *materia_editor_layout= new QHBoxLayout();
    materia_editor_layout->addWidget(materia_editor);
    ui->materia_editor_box->setLayout(materia_editor_layout);

    item_preview =new ItemPreview();
    QHBoxLayout *item_preview_layout =new QHBoxLayout();
    item_preview_layout->addWidget(item_preview);
    ui->item_box->setLayout(item_preview_layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_btn_set_materia_clicked()
{
    materia_preview->setMateria(ui->sb_mat_id->value(),ui->sb_mat_ap->value());
    this->adjustSize();
}

void MainWindow::on_btn_set_item_clicked()
{
    item_preview->setItem(ui->sb_item_id->value());
    this->adjustSize();
}

void MainWindow::on_combo_widget_currentIndexChanged(int index)
{
    ui->dialog_preview_box->setVisible(0);
    ui->materia_preview_box->setVisible(0);
    ui->materia_editor_box->setVisible(0);
    ui->item_preview_box->setVisible(0);

    switch(index)
    {
        case 1:ui->dialog_preview_box->setVisible(1); break;
        case 2:ui->materia_preview_box->setVisible(1); break;
        case 3:ui->materia_editor_box->setVisible(1); break;
        case 4:ui->item_preview_box->setVisible(1); break;
    };
    this->adjustSize();
}

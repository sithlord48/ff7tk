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
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hideAllBoxes();

    ListPHS = new PhsListWidget(0);
    QHBoxLayout *listLayout = new QHBoxLayout;
    listLayout->addWidget(ListPHS);
    ui->phsListBox->setLayout(listLayout);

    ListMenu = new MenuListWidget(0);
    QHBoxLayout *list2Layout = new QHBoxLayout;
    list2Layout->addWidget(ListMenu);
    ui->menuListBox->setLayout(list2Layout);

    optionsWidget= new OptionsWidget();
    QHBoxLayout *options_layout = new QHBoxLayout();
    options_layout->addWidget(optionsWidget);
    ui->dialog_preview_box->setLayout(options_layout);

    materia_editor = new MateriaEditor(this);
    QHBoxLayout *materia_editor_layout= new QHBoxLayout();
    materia_editor_layout->addWidget(materia_editor);
    ui->editor_box->setLayout(materia_editor_layout);

    char_editor = new CharEditor();
    QHBoxLayout * char_editor_layout = new QHBoxLayout();
    char_editor_layout->addWidget(char_editor);
    ui->charEditor_box->setLayout(char_editor_layout);

    item_list = new ItemList();
    QHBoxLayout *item_list_layout = new QHBoxLayout;
    item_list_layout->addWidget(item_list);
    ui->item_list_box->setLayout(item_list_layout);

    locViewer = new LocationViewer(this);
    QHBoxLayout *locLayout = new QHBoxLayout();
    locLayout->addWidget(locViewer);
    ui->innerLocBox->setLayout(locLayout);

    chocoboManager = new ChocoboManager();
    QHBoxLayout *ChocoboManagerLayout = new QHBoxLayout();
    ChocoboManagerLayout->addWidget(chocoboManager);
    ui->ChocoboManagerBox->setLayout(ChocoboManagerLayout);
    chocoboManager->setHoverStyle(QString("rgba(96,135,192,128);"));
}

MainWindow::~MainWindow(){delete ui;}

void MainWindow::on_combo_widget_currentIndexChanged(int index)
{
    hideAllBoxes();
    switch(index)
    {
        case 1:ui->dialog_preview_box->setVisible(1); break;
        case 2:ui->materia_editor_box->setVisible(1); break;
        case 3:ui->item_list_box->setVisible(1);break;
        case 4:ui->char_editor_box->setVisible(1); break;
        case 5:ui->metadata_box->setVisible(1);break;
        case 6:ui->slotSelect_Box->setVisible(1);break;
        case 7:ui->phsListBox->setVisible(1);break;
        case 8:ui->menuListBox->setVisible(1);break;
        case 9:ui->lgp_Box->setVisible(1);break;
        case 10:ui->locListBox->setVisible(1);break;
        case 11:ui->ChocoboManagerBox->setVisible(1);break;
    };
    this->adjustSize();
}

void MainWindow::on_sb_materia_editor_setStarSize_valueChanged(int size){materia_editor->setStarsSize(size);}
void MainWindow::on_cb_materia_editor_setEditable_toggled(bool checked){materia_editor->setEditable(checked);}
void MainWindow::on_cb_charEditor_clicked(bool checked){char_editor->setEditable(checked);}
void MainWindow::on_checkBox_toggled(bool checked){char_editor->setAdvancedMode(checked);}

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

void MainWindow::on_btn_lgpSelect_clicked()
{
    ui->listLgpFile->clear();
    QString fileName = QFileDialog::getOpenFileName(this,"Select Lgp Archive",QDir::homePath(),"Lgp Archive(*.lgp)");
    if(fileName.isEmpty()){return;}
    else
    {
        lgpFile = new Lgp(fileName);
        if(!lgpFile->open()){QMessageBox::information(this,"Error","Failed To Open Lgp Archive");}
        else
        {
            ui->listLgpFile->addItems(lgpFile->fileList());
            ui->lblLgpCompany->setText(QString("Company: %1").arg(lgpFile->companyName()));
            ui->lblLgpProduct->setText(QString("Product:%1").arg(lgpFile->productName()));
            QString title = fileName;
            title.remove(0,fileName.lastIndexOf("/")+1);
            title.append(QString (" (%1 files)").arg(lgpFile->fileList().count()));
            ui->groupLgpView->setTitle(title);
            ui->groupLgpView->setVisible(true);
        }
    }
}
void MainWindow::on_btnExtractLgp_clicked()
{
    QString extPath = QFileDialog::getExistingDirectory(this,"Select Path To Extract Files",QDir::homePath());
    if(extPath.isEmpty()){return;}
    else
    {
        for(int i=0;i<ui->listLgpFile->count();i++)
        {
            QString fileName = extPath;
            fileName.append(QString("/%1").arg(lgpFile->fileList().at(i)));
            QFile file(fileName);
            if(!file.open(QFile::WriteOnly)){return;}
            else
            {
                file.write(lgpFile->fileData(lgpFile->fileList().at(i)));
                file.close();
            }
        }
        QMessageBox::information(this,"Lgp Utility",QString("Extracted %1 File(s).").arg(lgpFile->fileList().count()));
    }
}
void MainWindow::hideAllBoxes(void)
{
    ui->dialog_preview_box->setVisible(0);
    ui->materia_editor_box->setVisible(0);
    ui->char_editor_box->setVisible(0);
    ui->item_list_box->setVisible(0);
    ui->metadata_box->setVisible(0);
    ui->slotSelect_Box->setVisible(0);
    ui->phsListBox->setVisible(0);
    ui->menuListBox->setVisible(0);
    ui->lgp_Box->setVisible(0);
    ui->groupLgpView->setVisible(0);
    ui->locListBox->setVisible(0);
    ui->ChocoboManagerBox->setVisible(0);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    locViewer->setSelected(arg1);
}

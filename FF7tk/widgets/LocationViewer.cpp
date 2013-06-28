/****************************************************************************/
//    copyright 2013  Chris Rizzitello <sithlord48@gmail.com>               //
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
#include "LocationViewer.h"

LocationViewer::LocationViewer(QWidget *parent) :  QWidget(parent)
{
    Locations = new FF7Location();
    init_display();
    init_connections();
}

void LocationViewer::setAdvancedMode(bool AdvancedMode)
{
    advancedMode = AdvancedMode;
    if(advancedMode)
    {
        //Show Advanced Items and data..
    }
    else
    {
        //Hide Advanced Items and data
    }
}
void LocationViewer::init_display(void)
{
    lblLocationPreview = new QLabel;
    lblLocationPreview->setFixedSize(300,300);
    QTableWidgetItem *newItem;

    //create and fill location list.
    locationTable = new QTableWidget;
    locationTable->setColumnCount(3);
    locationTable->setRowCount(Locations->len());
    locationTable->verticalHeader()->setHidden(true);
    locationTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    locationTable->setSortingEnabled(true);

    newItem = new QTableWidgetItem(tr("filename"),0);
    locationTable->setHorizontalHeaderItem(0,newItem);
    locationTable->setColumnWidth(0,80);
    newItem = new QTableWidgetItem(tr("Location String"),0);
    locationTable->setHorizontalHeaderItem(1,newItem);
    locationTable->setColumnWidth(1,160);
    newItem = new QTableWidgetItem(tr("Loc Id"),0);
    locationTable->setHorizontalHeaderItem(2,newItem);
    locationTable->setColumnWidth(2,50);
    locationTable->setMinimumWidth(310);

    for (int i=0;i<locationTable->rowCount();i++)
    {
        //set the tooltip to the needed file
        QString tooltip(QString("<html><head/><body><p><img src=\":/locations/%1_%2\"/></p></body></html>").arg(Locations->mapID(i),Locations->locationID(i)));

        newItem = new QTableWidgetItem(Locations->fileName(i),0);
        newItem->setFlags(newItem->flags()&=~Qt::ItemIsEditable);
        newItem->setToolTip(tooltip);
        locationTable->setItem(i,0,newItem);

        newItem = new QTableWidgetItem(Locations->locationString(i),0);
        newItem->setFlags(newItem->flags()&=~Qt::ItemIsEditable);
        newItem->setToolTip(tooltip);
        locationTable->setItem(i,1,newItem);

        newItem = new QTableWidgetItem(Locations->locationID(i),0);
        newItem->setFlags(newItem->flags()&=~Qt::ItemIsEditable);
        newItem->setTextAlignment(Qt::AlignHCenter);
        locationTable->setItem(i,2,newItem);
    }
    locationTable->adjustSize();
    QHBoxLayout *FinalLayout = new QHBoxLayout;
    FinalLayout->setContentsMargins(0,0,0,0);
    FinalLayout->addWidget(locationTable);
    FinalLayout->addWidget(lblLocationPreview);
    this->setLayout(FinalLayout);
    this->adjustSize();
}
void LocationViewer::init_connections(void)
{
    connect(locationTable,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(itemChanged(int,int,int,int)));
}
void LocationViewer::itemChanged(int currentRow, int currentColumn, int prevRow, int prevColumn)
{
    if(currentColumn == prevColumn){/*do nothing*/} //stop non use warning
    if(currentRow ==prevRow){return;}
    else
    {
        lblLocationPreview->setPixmap(QString("://locations/%1_%2").arg(Locations->mapID(locationTable->item(currentRow,0)->text()),Locations->locationID(locationTable->item(currentRow,0)->text())));
    }
    lblLocationPreview->adjustSize();
}

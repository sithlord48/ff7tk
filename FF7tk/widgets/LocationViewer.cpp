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
    locationTable->setSelectionMode(QAbstractItemView::SingleSelection);
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

    lineLocationName = new QLineEdit;
    lineLocationName->setPlaceholderText(tr("Location Name"));

    sbMapID = new QSpinBox;
    sbMapID->setMaximum(9);
    //setMax when varified
    sbMapID->setWrapping(true);
    sbMapID->setPrefix(tr("MapID: "));
    sbMapID->setAlignment(Qt::AlignCenter);

    sbLocID = new QSpinBox;
    sbLocID->setMaximum(786);
    sbLocID->setWrapping(true);
    sbLocID->setPrefix(tr("LocID:"));
    sbLocID->setAlignment(Qt::AlignCenter);


    sbX= new QSpinBox;
    sbX->setPrefix(tr("X: "));
    sbX->setMinimum(-32767);
    sbX->setMaximum(32767);
    sbX->setWrapping(true);
    sbX->setAlignment(Qt::AlignCenter);


    sbY= new QSpinBox;
    sbY->setPrefix(tr("Y: "));
    sbY->setMinimum(-32767);
    sbY->setMaximum(32767);
    sbY->setWrapping(true);
    sbY->setAlignment(Qt::AlignCenter);

    sbT= new QSpinBox;
    sbT->setPrefix(tr("T: "));
    sbT->setMaximum(65565);
    sbT->setWrapping(true);
    sbT->setAlignment(Qt::AlignCenter);

    sbD = new QSpinBox;
    sbD->setMaximum(255);
    sbD->setPrefix(tr("D: "));
    sbD->setWrapping(true);
    sbD->setAlignment(Qt::AlignCenter);

    QHBoxLayout *nameIDs = new QHBoxLayout;
    nameIDs->addWidget(lineLocationName);
    nameIDs->addWidget(sbMapID);
    nameIDs->addWidget(sbLocID);

    QHBoxLayout *XYTD = new QHBoxLayout;
    XYTD->addWidget(sbX);
    XYTD->addWidget(sbY);
    XYTD->addWidget(sbT);
    XYTD->addWidget(sbD);

    QVBoxLayout *CoordsLayout = new QVBoxLayout;
    CoordsLayout->addLayout(nameIDs);
    CoordsLayout->addLayout(XYTD);

    QVBoxLayout *RightSideLayout = new QVBoxLayout;
    RightSideLayout->setContentsMargins(0,0,0,0);
    RightSideLayout->addWidget(lblLocationPreview);
    RightSideLayout->addLayout(CoordsLayout);

    QHBoxLayout *FinalLayout = new QHBoxLayout;
    FinalLayout->setContentsMargins(0,0,0,0);
    FinalLayout->addWidget(locationTable);
    FinalLayout->addLayout(RightSideLayout);
    this->setLayout(FinalLayout);
    this->adjustSize();
}
void LocationViewer::init_connections(void)
{
    connect(locationTable,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(itemChanged(int,int,int,int)));
    connect(sbMapID,SIGNAL(valueChanged(int)),this,SLOT(sbMapIdChanged(int)));
    connect(sbLocID,SIGNAL(valueChanged(int)),this,SLOT(sbLocIdChanged(int)));
    connect(sbX,SIGNAL(valueChanged(int)),this,SLOT(sbXChanged(int)));
    connect(sbY,SIGNAL(valueChanged(int)),this,SLOT(sbYChanged(int)));
    connect(sbT,SIGNAL(valueChanged(int)),this,SLOT(sbTChanged(int)));
    connect(sbD,SIGNAL(valueChanged(int)),this,SLOT(sbDChanged(int)));
}


void LocationViewer::init_disconnect(void)
{
    disconnect(locationTable,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(itemChanged(int,int,int,int)));
    disconnect(sbMapID,SIGNAL(valueChanged(int)),this,SLOT(sbMapIdChanged(int)));
    disconnect(sbLocID,SIGNAL(valueChanged(int)),this,SLOT(sbLocIdChanged(int)));
    disconnect(sbX,SIGNAL(valueChanged(int)),this,SLOT(sbXChanged(int)));
    disconnect(sbY,SIGNAL(valueChanged(int)),this,SLOT(sbYChanged(int)));
    disconnect(sbT,SIGNAL(valueChanged(int)),this,SLOT(sbTChanged(int)));
    disconnect(sbD,SIGNAL(valueChanged(int)),this,SLOT(sbDChanged(int)));
}

void LocationViewer::itemChanged(int currentRow, int currentColumn, int prevRow, int prevColumn)
{
    if(currentColumn == prevColumn){/*do nothing*/} //stop non use warning
    if(currentRow ==prevRow){return;}
    else
    {
        int mapID = Locations->mapID(locationTable->item(currentRow,0)->text()).toInt();
        int locID= Locations->locationID(locationTable->item(currentRow,0)->text()).toInt();
        setLocation(mapID,locID);
        emit(locationChanged(Locations->fileName(mapID,locID)));
    }
    lblLocationPreview->adjustSize();
}
void LocationViewer::setSelected(QString locFilename)
{
    for(int i=0;i<Locations->len();i++)
    {
        if(locationTable->item(i,0)->text()== locFilename)
        {
            locationTable->setCurrentItem(locationTable->item(i,0));
        }
    }
}
void LocationViewer::sbMapIdChanged(int mapId)
{
    setLocation(mapId,sbLocID->value());
    emit(mapIdChanged(mapId));
}

void LocationViewer::sbLocIdChanged(int locId)
{
    setLocation(sbMapID->value(),locId);
    emit(locIdChanged(locId));
}

void LocationViewer::sbXChanged(int x){emit(xChanged(x));}
void LocationViewer::sbYChanged(int y){emit(yChanged(y));}
void LocationViewer::sbTChanged(int t){emit(tChanged(t));}
void LocationViewer::sbDChanged(int d){emit(dChanged(d));}

void LocationViewer::setLocation(int mapId,int locId)
{
    init_disconnect();
    QString fileName = Locations->fileName(mapId,locId);
    lblLocationPreview->setPixmap(QString("://locations/%1_%2").arg(QString::number(mapId),QString::number(locId)));
    if(fileName.isEmpty()){}
    else
    {
        lineLocationName->setText(Locations->locationString(fileName));
        sbMapID->setValue(Locations->mapID(fileName).toInt());
        sbLocID->setValue(Locations->locationID(fileName).toInt());
        sbX->setValue(Locations->x(fileName).toInt());
        sbY->setValue(Locations->y(fileName).toInt());
        sbT->setValue(Locations->t(fileName).toInt());
        sbD->setValue(Locations->d(fileName).toInt());
    }
    init_connections();
}

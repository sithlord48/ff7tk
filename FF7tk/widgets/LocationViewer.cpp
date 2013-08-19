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

#include "../static_data/icons/Common_Icons/delete.xpm"

LocationViewer::LocationViewer(QWidget *parent) :  QWidget(parent)
{
    region="";
    transBasePath="";
    regExpSearch=false;
    caseSensitive=false;
    Locations = new FF7Location();
    fItems= new FF7FieldItemList();
    init_display();
    init_connections();
}
void LocationViewer::resizeEvent(QResizeEvent *ev)
{
    if(ev->type()==QResizeEvent::Resize){/*Stop Warning*/}
    QPixmap pix(QString("://locations/%1_%2").arg(QString::number(sbMapID->value()),QString::number(sbLocID->value())));
    if(pix.isNull()){return;}
    else{lblLocationPreview->setPixmap(pix.scaled(lblLocationPreview->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));}
}

void LocationViewer::init_display(void)
{
    lblLocationPreview = new QLabel;
    lblLocationPreview->setMinimumSize(320,240);
    lblLocationPreview->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QTableWidgetItem *newItem;

    //create and fill location list.

    locationTable = new QTableWidget;
    locationTable->setColumnCount(3);
    locationTable->setRowCount(Locations->len());
    locationTable->verticalHeader()->setHidden(true);
    locationTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    locationTable->setSelectionMode(QAbstractItemView::SingleSelection);
    locationTable->setSortingEnabled(true);

    newItem = new QTableWidgetItem(tr("Filename"),0);
    locationTable->setHorizontalHeaderItem(0,newItem);
    locationTable->setColumnWidth(0,font().pointSize()*8);

    newItem = new QTableWidgetItem(tr("Location Name"),0);
    locationTable->setHorizontalHeaderItem(1,newItem);
    locationTable->setColumnWidth(1,font().pointSize()*24);
    newItem = new QTableWidgetItem(tr("LocID"),0);
    locationTable->setHorizontalHeaderItem(2,newItem);
    locationTable->setColumnWidth(2,font().pointSize()*6);

    for (int i=0;i<locationTable->rowCount();i++)
    {
        //set the tooltip to the needed file
        QString tooltip(QString("<html><head/><body><p><img src=\":/locations/%1_%2\"/></p></body></html>").arg(Locations->mapID(i),Locations->locationID(i)));

        newItem = new QTableWidgetItem(Locations->fileName(i),0);
        newItem->setFlags(newItem->flags()&=~Qt::ItemIsEditable);
        newItem->setToolTip(tooltip);
        newItem->setTextAlignment(Qt::AlignLeft);
        locationTable->setItem(i,0,newItem);

        newItem = new QTableWidgetItem(Locations->locationString(i),0);
        newItem->setFlags(newItem->flags()&=~Qt::ItemIsEditable);
        newItem->setTextAlignment(Qt::AlignLeft);
        newItem->setToolTip(tooltip);
        locationTable->setItem(i,1,newItem);

        //To Assure proper numerical sorting of location IDs they should all contain the same number of characters.
        newItem = new QTableWidgetItem(QString("%1").arg(Locations->locationID(i).toInt(),3,10,QChar('0')).toUpper());//Pad so at least 3 chars. Leading 0's
        newItem->setFlags(newItem->flags()&=~Qt::ItemIsEditable);
        newItem->setTextAlignment(Qt::AlignHCenter);
        locationTable->setItem(i,2,newItem);
        locationTable->setRowHeight(i,font().pointSizeF()*2+2);
    }
    locationTable->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    locationTable->setFixedWidth(locationTable->columnWidth(0)+locationTable->columnWidth(1)+locationTable->columnWidth(2)+locationTable->verticalScrollBar()->widthMM()-6);
    locationTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    locationTable->setCurrentCell(-1,-1);

    btnSearchOptions = new QToolButton;
    btnSearchOptions->setIcon(QIcon(QPixmap(delete_xpm)));
    btnSearchOptions->setPopupMode(QToolButton::MenuButtonPopup);

    actionRegExpSearch = new QAction(tr("Process Regular Expressions"),btnSearchOptions);
    actionRegExpSearch->setCheckable(true);

    actionCaseSensitive = new QAction(tr("Case Sensitive"),btnSearchOptions);
    actionCaseSensitive->setCheckable(true);

    QMenu * newMenu=new QMenu;
    newMenu->addAction(actionRegExpSearch);
    newMenu->addAction(actionCaseSensitive);

    btnSearchOptions->setMenu(newMenu);
    btnSearchOptions->setFixedWidth(36);

    lineTableFilter = new QLineEdit;
    lineTableFilter->setFixedWidth( locationTable->width() - btnSearchOptions->width());
    lineTableFilter->setPlaceholderText(tr("Location Filter..."));

    lineLocationName = new QLineEdit;
    lineLocationName->setPlaceholderText(tr("Location Name"));

    sbMapID = new QSpinBox;
    //sbMapID->setMaximum(3);
    //setMax when varified
    sbMapID->setWrapping(true);
    sbMapID->setPrefix(tr("MapID: "));
    sbMapID->setAlignment(Qt::AlignCenter);

    sbLocID = new QSpinBox;
    sbLocID->setMaximum(786);
    sbLocID->setWrapping(true);
    sbLocID->setPrefix(tr("LocID: "));
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

    fItemList = new QListWidget();
    fItemList->setFixedHeight(0);
    fItemList->setUniformItemSizes(true);
    fItemList->setSelectionMode(QAbstractItemView::NoSelection);

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
    CoordsLayout->setContentsMargins(6,6,6,6);
    CoordsLayout->addLayout(nameIDs);
    CoordsLayout->addLayout(XYTD);

    QHBoxLayout *PreviewLayout = new QHBoxLayout;
    PreviewLayout->setAlignment(Qt::AlignCenter);
    PreviewLayout->addWidget(lblLocationPreview);

    QHBoxLayout *FilterLayout = new QHBoxLayout;
    FilterLayout->addWidget(btnSearchOptions);
    FilterLayout->addWidget(lineTableFilter);

    QVBoxLayout *LeftSideLayout = new QVBoxLayout;
    LeftSideLayout->setSpacing(0);
    LeftSideLayout->addWidget(locationTable);
    LeftSideLayout->addLayout(FilterLayout);

    QVBoxLayout *RightSideLayout = new QVBoxLayout;
    RightSideLayout->addLayout(CoordsLayout);
    RightSideLayout->addLayout(PreviewLayout);
    RightSideLayout->addWidget(fItemList);

    QHBoxLayout *FinalLayout = new QHBoxLayout;
    FinalLayout->setContentsMargins(6,6,6,6);
    FinalLayout->addLayout(LeftSideLayout);
    FinalLayout->addLayout(RightSideLayout);
    this->setLayout(FinalLayout);
    this->adjustSize();
}
void LocationViewer::init_connections(void)
{
    connect(locationTable,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(itemChanged(int,int,int,int)));
    connect(lineTableFilter,SIGNAL(textChanged(QString)),this,SLOT(filterLocations(QString)));
    connect(btnSearchOptions,SIGNAL(clicked()),this,SLOT(btnSearchOptionsClicked()));
    connect(actionRegExpSearch,SIGNAL(toggled(bool)),this,SLOT(actionRegExpSearchToggled(bool)));
    connect(actionCaseSensitive,SIGNAL(toggled(bool)),this,SLOT(actionCaseSensitiveToggled(bool)));
    connect(sbMapID,SIGNAL(valueChanged(int)),this,SLOT(sbMapIdChanged(int)));
    connect(sbLocID,SIGNAL(valueChanged(int)),this,SLOT(sbLocIdChanged(int)));
    connect(sbX,SIGNAL(valueChanged(int)),this,SLOT(sbXChanged(int)));
    connect(sbY,SIGNAL(valueChanged(int)),this,SLOT(sbYChanged(int)));
    connect(sbT,SIGNAL(valueChanged(int)),this,SLOT(sbTChanged(int)));
    connect(sbD,SIGNAL(valueChanged(int)),this,SLOT(sbDChanged(int)));
    connect(lineLocationName,SIGNAL(textChanged(QString)),this,SLOT(lineLocationNameChanged(QString)));
    connect(fItemList,SIGNAL(clicked(QModelIndex)),this,SLOT(fItemChanged(QModelIndex)));
}
void LocationViewer::init_disconnect(void)
{
    disconnect(locationTable,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(itemChanged(int,int,int,int)));
    disconnect(lineTableFilter,SIGNAL(textChanged(QString)),this,SLOT(filterLocations(QString)));
    disconnect(actionRegExpSearch,SIGNAL(toggled(bool)),this,SLOT(actionRegExpSearchToggled(bool)));
    disconnect(actionCaseSensitive,SIGNAL(toggled(bool)),this,SLOT(actionCaseSensitiveToggled(bool)));
    disconnect(sbMapID,SIGNAL(valueChanged(int)),this,SLOT(sbMapIdChanged(int)));
    disconnect(sbLocID,SIGNAL(valueChanged(int)),this,SLOT(sbLocIdChanged(int)));
    disconnect(sbX,SIGNAL(valueChanged(int)),this,SLOT(sbXChanged(int)));
    disconnect(sbY,SIGNAL(valueChanged(int)),this,SLOT(sbYChanged(int)));
    disconnect(sbT,SIGNAL(valueChanged(int)),this,SLOT(sbTChanged(int)));
    disconnect(sbD,SIGNAL(valueChanged(int)),this,SLOT(sbDChanged(int)));
    disconnect(lineLocationName,SIGNAL(textChanged(QString)),this,SLOT(lineLocationNameChanged(QString)));
    disconnect(fItemList,SIGNAL(clicked(QModelIndex)),this,SLOT(fItemChanged(QModelIndex)));
}

void LocationViewer::itemChanged(int currentRow, int currentColumn, int prevRow, int prevColumn)
{
    if(currentColumn == prevColumn){/*do nothing*/} //stop non use warning
    if(currentRow ==0 and currentColumn ==0){return;}//return on selection cleared.
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
    locationTable->clearSelection();
    for(int i=0;i<Locations->len();i++)
    {
        if(locationTable->item(i,0)->text()== locFilename)
        {
            locationTable->setCurrentItem(locationTable->item(i,0));
            break;
        }
    }
}
void LocationViewer::sbMapIdChanged(int mapId)
{
    setLocation(mapId,sbLocID->value());
    QString fileName = Locations->fileName(mapId,sbLocID->value());
    if(fileName.isEmpty()){emit(mapIdChanged(mapId));}
    else{emit(locationChanged(fileName));}
}
void LocationViewer::sbLocIdChanged(int locId)
{
    setLocation(sbMapID->value(),locId);
    QString fileName = Locations->fileName(sbMapID->value(),locId);
    if(fileName.isEmpty()){emit(locIdChanged(locId));}
    else{emit(locationChanged(fileName));}
}
void LocationViewer::sbXChanged(int x){emit(xChanged(x));}
void LocationViewer::sbYChanged(int y){emit(yChanged(y));}
void LocationViewer::sbTChanged(int t){emit(tChanged(t));}
void LocationViewer::sbDChanged(int d){emit(dChanged(d));}
void LocationViewer::setLocation(int mapId,int locId)
{
    init_disconnect();
    QString fileName = Locations->fileName(mapId,locId);
    setSelected(fileName);

    if(fileName.isEmpty()){lblLocationPreview->setPixmap(QString(""));}
    else
    {
        qWarning()<<"Loading Map:"<<fileName;
        lblLocationPreview->setPixmap(QPixmap(QString("://locations/%1_%2").arg(QString::number(mapId),QString::number(locId))).scaled(lblLocationPreview->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));

        QString oldStr = Locations->locationString(fileName);
        QString newStr = translate(oldStr);
        if(oldStr !=newStr){emit(locationStringChanged(newStr));}
        sbMapID->setValue(Locations->mapID(fileName).toInt());
        sbLocID->setValue(Locations->locationID(fileName).toInt());
        sbX->setValue(Locations->x(fileName).toInt());
        sbY->setValue(Locations->y(fileName).toInt());
        sbT->setValue(Locations->t(fileName).toInt());
        sbD->setValue(Locations->d(fileName).toInt());
        lineLocationName->setText(newStr);
        init_fItems();
    }
    init_connections();
}
void LocationViewer::lineLocationNameChanged(QString locName){emit(locationStringChanged(locName));}
void LocationViewer::setX(int x){init_disconnect();sbX->setValue(x);init_connections();}
void LocationViewer::setY(int y){init_disconnect();sbY->setValue(y);init_connections();}
void LocationViewer::setT(int t){init_disconnect();sbT->setValue(t);init_connections();}
void LocationViewer::setD(int d){init_disconnect();sbD->setValue(d);init_connections();}
void LocationViewer::setMapId(int mapId){sbMapID->setValue(mapId);}
void LocationViewer::setLocationId(int locId){sbLocID->setValue(locId);}
void LocationViewer::setLocationString(QString locString)
{
    init_disconnect();
    QString newStr = translate(locString);
    if(locString !=newStr){emit(locationStringChanged(newStr));}
    lineLocationName->setText(newStr);
    init_connections();
}
void LocationViewer::setHorizontalHeaderStyle(QString styleSheet){locationTable->horizontalHeader()->setStyleSheet(styleSheet);}
void LocationViewer::setRegion(QString newRegion){region=newRegion;setLocation(sbMapID->value(),sbLocID->value());}
void LocationViewer::setTranslationBaseFile(QString basePathName){transBasePath= basePathName;}
QString LocationViewer::translate(QString text)
{
    if(region ==""){qWarning()<<"Translate: No Region";return text;}
    if(transBasePath==""){qWarning()<<"Translate: No Base Path";return text;}
    else
    {
        QString lang = transBasePath;
        QTranslator Translator;// will do the translating.
        QString reg = region;// remove trailing  FF7-SXX
        reg.chop(7);
        if(reg =="BASCUS-94163" || reg =="BESCES-00867"){lang.append("en.qm");}
        else if(reg =="BESCES-00868"){lang.append("fr.qm");}
        else if(reg =="BESCES-00869"){lang.append("de.qm");}
        else if(reg =="BESCES-00900"){lang.append("es.qm");}
        else if(reg =="BISLPS-00700" || reg =="BISLPS-01057"){lang.append("ja.qm");}
        else{qWarning()<<QString("Unknown Region:%1").arg(reg);return text;}//unknown language.
        Translator.load(lang);
        QString newText = Translator.translate("Locations",text.toUtf8());
        if(newText.isEmpty()){return text;}
        else{return newText;}
    }
}
void LocationViewer::filterLocations(QString filter)
{
    QRegExp exp(filter);

    if(regExpSearch){exp.setPatternSyntax(QRegExp::Wildcard);}
    else{exp.setPatternSyntax(QRegExp::FixedString);}
    if(caseSensitive){exp.setCaseSensitivity(Qt::CaseSensitive);}
    else{exp.setCaseSensitivity(Qt::CaseInsensitive);}

    for(int i=0;i<locationTable->rowCount();i++)
    {
        bool hidden=true;
        for (int j=0;j<locationTable->columnCount();j++)
        {
            if(locationTable->item(i,j)->text().contains(exp)){hidden=false;break;}
        }
        locationTable->setRowHidden(i,hidden);
    }
}
void LocationViewer::btnSearchOptionsClicked(){lineTableFilter->clear();}
void LocationViewer::actionRegExpSearchToggled(bool checked)
{   
    regExpSearch=checked;
    if(lineTableFilter->text().isEmpty()){return;}
    else{filterLocations(lineTableFilter->text());}
}
void LocationViewer::actionCaseSensitiveToggled(bool checked)
{
    caseSensitive=checked;
    if(lineTableFilter->text().isEmpty()){return;}
    else{filterLocations(lineTableFilter->text());}
}

void LocationViewer::init_fItems(void)
{
    fItemList->clear(); 
    for(int i=0;i<fItems->count();i++)
    {
        for(int j=0;j<fItems->maps(i).count();j++)
        {
            if(fItems->maps(i).at(j)== locationTable->item(locationTable->currentRow(),0)->text())
            {
                QListWidgetItem *newItem = new QListWidgetItem(fItems->text(i));
                newItem->setCheckState(Qt::Unchecked);
                fItemList->addItem(newItem);
                //Some Emit Needed Here, used to connect to data
                //this output does not account for items that set more then one bit (on same of different offsets)
                //this output also does not consider cases where an item is shown on more then one map with same offset and bit used for each map
                if( (fItems->offset(i).count()==1) && (fItems->bit(i).count()==1) && (fItems->maps(i).count()==1))
                {
                    qWarning()<<"Emit "<< QString("Item:%1 -> Offset:0x%2 Bit:%3")
                                .arg(QString::number(fItemList->count()-1),QString::number(fItems->offset(i).at(j),16).toUpper(),QString::number(fItems->bit(i).at(j)));
                    emit fItemConnectRequest(fItemList->count()-1,fItems->offset(i).at(j),fItems->bit(i).at(j));
                }
                else
                {
                    if(fItems->offset(i).count() == fItems->bit(i).count())
                    {
                        for(int k=0;k<fItems->offset(i).count();k++)
                        {
                            qWarning()<<QString("Item:%1 -> Offset:0x%2 Bit:%3")
                             .arg(QString::number(fItemList->count()-1),QString::number(fItems->offset(i).at(k),16).toUpper(),QString::number(fItems->bit(i).at(k)));
                            emit fItemConnectRequest(fItemList->count()-1,fItems->offset(i).at(k),fItems->bit(i).at(k));
                        }
                    }
                    else
                    {
                        qWarning()<<QString("Item:%1 -> Special Case").arg(QString::number(fItemList->count()-1));
                    }
                }
                //emit to check the item
                emit fItemCheck(fItemList->count()-1);
                qWarning()<<"Checked Item:"<<QString::number(fItemList->count()-1);
            }
        }        
    }
    if(fItemList->count()<=0){fItemList->setFixedHeight(0);}
    else if(fItemList->count()<5)
    {
        fItemList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);       
        fItemList->setFixedHeight((locationTable->rowHeight(0) *fItemList->count())+6);
        fItemList->viewport()->setFixedHeight(fItemList->height()-4);
    }
    else if(fItemList->count()==5)
    {
        fItemList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        fItemList->setFixedHeight((locationTable->rowHeight(0) *5)+9);
        fItemList->viewport()->setFixedHeight(fItemList->height()-4);
    }
    else
    {
        fItemList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        fItemList->setFixedHeight((locationTable->rowHeight(0)*5)+9);
        fItemList->viewport()->setFixedHeight((locationTable->rowHeight(0)*fItemList->count())+5);
    }
    qWarning()<<"ItemBox Height:"<<QString::number(fItemList->size().height());
    //need to check save data and mark the stuff that is picked up
}
void LocationViewer::fItemChanged(QModelIndex index)
{
    qWarning()<<QString("Item:%1 Changed").arg(QString::number(index.row()));
}
void LocationViewer::setFieldItemChecked(int row,bool checked)
{
    if(fItemList->count()>row)
    {
        if(checked){fItemList->item(row)->setCheckState(Qt::Checked);}
        else{fItemList->item(row)->setCheckState(Qt::Unchecked);}
    }
}

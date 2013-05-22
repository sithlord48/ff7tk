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
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "ChocoboManager.h"

ChocoboManager::ChocoboManager(QWidget *parent) :
    QWidget(parent)
{
    initDisplay();
    initData();
    initConnections();
}
void ChocoboManager::initDisplay(void)
{
    lblStablesOwned = new QLabel(QString(tr("Stables Owned")));
    sbStablesOwned = new QSpinBox;
    sbStablesOwned->setMaximum(6);
    sbStablesOwned->setWrapping(true);
    lblStablesOccupied = new QLabel(QString(tr("Stables Occupied")));
    lcdStablesOccupied = new QLCDNumber;
    lcdStablesOccupied->setSegmentStyle(QLCDNumber::Flat);

    QHBoxLayout *ownedLayout = new QHBoxLayout();
    ownedLayout->setContentsMargins(0,0,0,0);
    ownedLayout->addWidget(lblStablesOwned);
    ownedLayout->addWidget(sbStablesOwned);

    QHBoxLayout *occupiedLayout = new QHBoxLayout();
    occupiedLayout->setContentsMargins(0,0,0,0);
    occupiedLayout->addWidget(lblStablesOccupied);
    occupiedLayout->addWidget(lcdStablesOccupied);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(0,0,0,0);
    topLayout->addLayout(ownedLayout);
    topLayout->addLayout(occupiedLayout);

    QGridLayout *stableGridLayout =new QGridLayout();
    stableGridLayout->setContentsMargins(0,0,0,0);
    for(int i=0;i<6;i++)
    {
        chocoboLabel[i] = new ChocoboLabel(this,QString(tr("Stable:%1")).arg(QString::number(i+1)));
        chocoboLabel[i]->setObjectName(QString::number(i));
        stableGridLayout->addWidget(chocoboLabel[i],(i/2),(i%2),1,1,Qt::AlignCenter);
        chocoboLabel[i]->setEnabled(false);
    }
    chocoboEditor = new ChocoboEditor;
    stableGridLayout->addWidget(chocoboEditor,0,3,2,2);
    chocoboEditor->setEnabled(false);

    QVBoxLayout *finalLayout = new QVBoxLayout();
    finalLayout->addLayout(topLayout);
    finalLayout->addLayout(stableGridLayout);
    this->setLayout(finalLayout);
}
void ChocoboManager::initConnections()
{
    for(int i=0;i<6;i++)
    {
        connect(chocoboLabel[i],SIGNAL(copy()),this,SLOT(copy()));
        connect(chocoboLabel[i],SIGNAL(paste()),this,SLOT(paste()));
        connect(chocoboLabel[i],SIGNAL(remove()),this,SLOT(remove()));
        connect(chocoboLabel[i],SIGNAL(occupiedToggled(bool)),this,SLOT(occupiedToggled(bool)));
        connect(chocoboLabel[i],SIGNAL(clicked()),this,SLOT(clicked()));
    }
    connect(sbStablesOwned,SIGNAL(valueChanged(int)),this,SLOT(sbOwnedChanged(int)));
    connect(this,SIGNAL(setMode(bool)),chocoboEditor,SLOT(setAdvancedMode(bool)));
    connect(chocoboEditor,SIGNAL(nameChanged(QString)),this,SLOT(NameChange(QString)));
    connect(chocoboEditor,SIGNAL(sexChanged(quint8)),this,SLOT(SexChange(quint8)));
    connect(chocoboEditor,SIGNAL(typeChanged(quint8)),this,SLOT(TypeChange(quint8)));
    connect(chocoboEditor,SIGNAL(sprintChanged(quint16)),this,SLOT(SprintChanged(quint16)));
    connect(chocoboEditor,SIGNAL(mSprintChanged(quint16)),this,SLOT(MsprintChanged(quint16)));
    connect(chocoboEditor,SIGNAL(speedChanged(quint16)),this,SLOT(SpeedChanged(quint16)));
    connect(chocoboEditor,SIGNAL(mSpeedChanged(quint16)),this,SLOT(MspeedChanged(quint16)));
    connect(chocoboEditor,SIGNAL(staminaChanged(quint16)),this,SLOT(StaminaChanged(quint16)));
    connect(chocoboEditor,SIGNAL(accelChanged(quint8)),this,SLOT(AccelChanged(quint8)));
    connect(chocoboEditor,SIGNAL(coopChanged(quint8)),this,SLOT(CoopChanged(quint8)));
    connect(chocoboEditor,SIGNAL(intelligenceChanged(quint8)),this,SLOT(IntelligenceChanged(quint8)));
    connect(chocoboEditor,SIGNAL(personalityChanged(quint8)),this,SLOT(PersonalityChanged(quint8)));
    connect(chocoboEditor,SIGNAL(pCountChanged(quint8)),this,SLOT(PcountChanged(quint8)));
    connect(chocoboEditor,SIGNAL(winsChanged(quint8)),this,SLOT(WinsChanged(quint8)));
    connect(chocoboEditor,SIGNAL(cantMateChanged(bool)),this,SLOT(CantMateChanged(bool)));

}
void ChocoboManager::initData(void)
{
    stablesOwned=0;
    stablesOccupied=0;
    selectedStable=-1;
    for(int i=0;i<7;i++)
    {
        chocoboName[i] = QString("\xff\xff\xff\xff\xff\xff");
        chocoboStamina[i]=0;
        cantMate[i] = false;
        chocoboData[i].accel=0;
        chocoboData[i].coop=0;
        chocoboData[i].intelligence=0;
        chocoboData[i].maxspeed=0;
        chocoboData[i].maxsprintspd=0;
        chocoboData[i].pcount=0;
        chocoboData[i].personality=0;
        chocoboData[i].raceswon=0;
        chocoboData[i].sex=0;
        chocoboData[i].speed=0;
        chocoboData[i].sprintspd=0;
        chocoboData[i].type=0;
    }
}

void ChocoboManager::sbOwnedChanged(int value)
{
    if(value==stablesOwned){return;}
    else if(value<0 || value>6){return;}
    else
    {
        for(int i=0;i<6;i++){chocoboLabel[i]->setEnabled(false);}
        for(int i=0;i<value;i++){chocoboLabel[i]->setEnabled(true);}
        stablesOwned = value;
        emit(ownedChanged(value));
    }
}
void ChocoboManager::copy(void)
{
    int s=sender()->objectName().toInt();
    chocoboData[6]=chocoboData[s];
    chocoboName[6]=chocoboName[s];
    cantMate[6]=cantMate[s];
    chocoboStamina[6]=chocoboStamina[s];
}
void ChocoboManager::paste(void)
{
    int s=sender()->objectName().toInt();
    chocoboData[s]=chocoboData[6];
    chocoboName[s]=chocoboName[6];
    cantMate[s]=cantMate[6];
    chocoboStamina[s]=chocoboStamina[6];
    labelUpdate(s);
}
void ChocoboManager::remove(void)
{
    int s=sender()->objectName().toInt();
    chocoboName[s]=QString("\xff\xff\xff\xff\xff\xff");
    chocoboStamina[s]=0;
    cantMate[s]=false;
    chocoboData[s].accel=0;
    chocoboData[s].coop=0;
    chocoboData[s].intelligence=0;
    chocoboData[s].maxspeed=0;
    chocoboData[s].maxsprintspd=0;
    chocoboData[s].pcount=0;
    chocoboData[s].personality=0;
    chocoboData[s].raceswon=0;
    chocoboData[s].sex=0;
    chocoboData[s].speed=0;
    chocoboData[s].sprintspd=0;
    chocoboData[s].type=0;
}
void ChocoboManager::labelUpdate(int label)
{
    chocoboLabel[label]->setName(chocoboName[label]);
    chocoboLabel[label]->setSex(chocoboData[label].sex);
    chocoboLabel[label]->setRank(chocoboData[label].raceswon);
    chocoboLabel[label]->setType(chocoboData[label].type);
}
void ChocoboManager::occupiedToggled(bool occupied)
{
    int s=sender()->objectName().toInt();
    if(occupied){stableMask |= (1<<s);lcdStablesOccupied->display(lcdStablesOccupied->value()+1);}
    else{stableMask &= ~(1<<s);lcdStablesOccupied->display(lcdStablesOccupied->value()-1);}
    stablesOccupied=lcdStablesOccupied->value();

    emit(occupiedChanged(stablesOccupied));
    emit(stableMaskChanged(stableMask));
}
void ChocoboManager::setAdvancedMode(bool advanced){chocoboEditor->setAdvancedMode(advanced);}

void ChocoboManager::clicked()
{
    if(selectedStable ==-1){chocoboEditor->setEnabled(true);}
    selectedStable = sender()->objectName().toInt();
    chocoboEditor->SetChocobo(chocoboData[selectedStable],chocoboName[selectedStable],cantMate[selectedStable],chocoboStamina[selectedStable]);

    if(chocoboName[selectedStable].startsWith(QString("\xff\xff"))){return;}
    else{labelUpdate(selectedStable);}
}
void ChocoboManager::NameChange(QString name)
{
    if(name != chocoboName[selectedStable])
    {
        chocoboName[selectedStable]=name;
        labelUpdate(selectedStable);
        emit nameChanged(selectedStable,name);
    }
}
void ChocoboManager::SexChange(quint8 sex)
{
    if(sex!=chocoboData[selectedStable].sex)
    {
        chocoboData[selectedStable].sex=sex;
        labelUpdate(selectedStable);
        emit sexChanged(selectedStable,sex);
    }
}
void ChocoboManager::TypeChange(quint8 type)
{
    if(type!=chocoboData[selectedStable].type)
    {
        chocoboData[selectedStable].type=type;
        labelUpdate(selectedStable);
        emit typeChanged(selectedStable,type);
    }
}
void ChocoboManager::SprintChanged(quint16 sprint)
{
    if(sprint !=chocoboData[selectedStable].sprintspd)
    {
        chocoboData[selectedStable].sprintspd=sprint;
        emit(sprintChanged(selectedStable,sprint));
    }
}
void ChocoboManager::MsprintChanged(quint16 Msprint)
{
    if(Msprint !=chocoboData[selectedStable].maxsprintspd)
    {
        chocoboData[selectedStable].maxsprintspd=Msprint;
        emit(mSprintChanged(selectedStable,Msprint));
    }
}
void ChocoboManager::SpeedChanged(quint16 speed)
{
    if(speed !=chocoboData[selectedStable].speed)
    {
        chocoboData[selectedStable].speed=speed;
        emit(speedChanged(selectedStable,speed));
    }
}
void ChocoboManager::MspeedChanged(quint16 Mspeed)
{
    if(Mspeed !=chocoboData[selectedStable].maxspeed)
    {
        chocoboData[selectedStable].maxspeed=Mspeed;
        emit(mSpeedChanged(selectedStable,Mspeed));
    }
}
void ChocoboManager::StaminaChanged(quint16 stamina)
{
    if(stamina != chocoboStamina[selectedStable])
    {
        chocoboStamina[selectedStable]=stamina;
        emit(staminaChanged(selectedStable,stamina));
    }
}
void ChocoboManager::AccelChanged(quint8 accel)
{
    if(accel !=chocoboData[selectedStable].accel)
    {
        chocoboData[selectedStable].accel=accel;
        emit(accelChanged(selectedStable,accel));
    }
}

void ChocoboManager::CoopChanged(quint8 coop)
{
    if(coop !=chocoboData[selectedStable].coop)
    {
        chocoboData[selectedStable].coop=coop;
        emit(coopChanged(selectedStable,coop));
    }
}
void ChocoboManager::IntelligenceChanged(quint8 intelligence)
{
    if(intelligence !=chocoboData[selectedStable].intelligence)
    {
        chocoboData[selectedStable].intelligence=intelligence;
        emit(intelligenceChanged(selectedStable,intelligence));
    }
}
void ChocoboManager::PersonalityChanged(quint8 personality)
{
    if(personality !=chocoboData[selectedStable].personality)
    {
        chocoboData[selectedStable].personality=personality;
        emit(personalityChanged(selectedStable,personality));
    }
}
void ChocoboManager::PcountChanged(quint8 pCount)
{
    if(pCount !=chocoboData[selectedStable].pcount)
    {
        chocoboData[selectedStable].pcount=pCount;
        emit(pCountChanged(selectedStable,pCount));
    }
}
void ChocoboManager::WinsChanged(quint8 wins)
{
    if(wins !=chocoboData[selectedStable].raceswon)
    {
        chocoboData[selectedStable].raceswon=wins;
        labelUpdate(selectedStable);
        emit(winsChanged(selectedStable,wins));
    }
}
void ChocoboManager::CantMateChanged(bool cantmate)
{
    if(cantmate !=cantMate[selectedStable])
    {
        cantMate[selectedStable]=cantmate;
        emit(cantMateChanged(selectedStable,cantmate));
    }
}

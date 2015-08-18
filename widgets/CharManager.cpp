#include "CharManager.h"

CharManager::CharManager(qreal Scale,QWidget *parent) :
    QWidget(parent)
{
	scale=Scale;
    initDisplay();
    connectAll();
}

void CharManager::initDisplay(void)
{
    load= true;
    charData= new FF7Char;
    for(int i=0;i<3;i++)
    {
        comboParty[i] = new QComboBox();
        for (int j=0;j<11;j++)
        {
            comboParty[i]->addItem(charData->icon(j),charData->defaultName(j));
        }
        comboParty[i]->addItem("0x0B");
        comboParty[i]->addItem(tr("-Empty-"));
    }
    QHBoxLayout * partyLayout = new QHBoxLayout;
    partyLayout->setSpacing(0);
    partyLayout->setContentsMargins(0,0,0,0);
    partyLayout->addWidget(comboParty[0]);
    partyLayout->addWidget(comboParty[1]);
    partyLayout->addWidget(comboParty[2]);

    QGroupBox *partyBox =new QGroupBox(tr("Party Members"));
    partyBox->setLayout(partyLayout);

    tabWidget =new QTabWidget;
    for(int i=0;i<9;i++)
    {
		charEditor[i]= new CharEditor(scale);
        tabWidget->addTab(charEditor[i],QString("%1").arg(QString::number(i+1)));
    }

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(partyBox);
    mainLayout->addWidget(tabWidget);
    this->setLayout(mainLayout);
    load=false;
}
void CharManager::connectAll(void)
{
    connect(comboParty[0],SIGNAL(currentIndexChanged(int)),this,SLOT(party1Changed(int)));
    connect(comboParty[1],SIGNAL(currentIndexChanged(int)),this,SLOT(party2Changed(int)));
    connect(comboParty[2],SIGNAL(currentIndexChanged(int)),this,SLOT(party3Changed(int)));
}
void CharManager::disconnectAll(void)
{
    disconnect(comboParty[0],SIGNAL(currentIndexChanged(int)),this,SLOT(party1Changed(int)));
    disconnect(comboParty[1],SIGNAL(currentIndexChanged(int)),this,SLOT(party2Changed(int)));
    disconnect(comboParty[2],SIGNAL(currentIndexChanged(int)),this,SLOT(party3Changed(int)));
}
void CharManager::party1Changed(int index){if(!load){emit (comboParty1_changed(index));qWarning()<<QString("combo1:%1").arg(QString::number(index));}}
void CharManager::party2Changed(int index){if(!load){emit (comboParty2_changed(index));qWarning()<<QString("combo2:%1").arg(QString::number(index));}}
void CharManager::party3Changed(int index){if(!load){emit (comboParty3_changed(index));qWarning()<<QString("combo3:%1").arg(QString::number(index));}}

void CharManager::setParty(qint8 member1, qint8 member2, qint8 member3)
{
    load=true;
    comboParty[0]->setCurrentIndex(member1);
    comboParty[1]->setCurrentIndex(member2);
    comboParty[2]->setCurrentIndex(member3);
    load=false;
}

void CharManager::setChar(int charSlot, FF7CHAR Chardata,QString Processed_Name)
{
	if(charSlot>-1 && charSlot <9)
	{
		charEditor[charSlot]->setChar(Chardata,Processed_Name);
	}
}

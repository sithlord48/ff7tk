/****************************************************************************/
//    copyright 2015- 2019  Chris Rizzitello <sithlord48@gmail.com>         //
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
#include "CharManager.h"

CharManager::CharManager(qreal Scale, QWidget *parent) :
    QWidget(parent)
{
    scale = Scale;
    initDisplay();
    connectAll();
}

void CharManager::initDisplay(void)
{
    load = true;
    for (int i = 0; i < 3; i++) {
        comboParty[i] = new QComboBox();
        for (int j = 0; j < 11; j++)
            comboParty[i]->addItem(charData->icon(j), charData->defaultName(j));
        comboParty[i]->addItem("0x0B");
        comboParty[i]->addItem(tr("-Empty-"));
    }
    QHBoxLayout *partyLayout = new QHBoxLayout;
    partyLayout->setSpacing(0);
    partyLayout->setContentsMargins(0, 0, 0, 0);
    partyLayout->addWidget(comboParty[0]);
    partyLayout->addWidget(comboParty[1]);
    partyLayout->addWidget(comboParty[2]);

    QGroupBox *partyBox = new QGroupBox(tr("Party Members"));
    partyBox->setLayout(partyLayout);

    QVBoxLayout *charBox = new QVBoxLayout;
    for (int i = 0; i < 9; i++) {
        QPushButton *button = new QPushButton;
        button->setIcon(charData->icon(i));
        button->setIconSize(QSize(int(32 + scale), int(32 * scale)));
        button->setMaximumWidth(int(32 * scale));
        charBox->addWidget(button);
    }
    charEditor = new CharEditor(scale);

    QHBoxLayout *lowerBox = new QHBoxLayout;
    lowerBox->addLayout(charBox);
    lowerBox->addWidget(charEditor);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(partyBox);
    mainLayout->addLayout(lowerBox);
    this->setLayout(mainLayout);
    load = false;
}
void CharManager::connectAll(void)
{
    connect(comboParty[0], QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharManager::party1Changed);
    connect(comboParty[1], QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharManager::party2Changed);
    connect(comboParty[2], QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharManager::party3Changed);

}
void CharManager::disconnectAll(void)
{
    disconnect(comboParty[0], QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharManager::party1Changed);
    disconnect(comboParty[1], QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharManager::party2Changed);
    disconnect(comboParty[2], QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharManager::party3Changed);
}
void CharManager::party1Changed(int index)
{
    if (!load)
        emit(comboParty1_changed(qint8(index)));
}
void CharManager::party2Changed(int index)
{
    if (!load)
        emit(comboParty2_changed(qint8(index)));
}
void CharManager::party3Changed(int index)
{
    if (!load)
        emit(comboParty3_changed(qint8(index)));
}

void CharManager::setParty(qint8 member1, qint8 member2, qint8 member3)
{
    load = true;
    comboParty[0]->setCurrentIndex(member1);
    comboParty[1]->setCurrentIndex(member2);
    comboParty[2]->setCurrentIndex(member3);
    load = false;
}

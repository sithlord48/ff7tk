//    SPDX-FileCopyrightText: 2013 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <ChocoboManager.h>

#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QSpinBox>

void ChocoboManager::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        lblStablesOwned ->setText(tr("Stables Owned"));
        lblStablesOccupied->setText(tr("Stables Occupied"));
        penBox->setTitle(tr("Fenced Chocobos"));
        updateCombos();
        for (int i = 0; i < 6; i++)
            chocoboLabel[i]->setTitle(tr("Stable:%1").arg(QString::number(i + 1)));
    } else if (e->type() == QEvent::PaletteChange) {
        const auto list  = findChildren<QWidget*>();
            for( auto i: list)
                i->setPalette(palette());
    }
    QWidget::changeEvent(e);
}

ChocoboManager::ChocoboManager(QWidget *parent) :
    QWidget(parent)
    , penBox(new QGroupBox)
    , lblStablesOwned(new QLabel)
    , lblStablesOccupied(new QLabel)
{

    sbStablesOwned = new QSpinBox(this);
    sbStablesOwned->setMaximum(6);
    sbStablesOwned->setWrapping(true);
    connect(sbStablesOwned, QOverload<int>::of(&QSpinBox::valueChanged), this, &ChocoboManager::setStablesOwned);

    lcdStablesOccupied = new QLCDNumber(1, this);
    lcdStablesOccupied->setSegmentStyle(QLCDNumber::Flat);

    chocoboEditor = new ChocoboEditor(this);
    chocoboEditor->setHidden(true);
    connectEditor();

    lblStablesOwned ->setText(tr("Stables Owned"));
    QHBoxLayout *ownedLayout = new QHBoxLayout();
    ownedLayout->setContentsMargins(0, 0, 0, 0);
    ownedLayout->addWidget(lblStablesOwned);
    ownedLayout->addWidget(sbStablesOwned);

    lblStablesOccupied->setText(tr("Stables Occupied"));
    auto occupiedLayout = new QHBoxLayout;
    occupiedLayout->setContentsMargins(0, 0, 0, 0);
    occupiedLayout->addWidget(lblStablesOccupied);
    occupiedLayout->addWidget(lcdStablesOccupied);

    auto topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Preferred, QSizePolicy::Preferred));
    topLayout->addLayout(ownedLayout);
    topLayout->addLayout(occupiedLayout);
    topLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));

    auto leftSideLayout = new QVBoxLayout;
    leftSideLayout->setSpacing(0);
    leftSideLayout->addLayout(topLayout);
    leftSideLayout->addLayout(createChocoboLabelGrid());
    leftSideLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::MinimumExpanding));

    penBox->setTitle(tr("Fenced Chocobos"));
    penBox->setLayout(createChocoboPenGrid());

    auto rightSideLayout = new QVBoxLayout;
    rightSideLayout->addWidget(chocoboEditor);
    rightSideLayout->addWidget(penBox);
    rightSideLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::MinimumExpanding));

    auto finalLayout = new QHBoxLayout;
    finalLayout->addLayout(leftSideLayout);
    finalLayout->addLayout(rightSideLayout);
    this->setLayout(finalLayout);
}

void ChocoboManager::setStablesOwned(int value)
{
    if (value == stablesOwned)
        return;

    if ((value < 0) || (value > 6))
        return;

    disableChocoLabels();
    enableChocoboLabels(value);
    stablesOwned = qint8(value);
    Q_EMIT ownedChanged(qint8(value));
    for (int i = value; i < 6 ; i++) {
        if (chocoboLabel[i]->isOccupied()) {
            chocoboLabel[i]->setOccupied(false);
            setOccupied(stablesOccupied - 1, stableMask &= ~(1 << i));
            Q_EMIT occupiedChanged(stablesOccupied);
            Q_EMIT stableMaskChanged(stableMask);
            if (i == selectedStable) {
                selectedStable = -1;
                chocoboEditor->setHidden(true);
            }
        }
    }
}

void ChocoboManager::connectEditor()
{
    connect(this, &ChocoboManager::setMode, chocoboEditor, &ChocoboEditor::setAdvancedMode);
    connect(chocoboEditor, &ChocoboEditor::nameChanged, this, [this](const QString &name) {
        if (name != chocoboName[selectedStable]) {
            chocoboName[selectedStable] = name;
            labelUpdate(selectedStable);
            Q_EMIT nameChanged(selectedStable, name);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::sexChanged, this, [this](quint8 sex) {
        if (sex != chocoboData[selectedStable].sex) {
            chocoboData[selectedStable].sex = sex;
            labelUpdate(selectedStable);
            Q_EMIT sexChanged(selectedStable, sex);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::typeChanged, this, [this](quint8 type) {
        if (type != chocoboData[selectedStable].type) {
            chocoboData[selectedStable].type = type;
            labelUpdate(selectedStable);
            Q_EMIT typeChanged(selectedStable, type);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::sprintChanged, this, [this](quint16 sprint) {
        if (sprint != chocoboData[selectedStable].sprintspd) {
            chocoboData[selectedStable].sprintspd = sprint;
            Q_EMIT sprintChanged(selectedStable, sprint);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::mSprintChanged, this, [this](quint16 Msprint) {
        if (Msprint != chocoboData[selectedStable].maxsprintspd) {
            chocoboData[selectedStable].maxsprintspd = Msprint;
            Q_EMIT mSprintChanged(selectedStable, Msprint);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::speedChanged, this, [this](quint16 speed) {
        if (speed != chocoboData[selectedStable].speed) {
            chocoboData[selectedStable].speed = speed;
            Q_EMIT speedChanged(selectedStable, speed);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::mSpeedChanged, this, [this](quint16 Mspeed) {
        if (Mspeed != chocoboData[selectedStable].maxspeed) {
            chocoboData[selectedStable].maxspeed = Mspeed;
            Q_EMIT mSpeedChanged(selectedStable, Mspeed);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::staminaChanged, this, [this](quint16 stamina) {
        if (stamina != chocoboStamina[selectedStable]) {
            chocoboStamina[selectedStable] = stamina;
            Q_EMIT staminaChanged(selectedStable, stamina);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::accelChanged, this, [this](quint8 accel) {
        if (accel != chocoboData[selectedStable].accel) {
            chocoboData[selectedStable].accel = accel;
            Q_EMIT accelChanged(selectedStable, accel);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::coopChanged, this, [this](quint8 coop) {
        if (coop != chocoboData[selectedStable].coop) {
            chocoboData[selectedStable].coop = coop;
            Q_EMIT coopChanged(selectedStable, coop);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::intelligenceChanged, this, [this](quint8 intelligence) {
        if (intelligence != chocoboData[selectedStable].intelligence) {
            chocoboData[selectedStable].intelligence = intelligence;
            Q_EMIT intelligenceChanged(selectedStable, intelligence);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::personalityChanged, this, [this](quint8 personality) {
        if (personality != chocoboData[selectedStable].personality) {
            chocoboData[selectedStable].personality = personality;
            Q_EMIT personalityChanged(selectedStable, personality);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::pCountChanged, this, [this](quint8 pCount) {
        if (pCount != chocoboData[selectedStable].pcount) {
            chocoboData[selectedStable].pcount = pCount;
            Q_EMIT pCountChanged(selectedStable, pCount);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::winsChanged, this, [this](quint8 wins) {
        if (wins != chocoboData[selectedStable].raceswon) {
            chocoboData[selectedStable].raceswon = wins;
            labelUpdate(selectedStable);
            Q_EMIT winsChanged(selectedStable, wins);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::cantMateChanged, this, [this](bool cantmate) {
        if (cantmate != cantMate[selectedStable]) {
            cantMate[selectedStable] = cantmate;
            Q_EMIT cantMateChanged(selectedStable, cantmate);
        }
    });
    connect(chocoboEditor, &ChocoboEditor::ratingChanged, this, [this](quint8 rating) {
        if (rating != chocoboRatings[selectedStable]) {
            chocoboRatings[selectedStable] = rating;
            labelUpdate(selectedStable);
            Q_EMIT ratingChanged(selectedStable, rating);
        }
    });
}

void ChocoboManager::rmChocobo(int s)
{
    chocoboName[s] = QString("\xFF\xFF\xFF\xFF\xFF\xFF");
    chocoboStamina[s] = 0;
    cantMate[s] = false;
    chocoboData[s].accel = 0;
    chocoboData[s].coop = 0;
    chocoboData[s].intelligence = 0;
    chocoboData[s].maxspeed = 0;
    chocoboData[s].maxsprintspd = 0;
    chocoboData[s].pcount = 0;
    chocoboData[s].personality = 0;
    chocoboData[s].raceswon = 0;
    chocoboData[s].sex = 0;
    chocoboData[s].speed = 0;
    chocoboData[s].sprintspd = 0;
    chocoboData[s].type = 0;
    chocoboRatings[s] = 0;
    //emit the changes
    ChocoboChanged(s);
    if (selectedStable == s) {
        chocoboLabel[s]->setSelected(false);
        selectedStable = -1;
        chocoboEditor->setHidden(true);
    }
}

void ChocoboManager::labelUpdate(int label)
{
    if (!(chocoboName[label].startsWith(QString("\xff"))))
        chocoboLabel[label]->setName(chocoboName[label]);
    chocoboLabel[label]->setSex(chocoboData[label].sex);
    chocoboLabel[label]->setRank(chocoboData[label].raceswon);
    chocoboLabel[label]->setType(chocoboData[label].type);
    chocoboLabel[label]->setOccupied(stableMask & (1 << label));

}

void ChocoboManager::setData(FF7CHOCOBO chocos[6], QString names[6], quint16 staminas[6], bool cMate[6], qint8 owned, qint8 occupied, qint8 mask, qint8 chocoPens[4], quint8 chocoboRatings[6])
{
    for (int i = 0; i < 6; i++) {
        setChocobo(i, chocos[i], names[i], staminas[i], cMate[i], chocoboRatings[i]);
        if (!chocoboLabel[i]->isOccupied())
            chocoboLabel[i]->clearLabel();
        chocoboLabel[i]->setSelected(false);
    }
    setOwned(owned);
    setOccupied(occupied, mask);
    selectedStable = -1; //reset
    chocoboEditor->setHidden(true);
    for (int i = 0; i < 4; i++)
        setChocoboPen(i, chocoPens[i]);
}

void ChocoboManager::setData(QList<FF7CHOCOBO> chocos, QList<QString> names, QList<quint16> staminas, QList<bool> cMate, qint8 owned, qint8 occupied, qint8 mask, QList<qint8> chocoPens, QList<quint8> chocoboRatings)
{
    setOwned(owned);
    setOccupied(occupied, mask);
    selectedStable = -1; //reset

    chocoboEditor->setHidden(true);

    for (int i = 0; i < 6; i++) {
        setChocobo(i, chocos.at(i), names.at(i), staminas.at(i), cMate.at(i), chocoboRatings.at(i));
        if (!chocoboLabel[i]->isOccupied())
            chocoboLabel[i]->clearLabel();
        chocoboLabel[i]->setSelected(false);
    }

    for (int i = 0; i < 4; i++)
        setChocoboPen(i, chocoPens[i]);
}

void ChocoboManager::setChocobo(int s, const FF7CHOCOBO &chocoData, const QString &chocoName, quint16 chocoStamina, bool chocoCmate, quint8 rating)
{
    chocoboLabel[s]->clearLabel();
    chocoboData[s] = chocoData;
    chocoboName[s] = chocoName;
    chocoboStamina[s] = chocoStamina;
    chocoboRatings[s] = rating;
    cantMate[s] = chocoCmate;
    if (chocoboLabel[s]->isOccupied())
        labelUpdate(s);
    else
        chocoboLabel[s]->clearLabel();
}

void ChocoboManager::setChocoboPen(int pen, int value)
{
    if ((pen < 0) || (pen > 3) || (value < 0) || (value > 8))
        return;
    comboChocoPen[pen]->setCurrentIndex(value);
}

void ChocoboManager::setOwned(int owned)
{
    if ((owned < 0) || (owned > 6))
        return;
    stablesOwned = qint8(owned);
    sbStablesOwned->blockSignals(true);
    sbStablesOwned->setValue(owned);
    disableChocoLabels();
    enableChocoboLabels(owned);
    sbStablesOwned->blockSignals(false);
}

void ChocoboManager::setOccupied(int occupied, int mask)
{
    if ((occupied < 0) || (occupied > 6))
        return;
    stablesOccupied = qint8(occupied);
    stableMask = qint8(mask);

    for (int i = 0; i < 6; i++) {
        chocoboLabel[i]->blockSignals(true);
        if ((mask & (1 << i))) {
            chocoboLabel[i]->setOccupied(true);
            labelUpdate(i);
        } else {
            chocoboLabel[i]->setOccupied(false);
            chocoboLabel[i]->clearLabel();
        }
        chocoboLabel[i]->blockSignals(false);
    }
    lcdStablesOccupied->blockSignals(true);
    lcdStablesOccupied->display(occupied);
    lcdStablesOccupied->blockSignals(false);
}

void ChocoboManager::ChocoboChanged(int s)
{
    Q_EMIT nameChanged(s, chocoboName[s]);
    Q_EMIT staminaChanged(s, chocoboStamina[s]);
    Q_EMIT cantMateChanged(s, cantMate[s]);
    Q_EMIT sexChanged(s, chocoboData[s].sex);
    Q_EMIT typeChanged(s, chocoboData[s].type);
    Q_EMIT sprintChanged(s, chocoboData[s].sprintspd);
    Q_EMIT mSprintChanged(s, chocoboData[s].maxsprintspd);
    Q_EMIT speedChanged(s, chocoboData[s].speed);
    Q_EMIT mSpeedChanged(s, chocoboData[s].maxspeed);
    Q_EMIT accelChanged(s, chocoboData[s].accel);
    Q_EMIT coopChanged(s, chocoboData[s].coop);
    Q_EMIT intelligenceChanged(s, chocoboData[s].intelligence);
    Q_EMIT personalityChanged(s, chocoboData[s].personality);
    Q_EMIT pCountChanged(s, chocoboData[s].pcount);
    Q_EMIT winsChanged(s, chocoboData[s].raceswon);
    Q_EMIT ratingChanged(s, chocoboRatings[s]);
}

bool ChocoboManager::isEmpty(FF7CHOCOBO choco)
{
    int score = 0;
    if (!choco.accel)
        score++;

    if (!choco.coop)
        score++;

    if (!choco.intelligence)
        score++;

    if (!choco.maxspeed)
        score++;

    if (!choco.maxsprintspd)
        score++;

    if (!choco.pcount)
        score++;

    if (!choco.personality)
        score++;

    if (!choco.raceswon)
        score++;

    if (!choco.sex)
        score++;

    if (!choco.speed)
        score++;

    if (!choco.sprintspd)
        score++;

    if (!choco.type)
        score++;

    if (score > 5)
        return false;
    return true;
}

void ChocoboManager::clearSelection()
{
    for (int i = 0; i < 6; i++)
        chocoboLabel[i]->setSelected(false);
}

void ChocoboManager::disableChocoLabels()
{
    for (int i = 0; i < 6; i++)
        chocoboLabel[i]->setEnabled(false);
}

void ChocoboManager::enableChocoboLabels(int count)
{
    for (int i = 0; i < count; i++)
        chocoboLabel[i]->setEnabled(true);
}

QGridLayout *ChocoboManager::createChocoboLabelGrid()
{
    auto gridLayout = new QGridLayout;
    gridLayout->setContentsMargins(0, 0, 0, 0);
    for (int i = 0; i < 6; i++) {
        chocoboLabel[i] = new ChocoboLabel(tr("Stable:%1").arg(QString::number(i + 1)), false, this);
        chocoboLabel[i]->setObjectName(QString::number(i));
        gridLayout->addWidget(chocoboLabel[i], (i / 2), (i % 2), 1, 1, Qt::AlignCenter);
        chocoboLabel[i]->setEnabled(false);
        chocoboLabel[i]->setSelected(false);

        connect(chocoboLabel[i], &ChocoboLabel::clicked, this, [this] {
            if (selectedStable == -1)
                chocoboEditor->setHidden(false);
            selectedStable = sender()->objectName().toInt();
            chocoboEditor->SetChocobo(chocoboData[selectedStable], chocoboName[selectedStable], cantMate[selectedStable], chocoboStamina[selectedStable], chocoboRatings[selectedStable]);
            clearSelection();
            chocoboLabel[selectedStable]->setSelected(true);
        });
        connect(chocoboLabel[i], &ChocoboLabel::copy, this, [this] {
            int s = sender()->objectName().toInt();
            chocoboData[6] = chocoboData[s];
            chocoboName[6] = chocoboName[s];
            cantMate[6] = cantMate[s];
            chocoboStamina[6] = chocoboStamina[s];
            chocoboRatings[6] = chocoboRatings[s];
        });
        connect(chocoboLabel[i], &ChocoboLabel::paste, this, [this] {
            int s = sender()->objectName().toInt();
            setChocobo(s, chocoboData[6], chocoboName[6], chocoboStamina[6], cantMate[6], chocoboRatings[6]);
            //emit the changes
            ChocoboChanged(s);
            if (!chocoboLabel[s]->isOccupied()) {
                chocoboLabel[s]->setOccupied(true);
                setOccupied(stablesOccupied + 1, stableMask |= (1 << s));
                Q_EMIT occupiedChanged(stablesOccupied);
                Q_EMIT stableMaskChanged(stableMask);
            }
        });
        connect(chocoboLabel[i], &ChocoboLabel::remove, this, [this] {
            rmChocobo(sender()->objectName().toInt());
        });
        connect(chocoboLabel[i], &ChocoboLabel::occupiedToggled, this, [this](bool occupied) {
            int s = sender()->objectName().toInt();
            if (occupied) {
                stableMask |= (1 << s);
                lcdStablesOccupied->display(lcdStablesOccupied->value() + 1);
                labelUpdate(s);
            } else {
                stableMask &= ~(1 << s);
                lcdStablesOccupied->display(lcdStablesOccupied->value() - 1);
                chocoboLabel[s]->clearLabel();
                if (selectedStable == s) {
                    chocoboLabel[s]->setSelected(false);
                    selectedStable = -1;
                    chocoboEditor->setHidden(true);
                }
            }
            stablesOccupied = qint8(lcdStablesOccupied->intValue());
            Q_EMIT occupiedChanged(stablesOccupied);
            Q_EMIT stableMaskChanged(stableMask);
        });
        rmChocobo(i);
    }
    return gridLayout;
}
QGridLayout *ChocoboManager::createChocoboPenGrid()
{
    auto gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < 4; i++) {
        comboChocoPen[i] = new QComboBox(this);
        comboChocoPen[i]->setObjectName(QString::number(i));
        gridLayout->addWidget(comboChocoPen[i], i / 2, i % 2, 1, 1);
        connect(comboChocoPen[i], QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index) {
            Q_EMIT penChanged(sender()->objectName().toInt(), index);
        });
    }
    updateCombos();
    return gridLayout;
}

void ChocoboManager::updateCombos()
{
    QStringList typeList{
        {tr("Empty")}
        , {tr("Wonderful")}
        , {tr("Great")}
        , {tr("Good")}
        , {tr("Fair")}
        , {tr("Average")}
        , {tr("Poor")}
        , {tr("Bad")}
        , {tr("Terrible")}
    };

    for (int i = 0; i < 4; i++) {
        if (comboChocoPen[i]->count() != 0) {
            for (int j = 0; j < comboChocoPen[i]->count(); j++)
                comboChocoPen[i]->setItemText(j, typeList.at(j));
        } else {
            comboChocoPen[i]->addItems(typeList);
        }
    }
}

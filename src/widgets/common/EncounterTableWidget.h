/****************************************************************************/
//    Copyright (C) 2009-2022 Arzel Jérôme <myst6re@gmail.com>              //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#pragma once

#include <QGroupBox>
#include <ff7tkqtwidgets_export.h>

class QLabel;
class QSpinBox;
class QSlider;

class FF7TKQTWIDGETS_EXPORT EncounterTableWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit EncounterTableWidget(const QString &title, QWidget *parent = nullptr);
    QList<int> battleIdsValues();
    QList<int> battleProbasValues();
    int rateValue();
    void setBattleIdsValues(const QList<int> &ids);
    void setBattleProbasValues(const QList<int> &probas);
    void setRateValue(int value);
public slots:
    void changePercent();
    void changeProbaCount();
private:
    static void setProbaLabelColor(QLabel *label, qint16 points);
    QLabel *rateLabel = nullptr;
    QLabel *probaLabel = nullptr;
    QLabel *probaLabel2 = nullptr;
    QSlider *mainRate = nullptr;
    QGroupBox *group = nullptr;
    QList<QSpinBox*> battleIds;
    QList<QSpinBox*> battleProbas;
    inline static const QStringList specialBattleNames = QStringList{ QT_TR_NOOP("Back Attack 1"), QT_TR_NOOP("Back Attack 2"), QT_TR_NOOP("Side Attack"), QT_TR_NOOP("Attack From Both Sides")};
};

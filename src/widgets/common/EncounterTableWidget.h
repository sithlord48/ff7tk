//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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

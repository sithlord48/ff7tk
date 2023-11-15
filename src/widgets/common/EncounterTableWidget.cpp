//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <EncounterTableWidget.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

EncounterTableWidget::EncounterTableWidget(const QString &title, QWidget *parent)
    : QGroupBox(title, parent)
    , rateLabel(new QLabel(this))
    , probaLabel(new QLabel(this))
    , probaLabel2(new QLabel(this))
    , mainRate(new QSlider(Qt::Horizontal, this))
{
    setCheckable(true);
    rateLabel->setTextFormat(Qt::PlainText);
    probaLabel->setTextFormat(Qt::PlainText);
    probaLabel2->setTextFormat(Qt::PlainText);

    mainRate->setRange(0, 255);

    QHBoxLayout *rateLayout = new QHBoxLayout;
    rateLayout->addWidget(new QLabel(QStringLiteral("-")));
    rateLayout->addWidget(mainRate);
    rateLayout->addWidget(new QLabel(QStringLiteral("+")));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(rateLabel, 0, 0, 1, 3, Qt::AlignLeft);
    layout->addLayout(rateLayout, 1, 0, 1, 3, Qt::AlignLeft);
    layout->addWidget(new QLabel(tr("Battle ID"), this), 2, 1);
    layout->addWidget(new QLabel(tr("Probability"), this), 2, 2);

    int row=3;
    for (int i=0; i<10; ++i) {
        layout->addWidget(new QLabel(i>=6 ? specialBattleNames.at(i-6) : tr("Battle %1").arg(i+1), this), row, 0);
        QSpinBox *spinBox = new QSpinBox(this);
        spinBox->setRange(0, 1023);
        battleIds.append(spinBox);
        layout->addWidget(spinBox, row, 1);
        spinBox = new QSpinBox(this);
        spinBox->setRange(0, 63);
        battleProbas.append(spinBox);
        layout->addWidget(spinBox, row, 2);

        ++row;

        if (row == 9) {
            layout->addWidget(probaLabel, row, 0, 1, 3);
            ++row;
        } else if (row == 14) {
            layout->addWidget(probaLabel2, row, 0, 1, 3);
            ++row;
        }
    }

    connect(mainRate, &QSlider::valueChanged, this, &EncounterTableWidget::changePercent);
    for (QSpinBox *battleProba : std::as_const(battleProbas))
        connect(battleProba, &QSpinBox::valueChanged, this, &EncounterTableWidget::changeProbaCount);

    changePercent();
    changeProbaCount();
}

QList<int> EncounterTableWidget::battleIdsValues()
{
    QList<int> ids;
    for (QSpinBox *battleId : std::as_const(battleIds))
        ids.append(battleId->value());
    return ids;
}

QList<int> EncounterTableWidget::battleProbasValues()
{
    QList<int> probas;
    for (QSpinBox *battleProba : std::as_const(battleProbas))
        probas.append(battleProba->value());
    return probas;
}

int EncounterTableWidget::rateValue()
{
    return 255 - mainRate->value();
}

void EncounterTableWidget::setBattleIdsValues(const QList<int> &ids)
{
    for (int i=0; i<10; ++i)
        battleIds.at(i)->setValue(ids.at(i));
}

void EncounterTableWidget::setBattleProbasValues(const QList<int> &probas)
{
    for (int i=0; i<10; ++i)
        battleProbas.at(i)->setValue(probas.at(i));
}

void EncounterTableWidget::setRateValue(int value)
{
    mainRate->setValue(255-value);
}

void EncounterTableWidget::changePercent()
{
    rateLabel->setText(tr("Battle rate: %1/255").arg(rateValue()));
}

void EncounterTableWidget::setProbaLabelColor(QLabel *label, qint16 points)
{
    QPalette pal = label->palette();
    QColor col = QColor(points<0 ? Qt::red : (points==0 ? Qt::darkGreen : Qt::gray));
    pal.setColor(QPalette::Active, QPalette::WindowText, col);
    pal.setColor(QPalette::Inactive, QPalette::WindowText, col);
    label->setPalette(pal);
}

void EncounterTableWidget::changeProbaCount()
{
    qint16 points = 64;
    for (quint8 i=0; i<6; ++i)
        points -= battleProbas.at(i)->value();

    setProbaLabelColor(probaLabel, points);
    probaLabel->setText(tr("Remaining probability points: %1").arg(points));

    points = 64;
    for (quint8 i=6; i<10; ++i)
        points -= battleProbas.at(i)->value();

    setProbaLabelColor(probaLabel2, points);
    probaLabel2->setText(tr("Remaining probability points: %1").arg(points));
}

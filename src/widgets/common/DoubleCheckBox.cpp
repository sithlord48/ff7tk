//    SPDX-FileCopyrightText: 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <DoubleCheckBox.h>

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>

DoubleCheckBox::DoubleCheckBox(QWidget *parent) :
    QWidget(parent)
{
    init_display();
}

DoubleCheckBox::DoubleCheckBox(const QString &text, QWidget *parent) :
    QWidget(parent)
{
    init_display();
    setText(text);
}
void DoubleCheckBox::init_display()
{
    cb_one = new QCheckBox(this);
    connect(cb_one, &QCheckBox::toggled, this, &DoubleCheckBox::box1Toggled);

    cb_two = new QCheckBox(this);
    connect(cb_two, &QCheckBox::toggled, this, &DoubleCheckBox::box2Toggled);
    label = new QLabel(this);

    // TODO: remove for 2.0
    connect(cb_one, &QCheckBox::toggled, this, &DoubleCheckBox::box1_toggled);
    // TODO: remove for 2.0
    connect(cb_two, &QCheckBox::toggled, this, &DoubleCheckBox::box2_toggled);

    auto boxLayout = new QHBoxLayout;
    boxLayout->addWidget(cb_one);
    boxLayout->addWidget(cb_two);
    boxLayout->setContentsMargins(0, 0, 0, 0);

    auto Final = new QHBoxLayout;
    Final->addWidget(label, 2);
    Final->addLayout(boxLayout, 1);
    Final->setContentsMargins(0, 0, 0, 0);
    this->setLayout(Final);
}

void DoubleCheckBox::setText(const QString &text)
{
    label->setText(text);
}

void DoubleCheckBox::setChecked(int box, bool checked)
{
    switch (box) {
    case 1: cb_one->setChecked(checked); break;
    case 2: cb_two->setChecked(checked); break;
    default: break;
    }
}
bool DoubleCheckBox::isChecked(int box)
{
    switch (box) {
    case 1: return cb_one->isChecked();
    case 2: return cb_two->isChecked();
    default: return false;
    }
}

void DoubleCheckBox::setBoxToolTip(int box, const QString &text)
{
    switch (box) {
    case 1: cb_one->setToolTip(text); break;
    case 2: cb_two->setToolTip(text); break;
    default: break;
    }
}
void DoubleCheckBox::setToolTip(const QString &text)
{
    label->setToolTip(text);
}


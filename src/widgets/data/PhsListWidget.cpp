//    SPDX-FileCopyrightText: 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <PhsListWidget.h>

#include <QLabel>
#include <QVBoxLayout>
#include <FF7Char>

PhsListWidget::PhsListWidget(QWidget *parent) :
    QWidget(parent)
    , cb_cloud(new DoubleCheckBox)
    , cb_barret(new DoubleCheckBox)
    , cb_tifa(new DoubleCheckBox)
    , cb_aerith(new DoubleCheckBox)
    , cb_red(new DoubleCheckBox)
    , cb_yuffie(new DoubleCheckBox)
    , cb_cait(new DoubleCheckBox)
    , cb_vincent(new DoubleCheckBox)
    , cb_cid(new DoubleCheckBox)
    , lbl_phs(new QLabel)
{
    updateText();
    init_display();
    connectAll();
}

void PhsListWidget::changeEvent(QEvent *e)
{
    if (e->type() != QEvent::LanguageChange)
        QWidget::changeEvent(e);
    updateText();
}

void PhsListWidget::init_display()
{
    lbl_phs->setStyleSheet(QStringLiteral("text-decoration: underline;"));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lbl_phs);
    layout->setSpacing(3);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(cb_cloud);
    layout->addWidget(cb_barret);
    layout->addWidget(cb_tifa);
    layout->addWidget(cb_aerith);
    layout->addWidget(cb_red);
    layout->addWidget(cb_yuffie);
    layout->addWidget(cb_cait);
    layout->addWidget(cb_vincent);
    layout->addWidget(cb_cid);
    setLayout(layout);
}
void PhsListWidget::updateText()
{
    QString aString = tr("Allowed");
    QString vString = tr("Visible");
    lbl_phs->setText(tr("PHS Manager"));

    cb_cloud->setText(FF7Char::defaultName(FF7Char::Cloud));
    cb_cloud->setBoxToolTip(PHSALLOWED, aString);
    cb_cloud->setBoxToolTip(PHSVISIBLE, vString);

    cb_barret->setText(FF7Char::defaultName(FF7Char::Barret));
    cb_barret->setBoxToolTip(PHSALLOWED, aString);
    cb_barret->setBoxToolTip(PHSVISIBLE, vString);

    cb_tifa->setText(FF7Char::defaultName(FF7Char::Tifa));
    cb_tifa->setBoxToolTip(PHSALLOWED, aString);
    cb_tifa->setBoxToolTip(PHSVISIBLE, vString);

    cb_aerith->setText(FF7Char::defaultName(FF7Char::Aerith));
    cb_aerith->setBoxToolTip(PHSALLOWED, aString);
    cb_aerith->setBoxToolTip(PHSVISIBLE, vString);

    cb_red->setText(FF7Char::defaultName(FF7Char::Red));
    cb_red->setBoxToolTip(PHSALLOWED, aString);
    cb_red->setBoxToolTip(PHSVISIBLE, vString);

    cb_yuffie->setText(FF7Char::defaultName(FF7Char::Yuffie));
    cb_yuffie->setBoxToolTip(PHSALLOWED, aString);
    cb_yuffie->setBoxToolTip(PHSVISIBLE, vString);

    cb_cait->setText(FF7Char::defaultName(FF7Char::CaitSith));
    cb_cait->setBoxToolTip(PHSALLOWED, aString);
    cb_cait->setBoxToolTip(PHSVISIBLE, vString);

    cb_vincent->setText(FF7Char::defaultName(FF7Char::Vincent));
    cb_vincent->setBoxToolTip(PHSALLOWED, aString);
    cb_vincent->setBoxToolTip(PHSVISIBLE, vString);

    cb_cid->setText(FF7Char::defaultName(FF7Char::Cid));
    cb_cid->setBoxToolTip(PHSALLOWED, aString);
    cb_cid->setBoxToolTip(PHSVISIBLE, vString);
}

void PhsListWidget::setChecked(int row, int box, bool checked)
{
    disconnectAll();
    switch (row) {
    case 0: cb_cloud->setChecked(box, checked); break;
    case 1: cb_barret->setChecked(box, checked); break;
    case 2: cb_tifa->setChecked(box, checked); break;
    case 3: cb_aerith->setChecked(box, checked); break;
    case 4: cb_red->setChecked(box, checked); break;
    case 5: cb_yuffie->setChecked(box, checked); break;
    case 6: cb_cait->setChecked(box, checked); break;
    case 7: cb_vincent->setChecked(box, checked); break;
    case 8: cb_cid->setChecked(box, checked); break;
    }
    connectAll();
}

void PhsListWidget::cb_cloud_allowedToggled(bool checked)
{
    Q_EMIT allowedToggled(0, checked);
}
void PhsListWidget::cb_cloud_visibleToggled(bool checked)
{
    Q_EMIT visibleToggled(0, checked);
}
void PhsListWidget::cb_barret_allowedToggled(bool checked)
{
    Q_EMIT allowedToggled(1, checked);
}
void PhsListWidget::cb_barret_visibleToggled(bool checked)
{
    Q_EMIT visibleToggled(1, checked);
}
void PhsListWidget::cb_tifa_allowedToggled(bool checked)
{
    Q_EMIT allowedToggled(2, checked);
}
void PhsListWidget::cb_tifa_visibleToggled(bool checked)
{
    Q_EMIT visibleToggled(2, checked);
}
void PhsListWidget::cb_aerith_allowedToggled(bool checked)
{
    Q_EMIT allowedToggled(3, checked);
}
void PhsListWidget::cb_aerith_visibleToggled(bool checked)
{
    Q_EMIT visibleToggled(3, checked);
}
void PhsListWidget::cb_red_allowedToggled(bool checked)
{
    Q_EMIT allowedToggled(4, checked);
}
void PhsListWidget::cb_red_visibleToggled(bool checked)
{
    Q_EMIT visibleToggled(4, checked);
}
void PhsListWidget::cb_yuffie_allowedToggled(bool checked)
{
    Q_EMIT allowedToggled(5, checked);
}
void PhsListWidget::cb_yuffie_visibleToggled(bool checked)
{
    Q_EMIT visibleToggled(5, checked);
}
void PhsListWidget::cb_cait_allowedToggled(bool checked)
{
    Q_EMIT allowedToggled(6, checked);
}
void PhsListWidget::cb_cait_visibleToggled(bool checked)
{
    Q_EMIT visibleToggled(6, checked);
}
void PhsListWidget::cb_vincent_allowedToggled(bool checked)
{
    Q_EMIT allowedToggled(7, checked);
}
void PhsListWidget::cb_vincent_visibleToggled(bool checked)
{
    Q_EMIT visibleToggled(7, checked);
}
void PhsListWidget::cb_cid_allowedToggled(bool checked)
{
    Q_EMIT allowedToggled(8, checked);
}
void PhsListWidget::cb_cid_visibleToggled(bool checked)
{
    Q_EMIT visibleToggled(8, checked);
}

void PhsListWidget::connectAll()
{
    connect(cb_cloud, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_cloud_allowedToggled);
    connect(cb_cloud, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_cloud_visibleToggled);
    connect(cb_barret, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_barret_allowedToggled);
    connect(cb_barret, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_barret_visibleToggled);
    connect(cb_tifa, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_tifa_allowedToggled);
    connect(cb_tifa, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_tifa_visibleToggled);
    connect(cb_aerith, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_aerith_allowedToggled);
    connect(cb_aerith, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_aerith_visibleToggled);
    connect(cb_red, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_red_allowedToggled);
    connect(cb_red, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_red_visibleToggled);
    connect(cb_yuffie, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_yuffie_allowedToggled);
    connect(cb_yuffie, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_yuffie_visibleToggled);
    connect(cb_cait, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_cait_allowedToggled);
    connect(cb_cait, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_cait_visibleToggled);
    connect(cb_vincent, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_vincent_allowedToggled);
    connect(cb_vincent, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_vincent_visibleToggled);
    connect(cb_cid, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_cid_allowedToggled);
    connect(cb_cid, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_cid_visibleToggled);
}
void PhsListWidget::disconnectAll()
{
    disconnect(cb_cloud, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_cloud_allowedToggled);
    disconnect(cb_cloud, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_cloud_visibleToggled);
    disconnect(cb_barret, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_barret_allowedToggled);
    disconnect(cb_barret, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_barret_visibleToggled);
    disconnect(cb_tifa, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_tifa_allowedToggled);
    disconnect(cb_tifa, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_tifa_visibleToggled);
    disconnect(cb_aerith, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_aerith_allowedToggled);
    disconnect(cb_aerith, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_aerith_visibleToggled);
    disconnect(cb_red, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_red_allowedToggled);
    disconnect(cb_red, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_red_visibleToggled);
    disconnect(cb_yuffie, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_yuffie_allowedToggled);
    disconnect(cb_yuffie, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_yuffie_visibleToggled);
    disconnect(cb_cait, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_cait_allowedToggled);
    disconnect(cb_cait, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_cait_visibleToggled);
    disconnect(cb_vincent, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_vincent_allowedToggled);
    disconnect(cb_vincent, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_vincent_visibleToggled);
    disconnect(cb_cid, &DoubleCheckBox::box1Toggled, this, &PhsListWidget::cb_cid_allowedToggled);
    disconnect(cb_cid, &DoubleCheckBox::box2Toggled, this, &PhsListWidget::cb_cid_visibleToggled);
}

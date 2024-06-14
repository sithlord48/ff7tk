//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <MenuListWidget.h>

#include <QLabel>
#include <QVBoxLayout>

MenuListWidget::MenuListWidget(QWidget *parent) :
    QWidget(parent)
    , cb_item(new DoubleCheckBox)
    , cb_magic(new DoubleCheckBox)
    , cb_materia(new DoubleCheckBox)
    , cb_equip(new DoubleCheckBox)
    , cb_status(new DoubleCheckBox)
    , cb_order(new DoubleCheckBox)
    , cb_limit(new DoubleCheckBox)
    , cb_config(new DoubleCheckBox)
    , cb_phs(new DoubleCheckBox)
    , cb_save(new DoubleCheckBox)
    , lbl_title(new QLabel)
{
    updateText();
    init_display();
    connectAll();
}
void MenuListWidget::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
        updateText();
    QWidget::changeEvent(e);
}

void MenuListWidget::init_display()
{
    lbl_title->setStyleSheet(QStringLiteral("text-decoration: underline;"));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(3);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(lbl_title);
    layout->addWidget(cb_item);
    layout->addWidget(cb_magic);
    layout->addWidget(cb_materia);
    layout->addWidget(cb_equip);
    layout->addWidget(cb_status);
    layout->addWidget(cb_order);
    layout->addWidget(cb_limit);
    layout->addWidget(cb_config);
    layout->addWidget(cb_phs);
    layout->addWidget(cb_save);
    setLayout(layout);
}
void MenuListWidget::updateText()
{
    QString aString = tr("Visible");
    QString vString = tr("Locked");

    lbl_title->setText(tr("Menu Manager"));
    cb_item->setText(tr("Item"));
    cb_item->setBoxToolTip(MENUVISIBLE, aString);
    cb_item->setBoxToolTip(MENULOCKED, vString);

    cb_magic->setText(tr("Magic"));
    cb_magic->setBoxToolTip(MENUVISIBLE, aString);
    cb_magic->setBoxToolTip(MENULOCKED, vString);

    cb_materia->setText(tr("Materia"));
    cb_materia->setBoxToolTip(MENUVISIBLE, aString);
    cb_materia->setBoxToolTip(MENULOCKED, vString);

    cb_equip->setText(tr("Equip"));
    cb_equip->setBoxToolTip(MENUVISIBLE, aString);
    cb_equip->setBoxToolTip(MENULOCKED, vString);

    cb_status->setText(tr("Status"));
    cb_status->setBoxToolTip(MENUVISIBLE, aString);
    cb_status->setBoxToolTip(MENULOCKED, vString);

    cb_order->setText(tr("Order"));
    cb_order->setBoxToolTip(MENUVISIBLE, aString);
    cb_order->setBoxToolTip(MENULOCKED, vString);

    cb_limit->setText(tr("Limit"));
    cb_limit->setBoxToolTip(MENUVISIBLE, aString);
    cb_limit->setBoxToolTip(MENULOCKED, vString);

    cb_config->setText(tr("Config"));
    cb_config->setBoxToolTip(MENUVISIBLE, aString);
    cb_config->setBoxToolTip(MENULOCKED, vString);

    cb_phs->setText(tr("P.H.S"));
    cb_phs->setBoxToolTip(MENUVISIBLE, aString);
    cb_phs->setBoxToolTip(MENULOCKED, vString);

    cb_save->setText(tr("Save"));
    cb_save->setBoxToolTip(MENUVISIBLE, aString);
    cb_save->setBoxToolTip(MENULOCKED, vString);
}

void MenuListWidget::setChecked(int row, int box, bool checked)
{
    disconnectAll();
    switch (row) {
    case 0: cb_item->setChecked(box, checked); break;
    case 1: cb_magic->setChecked(box, checked); break;
    case 2: cb_materia->setChecked(box, checked); break;
    case 3: cb_equip->setChecked(box, checked); break;
    case 4: cb_status->setChecked(box, checked); break;
    case 5: cb_order->setChecked(box, checked); break;
    case 6: cb_limit->setChecked(box, checked); break;
    case 7: cb_config->setChecked(box, checked); break;
    case 8: cb_phs->setChecked(box, checked); break;
    case 9: cb_save->setChecked(box, checked); break;
    };
    connectAll();
}
void MenuListWidget::cb_item_one_toggled(bool checked)
{
    Q_EMIT visibleToggled(0, checked);
}
void MenuListWidget::cb_item_two_toggled(bool checked)
{
    Q_EMIT lockedToggled(0, checked);
}
void MenuListWidget::cb_magic_one_toggled(bool checked)
{
    Q_EMIT visibleToggled(1, checked);
}
void MenuListWidget::cb_magic_two_toggled(bool checked)
{
    Q_EMIT lockedToggled(1, checked);
}
void MenuListWidget::cb_materia_one_toggled(bool checked)
{
    Q_EMIT visibleToggled(2, checked);
}
void MenuListWidget::cb_materia_two_toggled(bool checked)
{
    Q_EMIT lockedToggled(2, checked);
}
void MenuListWidget::cb_equip_one_toggled(bool checked)
{
    Q_EMIT visibleToggled(3, checked);
}
void MenuListWidget::cb_equip_two_toggled(bool checked)
{
    Q_EMIT lockedToggled(3, checked);
}
void MenuListWidget::cb_status_one_toggled(bool checked)
{
    Q_EMIT visibleToggled(4, checked);
}
void MenuListWidget::cb_status_two_toggled(bool checked)
{
    Q_EMIT lockedToggled(4, checked);
}
void MenuListWidget::cb_order_one_toggled(bool checked)
{
    Q_EMIT visibleToggled(5, checked);
}
void MenuListWidget::cb_order_two_toggled(bool checked)
{
    Q_EMIT lockedToggled(5, checked);
}
void MenuListWidget::cb_limit_one_toggled(bool checked)
{
    Q_EMIT visibleToggled(6, checked);
}
void MenuListWidget::cb_limit_two_toggled(bool checked)
{
    Q_EMIT lockedToggled(6, checked);
}
void MenuListWidget::cb_config_one_toggled(bool checked)
{
    Q_EMIT visibleToggled(7, checked);
}
void MenuListWidget::cb_config_two_toggled(bool checked)
{
    Q_EMIT lockedToggled(7, checked);
}
void MenuListWidget::cb_phs_one_toggled(bool checked)
{
    Q_EMIT visibleToggled(8, checked);
}
void MenuListWidget::cb_phs_two_toggled(bool checked)
{
    Q_EMIT lockedToggled(8, checked);
}
void MenuListWidget::cb_save_one_toggled(bool checked)
{
    Q_EMIT visibleToggled(9, checked);
}
void MenuListWidget::cb_save_two_toggled(bool checked)
{
    Q_EMIT lockedToggled(9, checked);
}

void MenuListWidget::connectAll()
{
    connect(cb_item, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_item_one_toggled);
    connect(cb_item, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_item_two_toggled);
    connect(cb_magic, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_magic_one_toggled);
    connect(cb_magic, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_magic_two_toggled);
    connect(cb_materia, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_materia_one_toggled);
    connect(cb_materia, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_materia_two_toggled);
    connect(cb_equip, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_equip_one_toggled);
    connect(cb_equip, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_equip_two_toggled);
    connect(cb_status, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_status_one_toggled);
    connect(cb_status, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_status_two_toggled);
    connect(cb_order, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_order_one_toggled);
    connect(cb_order, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_order_two_toggled);
    connect(cb_limit, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_limit_one_toggled);
    connect(cb_limit, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_limit_two_toggled);
    connect(cb_config, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_config_one_toggled);
    connect(cb_config, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_config_two_toggled);
    connect(cb_phs, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_phs_one_toggled);
    connect(cb_phs, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_phs_two_toggled);
    connect(cb_save, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_save_one_toggled);
    connect(cb_save, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_save_two_toggled);
}

void MenuListWidget::disconnectAll()
{
    disconnect(cb_item, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_item_one_toggled);
    disconnect(cb_item, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_item_two_toggled);
    disconnect(cb_magic, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_magic_one_toggled);
    disconnect(cb_magic, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_magic_two_toggled);
    disconnect(cb_materia, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_materia_one_toggled);
    disconnect(cb_materia, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_materia_two_toggled);
    disconnect(cb_equip, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_equip_one_toggled);
    disconnect(cb_equip, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_equip_two_toggled);
    disconnect(cb_status, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_status_one_toggled);
    disconnect(cb_status, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_status_two_toggled);
    disconnect(cb_order, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_order_one_toggled);
    disconnect(cb_order, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_order_two_toggled);
    disconnect(cb_limit, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_limit_one_toggled);
    disconnect(cb_limit, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_limit_two_toggled);
    disconnect(cb_config, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_config_one_toggled);
    disconnect(cb_config, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_config_two_toggled);
    disconnect(cb_phs, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_phs_one_toggled);
    disconnect(cb_phs, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_phs_two_toggled);
    disconnect(cb_save, &DoubleCheckBox::box1Toggled, this, &MenuListWidget::cb_save_one_toggled);
    disconnect(cb_save, &DoubleCheckBox::box2Toggled, this, &MenuListWidget::cb_save_two_toggled);
}

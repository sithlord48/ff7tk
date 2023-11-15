//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QWidget>
#include <QEvent>
#include <ff7tkwidgets_export.h>
#include <DoubleCheckBox>

/** \class MenuListWidget
 *  \brief easily manage the menus in Final Fantasy 7
 */
class FF7TKWIDGETS_EXPORT MenuListWidget : public QWidget
{
    Q_OBJECT
public:
    /** \enum BOX
     *  \brief Acces to Visible and Locked boxes without knowing their index
     */
    enum BOX {
        MENUVISIBLE = 1,
        MENULOCKED = 2
    };
    explicit MenuListWidget(QWidget *parent = nullptr);
protected:
    void changeEvent(QEvent *e);
signals:
    /** \brief SIGNAL: The visible box has changed its checked state
     *  \param row the row (FF7Save::MENUITEMS)
     *  \param checked the new check state
     */
    void visibleToggled(int row, bool checked);

    /** \brief SIGNAL: The locked box has changed its checked state
     *  \param row the row (FF7Save::MENUITEMS)
     *  \param checked the new check state
     */
    void lockedToggled(int row, bool checked);
public slots:
    /** \brief SLOT: set the check state for an item
     *  \param row the row (FF7Save::MENUITEMS)
     *  \param box the box that is being set (MenuListWidget::Box)
     *  \param checked the new check state
     */
    void setChecked(int row, int box, bool checked);

private slots:
    void cb_item_one_toggled(bool checked);
    void cb_item_two_toggled(bool checked);
    void cb_magic_one_toggled(bool checked);
    void cb_magic_two_toggled(bool checked);
    void cb_materia_one_toggled(bool checked);
    void cb_materia_two_toggled(bool checked);
    void cb_equip_one_toggled(bool checked);
    void cb_equip_two_toggled(bool checked);
    void cb_status_one_toggled(bool checked);
    void cb_status_two_toggled(bool checked);
    void cb_order_one_toggled(bool checked);
    void cb_order_two_toggled(bool checked);
    void cb_limit_one_toggled(bool checked);
    void cb_limit_two_toggled(bool checked);
    void cb_config_one_toggled(bool checked);
    void cb_config_two_toggled(bool checked);
    void cb_phs_one_toggled(bool checked);
    void cb_phs_two_toggled(bool checked);
    void cb_save_one_toggled(bool checked);
    void cb_save_two_toggled(bool checked);
private:
    DoubleCheckBox *cb_item = nullptr;
    DoubleCheckBox *cb_magic = nullptr;
    DoubleCheckBox *cb_materia = nullptr;
    DoubleCheckBox *cb_equip = nullptr;
    DoubleCheckBox *cb_status = nullptr;
    DoubleCheckBox *cb_order = nullptr;
    DoubleCheckBox *cb_limit = nullptr;
    DoubleCheckBox *cb_config = nullptr;
    DoubleCheckBox *cb_phs = nullptr;
    DoubleCheckBox *cb_save = nullptr;
    QLabel *lbl_title = nullptr;
    void init_display();
    void connectAll();
    void disconnectAll();
    void updateText();
};

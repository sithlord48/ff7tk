//    SPDX-FileCopyrightText: 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QEvent>
#include <QLabel>
#include <ff7tkwidgets_export.h>
#include <DoubleCheckBox>

/** \class PhsListWidget
 *  \brief Easily manage the who can be in the phs
 *
 *  Ment to be used with FF7Save
 */
class FF7TKWIDGETS_EXPORT PhsListWidget : public QWidget
{
    Q_OBJECT
public:
    /** \enum Box
     *  \brief Acces to Allow and Visible boxes without knowing their index
     */
    enum Box {
        PHSALLOWED = 1/**< 1*/,
        PHSVISIBLE = 2/**< 2*/
    };

    explicit PhsListWidget(QWidget *parent = nullptr);

protected:
    void changeEvent(QEvent *e);

signals:
    /** \brief SIGNAL: The allowed box has changed its checked state
     *  \param row the row its changed in (FF7Char::Char)
     *  \param checked the new check state
     */
    void allowedToggled(int row, bool checked);

    /** \brief SIGNAL: The visible box has changed its checked state
     *  \param row the row its changed in (FF7Char::Char)
     *  \param checked the new check state
     */
    void visibleToggled(int row, bool checked);
public slots:

    /** \brief SLOT: set the check state for an item
     *  \param row the row (char id is row order)
     *  \param box the box that is being set (PhsListWidget::Box)
     *  \param checked the new check state
     */
    void setChecked(int row, int box, bool checked);

private slots:
    void cb_cloud_allowedToggled(bool checked);
    void cb_cloud_visibleToggled(bool checked);
    void cb_barret_allowedToggled(bool checked);
    void cb_barret_visibleToggled(bool checked);
    void cb_tifa_allowedToggled(bool checked);
    void cb_tifa_visibleToggled(bool checked);
    void cb_aerith_allowedToggled(bool checked);
    void cb_aerith_visibleToggled(bool checked);
    void cb_red_allowedToggled(bool checked);
    void cb_red_visibleToggled(bool checked);
    void cb_yuffie_allowedToggled(bool checked);
    void cb_yuffie_visibleToggled(bool checked);
    void cb_cait_allowedToggled(bool checked);
    void cb_cait_visibleToggled(bool checked);
    void cb_vincent_allowedToggled(bool checked);
    void cb_vincent_visibleToggled(bool checked);
    void cb_cid_allowedToggled(bool checked);
    void cb_cid_visibleToggled(bool checked);

private:
    DoubleCheckBox *cb_cloud =  nullptr;
    DoubleCheckBox *cb_barret =  nullptr;
    DoubleCheckBox *cb_tifa =  nullptr;
    DoubleCheckBox *cb_aerith =  nullptr;
    DoubleCheckBox *cb_red =  nullptr;
    DoubleCheckBox *cb_yuffie =  nullptr;
    DoubleCheckBox *cb_cait =  nullptr;
    DoubleCheckBox *cb_vincent =  nullptr;
    DoubleCheckBox *cb_cid =  nullptr;
    QLabel *lbl_phs =  nullptr;
    void init_display();
    void connectAll();
    void disconnectAll();
    void updateText();
};

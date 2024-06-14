//    SPDX-FileCopyrightText: 2012 - 2022 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QWidget>
#include <ff7tkqtwidgets_export.h>

class QCheckBox;
class QLabel;

/** \class DoubleCheckBox
 *  \brief one text two checkable boxes
 *  \todo  remove deprecated Emits on ff7tk 2.0 release
 */
class FF7TKQTWIDGETS_EXPORT DoubleCheckBox : public QWidget
{
    Q_OBJECT
public:
    /** \brief create a new empty Double Checkbox
     *  \param parent parent of this widget
    */
    explicit DoubleCheckBox(QWidget *parent = nullptr);
    /** \brief create a new empty Double Checkbox
     *  \param text Text for this checkbox
     *  \param parent parent of this widget
     */
    explicit DoubleCheckBox(const QString &text, QWidget *parent = nullptr);
    ~DoubleCheckBox() = default;
    /** \brief set the text displayed
     *  \param text Text for this checkbox
     */
    void setText(const QString &text);

    /** \brief set if a box is checked
     *  \param box checkbox (1-2) 1 is closest to text
     *  \param checked is this box checked?
     */
    void setChecked(int box, bool checked);

    /** \brief check if a box has been checked .
     *  \param box checkbox (1-2) 1 is closest to text
     *  \return checkbox checked ?
     */
    bool isChecked(int box);

    /** \brief Set the tooltip for a checkbox
     *  \param box checkbox (1-2) 1 is closest to text
     *  \param text tooltip text
     */
    void setBoxToolTip(int box, const QString &text);

    /** \brief Set the tooltip for the widget
     *  \param text tooltip text
     */
    void setToolTip(const QString &text);

signals:
    /** \brief Signal: box1 has had its state changed
     *  \param checked checked state
     */
    void box1Toggled(bool checked);
    [[ deprecated ("will be removed in ff7tk 2.0, Use DoubleCheckbox::box1Toggled") ]]void box1_toggled(bool checked);

    /** \brief Signal: box2 has had its state changed
     *  \param checked checked state
     */
    void box2Toggled(bool checked);
    [[ deprecated ("will be removed in ff7tk 2.0, Use DoubleCheckbox::box2Toggled") ]]void box2_toggled(bool checked);
private:
    void init_display();
    QCheckBox *cb_one = nullptr;
    QCheckBox *cb_two = nullptr;
    QLabel *label = nullptr;
};

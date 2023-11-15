//    SPDX-FileCopyrightText: 2013 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QWidget>
#include <ff7tkwidgets_export.h>

class QCheckBox;
class QFrame;
class QLabel;
class QPushButton;


/** \class ChocoboLabel
 * \brief A Label to display a single chocobo's brief data.
 */
class FF7TKWIDGETS_EXPORT ChocoboLabel : public QWidget
{
    Q_OBJECT
public:
    /** \brief Create a new Chocobo label.
     *
     *  This Widget is designed to be part of a more complex chocobo manager (chocoboManager) it is useful on its own but will need to be
     * \param parent Parent of this widget
     * \param titleText Name for the box something like "Stable 1 "
     * \param occupied Is there a chocobo here? else set a blank label
     */
    explicit ChocoboLabel(const QString &titleText = nullptr, bool occupied = false, QWidget *parent = nullptr);
    ~ChocoboLabel() = default;
signals:
    void clicked(); /**< \brief Emit Signal: the widget has been clicked*/
    void copy();    /**< \brief Emit Signal: the copy button pressed*/
    void paste();   /**< \brief Emit Signal: the paste button pressed*/
    void remove();  /**< \brief Emit Signal: the remove button pressed*/
    void occupiedToggled(bool occupied); /**< \brief the occupied checkbox has been toggled \param occupied: is this stable occupied?*/
public slots:
    void setSelected(bool selected); /**< \brief Change if the label looks selected. \param selected: is this label selected?*/
    void setType(int type); /**< \brief Set the type of chocobo shown on the label. \param type the type of chocobo 0:yellow 1:green 2:blue 3:black 4:gold. */
    void setName(QString decodedName);/**< \brief Set string to be shown as chocobo's name. \param decodedName: String to be displayed as name. will not be decoded from ff7text format*/
    void setRank(int wins); /**< \brief Show the racing rank of the chocobo. \param wins: number of race wins chocobo has.*/
    void setSex(bool Male); /**< \brief Set the sex of the chocobo. \param Male: is this chocobo a male? \sa setSex(int)*/
    void setSex(int sex);  /**< \brief Set the sex of the chocobo. \param sex: 0:male 1:female \sa setSex(bool)*/
    void setOccupied(bool occupied);/**< \brief Set if the stall is occupied \param occupied: is this stable occupied?*/
    void setTitle(QString title); /**< \brief The occupied checkbox has been toggled \param title: String that will be shown as labels title*/
    void setFontSize(int fontSize); /**< \brief Set the size of the labels font \param fontSize: pointSize of the font for this label*/
    void clearLabel(void); /**< \brief Clear the labels data */
    bool isOccupied(void); /**< \brief occupied state \return true if occupied*/
    //Deprecated Methods
    [[ deprecated ("Now Respects the System palette") ]]
    FF7TKWIDGETS_DEPRECATED void setHoverColorStyle(QString backgroundColor) {/*NOTHING*/} /**< \brief [DEPRECATED: set by system] Set the style for when you hover \param backgroundColor A valid color for a style sheet either a predefined color or rgb(r,g,b) style string */
protected:
    bool event(QEvent *ev);
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent *);
private:
    void enable(bool enabled); /**< \brief enable/disable inner part of the form when needed \param enabled enable the lower frame?*/
    QPushButton *btnCopy = nullptr; /**< \brief copy button */
    QPushButton *btnPaste = nullptr; /**< \brief paste button */
    QPushButton *btnRemove = nullptr; /**< \brief remove button */
    QCheckBox *chkOccupied = nullptr; /**< \brief checkbox to show if occupied */
    QLabel *lblType = nullptr;/**< \brief label to show type */
    QLabel *lblName = nullptr;/**< \brief label to show name */
    QLabel *lblRank = nullptr;/**< \brief label to show rank */
    QLabel *lblSex = nullptr;/**< \brief label to show sex*/
    QFrame *innerFrame = nullptr;/**< \brief inner frame of widget contains all the chocobo into */
    QFrame *outerFrame = nullptr;/**< \brief outer frame of widget contains the label checkbox, copy,paste,remove buttons*/
    int m_wins = -1;
    int m_fontSize = 14;
    bool isSelected;
    bool isEnabled; /**< \brief isEnabled hold if enabled */
    inline static const auto _style = QStringLiteral("QPushButton:enabled{background-color:rgba(0,0,0,0);border:0px solid;} QWidget[HoverStyled=\"true\"]:enabled:hover{background-color: palette(highlight)}");
};

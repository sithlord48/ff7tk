/****************************************************************************/
//    copyright 2012 - 2022 Chris Rizzitello <sithlord48@gmail.com>         //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#pragma once

#include <QWidget>
#include <QEvent>
#include <ff7tkwidgets_export.h>
#include <FF7Materia>

class QComboBox;
class QFrame;
class QGroupBox;
class QHBoxLayout;
class QLabel;
class QListWidget;
class QPushButton;
class QSpacerItem;
class QSpinBox;
/**
 * @brief The MateriaEditor class \n
 * \p MateriaEditor is a Widget that can be used to edit materia in the player's inventory or on a character.
  */
class FF7TKWIDGETS_EXPORT MateriaEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MateriaEditor(QWidget *parent = nullptr, quint8 materia_id = FF7Materia::EmptyId, qint32 ap = FF7Materia::MaxMateriaAp);
    void setMateria(quint8 materia_id = 0, qint32 materia_ap = 0);
    void setAP(qint32 current_ap = 0);
    void setStarsSize(int);
    qint32 ap();
    qint32 MaxAP();
    qint8 id();
    bool isEditable(void);
    void setEditable(bool);

    /**
     * @brief setShowPlaceHolderMateria Sets if the list of possible materia contains the placeholder materia
     * @param showPlaceHolders: True if you want to show the placeholders.
     */
    void setShowPlaceHolderMateria(bool showPlaceHolders);
protected:
    void changeEvent(QEvent *e);
public slots:
    void setEditableMateriaCombo(bool enabled);
private:
    //Private Functions
    void init_display();
    QHBoxLayout *makeNameLayout();
    QWidget *makeStarWidget();
    QWidget *makeSkillWidget();
    QWidget *makeStatWidget();
    void setStars();
    void setName();
    void setStats();
    void setSkills();
    void setLevel();
    void updateESkillList();
    void updatePalette();
    //Private Gui Parts.
    QLabel *lbl_max_ap = nullptr;
    QHBoxLayout *Final = nullptr;
    QComboBox *combo_type = nullptr;
    QComboBox *combo_materia = nullptr;
    QPushButton *btn_paste_materia = nullptr;
    QPushButton *btn_rm_materia = nullptr;
    QPushButton *btn_copy_materia = nullptr;
    QPushButton *btn_eskill_master = nullptr;
    QPushButton *btn_eskill_clear = nullptr;
    QSpinBox *sb_ap = nullptr;
    QFrame *frm_ap = nullptr;
    QFrame *frm_skill_status = nullptr;
    QList<QPushButton *> btn_stars = {nullptr, nullptr, nullptr, nullptr, nullptr};
    QFrame *box_stars = nullptr;
    QGroupBox *box_skills = nullptr;
    QWidget *eskill_group = nullptr;
    QListWidget *eskill_list = nullptr;
    QWidget *eskillButtons = nullptr;
    QListWidget *list_skills = nullptr;
    QGroupBox *box_stats = nullptr;
    QGroupBox *box_status_effects = nullptr;
    QLabel *lbl_stats = nullptr;
    QListWidget *list_status = nullptr;
    QSpacerItem *v_spacer = nullptr;
    QFrame *frm_ap_stars = nullptr;
    QLabel *lbl_materiaIcon = nullptr;
    QLabel *lbl_materiaName = nullptr;
    //Private Data Members
    quint8 _id;// current id
    quint8 buffer_id;
    qint32 buffer_ap;
    qint8 _level;//current level
    qint32 _current_ap;// current ap amount
    QSize _iconSize;
    bool _showPlaceHolders; // Show Materia Named "ID:0x\\d+"
    bool _editable;
    inline static const auto _comboStyle = QStringLiteral("QComboBox { combobox-popup: 0;}");
    inline static const auto _buttonStyle = QStringLiteral("QPushButton:enabled{background-color: rgba(0,0,0,0);border:0px solid;} QPushButton:hover{background-color: palette(highlight);}");
    inline static const auto _buttonHighlightStyle_addition = QStringLiteral(" QPushButton:hover{background-color: palette(highlight);}");
    inline static const auto _itemStyle = QStringLiteral("::indicator:unchecked {image: url(:/materia/command_star_empty);}"
                                                         "::indicator:checked{image: url(:/materia/command_star_full);}"
                                                         "::item{border: 1px solid transparent;}"
                                                         );

private slots:
    void typeChanged(int new_type);
    void materia_changed(const QString &new_name);
    void editMode(void);
    QPushButton *newStyledButton(const QIcon &icon = QIcon(), QKeySequence shortcut = QKeySequence(), const QString &toolip = QString(), QWidget *parent = nullptr);
signals:
    void apChanged(qint32);
    void idChanged(qint8);
};

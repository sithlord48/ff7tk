/****************************************************************************/
//    copyright 2012 -2022  Chris Rizzitello <sithlord48@gmail.com>         //
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
#include <MateriaEditor.h>

#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>

MateriaEditor::MateriaEditor(QWidget *parent, quint8 materia_id, qint32 materia_ap)
    : QWidget(parent)
    , v_spacer(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding))
    , _id(0)
    , buffer_id(0)
    , buffer_ap(0)
    , _current_ap(0)
    , _highlightColor(QStringLiteral("%1,%2,%3,128").arg(QString::number(palette().highlight().color().red()), QString::number(palette().highlight().color().green()), QString::number(palette().highlight().color().blue())))
    , _iconSize (QSize(fontMetrics().height(), fontMetrics().height()))
    , _editable(true)
{
    init_display();
    setMateria(materia_id, materia_ap);
}
void MateriaEditor::init_display()
{
    setContentsMargins(0, 0, 0, 0);

    auto main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(3, 0, 0, 0);
    main_layout->setSpacing(2);
    main_layout->addLayout(makeNameLayout());
    main_layout->addWidget(makeStarWidget());
    main_layout->addWidget(makeSkillWidget());
    main_layout->addWidget(makeStatWidget());

    auto Final = new QVBoxLayout(this);
    Final->setSpacing(0);
    Final->addLayout(main_layout);
    Final->addSpacerItem(v_spacer);
    Final->setContentsMargins(6, 6, 6, 0);
    setLayout(Final);
}

void MateriaEditor::setMateria(quint8 materia_id, qint32 materia_ap)
{
    if (materia_id < 91) {
        //valid Materia..
        if (_id != materia_id) {
            _id = materia_id;
            sb_ap->setEnabled(1);
            Q_EMIT idChanged(qint8(_id));
        }
    } else {
        //Invalid Data Reset Materia.
        if (_id != FF7Materia::EmptyId)
            Q_EMIT idChanged(qint8(FF7Materia::EmptyId));
        _id = FF7Materia::EmptyId;
        sb_ap->setEnabled(false);
        sb_ap->setValue(FF7Materia::MaxMateriaAp);
        _current_ap = FF7Materia::MaxMateriaAp;//set since setAp ingores the 0xFF id.
        box_status_effects->setHidden(true);
        box_stats->setHidden(true);
    }
    setName();
    setAP(materia_ap);
    setStats();
}
void MateriaEditor::setAP(qint32 ap)
{
    if (FF7Materia::levels(_id) == 1) {
        if (_current_ap != ap) {
            _current_ap = ap;
            Q_EMIT apChanged(_current_ap);
        }
        if (_id == FF7Materia::EnemySkill) {
            for (int i = 0; i < 24; i++) {
                if (_current_ap & (1 << i))
                    eskill_list->item(i)->setCheckState(Qt::Checked);
                else
                    eskill_list->item(i)->setCheckState(Qt::Unchecked);
            }
        }
    } else {
        //All Other Materia
        if ((ap < FF7Materia::MaxMateriaAp) && (ap < FF7Materia::apForLevel(_id, FF7Materia::levels(_id) - 1))) {
            _current_ap = ap;
            sb_ap->setValue(_current_ap);
        } else {
            _current_ap = FF7Materia::MaxMateriaAp;
            sb_ap->setValue(FF7Materia::apForLevel(_id, FF7Materia::levels(_id) - 1));
        }
        Q_EMIT apChanged(_current_ap);
    }
    setLevel();
}

void MateriaEditor::setName()
{
    sb_ap->setMaximum(MaxAP());
    lbl_max_ap->setText(QString(" %1").arg(QString::number(MaxAP())));
    frm_ap_stars->setHidden(true);
    if (_id == FF7Materia::EmptyId) {
        combo_type->setCurrentIndex(0);
        combo_materia->setCurrentIndex(-1);
        lbl_materiaName->clear();
        lbl_materiaIcon->setPixmap(QPixmap());
         lbl_max_ap->clear();
    } else {
        lbl_materiaIcon->setPixmap(FF7Materia::pixmap(_id));
        lbl_materiaName->setText(FF7Materia::name(_id));
        if (combo_type->currentIndex() != FF7Materia::AllMaterias)
            combo_type->setCurrentIndex(FF7Materia::type(_id));
        combo_materia->setCurrentIndex(combo_materia->findText(FF7Materia::name(_id)));
        if(FF7Materia::levels(_id) != 1)
            frm_ap_stars->setHidden(false);
    }
}

void MateriaEditor::setStats()
{
    list_status->clear();
    lbl_stats->clear();
    QString title = tr("Skills");
    if (_id != FF7Materia::EmptyId) {
        if (!FF7Materia::element(_id).isEmpty()) {
            title.append("-");
            title.append(FF7Materia::element(_id));
        }
        if (!FF7Materia::statString(_id).isEmpty()) {
            lbl_stats->setText(FF7Materia::statString(_id));
            box_stats->setHidden(false);
        } else {
            box_stats->setHidden(true);
        }
        if (!FF7Materia::status(_id).at(0).toLocal8Bit().isEmpty()) {
            list_status->addItems(FF7Materia::status(_id));
            box_status_effects->setFixedWidth(this->width() / 3);
            box_status_effects->setHidden(false);
        } else {
            box_status_effects->setHidden(true);
        }
        box_skills->setTitle(title);
    }
}
void MateriaEditor::setLevel()
{
    _level = 0;
    if (FF7Materia::levels(_id) == 1){
        _level = 1;
    } else if (_id != FF7Materia::EmptyId) {
        for (int i = 0; i < FF7Materia::levels(_id); i++) {
            if (_current_ap >= FF7Materia::apForLevel(_id, i))
                _level++;
        }
    }
    setStars();
    setSkills();
}

void MateriaEditor::setStars()
{
    //Hide if its eskill Materia
    if (FF7Materia::levels(_id) == 1
     || (_id == FF7Materia::EmptyId)) {
        box_stars->setHidden(true);
        return;
    } else {
        box_stars->setHidden(false);
        for (QPushButton *button : qAsConst(btn_stars))
            button->setHidden(true);
        if (FF7Materia::type(_id) != 0) {
            for (QPushButton *button : qAsConst(btn_stars))
                button->setIcon(FF7Materia::pixmapEmptyStar(_id));
        }
        for (int i = 0 ; i < _level ; i ++)
            btn_stars.at(i)->setIcon(FF7Materia::pixmapFullStar(_id));
        for (int i = 0 ; i < FF7Materia::levels(_id) ; i ++)
            btn_stars.at(i)->setHidden(false);
    }
}

void MateriaEditor::setSkills()
{
    list_skills->clear();
    box_skills->setHidden(false);
    eskill_group->setHidden(true);
    list_skills->setHidden(false);
    v_spacer->changeSize(0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding);

    if (_id == FF7Materia::EmptyId) {
        box_skills->setHidden(true);
        list_skills->setHidden(true);
    } else if (_id == FF7Materia::EnemySkill) {
        list_skills->setHidden(true);
        eskill_group->setHidden(false);
    } else if(_id == FF7Materia::MasterCommand || _id == FF7Materia::MasterSummon || _id == FF7Materia::MasterMagic) {
        list_skills->addItems(FF7Materia::skills(_id));
    } else {
        for (int i = 0; i < _level; i++) {
            if (FF7Materia::skills(_id).count() > i)
                list_skills->addItem(FF7Materia::skills(_id).at(i));
        }
    }
}

void MateriaEditor::typeChanged(int new_type)
{
    combo_materia->clear();
    combo_materia->blockSignals(true);
    if (new_type == 0) {
        for (int i = 0; i < 91; i++) {
            if (FF7Materia::name(i) != "DON'T USE")
                combo_materia->addItem(FF7Materia::icon(i), FF7Materia::name(i));
        }
    } else {
        for (int i = 0; i < 91; i++) {
            if (FF7Materia::type(i) == new_type)
                combo_materia->addItem(FF7Materia::icon(i), FF7Materia::name(i));
        }
    }
    if (_id != FF7Materia::EmptyId)
        combo_materia->setCurrentIndex(combo_materia->findText(FF7Materia::name(_id)));
    else
        combo_materia->setCurrentIndex(-1);
    combo_materia->blockSignals(false);
}

void MateriaEditor::materia_changed(const QString &new_name)
{
    for (quint8 i = 0; i < 91; i++) {
        if (FF7Materia::name(i) == new_name) {
            if (_id != i)
                setMateria(i, _current_ap);
            return;
        }
    }
}

qint32 MateriaEditor::ap(void)
{
    return _current_ap;
}
qint8 MateriaEditor::id(void)
{
    return qint8(_id);
}

qint32 MateriaEditor::MaxAP(void)
{
    if (FF7Materia::levels(_id) == 1)
        return FF7Materia::MaxMateriaAp;
    else
        return FF7Materia::apForLevel(_id, FF7Materia::levels(_id) - 1);
}

void MateriaEditor::setStarsSize(int size)
{
    QSize iconSize(size, size);
    for (QPushButton *button : qAsConst(btn_stars)) {
        button->setFixedSize(iconSize);
        button->setIconSize(iconSize);
    }
    box_stars->setFixedHeight(size + (size / 8));
    setStars();
    box_stars->adjustSize();

    auto layout = dynamic_cast<QGridLayout *>(frm_ap_stars->layout());

    if (size <= fontMetrics().height() * 2) {
        layout->addWidget(box_stars, 0, 0, 1, 1, Qt::AlignLeft);
        layout->addWidget(frm_ap, 0, 1, 1, 1, Qt::AlignRight);
        if (box_stars->sizeHint().height() < frm_ap->sizeHint().height())
            frm_ap_stars->setFixedHeight(frm_ap->sizeHint().height() + 6);
        else
            frm_ap_stars->setFixedHeight(box_stars->sizeHint().height() + 6);
    } else {
        layout->addWidget(box_stars, 0, 0, 1, 1, Qt::AlignLeft);
        layout->addWidget(frm_ap, 1, 0, 1, 1, Qt::AlignLeft);
        frm_ap_stars->setFixedHeight((size + (size / 6)) + (frm_ap->sizeHint().height() + 6));
    }
    frm_ap_stars->adjustSize();
}

bool MateriaEditor::isEditable(void)
{
    return _editable;
}

void MateriaEditor::setEditable(bool edit)
{
    _editable = edit;
    editMode();
}

void MateriaEditor::editMode()
{
    for (QPushButton *button : qAsConst(btn_stars))
        button->blockSignals(!_editable);

    if (_id != FF7Materia::EmptyId)
        sb_ap->setEnabled(_editable);

    btn_paste_materia->setHidden(!_editable);
    btn_rm_materia->setHidden(!_editable);
    combo_materia->setHidden(!_editable);
    combo_type->setHidden(!_editable);

    lbl_materiaIcon->setHidden(_editable);
    lbl_materiaName->setHidden(_editable);
    eskillButtons->setHidden(!_editable);

    if (_editable) {
        for (int i = 0; i < eskill_list->count(); i++)
            eskill_list->item(i)->setFlags(eskill_list->item(i)->flags() |= Qt::ItemIsUserCheckable);

        eskill_list->setStyleSheet(_itemStyle.arg(_highlightColor, QString::number(fontMetrics().height())));
        for (QPushButton *button : qAsConst(btn_stars))
            button->setStyleSheet(_buttonStyle.arg(_highlightColor));
    } else {
        for (int i = 0; i < eskill_list->count(); i++)
            eskill_list->item(i)->setFlags(eskill_list->item(i)->flags() &= ~Qt::ItemIsUserCheckable);
        QString emptyColor = QStringLiteral("0,0,0,0");
        eskill_list->setStyleSheet(_itemStyle.arg(emptyColor, QString::number(fontMetrics().height())));
        for (QPushButton *button : qAsConst(btn_stars))
            button->setStyleSheet(_buttonStyle.arg(emptyColor));
    }
}

void MateriaEditor::setEditableMateriaCombo(bool enabled)
{
    combo_materia->setEditable(enabled);
}

QPushButton *MateriaEditor::newStyledButton(const QIcon &icon, QKeySequence shortcut, const QString &tooltip, QWidget *parent)
{
    auto newButton = new QPushButton(parent);
    newButton->setIcon(icon);
    newButton->setStyleSheet(_buttonStyle.arg(_highlightColor));
    newButton->setShortcut(shortcut);
    newButton->setToolTip(tooltip);
    newButton->setIconSize(_iconSize);
    newButton->setMaximumSize(_iconSize);
    newButton->setFlat(true);
    return newButton;
}

QHBoxLayout *MateriaEditor::makeNameLayout()
{
    combo_type = new QComboBox;
    combo_type->setIconSize(_iconSize);
    combo_type->setMinimumHeight(fontMetrics().height() + fontMetrics().xHeight());
    combo_type->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    combo_type->addItem(FF7Materia::iconAllMateria(), tr("All Materia"));
    combo_type->addItem(FF7Materia::icon(FF7Materia::MasterMagic), tr("Magic"));
    combo_type->addItem(FF7Materia::icon(FF7Materia::MasterSummon), tr("Summon"));
    combo_type->addItem(FF7Materia::icon(FF7Materia::Underwater), tr("Independent"));
    combo_type->addItem(FF7Materia::icon(FF7Materia::StealAsWell), tr("Support"));
    combo_type->addItem(FF7Materia::icon(FF7Materia::MasterCommand), tr("Command"));
    connect(combo_type, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MateriaEditor::typeChanged);

    combo_materia = new QComboBox;
    combo_materia->setIconSize(_iconSize);
    combo_materia->setMinimumHeight(fontMetrics().height());
    combo_materia->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    combo_materia->setInsertPolicy(QComboBox::NoInsert);
    combo_materia->setStyleSheet(QStringLiteral("QComboBox { combobox-popup: 0;}"));
    combo_materia->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    for (int i = 0; i < 91; i++) {
        if (FF7Materia::name(i) != "DON'T USE")
            combo_materia->addItem(FF7Materia::pixmap(i), FF7Materia::name(i));
    }
    connect(combo_materia, &QComboBox::currentTextChanged, this, &MateriaEditor::materia_changed);

    btn_rm_materia = newStyledButton(QIcon::fromTheme(QString("edit-clear"), QPixmap(":/common/edit-clear"))
                                     , QKeySequence::Delete
                                     , tr("Delete")
                                     , this);
    connect(btn_rm_materia, &QPushButton::clicked, this, [this] {
        setMateria(FF7Materia::EmptyId, FF7Materia::MaxMateriaAp);
    });

    btn_copy_materia = newStyledButton(QIcon::fromTheme(QString("edit-copy"), QPixmap(":/common/edit-copy"))
                                       , QKeySequence::Copy
                                       , tr("Copy")
                                       , this);
    connect(btn_copy_materia, &QPushButton::clicked, this, [this] {
        buffer_id = _id;
        buffer_ap = _current_ap;
    });

    btn_paste_materia = newStyledButton(QIcon::fromTheme(QString("edit-paste"), QPixmap(":/common/edit-paste"))
                                        , QKeySequence::Paste
                                        , tr("Paste")
                                        , this);
    connect(btn_paste_materia, &QPushButton::clicked, this, [this] {
        setMateria(buffer_id, buffer_ap);
    });

    lbl_materiaIcon = new QLabel;
    lbl_materiaIcon->setFixedSize(_iconSize);
    lbl_materiaIcon->setScaledContents(true);
    lbl_materiaIcon->setHidden(_editable);

    lbl_materiaName = new QLabel;
    lbl_materiaName->setHidden(_editable);

    auto layout = new QHBoxLayout;
    layout->addWidget(lbl_materiaIcon);
    layout->addWidget(lbl_materiaName);
    layout->addWidget(combo_type);
    layout->addWidget(combo_materia);
    layout->addWidget(btn_copy_materia);
    layout->addWidget(btn_paste_materia);
    layout->addWidget(btn_rm_materia);
    layout->setContentsMargins(3, 0, 0, 0);
    return layout;
}

QWidget *MateriaEditor::makeStarWidget()
{
    sb_ap = new QSpinBox;
    sb_ap->setWrapping(1);
    sb_ap->setAlignment(Qt::AlignCenter);
    sb_ap->setFixedSize(fontMetrics().horizontalAdvance(QChar('W')) * 7, fontMetrics().height() + fontMetrics().xHeight());
    connect(sb_ap, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](const qint32 ap) {
        setAP(ap);
    });

    box_stars = new QFrame;
    for (int i = 0; i < 5; i++) {
        btn_stars.replace(i, newStyledButton());
        if (i < 4) {
            connect(btn_stars.at(i), &QPushButton::clicked, this, [this, i] {
                setAP(FF7Materia::apForLevel(_id, i));
                setLevel();
            });
        } else {
            connect(btn_stars.at(i), &QPushButton::clicked, this, [this] {
                setAP(FF7Materia::MaxMateriaAp);
                setLevel();
            });
        }
    }
    auto lbl_slash = new QLabel(QStringLiteral("/"));
    lbl_slash->setFixedWidth(this->font().pointSize());

    lbl_max_ap = new QLabel;
    frm_ap = new QFrame;

    auto ap_layout = new QHBoxLayout;
    ap_layout->addWidget(sb_ap);
    ap_layout->addWidget(lbl_slash);
    ap_layout->addWidget(lbl_max_ap);
    ap_layout->setContentsMargins(0, 0, 0, 0);
    frm_ap->setLayout(ap_layout);

    auto stars = new QHBoxLayout;
    stars->setContentsMargins(3, 0, 0, 0);
    for (QPushButton *button : qAsConst(btn_stars)) {
        stars->addWidget(button);
    }
    auto spacer = new QSpacerItem(30, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    stars->addSpacerItem(spacer);
    box_stars->setLayout(stars);

    /* Init Skills Area */
    auto layout = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(box_stars, 0, 0, 1, 1, Qt::AlignLeft);
    layout->addWidget(frm_ap, 0, 1, 1, 1, Qt::AlignRight);
    frm_ap_stars = new QFrame();
    frm_ap_stars->setLayout(layout);
    return frm_ap_stars;
}
void MateriaEditor::changeEvent(QEvent *e)
{
    if (e->type() != QEvent::LanguageChange)
        QWidget::changeEvent(e);

    updateESkillList();
    box_skills->setTitle(tr("Skills"));
    box_status_effects->setTitle(tr("Added Effect"));
    box_stats->setTitle(tr("Stat Changes"));
    btn_rm_materia->setToolTip(tr("Delete"));
    btn_paste_materia->setToolTip(tr("Paste"));
    btn_copy_materia->setToolTip(tr("Copy"));
    btn_eskill_master->setText(tr("Master"));
    btn_eskill_clear->setText(tr("Clear"));
    combo_type->setItemText(0, tr("All Materia"));
    combo_type->setItemText(1, tr("Magic"));
    combo_type->setItemText(2, tr("Summon"));
    combo_type->setItemText(3, tr("Independent"));
    combo_type->setItemText(4, tr("Support"));
    combo_type->setItemText(5, tr("Command"));
    typeChanged(combo_type->currentIndex());
    setStats();
    setSkills();
}
void MateriaEditor::updateESkillList()
{
    if (eskill_list) {
        for (int i = 0; i < 24; i++)
            eskill_list->item(i)->setText(FF7Materia::enemySkill(i));
    } else {
        eskill_list = new QListWidget;
        eskill_list->clear();
        //Fill Eskill List.
        for (int i = 0; i < 24; i++) {
            QListWidgetItem *newItem = new QListWidgetItem();
            newItem->setText(FF7Materia::enemySkill(i));
            newItem->setCheckState(Qt::Unchecked);
            eskill_list->addItem(newItem);
        }
    }
}
QWidget *MateriaEditor::makeSkillWidget()
{
    updateESkillList();
    eskill_list->setStyleSheet(_itemStyle.arg(_highlightColor, QString::number(fontMetrics().height())));
    eskill_list->setMinimumHeight(eskill_list->sizeHintForRow(0) * 5 + eskill_list->contentsMargins().top() + eskill_list->contentsMargins().bottom());
    eskill_list->setMaximumHeight(eskill_list->sizeHintForRow(0) * 48 + eskill_list->contentsMargins().top() + eskill_list->contentsMargins().bottom());
    eskill_list->setSelectionMode(QAbstractItemView::NoSelection);
    eskill_list->setUniformItemSizes(true);

    connect(eskill_list, &QListWidget::itemPressed, this, [](QListWidgetItem * item) {
        if (item->flags() & Qt::ItemIsUserCheckable)
            item->setCheckState((item->checkState() ? Qt::Unchecked : Qt::Checked));
    });

    connect(eskill_list, &QListWidget::clicked, this, [this](QModelIndex index) {
        int i = index.row();
        if (eskill_list->item(i)->checkState() == Qt::Checked)
            _current_ap |= (1 << i);
        else
            _current_ap &= ~(1 << i);
        Q_EMIT apChanged(_current_ap);
    });

    btn_eskill_clear = new QPushButton(tr("Clear"));
    connect(btn_eskill_clear, &QPushButton::clicked, this, [this] {
        if (_current_ap != 0)
            setAP(0);
    });

    btn_eskill_master = new QPushButton(tr("Master"));
    connect(btn_eskill_master, &QPushButton::clicked, this, [this] {
        if (_current_ap != FF7Materia::MaxMateriaAp)
            setAP(FF7Materia::MaxMateriaAp);
    });

    auto eSkillButtonLayout = new QHBoxLayout;
    eSkillButtonLayout->addWidget(btn_eskill_master);
    eSkillButtonLayout->addWidget(btn_eskill_clear);

    eskillButtons = new QWidget;
    eskillButtons->setLayout(eSkillButtonLayout);

    auto eskill_layout = new QVBoxLayout;
    eskill_layout->setContentsMargins(0, 0, 0, 0);
    eskill_layout->setSpacing(0);
    eskill_layout->addWidget(eskill_list);
    eskill_layout->addWidget(eskillButtons);

    eskill_group = new QWidget;
    eskill_group->setHidden(true);
    eskill_group->setLayout(eskill_layout);
    eskill_group->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    list_skills = new QListWidget;
    list_skills->addItem(new QListWidgetItem("Item"));
    list_skills->setFixedHeight(list_skills->sizeHintForRow(0) * 5 + list_skills->contentsMargins().top() + list_skills->contentsMargins().bottom() + 3);
    list_skills->setSelectionMode(QAbstractItemView::NoSelection);

    auto skill_layout = new QVBoxLayout;
    skill_layout->setContentsMargins(0, 0, 0, 0);
    skill_layout->setSpacing(2);
    skill_layout->addWidget(list_skills);
    skill_layout->addWidget(eskill_group);

    box_skills = new QGroupBox(tr("Skills"));
    box_skills->setLayout(skill_layout);

    list_status = new QListWidget;
    list_status->setFixedHeight(list_skills->height());
    list_status->setSelectionMode(QAbstractItemView::NoSelection);

    auto status_effect_layout = new QHBoxLayout;
    status_effect_layout->addWidget(list_status);
    status_effect_layout->setContentsMargins(3, 0, 0, 0);

    box_status_effects = new QGroupBox(tr("Added Effect"));
    box_status_effects->setHidden(true);
    box_status_effects->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    box_status_effects->setLayout(status_effect_layout);

    auto skill_status_layout = new QHBoxLayout;
    skill_status_layout->addWidget(box_skills);
    skill_status_layout->addWidget(box_status_effects);

    frm_skill_status = new QFrame;
    frm_skill_status->setContentsMargins(0, 0, 0, 0);
    frm_skill_status->setLayout(skill_status_layout);
    frm_skill_status->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    return frm_skill_status;
}

QWidget *MateriaEditor::makeStatWidget()
{
    lbl_stats = new QLabel;
    auto stat_layout = new QHBoxLayout;
    stat_layout->setContentsMargins(3, 0, 0, 0);
    stat_layout->addWidget(lbl_stats);

    box_stats = new QGroupBox(tr("Stat Changes"));
    box_stats->setHidden(true);
    box_stats->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    box_stats->setLayout(stat_layout);

    return box_stats;
}

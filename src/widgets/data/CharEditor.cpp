//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <CharEditor.h>

#include <QCheckBox>
#include <QComboBox>
#include <QEvent>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QLineEdit>
#include <QListWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QSpinBox>
#include <QToolBox>
#include <QVBoxLayout>

#include <FF7Char>
#include <FF7Item>
#include <FF7Materia>
#include <MateriaEditor>
/**
 * @brief CharEditor::CharEditor
 * @param parent
 * \todo Remove old signals for 2.0
 */
CharEditor::CharEditor(QWidget *parent)
    : QWidget(parent)
    , data(FF7CHAR())
    , elemental_effects(new QListWidget)
    , status_effects(new QListWidget)
    , charWidth(fontMetrics().horizontalAdvance(QChar('W')))
    , lineHeight(fontMetrics().height())
    , sbSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed)
{
    updateText();
    init_display();
    init_connections();
}

void CharEditor::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        updateText();
    } else if(e->type() == QEvent::PaletteChange) {
        weapon_selection->setStyleSheet(comboStyle);
        armor_selection->setStyleSheet(comboStyle);
        accessory_selection->setStyleSheet(comboStyle);
        for(auto m : std::as_const(materiaSlotFrames)) {
            m->setStyleSheet(transparentBackgroundStyle);
        }
    }
    QWidget::changeEvent(e);
}

void CharEditor::updateText()
{
    if (!lineName) {
        lineName = new QLineEdit(this);
        lineName->setMaxLength(11);
        lineName->setMaximumWidth(charWidth * lineName->maxLength());
    }
    lineName->setPlaceholderText(tr("Name"));

    if (!lblCurrentHp) {
        lblCurrentHp = new QLabel(this);
        lblCurrentHp->setSizePolicy(sbSizePolicy);
    }
    lblCurrentHp->setText(tr("Current HP"));

    if (!sbCurrentHp) {
        sbCurrentHp = new QSpinBox(this);
        sbCurrentHp->setMaximum(qint16Max);
        sbCurrentHp->setWrapping(true);
        sbCurrentHp->setAlignment(Qt::AlignHCenter);
        sbCurrentHp->setSizePolicy(sbSizePolicy);
    }
    sbCurrentHp->setToolTip(tr("Current HP"));

    if (!sbBaseHp)
        sbBaseHp = new QSpinBox(this);
    sbBaseHp->setToolTip(tr("Base HP"));

    if (!lblBaseHp)
        lblBaseHp = new QLabel(this);
    lblBaseHp->setText(tr("HP"));

    if (!lblBaseHpBonus)
        lblBaseHpBonus = new QLabel(this);
    lblBaseHpBonus->setToolTip(tr("Materia and Equipment Bonus"));

    if (!lblMaxHp)
        lblMaxHp = new QLabel(this);
    lblMaxHp->setToolTip(tr("Maximum HP"));

    if (!lblCurrentMp) {
        lblCurrentMp = new QLabel(this);
        lblCurrentMp->setSizePolicy(sbSizePolicy);
    }
    lblCurrentMp->setText(tr("Current MP"));

    if (!sbCurrentMp) {
        sbCurrentMp = new QSpinBox(this);
        sbCurrentMp->setMaximum(qint16Max);
        sbCurrentMp->setWrapping(true);
        sbCurrentMp->setAlignment(Qt::AlignHCenter);
        sbCurrentMp->setSizePolicy(sbSizePolicy);
    }
    sbCurrentMp->setToolTip(tr("Current MP"));

    if (!sbBaseMp)
        sbBaseMp = new QSpinBox(this);
    sbBaseMp->setToolTip(tr("Base MP"));

    if (!lblBaseMp)
        lblBaseMp = new QLabel(this);
    lblBaseMp->setText(tr("MP"));

    if (!lblBaseMpBonus)
        lblBaseMpBonus = new QLabel(this);
    lblBaseMpBonus->setToolTip(tr("Materia and Equipment Bonus"));

    if (!lblMaxMp)
        lblMaxMp = new QLabel(this);
    lblMaxMp->setToolTip(tr("Maximum MP"));

    if (!sbLevel) {
        sbLevel = new QSpinBox(this);
        sbLevel->setMaximum(99);
        sbLevel->setSizePolicy(sbSizePolicy);
    }
    sbLevel->setPrefix(tr("Level").append(QStringLiteral(": ")));

    if (!sbLimitLevel){
        sbLimitLevel = new QSpinBox;
        sbLimitLevel->setMaximum(4);
        sbLimitLevel->setWrapping(true);
        sbLimitLevel->setAlignment(Qt::AlignHCenter);
        sbLimitLevel->setSizePolicy(sbSizePolicy);
    }
    sbLimitLevel->setPrefix(tr("Limit Level").append(QStringLiteral(": ")));

    if (!sbKills) {
        sbKills = new QSpinBox(this);
        sbKills->setMaximum(quint16Max);
        sbKills->setWrapping(true);
        sbKills->setSizePolicy(sbSizePolicy);
    }
    sbKills->setPrefix(tr("Kills").append(QStringLiteral(": ")));

    if (!cbFury)
        cbFury = new QCheckBox(this);
    cbFury->setText(tr("Fury"));

    if (!cbSadness)
        cbSadness = new QCheckBox(this);
    cbSadness->setText(tr("Sadness"));

    if (!cbFrontRow)
        cbFrontRow = new QCheckBox(this);
    cbFrontRow->setText(tr("Front Row"));

    if (!lbl_level_next)
        lbl_level_next = new QLabel(this);
    lbl_level_next->setText(tr("Next"));

    if (!sbTotalExp) {
        sbTotalExp = new QSpinBox(this);
        sbTotalExp->setMaximumWidth(fontMetrics().horizontalAdvance(QChar('9')) * 16);
        sbTotalExp->setMaximum(expMax);
        sbTotalExp->setWrapping(true);
    }
    sbTotalExp->setPrefix(tr("Exp: "));

    if (!lbl_0x34)
        lbl_0x34 = new QLabel(this);
    lbl_0x34->setText(tr("0x34"));

    if (!lbl_0x35)
        lbl_0x35 = new QLabel(this);
    lbl_0x35->setText(tr("0x35"));

    if (!lbl_0x36)
        lbl_0x36 = new QLabel(this);
    lbl_0x36->setText(tr("0x36"));

    if (!lbl_0x37)
        lbl_0x37 = new QLabel(this);
    lbl_0x37->setText(tr("0x37"));

    if (!lblStr)
        lblStr = new QLabel(this);
    lblStr->setText(tr("Str"));

    if (!sbStr)
        sbStr = new QSpinBox(this);
    sbStr->setToolTip(tr("Base Strength"));

    if (!sbStrSourceUse)
        sbStrSourceUse = new QSpinBox(this);
    sbStrSourceUse->setToolTip(tr("Power Sources Used"));

    if (!lblStrMateriaBonus)
        lblStrMateriaBonus = new QLabel(this);
    lblStrMateriaBonus->setToolTip(tr("Materia and Equipment Bonus"));

    if (!lblStrTotal)
        lblStrTotal = new QLabel(this);
    lblStrTotal->setToolTip(tr("Strength Stat Total"));

    if (!lblVit)
        lblVit = new QLabel(this);
    lblVit->setText(tr("Vit"));

    if (!sbVit)
        sbVit = new QSpinBox(this);
    sbVit->setToolTip(tr("Base Vitality"));

    if (!sbVitSourceUse)
        sbVitSourceUse = new QSpinBox(this);
    sbVitSourceUse->setToolTip(tr("Guard Sources Used"));

    if (!lblVitMateriaBonus)
        lblVitMateriaBonus = new QLabel(this);
    lblVitMateriaBonus->setToolTip(tr("Materia and Equipment Bonus"));

    if (!lblVitTotal)
        lblVitTotal = new QLabel(this);
    lblVitTotal->setToolTip(tr("Vitality Stat Total"));

    if (!lblMag)
        lblMag = new QLabel(this);
    lblMag->setText(tr("Mag"));

    if (!sbMag)
        sbMag = new QSpinBox(this);
    sbMag->setToolTip(tr("Base Magic"));

    if (!sbMagSourceUse)
        sbMagSourceUse = new QSpinBox(this);
    sbMagSourceUse->setToolTip(tr("Magic Sources Used"));

    if (!lblMagMateriaBonus)
        lblMagMateriaBonus = new QLabel(this);
    lblMagMateriaBonus->setToolTip(tr("Materia and Equipment Bonus"));

    if (!lblMagTotal)
        lblMagTotal = new QLabel(this);
    lblMagTotal->setToolTip(tr("Magic Stat Total"));

    if (!lblSpi)
        lblSpi = new QLabel(this);
    lblSpi->setText(tr("Spi"));

    if (!sbSpi)
        sbSpi = new QSpinBox(this);
    sbSpi->setToolTip(tr("Base Spirit"));

    if (!sbSpiSourceUse)
        sbSpiSourceUse = new QSpinBox(this);
    sbSpiSourceUse->setToolTip(tr("Mind Sources Used"));

    if (!lblSpiMateriaBonus)
        lblSpiMateriaBonus = new QLabel(this);
    lblSpiMateriaBonus->setToolTip(tr("Materia and Equipment Bonus"));

    if (!lblSpiTotal)
        lblSpiTotal = new QLabel(this);
    lblSpiTotal->setToolTip(tr("Spirit Stat Total"));

    if (!lblDex)
        lblDex = new QLabel(this);
    lblDex->setText(tr("Dex"));

    if (!sbDex)
        sbDex = new QSpinBox(this);
    sbDex->setToolTip(tr("Base Dexterity"));

    if (!sbDexSourceUse)
        sbDexSourceUse = new QSpinBox(this);
    sbDexSourceUse->setToolTip(tr("Speed Sources Used"));

    if (!lblDexMateriaBonus)
        lblDexMateriaBonus = new QLabel(this);
    lblDexMateriaBonus->setToolTip(tr("Materia and Equipment Bonus"));

    if (!lblDexTotal)
        lblDexTotal = new QLabel(this);
    lblDexTotal->setToolTip(tr("Dexterity Stat Total"));

    if (!lblLck)
        lblLck = new QLabel(this);
    lblLck->setText(tr("Lck"));

    if (!sbLck)
        sbLck = new QSpinBox(this);
    sbLck->setToolTip(tr("Base Luck"));

    if (!sbLckSourceUse)
        sbLckSourceUse = new QSpinBox(this);
    sbLckSourceUse->setToolTip(tr("Luck Sources Used"));

    if (!lblLckMateriaBonus)
        lblLckMateriaBonus = new QLabel(this);
    lblLckMateriaBonus->setToolTip(tr("Materia and Equipment Bonus"));

    if (!lblLckTotal)
        lblLckTotal = new QLabel(this);
    lblLckTotal->setToolTip(tr("Luck Stat Total"));

    if (!toolbox)
        toolbox = new QToolBox(this);
    toolbox->setItemText(0, tr("Status Info"));
    toolbox->setItemText(1, tr("Equipment"));

    if (!elemental_box)
        elemental_box = new QGroupBox(this);
    elemental_box->setTitle(tr("Elemental Effects"));

    if (!status_box)
        status_box = new QGroupBox(this);
    status_box->setTitle(tr("Status Effects"));

    if (!weapon_box)
        weapon_box = new QGroupBox(this);
    weapon_box->setTitle(tr("Weapon"));

    if (!armor_box)
        armor_box = new QGroupBox(this);
    armor_box->setTitle(tr("Armor"));

    if (!accessory_box)
        accessory_box = new QGroupBox(this);
    accessory_box->setTitle(tr("Accessory"));

    if (!lblWeaponStats)
        lblWeaponStats = new QLabel(this);
    lblWeaponStats->setText(tr("AP:x%1").arg(FF7Item::materiaGrowthRate(data.weapon + 128)));

    if (!lblArmorStats)
        lblArmorStats = new QLabel(this);
    lblArmorStats->setText(tr("AP:x%1").arg(FF7Item::materiaGrowthRate(data.armor + 256)));

    QSize iconSize(lineHeight, lineHeight);

    if(!comboId) {
        comboId = new QComboBox(this);
        comboId->setSizePolicy(sbSizePolicy);
        comboId->setIconSize(iconSize);
        comboId->setHidden(true);
        comboId->setMaxVisibleItems(12);
        for (int i = 0; i <= FF7Char::totalCharacters(); i++)
            comboId->addItem(FF7Char::icon(i), FF7Char::defaultName(i));
    } else {
        for (int i = 0; i <= FF7Char::totalCharacters(); i++)
            comboId->setItemText(i, FF7Char::defaultName(i));
    }

    if (!accessory_selection) {
        accessory_selection = new QComboBox(this);
        accessory_selection->setInsertPolicy(QComboBox::NoInsert);
        accessory_selection->setIconSize(iconSize);
        for (int i = 288; i < 320; i++)
            accessory_selection->addItem(FF7Item::icon(i), FF7Item::name(i));
        accessory_selection->addItem(FF7Item::icon(288), tr("-NONE-"));
    } else {
        for (int i = 0; i < accessory_selection->count() - 1; i++)
            accessory_selection->setItemText(i, FF7Item::name(i + 288));
        accessory_selection->setItemText(accessory_selection->count() - 1, tr("-NONE-"));
    }

    if (!armor_selection) {
        armor_selection = new QComboBox(this);
        armor_selection->setInsertPolicy(QComboBox::NoInsert);
        armor_selection->setIconSize(iconSize);
        for (int i = 256; i < 288; i++)
            armor_selection->addItem(FF7Item::icon(i), FF7Item::name(i));
    } else {
        for (int i = 0; i < armor_selection->count(); i++)
            armor_selection->setItemText(i, FF7Item::name(i + 256));
    }

    if (!weapon_selection) {
        weapon_selection = new QComboBox(this);
        weapon_selection->setInsertPolicy(QComboBox::NoInsert);
        weapon_selection->setIconSize(iconSize);
    } else {
        for (int i = 0; i < weapon_selection->count(); i++)
            weapon_selection->setItemText(i, FF7Item::name(FF7Char::weaponStartingId(data.id) + i));
    }

    if (!lbl_limit_bar)
        lbl_limit_bar = new QLabel(this);
    lbl_limit_bar->setText(tr("Limit Bar"));

    if (!lbl_uses) {
        lbl_uses = new QLabel(this);
        lbl_uses->setAlignment(Qt::AlignHCenter);
    }
    lbl_uses->setText(tr("Limit Uses"));

    if (!lbl_1_1) {
        lbl_1_1 = new QLabel(this);
        lbl_1_1->setFixedWidth(charWidth * 3);
        lbl_1_1->setAlignment(Qt::AlignHCenter);
    }
    lbl_1_1->setText(tr("1-1"));

    if (!lbl_2_1) {
        lbl_2_1 = new QLabel(this);
        lbl_2_1->setFixedWidth(charWidth * 3);
        lbl_2_1->setAlignment(Qt::AlignHCenter);
    }
    lbl_2_1->setText(tr("2-1"));

    if (!lbl_3_1) {
        lbl_3_1 = new QLabel(this);
        lbl_3_1->setFixedWidth(charWidth * 3);
        lbl_3_1->setAlignment(Qt::AlignHCenter);
    }
    lbl_3_1->setText(tr("3-1"));

    if (!list_limits) {
        list_limits = new QListWidget();
        list_limits->addItems(FF7Char::limits(0));
        list_limits->setFixedHeight( (list_limits->sizeHintForRow(0) * 7) + list_limits->contentsMargins().top() + list_limits->contentsMargins().bottom() + 4);
    } else {
        for (int i = 0; i < list_limits->count(); i++)
            list_limits->item(i)->setText(FF7Char::limits(data.id).at(i));
    }

    updateMateriaToolTips();
    status_info();
    elemental_info();
}

void CharEditor::updateMateriaToolTips()
{
    int i =0;
    for(auto button : std::as_const(materiaSlots)) {
        if (data.materias[i].id != FF7Materia::EmptyId)
            button->setToolTip(FF7Materia::name(data.materias[i].id));
        else
            button->setToolTip(QString(tr("-Empty-")));
        i++;
    }
}

void CharEditor::init_display()
{
    lblAvatar = new QLabel(this);
    lblAvatar->setFixedSize(lineHeight * 6, lineHeight * 7);
    lblAvatar->setScaledContents(true);

    cb_idChanger = new QCheckBox(this);
    cb_idChanger->setHidden(true);

    bar_tnl = new QProgressBar(this);
    bar_tnl->setMaximum(61);//strange indeed..
    bar_tnl->setTextVisible(false);
    bar_tnl->setFixedHeight(lineHeight / 2);
    bar_tnl->setFixedWidth(charWidth * 5);

    auto name_level_layout = new QHBoxLayout;
    name_level_layout->addWidget(lineName);
    name_level_layout->addWidget(sbLevel);
    name_level_layout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    auto hp_layout = new QHBoxLayout;
    hp_layout->addWidget(lblCurrentHp);
    hp_layout->addWidget(sbCurrentHp);
    hp_layout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    auto mp_layout = new QHBoxLayout;
    mp_layout->addWidget(lblCurrentMp);
    mp_layout->addWidget(sbCurrentMp);
    mp_layout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    auto barNextLayout = new QHBoxLayout();
    barNextLayout->setContentsMargins(0, 0, 0, 0);
    barNextLayout->addWidget(bar_tnl);
    barNextLayout->addWidget(lbl_level_next);
    barNextLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));

    auto exp_layout = new QHBoxLayout;
    exp_layout->setContentsMargins(0, 0, 0, 0);
    exp_layout->addWidget(sbTotalExp);
    exp_layout->addLayout(barNextLayout);

    auto name_hp_mp_kills_layout = new QVBoxLayout;
    name_hp_mp_kills_layout->addLayout(name_level_layout);
    name_hp_mp_kills_layout->addLayout(hp_layout);
    name_hp_mp_kills_layout->addLayout(mp_layout);
    name_hp_mp_kills_layout->addWidget(sbKills);
    name_hp_mp_kills_layout->addLayout(exp_layout);

    auto fury_sadness_layout = new QVBoxLayout;
    fury_sadness_layout->setContentsMargins(0, 0, 0, 0);
    fury_sadness_layout->addWidget(cbFury);
    fury_sadness_layout->addWidget(cbSadness);

    auto sadness_row_id_layout = new QVBoxLayout;
    sadness_row_id_layout->addLayout(fury_sadness_layout);
    sadness_row_id_layout->addSpacerItem(new QSpacerItem(0, 6, QSizePolicy::Preferred, QSizePolicy::Preferred));
    sadness_row_id_layout->addWidget(cbFrontRow);
    sadness_row_id_layout->addWidget(cb_idChanger);
    sadness_row_id_layout->addSpacerItem(new QSpacerItem(0, 6, QSizePolicy::Preferred, QSizePolicy::Preferred));
    sadness_row_id_layout->addWidget(comboId);
    sadness_row_id_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));

    auto lcdSize = QSize(charWidth * 2, lineHeight);
    lcd_0x34 = new QLCDNumber(2);
    lcd_0x34->setFixedSize(lcdSize);
    lcd_0x34->setHexMode();
    lcd_0x34->setSegmentStyle(QLCDNumber::Flat);
    auto _0x34_layout = new QVBoxLayout;
    _0x34_layout->setContentsMargins(0, 0, 0, 0);
    _0x34_layout->setSpacing(0);
    _0x34_layout->addWidget(lbl_0x34);
    _0x34_layout->addWidget(lcd_0x34);

    lcd_0x35 = new QLCDNumber(2);
    lcd_0x35->setFixedSize(lcdSize);
    lcd_0x35->setHexMode();
    lcd_0x35->setSegmentStyle(QLCDNumber::Flat);
    auto _0x35_layout = new QVBoxLayout;
    _0x35_layout->setContentsMargins(0, 0, 0, 0);
    _0x35_layout->setSpacing(0);
    _0x35_layout->addWidget(lbl_0x35);
    _0x35_layout->addWidget(lcd_0x35);

    lcd_0x36 = new QLCDNumber(2);
    lcd_0x36->setFixedSize(lcdSize);
    lcd_0x36->setHexMode();
    lcd_0x36->setSegmentStyle(QLCDNumber::Flat);
    auto _0x36_layout = new QVBoxLayout;
    _0x36_layout->setContentsMargins(0, 0, 0, 0);
    _0x36_layout->setSpacing(0);
    _0x36_layout->addWidget(lbl_0x36);
    _0x36_layout->addWidget(lcd_0x36);

    lcd_0x37 = new QLCDNumber(2);
    lcd_0x37->setFixedSize(lcdSize);
    lcd_0x37->setHexMode();
    lcd_0x37->setSegmentStyle(QLCDNumber::Flat);
    auto _0x37_layout = new QVBoxLayout;
    _0x37_layout->setContentsMargins(0, 0, 0, 0);
    _0x37_layout->setSpacing(0);
    _0x37_layout->addWidget(lbl_0x37);
    _0x37_layout->addWidget(lcd_0x37);

    auto unknown_layout = new QVBoxLayout;
    unknown_layout->setContentsMargins(0, 0, 0, 0);
    unknown_layout->setSpacing(0);
    unknown_layout->addLayout(_0x34_layout);
    unknown_layout->addLayout(_0x35_layout);
    unknown_layout->addLayout(_0x36_layout);
    unknown_layout->addLayout(_0x37_layout);

    unknown_box = new QFrame;
    unknown_box->setLayout(unknown_layout);
    unknown_box->setVisible(false);

    auto avatar_name_layout = new QHBoxLayout;
    avatar_name_layout->setContentsMargins(0, 0, 0, 0);
    avatar_name_layout->addWidget(lblAvatar);
    avatar_name_layout->addLayout(name_hp_mp_kills_layout);
    avatar_name_layout->addLayout(sadness_row_id_layout);
    avatar_name_layout->addWidget(unknown_box);
    avatar_name_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    auto lower_section = new QVBoxLayout;
    lower_section->setContentsMargins(0, 0, 0, 0);
    lower_section->setSpacing(6);
    lower_section->addWidget(makeStatFrame());
    lower_section->addWidget(makeLimitLayout());

    auto left_Final = new QVBoxLayout;
    left_Final->setContentsMargins(0, 0, 0, 0);
    left_Final->addLayout(avatar_name_layout);
    left_Final->addLayout(lower_section);
    left_Final->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::MinimumExpanding));

    materia_edit  = new MateriaEditor(this);
    materia_edit->setVisible(false);
    materia_edit->setStarsSize(lineHeight * 1.75F);

    auto elemental = new QHBoxLayout();
    elemental->setContentsMargins(3, 3, 3, 3);
    elemental->addWidget(elemental_effects);

    elemental_box->setContentsMargins(3, fontMetrics().height() + 2 , 3, 6);
    elemental_box->setLayout(elemental);
    elemental_box->setHidden(true);

    auto elemental_layout = new QVBoxLayout();
    elemental_layout->setContentsMargins(0, 0, 0, 0);
    elemental_layout->addWidget(elemental_box);
    elemental_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    auto status = new QHBoxLayout();
    status->setContentsMargins(3, 3, 3, 3);
    status->addWidget(status_effects);

    status_box->setContentsMargins(3, fontMetrics().height() + 2, 3, 6);
    status_box->setLayout(status);
    status_box->setHidden(true);

    auto status_layout = new QVBoxLayout();
    status_layout->setContentsMargins(0, 0, 0, 0);
    status_layout->addWidget(status_box);
    status_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    auto effects_layout = new QHBoxLayout();
    effects_layout->setContentsMargins(0, 0, 0, 0);
    effects_layout->addLayout(elemental_layout);
    effects_layout->addLayout(status_layout);
    effects_layout->addSpacerItem(new QSpacerItem(-1, -1, QSizePolicy::Expanding, QSizePolicy::Minimum));
    effects_layout->setSpacing(0);

    for(int i = 0; i< 16; i++) {
        materiaSlots.append(new QPushButton);
        connect(materiaSlots.at(i), &QPushButton::clicked, this, [this, i] {
            materiaSlotClicked(i);
        });
    }

    for(int i = 0; i< 16; i++) {
        materiaSlotFrames.append(new QFrame);
        materiaSlotFrames.at(i)->setStyleSheet(transparentBackgroundStyle);
    }

    weapon_m_link_1 = new QLabel(this);
    weapon_m_link_2 = new QLabel(this);
    weapon_m_link_3 = new QLabel(this);
    weapon_m_link_4 = new QLabel(this);
    auto weapon_materia_slots = new QHBoxLayout;
    weapon_materia_slots->setContentsMargins(0, 0, 0, 0);
    weapon_materia_slots->addLayout(makeMateriaSlotPair(materiaSlots.at(0), materiaSlots.at(1), materiaSlotFrames.at(0), materiaSlotFrames.at(1), weapon_m_link_1));
    weapon_materia_slots->addLayout(makeMateriaSlotPair(materiaSlots.at(2), materiaSlots.at(3), materiaSlotFrames.at(2), materiaSlotFrames.at(3), weapon_m_link_2));
    weapon_materia_slots->addLayout(makeMateriaSlotPair(materiaSlots.at(4), materiaSlots.at(5), materiaSlotFrames.at(4), materiaSlotFrames.at(5), weapon_m_link_3));
    weapon_materia_slots->addLayout(makeMateriaSlotPair(materiaSlots.at(6), materiaSlots.at(7), materiaSlotFrames.at(6), materiaSlotFrames.at(7), weapon_m_link_4));
    weapon_materia_slots->addSpacerItem(new QSpacerItem(-1, -1, QSizePolicy::Expanding, QSizePolicy::Minimum));
    weapon_materia_slots->setSpacing(12);

    weapon_materia_box = new QFrame;
    weapon_materia_box->setLayout(weapon_materia_slots);
    weapon_materia_box->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    weapon_selection->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    weapon_selection->setStyleSheet(comboStyle);

    auto weapon_layout = new QVBoxLayout;
    weapon_layout->setContentsMargins(0, 0, 0, 0);
    weapon_layout->addWidget(weapon_selection);
    weapon_layout->addWidget(lblWeaponStats);
    weapon_layout->addWidget(weapon_materia_box);

    weapon_box->setLayout(weapon_layout);
    weapon_box->adjustSize();
    //set up materia slots and box for armor.

    armor_m_link_1 = new QLabel(this);
    armor_m_link_2 = new QLabel(this);
    armor_m_link_3 = new QLabel(this);
    armor_m_link_4 = new QLabel(this);
    auto armor_materia_slots = new QHBoxLayout();
    armor_materia_slots->setContentsMargins(0, 0, 0, 0);
    armor_materia_slots->addLayout(makeMateriaSlotPair(materiaSlots.at(8), materiaSlots.at(9), materiaSlotFrames.at(8), materiaSlotFrames.at(9), armor_m_link_1));
    armor_materia_slots->addLayout(makeMateriaSlotPair(materiaSlots.at(10), materiaSlots.at(11), materiaSlotFrames.at(10), materiaSlotFrames.at(11), armor_m_link_2));
    armor_materia_slots->addLayout(makeMateriaSlotPair(materiaSlots.at(12), materiaSlots.at(13), materiaSlotFrames.at(12), materiaSlotFrames.at(13), armor_m_link_3));
    armor_materia_slots->addLayout(makeMateriaSlotPair(materiaSlots.at(14), materiaSlots.at(15), materiaSlotFrames.at(14), materiaSlotFrames.at(15), armor_m_link_4));
    armor_materia_slots->addSpacerItem(new QSpacerItem(-1, -1, QSizePolicy::Expanding, QSizePolicy::Minimum));
    armor_materia_slots->setSpacing(12);

    armor_materia_box = new QFrame(this);
    armor_materia_box->setLayout(armor_materia_slots);
    armor_materia_box->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    armor_selection->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    armor_selection->setStyleSheet(comboStyle);

    auto armor_layout = new QVBoxLayout;
    armor_layout->setContentsMargins(0, 0, 0, 0);
    armor_layout->addWidget(armor_selection);
    armor_layout->addWidget(lblArmorStats);
    armor_layout->addWidget(armor_materia_box);

    armor_box->setLayout(armor_layout);

    accessory_selection->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    accessory_selection->setStyleSheet(comboStyle);

    auto accessory_layout = new QVBoxLayout;
    accessory_layout->setContentsMargins(0, 0, 0, 0);
    accessory_layout->addWidget(accessory_selection);

    accessory_box->setLayout(accessory_layout);

    auto right_Top = new QVBoxLayout;
    right_Top->setContentsMargins(0, 0, 0, 0);
    right_Top->addWidget(weapon_box);
    right_Top->addWidget(armor_box);
    right_Top->addWidget(accessory_box);

    auto right_top = new QWidget;
    right_top->setContentsMargins(0, 0, 0, 0);
    right_top->setLayout(right_Top);

    auto right_bottom = new QVBoxLayout;
    right_bottom->setContentsMargins(0, 0, 0, 0);
    right_bottom->addWidget(materia_edit);
    right_bottom->addLayout(effects_layout);

    auto right_Final = new QVBoxLayout;
    right_Final->setContentsMargins(3, 0, 3, 0);
    right_Final->addWidget(right_top);
    right_Final->setSpacing(3);
    right_Final->addLayout(right_bottom);

    auto tabStatus = new QFrame;
    tabStatus->setLayout(left_Final);
    tabStatus->adjustSize();
    toolbox->addItem(tabStatus, FF7Char::icon(0), tr("Status Info"));

    auto tabEquipment = new QFrame;
    tabEquipment->setLayout(right_Final);
    tabEquipment->adjustSize();
    toolbox->addItem(tabEquipment, QIcon(FF7Item::icon(256)), tr("Equipment"));

    auto toolbox_layout = new QVBoxLayout;
    toolbox_layout->setContentsMargins(0, 0, 0, 0);
    toolbox_layout->addWidget(toolbox);

    setLayout(toolbox_layout);
}

void CharEditor::setToolBoxStyle(const QString &stylesheet)
{
    toolbox->setStyleSheet(stylesheet);
}

void CharEditor::setSliderStyle(const QString &style)
{
    slider_limit->setStyleSheet(style);
}

void CharEditor::init_connections()
{
    connect(cb_idChanger, &QCheckBox::toggled, this, &CharEditor::cb_idChanger_toggled);
    connect(sbLevel, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::Level_Changed);
    connect(sbCurrentMp, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setCurMp);
    connect(sbCurrentHp, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setCurHp);
    connect(sbBaseHp, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setBaseHp);
    connect(sbBaseMp, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setBaseMp);
    connect(sbKills, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setKills);
    connect(lineName, &QLineEdit::textChanged, this, &CharEditor::setName);
    connect(cbFrontRow, &QCheckBox::toggled, this, &CharEditor::setRow);
    connect(cbFury, &QCheckBox::toggled, this, &CharEditor::cb_fury_toggled);
    connect(cbSadness, &QCheckBox::toggled, this, &CharEditor::cb_sadness_toggled);
    connect(sbStr, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setStr);
    connect(sbStrSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setStrBonus);
    connect(sbVit, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setVit);
    connect(sbVitSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setVitBonus);
    connect(sbMag, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setMag);
    connect(sbMagSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setMagBonus);
    connect(sbSpi, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setSpi);
    connect(sbSpiSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setSpiBonus);
    connect(sbDex, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setDex);
    connect(sbDexSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setDexBonus);
    connect(sbLck, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setLck);
    connect(sbLckSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setLckBonus);
    connect(slider_limit, QOverload<int>::of(&QSlider::valueChanged), this, &CharEditor::setLimitBar);
    connect(sbTotalExp, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::Exp_Changed);
    connect(slider_limit, QOverload<int>::of(&QSlider::valueChanged),lcdLimitValue, QOverload<int>::of(&QLCDNumber::display));
    connect(list_limits, &QListWidget::clicked, this, &CharEditor::calc_limit_value);
    connect(sb_uses_limit_1_1, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setTimesused1);
    connect(sb_uses_limit_2_1, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setTimesused2);
    connect(sb_uses_limit_3_1, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setTimesused3);
    connect(sbLimitLevel, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setLimitLevel);
    connect(comboId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharEditor::setId);
    connect(weapon_selection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharEditor::setWeapon);
    connect(armor_selection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharEditor::setArmor);
    connect(accessory_selection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharEditor::setAccessory);
    connect(materia_edit, &MateriaEditor::apChanged, this, &CharEditor::matAp_changed);
    connect(materia_edit, &MateriaEditor::idChanged, this, &CharEditor::matId_changed);
}

void CharEditor::disconnectAll()
{
    disconnect(cb_idChanger, &QCheckBox::toggled, this, &CharEditor::cb_idChanger_toggled);
    disconnect(sbLevel, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::Level_Changed);
    disconnect(sbCurrentMp, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setCurMp);
    disconnect(sbCurrentHp, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setCurHp);
    disconnect(sbBaseHp, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setBaseHp);
    disconnect(sbBaseMp, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setBaseMp);
    disconnect(sbKills, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setKills);
    disconnect(lineName, &QLineEdit::textChanged, this, &CharEditor::setName);
    disconnect(cbFrontRow, &QCheckBox::toggled, this, &CharEditor::setRow);
    disconnect(cbFury, &QCheckBox::toggled, this, &CharEditor::cb_fury_toggled);
    disconnect(cbSadness, &QCheckBox::toggled, this, &CharEditor::cb_sadness_toggled);
    disconnect(sbStr, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setStr);
    disconnect(sbStrSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setStrBonus);
    disconnect(sbVit, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setVit);
    disconnect(sbVitSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setVitBonus);
    disconnect(sbMag, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setMag);
    disconnect(sbMagSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setMagBonus);
    disconnect(sbSpi, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setSpi);
    disconnect(sbSpiSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setSpiBonus);
    disconnect(sbDex, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setDex);
    disconnect(sbDexSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setDexBonus);
    disconnect(sbLck, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setLck);
    disconnect(sbLckSourceUse, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setLckBonus);
    disconnect(slider_limit, QOverload<int>::of(&QSlider::valueChanged), this, &CharEditor::setLimitBar);
    disconnect(sbTotalExp, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::Exp_Changed);
    disconnect(slider_limit, QOverload<int>::of(&QSlider::valueChanged),lcdLimitValue, QOverload<int>::of(&QLCDNumber::display));
    disconnect(list_limits, &QListWidget::clicked, this, &CharEditor::calc_limit_value);
    disconnect(sb_uses_limit_1_1, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setTimesused1);
    disconnect(sb_uses_limit_2_1, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setTimesused2);
    disconnect(sb_uses_limit_3_1, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setTimesused3);
    disconnect(sbLimitLevel, QOverload<int>::of(&QSpinBox::valueChanged), this, &CharEditor::setLimitLevel);
    disconnect(comboId, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharEditor::setId);
    disconnect(weapon_selection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharEditor::setWeapon);
    disconnect(armor_selection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharEditor::setArmor);
    disconnect(accessory_selection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CharEditor::setAccessory);
    disconnect(materia_edit, &MateriaEditor::apChanged, this, &CharEditor::matAp_changed);
    disconnect(materia_edit, &MateriaEditor::idChanged, this, &CharEditor::matId_changed);
}

quint8 CharEditor::id()
{
    return data.id;
}

quint8 CharEditor::level()
{
    return data.level;
}

quint8 CharEditor::str()
{
    return data.strength;
}

quint8 CharEditor::vit()
{
    return data.vitality;
}

quint8 CharEditor::mag()
{
    return data.magic;
}

quint8 CharEditor::spi()
{
    return data.spirit;
}

quint8 CharEditor::dex()
{
    return data.dexterity;
}

quint8 CharEditor::lck()
{
    return data.luck;
}

quint8 CharEditor::strBonus()
{
    return data.strength_bonus;
}

quint8 CharEditor::vitBonus()
{
    return data.vitality_bonus;
}

quint8 CharEditor::magBonus()
{
    return data.magic_bonus;
}

quint8 CharEditor::spiBonus()
{
    return data.spirit_bonus;
}

quint8 CharEditor::dexBonus()
{
    return data.dexterity_bonus;
}

quint8 CharEditor::lckBonus()
{
    return data.luck_bonus;
}

qint8 CharEditor::limitLevel()
{
    return data.limitlevel;
}

quint8 CharEditor::limitBar()
{
    return data.limitbar;
}

QString CharEditor::name()
{
    return lineName->text();
}

quint8 CharEditor::weapon()
{
    return data.weapon;
}

quint8 CharEditor::armor()
{
    return data.armor;
}

quint8 CharEditor::accessory()
{
    return data.accessory;
}

quint16 CharEditor::curHp()
{
    return data.curHP;
}

quint16 CharEditor::maxHp()
{
    return data.maxHP;
}

quint16 CharEditor::curMp()
{
    return data.curMP;
}

quint16 CharEditor::maxMp()
{
    return data.maxMP;
}

quint16 CharEditor::kills()
{
    return data.kills;
}

quint8 CharEditor::row()
{
    return data.rowFlag;
}

quint8 CharEditor::levelProgress()
{
    return data.tnlFlag;
}

quint8 CharEditor::sadnessfury()
{
    return data.statusFlag;
}

quint16 CharEditor::limits()
{
    return data.limits;
}

quint16 CharEditor::timesused1()
{
    return data.timesused1;
}

quint16 CharEditor::timesused2()
{
    return data.timesused2;
}

quint16 CharEditor::timesused3()
{
    return data.timesused3;
}

quint16 CharEditor::baseHp()
{
    return data.baseHP;
}

quint16 CharEditor::baseMp()
{
    return data.baseMP;
}

quint32 CharEditor::exp()
{
    return data.exp;
}

quint32 CharEditor::expNext()
{
    return data.expNext;
}

materia CharEditor::char_materia(int mat)
{
    return data.materias[mat];
}

void CharEditor::Exp_Changed(int exp)
{
    if (quint32(exp) != data.exp) {
        setExp(exp);
        if (autolevel) {
            if ((data.exp >= FF7Char::totalExpForLevel(data.id, data.level)) || (data.exp <= FF7Char::totalExpForLevel(data.id, data.level - 1))) {
                int level = 0;
                int prev_level = data.level;
                for (int i = level; i < 99; i++) {
                    if (data.exp >= FF7Char::totalExpForLevel(data.id, i))
                        level++;
                }
                sbLevel->blockSignals(true);
                sbLevel->setValue(level);
                setLevel(level);
                sbLevel->blockSignals(false);
                level_up(prev_level);
            }
            update_tnl_bar();
        }
    }
}

void CharEditor::Level_Changed(int level)
{
    if (level != data.level) {
        if (autolevel) {
            int prev_level = data.level;
            setLevel(level);
            if (level <= 0)
                setExp(0);
            else
                setExp(int(FF7Char::totalExpForLevel(data.id, level - 1)));
            sbTotalExp->blockSignals(true);
            sbTotalExp->setValue(int(data.exp));
            sbTotalExp->blockSignals(false);
            level_up(prev_level);
            update_tnl_bar();
        } else {
            setLevel(level);
        }
    }
}
void CharEditor::setChar(const FF7CHAR &Chardata, const QString &Processed_Name)
{
    disconnectAll();// remove all connections. safer signal blocking!
    if(data.id != Chardata.id)
        materiaSlotClicked(-1);

    data = Chardata;
    _name = Processed_Name;
    //more here like setting the gui stuff.
    lblAvatar->setPixmap(FF7Char::pixmap(data.id));
    lineName->setText(_name);
    sbLevel->setValue(data.level);
    sbCurrentMp->setValue(data.curMP);
    sbCurrentHp->setValue(data.curHP);
    lblMaxHp->setNum(data.maxHP);
    lblMaxMp->setNum(data.maxMP);
    sbKills->setValue(data.kills);
    comboId->setCurrentIndex(data.id);
    cbFury->setChecked(data.statusFlag == FF7Char::Fury);
    cbSadness->setChecked(data.statusFlag == FF7Char::Sadness);
    cbFrontRow->setChecked(data.rowFlag == FF7Char::FrontRow);
    sbTotalExp->setValue(int(data.exp));
    lbl_level_next->setText(tr("Next: %1").arg(QString::number(data.expNext)));
    slider_limit->setValue(data.limitbar);
    lcdLimitValue->display(int(data.limitbar));
    bar_tnl->setValue(data.tnlFlag);
    sbStr->setValue(data.strength);
    sbStrSourceUse->setValue(data.strength_bonus);
    sbVit->setValue(data.vitality);
    sbVitSourceUse->setValue(data.vitality_bonus);
    sbDex->setValue(data.dexterity);
    sbDexSourceUse->setValue(data.dexterity_bonus);
    sbMag->setValue(data.magic);
    sbMagSourceUse->setValue(data.magic_bonus);
    sbSpi->setValue(data.spirit);
    sbSpiSourceUse->setValue(data.spirit_bonus);
    sbLck->setValue(data.luck);
    sbLckSourceUse->setValue(data.luck_bonus);
    sbBaseHp->setValue(data.baseHP);
    sbBaseMp->setValue(data.baseMP);

    if (data.id == FF7Char::CaitSith || data.id == FF7Char::Vincent || data.id == FF7Char::YoungCloud || data.id == FF7Char::Sephiroth) {
        cb_idChanger->setHidden(advancedMode);
        if (data.id == FF7Char::CaitSith || data.id == FF7Char::YoungCloud) {
            cb_idChanger->setText(tr("Young Cloud"));
            cb_idChanger->setCheckState((data.id == FF7Char::CaitSith) ? Qt::Unchecked : Qt::Checked);
        }
        if (data.id == FF7Char::Vincent || data.id == FF7Char::Sephiroth) {
            cb_idChanger->setText(tr("Sephiroth"));
            cb_idChanger->setCheckState((data.id == FF7Char::Vincent) ? Qt::Unchecked : Qt::Checked);
        }
    } else {
        cb_idChanger->setHidden(true);
    }

    for(int i =0; i< list_limits->count(); i++) {
        list_limits->item(i)->setText(FF7Char::limits(data.id).at(i));
        list_limits->item(i)->setHidden((list_limits->item(i)->text().isEmpty()));
        list_limits->item(i)->setCheckState((data.limits & (1 << FF7Char::limitBitConvert(i)))? Qt::Checked : Qt::Unchecked );
    }

    sb_uses_limit_1_1->setValue(data.timesused1);
    sb_uses_limit_2_1->setValue(data.timesused2);
    sb_uses_limit_3_1->setValue(data.timesused3);
    sbLimitLevel->setValue(data.limitlevel);

    weapon_selection->clear();
    for (int i = FF7Char::weaponStartingId(data.id); i < FF7Char::numberOfWeapons(data.id) + FF7Char::weaponStartingId(data.id); i++)
        weapon_selection->addItem(FF7Item::icon(i), FF7Item::name(i));
    weapon_selection->setCurrentIndex(data.weapon - FF7Char::weaponOffset(data.id));

    if (weapon_selection->currentText().isEmpty()) {
        data.weapon = quint8(FF7Char::weaponOffset(data.id));
        weapon_selection->setCurrentIndex(data.weapon - FF7Char::weaponOffset(data.id));
    }

    armor_selection->setCurrentIndex(data.armor);

    if (data.accessory != FF7Char::EmptyAccessory)
        accessory_selection->setCurrentIndex(data.accessory);
    else
        accessory_selection->setCurrentIndex(32);

    //set the unknowns
    lcd_0x34->display(data.z_4[0]);
    lcd_0x35->display(data.z_4[1]);
    lcd_0x36->display(data.z_4[2]);
    lcd_0x37->display(data.z_4[3]);
    elemental_info();
    status_info();
    materiaSlotClicked(mslotsel);
    update_materia_slots();
    init_connections();//reconnect all
}

void CharEditor::setLevel(int level)
{
    if (data.level == level)
        return;
    data.level = quint8(std::clamp(level, 0, 99));
    Q_EMIT levelChanged(data.level);
    Q_EMIT levelChanged(qint8(data.level));
/* Remove for 2.0 */Q_EMIT level_changed(qint8(data.level));
}

void CharEditor::cb_sadness_toggled(bool sad)
{
    if (sad) {
        setSadnessFury(FF7Char::Sadness);
        cbFury->blockSignals(true);
        cbFury->setChecked(false);
        cbFury->blockSignals(false);
    } else {
        setSadnessFury(0);
    }
}

void CharEditor::cb_fury_toggled(bool fury)
{
    if (fury) {
        setSadnessFury(FF7Char::Fury);
        cbSadness->blockSignals(true);
        cbSadness->setChecked(false);
        cbSadness->blockSignals(false);
    } else {
        setSadnessFury(0);
    }
}

void CharEditor::setMaxHp(int maxHp)
{
    if (data.maxHP == maxHp)
        return;
    data.maxHP = quint16(std::clamp(maxHp, 0, qint16Max));
    Q_EMIT maxHpChanged(data.maxHP);
/* Remove for 2.0 */Q_EMIT maxHp_changed(data.maxHP);
}

void CharEditor::setCurHp(int curHp)
{
    if (data.curHP == curHp)
        return;
    data.curHP = quint16(std::clamp(curHp, 0, qint16Max));
    Q_EMIT curHpChanged(data.curHP);
/* Remove for 2.0 */Q_EMIT curHp_changed(data.curHP);
}

void CharEditor::setMaxMp(int maxMp)
{
    if (data.maxMP == maxMp)
        return;
    data.maxMP = quint16(std::clamp(maxMp, 0, qint16Max));
    Q_EMIT maxMpChanged(data.maxMP);
/* Remove for 2.0 */Q_EMIT maxMp_changed(data.maxMP);
}

void CharEditor::setCurMp(int curMp)
{
    if (data.curMP == curMp)
        return;
    data.curMP = quint16(std::clamp(curMp, 0, qint16Max));
    Q_EMIT curMpChanged(data.curMP);
/* Remove for 2.0 */Q_EMIT curMp_changed(data.curMP);
}

void CharEditor::setKills(int kills)
{
    if (data.kills == kills)
        return;
    data.kills = quint16(std::clamp(kills, 0, quint16Max));
    Q_EMIT killsChanged(data.kills);
/* Remove for 2.0 */Q_EMIT kills_changed(data.kills);
}

void CharEditor::setName(const QString &name)
{
    if (_name == name)
        return;
    _name = name;
    Q_EMIT nameChanged(_name);
/* Remove for 2.0 */Q_EMIT name_changed(_name);
}

void CharEditor::setId(int id)
{
    if (data.id == id)
        return;
    if (id < 0)
        data.id = 0;
    else if (id > 0x0B)
        data.id = FF7Char::Empty;
    else
        data.id = quint8(id);
    setWeapon(0);
    setChar(data, lineName->text());
    Q_EMIT idChanged(qint8(data.id));
/* Remove for 2.0 */Q_EMIT id_changed(qint8(data.id));
}

void CharEditor::setStr(int strength)
{
    if (data.strength == strength)
        return;
    data.strength = quint8(std::clamp(strength, 0, quint8Max));
    Q_EMIT strengthChanged(data.strength);
/* Remove for 2.0 */Q_EMIT str_changed(data.strength);
    calc_stats();
}

void CharEditor::setVit(int vitality)
{
    if (data.vitality == vitality)
        return;
    data.vitality = quint8(std::clamp(vitality, 0, quint8Max));
    Q_EMIT vitalityChanged(data.vitality);
/* Remove for 2.0 */Q_EMIT vit_changed(data.vitality);
    calc_stats();
}

void CharEditor::setMag(int magic)
{
    if (data.magic == magic)
        return;
    data.magic = quint8(std::clamp(magic, 0, quint8Max));
    Q_EMIT magicChanged(data.magic);
/* Remove for 2.0 */Q_EMIT mag_changed(data.magic);
    calc_stats();
}

    void CharEditor::setSpi(int spirit)
{
    if (data.spirit == spirit)
        return;
    data.spirit = quint8(std::clamp(spirit, 0, quint8Max));
    Q_EMIT spiritChanged(data.spirit);
/* Remove for 2.0 */Q_EMIT spi_changed(data.spirit);
    calc_stats();
}

void CharEditor::setDex(int dexterity)
{
    if (data.dexterity == dexterity)
        return;
    data.dexterity = quint8(std::clamp(dexterity, 0, quint8Max));
    Q_EMIT dexterityChanged(data.dexterity);
/* Remove for 2.0 */Q_EMIT dex_changed(data.dexterity);
    calc_stats();
}

void CharEditor::setLck(int luck)
{
    if (data.luck == luck)
        return;
    data.luck = quint8(std::clamp(luck, 0, quint8Max));
    Q_EMIT luckChanged(data.luck);
/* Remove for 2.0 */Q_EMIT lck_changed(data.luck);
    calc_stats();
}

void CharEditor::setStrBonus(int strength_bonus)
{
    if (data.strength_bonus == strength_bonus)
        return;
    data.strength_bonus = quint8(std::clamp(strength_bonus, 0, quint8Max));
    Q_EMIT strengthBonusChanged(data.strength_bonus);
/* Remove for 2.0 */Q_EMIT strBonus_changed(data.strength_bonus);
    calc_stats();
}

void CharEditor::setVitBonus(int vitality_bonus)
{
    if (data.vitality_bonus == vitality_bonus)
        return;
    data.vitality_bonus = quint8(std::clamp(vitality_bonus, 0, quint8Max));
    Q_EMIT vitalityBonusChanged(data.vitality_bonus);
/* Remove for 2.0 */Q_EMIT vitBonus_changed(data.vitality_bonus);
    calc_stats();
}

void CharEditor::setMagBonus(int magic_bonus)
{
    if (data.magic_bonus == magic_bonus)
        return;
    data.magic_bonus = quint8(std::clamp(magic_bonus, 0, quint8Max));
    Q_EMIT magicBonusChanged(data.magic_bonus);
/* Remove for 2.0 */Q_EMIT magBonus_changed(data.magic_bonus);
    calc_stats();
}

void CharEditor::setSpiBonus(int spirit_bonus)
{
    if (data.spirit_bonus == spirit_bonus)
        return;
    data.spirit_bonus = quint8(std::clamp(spirit_bonus, 0, quint8Max));
    Q_EMIT spiritBonusChanged(data.spirit_bonus);
/* Remove for 2.0 */Q_EMIT spiBonus_changed(data.spirit_bonus);
    calc_stats();
}

void CharEditor::setDexBonus(int dexterity_bonus)
{
    if (data.dexterity_bonus == dexterity_bonus)
        return;
    data.dexterity_bonus = quint8(std::clamp(dexterity_bonus, 0, quint8Max));
    Q_EMIT dexterityBonusChanged(data.dexterity_bonus);
/* Remove for 2.0 */Q_EMIT dexBonus_changed(data.dexterity_bonus);
    calc_stats();
}

void CharEditor::setLckBonus(int luck_bonus)
{
    if (data.luck_bonus == luck_bonus)
        return;
    data.luck_bonus = quint8(std::clamp(luck_bonus, 0, quint8Max));
    Q_EMIT luckBonusChanged(data.luck_bonus);
/* Remove for 2.0 */Q_EMIT lckBonus_changed(data.luck_bonus);
    calc_stats();
}

void CharEditor::setLimitLevel(int limitlevel)
{
    if (data.limitlevel == limitlevel)
        return;
    data.limitlevel = qint8(std::clamp(limitlevel, 0, 4));
    Q_EMIT limitLevelChanged(data.limitlevel);
/* Remove for 2.0 */Q_EMIT limitLevel_changed(data.limitlevel);
}

void CharEditor::setLimitBar(int limitbar)
{
    if (data.limitbar == limitbar)
        return;
    data.limitbar = quint8(std::clamp(limitbar, 0, quint8Max));
    Q_EMIT limitBarChanged(data.limitbar);
/* Remove for 2.0 */Q_EMIT limitBar_changed(data.limitbar);
}

void CharEditor::setWeapon(int weapon)
{
    if (weapon == (data.weapon - FF7Char::weaponOffset(data.id)) && data.id != FF7Char::Sephiroth)
        return;
    if (weapon < 0)
        data.weapon = quint8(FF7Char::weaponOffset(data.id));
    else if (weapon > FF7Char::numberOfWeapons(data.id))
        data.weapon = quint8(FF7Char::numberOfWeapons(data.id) + FF7Char::weaponOffset(data.id));
    else
        data.weapon = quint8(weapon + FF7Char::weaponOffset(data.id));
    Q_EMIT weaponChanged(data.weapon);
/* Remove for 2.0 */Q_EMIT weapon_changed(data.weapon);

    elemental_info();
    status_info();
    update_materia_slots();
    if (mslotsel >= 0 && mslotsel <= 7)
        materiaSlotClicked(-1);
}

void CharEditor::setArmor(int armor)
{
    if (armor == data.armor)
        return;
    if (armor < 0)
        data.armor = 0;
    else if (armor > 32)
        data.armor = FF7Char::EmptyArmor;
    else
        data.armor = quint8(armor);
    Q_EMIT armorChanged(data.armor);
/* Remove for 2.0 */Q_EMIT armor_changed(data.armor);
    elemental_info();
    status_info();
    update_materia_slots();
    if(mslotsel >= 8 && mslotsel <= 15)
        materiaSlotClicked(-1);
}

void CharEditor::setAccessory(int accessory)
{
    if (accessory == data.accessory)
        return;
    if (accessory < 0)
        data.accessory = 0;
    else if (accessory > 32)
        data.accessory = FF7Char::EmptyAccessory;
    else
        data.accessory = quint8(accessory);
    Q_EMIT accessoryChanged(data.accessory);
/* Remove for 2.0 */Q_EMIT accessory_changed(data.accessory);
    elemental_info();
    status_info();
    calc_stats();
}

void CharEditor::setSadnessFury(int sad_fury)
{
    if (sad_fury != FF7Char::Fury && sad_fury != FF7Char::Sadness && sad_fury != FF7Char::Normal)
        sad_fury = FF7Char::Normal;

    if (sad_fury == data.statusFlag)
        return;

    data.statusFlag = sad_fury;
    Q_EMIT stateChanged(sad_fury);
/* Remove for 2.0 */Q_EMIT sadnessfury_changed(sad_fury);
}

void CharEditor::setRow(bool front_row)
{
    if ((front_row) && (data.rowFlag == FF7Char::FrontRow))
        return;
    if ((!front_row) && (data.rowFlag == FF7Char::BackRow))
        return;

    if (front_row)
        data.rowFlag = FF7Char::FrontRow;
    else
        data.rowFlag = FF7Char::BackRow;
    Q_EMIT rowChanged(data.rowFlag);
/* Remove for 2.0 */Q_EMIT row_changed(data.rowFlag);
}

void CharEditor::setLevelProgress(int level_progress)
{
    //Level progress bar (0-63) game ingores values <4 4-63 are visible as "progress"
    if (level_progress == data.tnlFlag)
        return;
    data.tnlFlag = quint8(std::clamp(level_progress, 0, 63));
    Q_EMIT levelProgressChanged(data.tnlFlag);
/* Remove for 2.0 */Q_EMIT levelProgress_changed(data.tnlFlag);
}

void CharEditor::setLimits(int limits)
{
    if (limits == data.limits)
        return;
    data.limits = quint16(std::clamp(limits, 0, qint16Max));
    Q_EMIT limitsChanged(data.limits);
/* Remove for 2.0 */Q_EMIT limits_changed(data.limits);
}

void CharEditor::setTimesused1(int timesused)
{
    if (timesused == data.timesused1)
        return;
    data.timesused1 = quint16(std::clamp(timesused, 0, quint16Max));
    Q_EMIT times1UsedChanged(data.timesused1);
/* Remove for 2.0 */Q_EMIT timesused1_changed(data.timesused1);
}

void CharEditor::setTimesused2(int timesused)
{
    if (timesused == data.timesused2)
        return;
    data.timesused2 = quint16(std::clamp(timesused, 0, quint16Max));
    Q_EMIT times2UsedChanged(data.timesused2);
/* Remove for 2.0 */Q_EMIT timesused2_changed(data.timesused2);
}

void CharEditor::setTimesused3(int timesused)
{
    if (timesused == data.timesused3)
        return;
    data.timesused3 = quint16(std::clamp(timesused, 0, quint16Max));
    Q_EMIT times3UsedChanged(data.timesused3);
/* Remove for 2.0 */Q_EMIT timesused3_changed(data.timesused3);
}

void CharEditor::setBaseHp(int baseHp)
{
    if (data.baseHP == baseHp)
        return;
    data.baseHP = quint16(std::clamp(baseHp, 0, qint16Max));
    Q_EMIT baseHpChanged(data.baseHP);
/* Remove for 2.0 */Q_EMIT baseHp_changed(data.baseHP);
    calc_stats();
}

void CharEditor::setBaseMp(int baseMp)
{
    if (data.baseMP == baseMp)
        return;
    data.baseMP = quint16(std::clamp(baseMp, 0, qint16Max));
    Q_EMIT baseMpChanged(data.baseMP);
/* Remove for 2.0 */Q_EMIT baseMp_changed(data.baseMP);
    calc_stats();
}

void CharEditor::setExp(int exp)
{
    if (data.exp == quint32(exp))
        return;
    data.exp = std::clamp(exp, 0, expMax);
    Q_EMIT expChanged(data.exp);
/* Remove for 2.0 */Q_EMIT exp_changed(data.exp);
}

void CharEditor::setExpNext(int expNext)
{
    if (data.expNext == quint32(expNext))
        return;
    data.expNext = data.exp = std::clamp(expNext, 0, expMax);
    Q_EMIT expNextChanged(data.expNext);
/* Remove for 2.0 */Q_EMIT expNext_changed(data.expNext);
}

void CharEditor::calc_limit_value(QModelIndex item)
{
    int row = item.row();
    int limits = data.limits;
    if (list_limits->item(row)->checkState() == Qt::Checked)
        limits |= (1 << FF7Char::limitBitConvert(row));
    else
        limits &= ~(1 << FF7Char::limitBitConvert(row));
    setLimits(limits);
}

void CharEditor::setAutoLevel(bool ans)
{
    autolevel = ans;    //used to turn off auto char leveling
    if (ans)
        Level_Changed(data.level);
}

bool CharEditor::AutoLevel()
{
    return autolevel;
}

void CharEditor::setAutoStatCalc(bool ans)
{
    autostatcalc = ans;    //Toggle stat calculation
    calc_stats();
}

bool CharEditor::AutoStatCalc()
{
    return autostatcalc;
}

bool CharEditor::AdvancedMode()
{
    return advancedMode;
}

void CharEditor::setAdvancedMode(bool new_advancedMode)
{
    advancedMode = new_advancedMode;
    unknown_box->setVisible(advancedMode);
    comboId->setVisible(advancedMode);

    //if viewing cait/vincent/y.cloud or sephiroth hid the checkbox for simple id changing.
    if (data.id == FF7Char::CaitSith || data.id == FF7Char::Vincent || data.id == FF7Char::YoungCloud || data.id == FF7Char::Sephiroth)
        cb_idChanger->setHidden(advancedMode);
}

void CharEditor::setEditable(bool edit)
{
    editable = edit;
    setEnabled(editable);
}

void CharEditor::setShowPlaceholderMateria(bool shown)
{
    showplaceholderMateria = shown;
    materia_edit->setShowPlaceHolderMateria(shown);
}

bool CharEditor::Editable()
{
    return editable;
}

bool CharEditor::showPlaceholderMateria()
{
    return showplaceholderMateria;
}

void CharEditor::calc_stats()
{
    int str_total = 0;
    int vit_total = 0;
    int spi_total = 0;
    int dex_total = 0;
    int mag_total = 0;
    int lck_total = 0;

    int str_bonus = 0;
    int vit_bonus = 0;
    int spi_bonus = 0;
    int dex_bonus = 0;
    int mag_bonus = 0;
    int lck_bonus = 0;
    int hp_bonus = 0;
    int mp_bonus = 0;

    str_total = data.strength + data.strength_bonus;
    vit_total = data.vitality + data.vitality_bonus;
    dex_total = data.dexterity + data.dexterity_bonus;
    spi_total = data.spirit + data.spirit_bonus;
    mag_total = data.magic + data.magic_bonus;
    lck_total = data.luck + data.luck_bonus;

    if (autostatcalc) {
        //add equipment bonuses
        //Weapon
        str_bonus += FF7Item::statSTR(data.weapon + 128);
        vit_bonus += FF7Item::statVIT(data.weapon + 128);
        dex_bonus += FF7Item::statDEX(data.weapon + 128);
        spi_bonus += FF7Item::statSPI(data.weapon + 128);
        mag_bonus += FF7Item::statMAG(data.weapon + 128);
        lck_bonus += FF7Item::statLCK(data.weapon + 128);
        hp_bonus += FF7Item::statHP(data.weapon + 128);
        mp_bonus += FF7Item::statMP(data.weapon + 128);
        QString title;
        title.append(tr("AP:x%1").arg(QString::number(FF7Item::materiaGrowthRate(data.weapon + 128))));

        if (FF7Item::statSTR(data.weapon + 128) != 0)
            title.append(tr(" Str:+%1").arg(QString::number(FF7Item::statSTR(data.weapon + 128))));

        if (FF7Item::statVIT(data.weapon + 128) != 0)
            title.append(tr(" Vit:+%1").arg(QString::number(FF7Item::statVIT(data.weapon + 128))));

        if (FF7Item::statDEX(data.weapon + 128) != 0)
            title.append(tr(" Dex:+%1").arg(QString::number(FF7Item::statDEX(data.weapon + 128))));

        if (FF7Item::statSPI(data.weapon + 128) != 0)
            title.append(tr(" Spi:+%1").arg(QString::number(FF7Item::statSPI(data.weapon + 128))));

        if (FF7Item::statMAG(data.weapon + 128) != 0)
            title.append(tr(" Mag:+%1").arg(QString::number(FF7Item::statMAG(data.weapon + 128))));

        if (FF7Item::statLCK(data.weapon + 128) != 0)
            title.append(tr(" Lck:+%1").arg(QString::number(FF7Item::statLCK(data.weapon + 128))));

        if (FF7Item::statHP(data.weapon + 128) != 0)
            title.append(tr(" Hp:+%1%").arg(QString::number(FF7Item::statHP(data.weapon + 128))));

        if (FF7Item::statMP(data.weapon + 128) != 0)
            title.append(tr(" Mp:+%1%").arg(QString::number(FF7Item::statMP(data.weapon + 128))));

        lblWeaponStats->setText(title);
        //Armor
        str_bonus += FF7Item::statSTR(data.armor + 256);
        vit_bonus += FF7Item::statVIT(data.armor + 256);
        dex_bonus += FF7Item::statDEX(data.armor + 256);
        spi_bonus += FF7Item::statSPI(data.armor + 256);
        mag_bonus += FF7Item::statMAG(data.armor + 256);
        lck_bonus += FF7Item::statLCK(data.armor + 256);
        hp_bonus += FF7Item::statHP(data.armor + 256);
        mp_bonus += FF7Item::statMP(data.armor + 256);
        title.clear();
        title.append(tr("AP:x%1").arg(QString::number(FF7Item::materiaGrowthRate(data.armor + 256))));
        if (FF7Item::statSTR(data.armor + 256) != 0)
            title.append(tr(" Str:+%1").arg(QString::number(FF7Item::statSTR(data.armor + 256))));

        if (FF7Item::statVIT(data.armor + 256) != 0)
            title.append(tr(" Vit:+%1").arg(QString::number(FF7Item::statVIT(data.armor + 256))));

        if (FF7Item::statDEX(data.armor + 256) != 0)
            title.append(tr(" Dex:+%1").arg(QString::number(FF7Item::statDEX(data.armor + 256))));

        if (FF7Item::statSPI(data.armor + 256) != 0)
            title.append(tr(" Spi:+%1").arg(QString::number(FF7Item::statSPI(data.armor + 256))));

        if (FF7Item::statMAG(data.armor + 256) != 0)
            title.append(tr(" Mag:+%1").arg(QString::number(FF7Item::statMAG(data.armor + 256))));

        if (FF7Item::statLCK(data.armor + 256) != 0)
            title.append(tr(" Lck:+%1").arg(QString::number(FF7Item::statLCK(data.armor + 256))));

        if (FF7Item::statHP(data.armor + 256) != 0)
            title.append(tr(" Hp:+%1%").arg(QString::number(FF7Item::statHP(data.armor + 256))));

        if (FF7Item::statMP(data.armor + 256) != 0)
            title.append(tr(" Mp:+%1%").arg(QString::number(FF7Item::statMP(data.armor + 256))));

        lblArmorStats->setText(title);
        //Accessory
        if (data.accessory < 32) {
            str_bonus += FF7Item::statSTR(data.accessory + 288);
            vit_bonus += FF7Item::statVIT(data.accessory + 288);
            dex_bonus += FF7Item::statDEX(data.accessory + 288);
            spi_bonus += FF7Item::statSPI(data.accessory + 288);
            mag_bonus += FF7Item::statMAG(data.accessory + 288);
            lck_bonus += FF7Item::statLCK(data.accessory + 288);
            hp_bonus += FF7Item::statHP(data.accessory + 288);
            mp_bonus += FF7Item::statMP(data.accessory + 288);
            title.clear();
            title.append(tr("Accessory"));
            if (FF7Item::statSTR(data.accessory + 288) != 0)
                title.append(tr(" Str:+%1").arg(QString::number(FF7Item::statSTR(data.accessory + 288))));

            if (FF7Item::statVIT(data.accessory + 288) != 0)
                title.append(tr(" Vit:+%1").arg(QString::number(FF7Item::statVIT(data.accessory + 288))));

            if (FF7Item::statDEX(data.accessory + 288) != 0)
                title.append(tr(" Dex:+%1").arg(QString::number(FF7Item::statDEX(data.accessory + 288))));

            if (FF7Item::statSPI(data.accessory + 288) != 0)
                title.append(tr(" Spi:+%1").arg(QString::number(FF7Item::statSPI(data.accessory + 288))));

            if (FF7Item::statMAG(data.accessory + 288) != 0)
                title.append(tr(" Mag:+%1").arg(QString::number(FF7Item::statMAG(data.accessory + 288))));

            if (FF7Item::statLCK(data.accessory + 288) != 0)
                title.append(tr(" Lck:+%1").arg(QString::number(FF7Item::statLCK(data.accessory + 288))));

            if (FF7Item::statHP(data.accessory + 288) != 0)
                title.append(tr(" Hp:+%1%").arg(QString::number(FF7Item::statHP(data.accessory + 288))));

            if (FF7Item::statMP(data.accessory + 288) != 0)
                title.append(tr(" Mp:+%1%").arg(QString::number(FF7Item::statMP(data.accessory + 288))));

            accessory_box->setTitle(title);
        } else {
            title.clear();
            title.append(tr("Accessory"));
            accessory_box->setTitle(title);
        }
        //process materia
        for (int i = 0; i < 16; i++) {
            if (data.materias[i].id != FF7Materia::EmptyId) {
                int level = 0;
                qint32 aptemp = FF7Materia::materiaAP(data.materias[i]);
                for (int m = 0; m < FF7Materia::levels(data.materias[i].id); m++) {
                    if (aptemp >= FF7Materia::apForLevel(data.materias[i].id, m))
                        level++;
                }

                if (!materiaSlots.at(i)->isHidden()) {
                    // no special materia that affects these stats.
                    str_bonus += FF7Materia::strengthChange(data.materias[i].id);
                    vit_bonus += FF7Materia::vitalityChange(data.materias[i].id);
                    spi_bonus += FF7Materia::spiritChange(data.materias[i].id);

                    //Show in Percentage.
                    if (data.materias[i].id == FF7Materia::MpPlus)
                        mp_bonus += (10 * level);
                    else
                        mp_bonus += FF7Materia::mpChange(data.materias[i].id);

                    if (data.materias[i].id == FF7Materia::HpPlus)
                        hp_bonus += (10 * level);
                    else
                        hp_bonus += FF7Materia::hpChange(data.materias[i].id);

                    //show exact numbers
                    if (data.materias[i].id == FF7Materia::SpeedPlus)
                        dex_bonus += data.dexterity * int(0.01 * (level * 10));
                    else
                        dex_bonus += FF7Materia::dexterityChange(data.materias[i].id);

                    if (data.materias[i].id == FF7Materia::MagicPlus)
                        mag_bonus += data.magic * int(0.01 * (level * 10));
                    else
                        mag_bonus += FF7Materia::magicChange(data.materias[i].id);

                    if (data.materias[i].id == FF7Materia::LuckPlus)
                        lck_bonus += data.luck * int(0.01 * (level * 10));
                    else
                        lck_bonus += FF7Materia::luckChange(data.materias[i].id);
                }// end of add case.
            }
        }

    }

    lblStrMateriaBonus->setText(QString::number(str_bonus));
    lblVitMateriaBonus->setText(QString::number(vit_bonus));
    lblDexMateriaBonus->setText(QString::number(dex_bonus));
    lblSpiMateriaBonus->setText(QString::number(spi_bonus));
    lblMagMateriaBonus->setText(QString::number(mag_bonus));
    lblLckMateriaBonus->setText(QString::number(lck_bonus));

    str_total += str_bonus;
    vit_total += vit_bonus;
    dex_total += dex_bonus;
    spi_total += spi_bonus;
    mag_total += mag_bonus;
    lck_total += lck_bonus;

    lblStrTotal->setText(QString::number(std::min(str_total, quint8Max)));
    lblVitTotal->setText(QString::number(std::min(vit_total, quint8Max)));
    lblMagTotal->setText(QString::number(std::min(mag_total, quint8Max)));
    lblSpiTotal->setText(QString::number(std::min(spi_total, quint8Max)));
    lblDexTotal->setText(QString::number(std::min(dex_total, quint8Max)));
    lblLckTotal->setText(QString::number(std::min(lck_total, quint8Max)));

    if (hp_bonus >= 0)
        lblBaseHpBonus->setText(QStringLiteral(" +%1%").arg(QString::number(hp_bonus)));
    else
        lblBaseHpBonus->setText(QStringLiteral(" %1%").arg(QString::number(hp_bonus)));

    if (mp_bonus >= 0)
        lblBaseMpBonus->setText(QStringLiteral(" +%1%").arg(QString::number(mp_bonus)));
    else
        lblBaseMpBonus->setText(QString(" %1%").arg(QString::number(mp_bonus)));

    lblMaxHp->setNum(std::min(int(data.baseHP + (data.baseHP * (hp_bonus * .01))), qint16Max));
    lblMaxMp->setNum(std::min(int(data.baseMP + (data.baseMP * (mp_bonus * .01))), qint16Max));
}

void CharEditor::level_up(int pre_level)
{
    if (pre_level < data.level) {
        //level up
        for (int i = pre_level; i < data.level; i++) {
            // for statGain stat guide, 0=str; 1=vit;2=mag;3=spr;4=dex;5=lck;6=basehp;7basemp also use id incase of mods that could move a char.
            sbStr->setValue(data.strength + FF7Char::statGain(data.id, 0, data.strength, i, i + 1));
            sbVit->setValue(data.vitality + FF7Char::statGain(data.id, 1, data.vitality, i, i + 1));
            sbMag->setValue(data.magic + FF7Char::statGain(data.id, 2, data.magic, i, i + 1));
            sbSpi->setValue(data.spirit + FF7Char::statGain(data.id, 3, data.spirit, i, i + 1));
            sbDex->setValue(data.dexterity + FF7Char::statGain(data.id, 4, data.dexterity, i, i + 1));
            sbLck->setValue(data.luck + FF7Char::statGain(data.id, 5, data.luck, i, i + 1));
            sbBaseHp->setValue(data.baseHP + FF7Char::statGain(data.id, 6, data.baseHP, i, i + 1));
            sbBaseMp->setValue(data.baseMP + FF7Char::statGain(data.id, 7, data.baseMP, i, i + 1));
        }
    } else if (pre_level > data.level) {
        //level down
        for (int i = pre_level; i > data.level; i--) {
            // for statGain stat guide, 0=str; 1=vit; 2=mag; 3=spr; 4=dex; 5=lck; 6=basehp; 7basemp
            sbStr->setValue(data.strength - FF7Char::statGain(data.id, 0, data.strength, i, i - 1));
            sbVit->setValue(data.vitality - FF7Char::statGain(data.id, 1, data.vitality, i, i - 1));
            sbMag->setValue(data.magic - FF7Char::statGain(data.id, 2, data.magic, i, i - 1));
            sbSpi->setValue(data.spirit - FF7Char::statGain(data.id, 3, data.spirit, i, i - 1));
            sbDex->setValue(data.dexterity - FF7Char::statGain(data.id, 4, data.dexterity, i, i - 1));
            sbLck->setValue(data.luck - FF7Char::statGain(data.id, 5, data.luck, i, i - 1));
            sbBaseHp->setValue(data.baseHP - FF7Char::statGain(data.id, 6, data.baseHP, i, i - 1));
            sbBaseMp->setValue(data.baseMP - FF7Char::statGain(data.id, 7, data.baseMP, i, i - 1));
        }
    }
    calc_stats();
}
void CharEditor::update_tnl_bar()
{
    if (data.level != 99) {
        setExpNext(int(FF7Char::totalExpForLevel(data.id, data.level) - data.exp));
        if (data.level > 0)
            setLevelProgress(int(((FF7Char::tnlForLevel(data.id, data.level) - data.expNext) * 62) / FF7Char::tnlForLevel(data.id, data.level)));
    } else {
        setExpNext(0);
        setLevelProgress(0x3D);
    }
    bar_tnl->setValue(data.tnlFlag);
    if (bar_tnl->value() < 4)
        bar_tnl->setValue(0);   //ff7 ingores the value if its <4 (but we don't save this)
    lbl_level_next->setText(tr("Next: %1").arg(QString::number(data.expNext)));
}

void CharEditor::elemental_info()
{
    int y = elemental_effects->contentsMargins().top() + elemental_effects->contentsMargins().bottom();
    bool show = false;
    int item_id = 0;
    QString m_effect;
    elemental_effects->clear();
    for (int r = 0; r < 3; r++) {
        switch (r) {
            case 0: item_id = data.weapon + 128; break;
            case 1: item_id = data.armor + 256; break;
            case 2: item_id = data.accessory + 288; break;
        }
        if ((item_id >= 0) && (item_id <= 319)) {
            for (int i = 0; i < 14; i++) {
                QString effect;
                int element = 0;
                switch (i) {
                    case 0: element = FF7Item::elementRestoration(item_id); effect.append(tr("Restoration")); break;
                    case 1: element = FF7Item::elementFire(item_id); effect.append(tr("Fire")); break;
                    case 2: element = FF7Item::elementCold(item_id); effect.append(tr("Cold")); break;
                    case 3: element = FF7Item::elementLightning(item_id); effect.append(tr("Lightning")); break;
                    case 4: element = FF7Item::elementEarth(item_id); effect.append(tr("Earth")); break;
                    case 5: element = FF7Item::elementWind(item_id); effect.append(tr("Wind")); break;
                    case 6: element = FF7Item::elementWater(item_id); effect.append(tr("Water")); break;
                    case 7: element = FF7Item::elementGravity(item_id); effect.append(tr("Gravity")); break;
                    case 8: element = FF7Item::elementHoly(item_id); effect.append(tr("Holy")); break;
                    case 9: element = FF7Item::elementPoison(item_id); effect.append(tr("Poison")); break;
                    case 10: element = FF7Item::elementCut(item_id); effect.append(tr("Cut")); break;
                    case 11: element = FF7Item::elementShoot(item_id); effect.append(tr("Shoot")); break;
                    case 12: element = FF7Item::elementPunch(item_id); effect.append(tr("Punch")); break;
                    case 13: element = FF7Item::elementHit(item_id); effect.append(tr("Hit")); break;
                }
                switch (element) {
                    case -3: effect.prepend(tr("Absorb:")); break;
                    case -2: effect.prepend(tr("Nullify:")); break;
                    case -1: effect.prepend(tr("Halve:")); break;
                    case  0: effect.clear(); break;
                    case +1: effect.prepend(tr("Attack:")); break;
                }
                if (!effect.isNull() && !m_effect.contains(effect, Qt::CaseSensitive)) {
                    m_effect.append(effect);
                    elemental_effects->addItem(effect);
                    show = true;
                    y += elemental_effects->sizeHintForRow(0);
                }
            }//end of for Loop
            elemental_effects->setFixedHeight(y);
            elemental_box->setFixedSize( (charWidth * 16), y + elemental_box->contentsMargins().top() + elemental_box->contentsMargins().bottom());
        }//end of if
    }//end of other loop.
    elemental_box->setVisible(show);
    elemental_box->adjustSize();
}//end of function

void CharEditor::status_info()
{
    int y = status_effects->contentsMargins().top() + status_effects->contentsMargins().bottom();
    bool show = false;
    int item_id = 0;
    QString m_status;
    status_effects->clear();
    status_effects->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for (int r = 0; r < 3; r++) {
        switch (r) {
            case 0: item_id = data.weapon + 128; break;
            case 1: item_id = data.armor + 256; break;
            case 2: item_id = data.accessory + 288; break;
        }
        if ((item_id >= 0) && (item_id <= 319)) {
            for (int i = 0; i < 24; i++) {
                QString effect;
                int status = 0;
                switch (i) {
                    case 0: status = FF7Item::statusDeath(item_id); effect.append(tr("Death")); break;
                    case 1: status = FF7Item::statusSlowNumb(item_id); effect.append(tr("Slow-Numb")); break;
                    case 2: status = FF7Item::statusDeathSentence(item_id); effect.append(tr("D.Sentence")); break;
                    case 3: status = FF7Item::statusParalysis(item_id); effect.append(tr("Paralysis")); break;
                    case 4: status = FF7Item::statusPetrify(item_id); effect.append(tr("Petrify")); break;
                    case 5: status = FF7Item::statusSilence(item_id); effect.append(tr("Silence")); break;
                    case 6: status = FF7Item::statusSleep(item_id); effect.append(tr("Sleep")); break;
                    case 7: status = FF7Item::statusConfusion(item_id); effect.append(tr("Confusion")); break;
                    case 8: status = FF7Item::statusBerserk(item_id); effect.append(tr("Berserk")); break;
                    case 9: status = FF7Item::statusFrog(item_id); effect.append(tr("Frog")); break;
                    case 10: status = FF7Item::statusMini(item_id); effect.append(tr("Mini")); break;
                    case 11: status = FF7Item::statusPoison(item_id); effect.append(tr("Poison")); break;
                    case 12: status = FF7Item::statusFury(item_id); effect.append(tr("Fury")); break;
                    case 13: status = FF7Item::statusSadness(item_id); effect.append(tr("Sadness")); break;
                    case 14: status = FF7Item::statusDarkness(item_id); effect.append(tr("Darkness")); break;
                    case 15: status = FF7Item::statusHaste(item_id); effect.append(tr("Haste")); break;
                    case 16: status = FF7Item::statusSlow(item_id); effect.append(tr("Slow")); break;
                    case 17: status = FF7Item::statusStop(item_id); effect.append(tr("Stop")); break;
                    case 18: status = FF7Item::statusBarrier(item_id); effect.append(tr("Barrier")); break;
                    case 19: status = FF7Item::statusMagicBarrier(item_id); effect.append(tr("M.Barrier")); break;
                    case 20: status = FF7Item::statusReflect(item_id); effect.append(tr("Reflect")); break;
                    case 21: status = FF7Item::statusShield(item_id); effect.append(tr("Shield")); break;
                    case 22: status = FF7Item::statusRegen(item_id); effect.append(tr("Regen")); break;
                    case 23: status = FF7Item::statusResist(item_id); effect.append(tr("Resist")); break;
                }
                switch (status) {
                    case -2: effect.prepend(tr("Protect:")); break;
                    case -1: effect.prepend(tr("Remove:")); break;
                    case  0: effect.clear(); break;
                    case +1: effect.prepend(tr("Inflict:")); break;
                    case +2: effect.prepend(tr("OnBattle:")); break;
                }
                if (!effect.isNull() && !m_status.contains(effect, Qt::CaseSensitive)) {
                    m_status.append(effect);
                    status_effects->addItem(effect);
                    show = true; y += status_effects->sizeHintForRow(0);
                }
            }//end of for Loop
            status_effects->setFixedHeight(y);
            status_box->setFixedSize(charWidth * 16, y + status_box->contentsMargins().top() + status_box->contentsMargins().bottom());
        }//end of else.
    }//end of loop
    status_box->setVisible(show);
    status_box->adjustSize();
}//end of function

void CharEditor::update_materia_slots()
{
    QList<QPushButton *> buttons = weapon_box->findChildren<QPushButton *>();
    int i = 0;
    for(auto button : std::as_const(buttons)) {
        button->setVisible((i+1) <= FF7Item::materiaSlots(data.weapon + 128));
        if (data.materias[i].id != FF7Materia::EmptyId)
            button->setIcon(FF7Materia::icon(data.materias[i].id));
        else
            button->setIcon(QIcon());
        i++;
    }
    buttons = armor_box->findChildren<QPushButton *>();
    for(auto button : std::as_const(buttons)) {
        button->setVisible((i-7) <= FF7Item::materiaSlots(data.armor + 256));
        if (data.materias[i].id != FF7Materia::EmptyId)
            button->setIcon(FF7Materia::icon(data.materias[i].id));
        else
            button->setIcon(QIcon());
        i++;
    }

    updateMateriaToolTips();
    //set up weapon
    QString ap_rate = tr("AP:x%1").arg(FF7Item::materiaGrowthRate(data.weapon + 128));
    lblWeaponStats->setText(ap_rate);

    QList<QLabel *> labels = weapon_box->findChildren<QLabel *>();
    labels.append(armor_box->findChildren<QLabel *>());
    for(auto label : std::as_const(labels))
        label->setStyleSheet(QString());

    switch (FF7Item::linkedSlots((data.weapon + 128))) {
        case 4: weapon_m_link_4->setStyleSheet(FF7Item::styleMateriaLink()); [[fallthrough]];
        case 3: weapon_m_link_3->setStyleSheet(FF7Item::styleMateriaLink()); [[fallthrough]];
        case 2: weapon_m_link_2->setStyleSheet(FF7Item::styleMateriaLink()); [[fallthrough]];
        case 1: weapon_m_link_1->setStyleSheet(FF7Item::styleMateriaLink());
    }

    //set up armor
    ap_rate = tr("AP:x%1").arg(FF7Item::materiaGrowthRate(data.armor + 256));
    lblArmorStats->setText(ap_rate);

    switch (FF7Item::linkedSlots((data.armor + 256))) {
        case 4: armor_m_link_4->setStyleSheet(FF7Item::styleMateriaLink()); [[fallthrough]];
        case 3: armor_m_link_3->setStyleSheet(FF7Item::styleMateriaLink()); [[fallthrough]];
        case 2: armor_m_link_2->setStyleSheet(FF7Item::styleMateriaLink()); [[fallthrough]];
        case 1: armor_m_link_1->setStyleSheet(FF7Item::styleMateriaLink());
    }
    calc_stats();
}
void CharEditor::matId_changed(qint8 id)
{
    data.materias[mslotsel].id = quint8(id);
    if (!load) {
        Q_EMIT materiaChanged(data.materias[mslotsel]);
/* Remove for 2.0 */Q_EMIT Materias_changed(data.materias[mslotsel]);
    }
    update_materia_slots();
}
void CharEditor::matAp_changed(qint32 ap)
{
    if (ap >= 0 && ap < FF7Materia::MaxMateriaAp) {
        int a = (ap & 0xff);
        int b = (ap & 0xff00) >> 8;
        int c = (ap & 0xff0000) >> 16;
        data.materias[mslotsel].ap[0] = quint8(a);
        data.materias[mslotsel].ap[1] = quint8(b);
        data.materias[mslotsel].ap[2] = quint8(c);
    } else {
        data.materias[mslotsel].ap[0] = quint8Max;
        data.materias[mslotsel].ap[1] = quint8Max;
        data.materias[mslotsel].ap[2] = quint8Max;
    }
    if (!load) {
        Q_EMIT materiaChanged(data.materias[mslotsel]);
/* Remove for 2.0 */Q_EMIT Materias_changed(data.materias[mslotsel]);
    }
    update_materia_slots();
}

void CharEditor::materiaSlotClicked(int slotClicked)
{
    if (slotClicked == mslotsel) {
        if (slotClicked < 0 )
            return;
        load = true;
        materia_edit->setMateria(char_materia(mslotsel).id, FF7Materia::materiaAP(char_materia(mslotsel)));
        load = false;
        return;
    }

    mslotsel = slotClicked;

    for (auto frame : std::as_const(materiaSlotFrames))
        frame->setFrameShape(QFrame::NoFrame);

    if (slotClicked < 0) {
        materia_edit->setVisible(false);
        return;
    }

    materia_edit->setVisible(true);
    materiaSlotFrames.at(mslotsel)->setFrameShape(QFrame::Box);

    load = true;
    materia_edit->setMateria(char_materia(mslotsel).id, FF7Materia::materiaAP(char_materia(mslotsel)));
    Q_EMIT mslotChanged(mslotsel);
    load = false;
}


void CharEditor::cb_idChanger_toggled(bool checked)
{
    if (checked && data.id == FF7Char::CaitSith)
        comboId->setCurrentIndex(FF7Char::YoungCloud);
    if (checked && data.id == FF7Char::Vincent)
        comboId->setCurrentIndex(FF7Char::Sephiroth);
    if (!checked && data.id == FF7Char::YoungCloud)
        comboId->setCurrentIndex(FF7Char::CaitSith);
    if (!checked && data.id == FF7Char::Sephiroth)
        comboId->setCurrentIndex(FF7Char::Vincent);
}

void CharEditor::MaxStats()
{
    if (data.id == FF7Char::YoungCloud || data.id == FF7Char::Sephiroth)
        return;

    sbLevel->setValue(99);
    sbBaseHp->setValue(10000); //set to 10k to prevent overflow
    sbBaseMp->setValue(10000); //set to 10k to prevent overflow
    sbStrSourceUse->setValue(quint8Max);
    sbDexSourceUse->setValue(quint8Max);
    sbSpiSourceUse->setValue(quint8Max);
    sbVitSourceUse->setValue(quint8Max);
    sbMagSourceUse->setValue(quint8Max);
    sbLckSourceUse->setValue(quint8Max);
    sbCurrentHp->setValue(data.maxHP);
    sbCurrentMp->setValue(data.maxMP);

    if (data.id == FF7Char::CaitSith) {
        sbLimitLevel->setValue(2);
        setLimits(0x09);
    } else if (data.id == FF7Char::Vincent) {
        sbLimitLevel->setValue(4);
        setLimits(0x249);
    } else {
        sbLimitLevel->setValue(4);
        setLimits(0x2DB);
    }
}

void CharEditor::MaxEquip()
{
    if (data.id == FF7Char::YoungCloud || data.id == FF7Char::Sephiroth)
        return;

    //set up weapons/ armor
    weapon_selection->setCurrentIndex(FF7Char::numberOfWeapons(data.id) - 1);
    armor_selection->setCurrentIndex(29);
    accessory_selection->setCurrentIndex(18);
    for (int i = 15; i >= 0; i--) {
        mslotsel = i;
        quint8 new_id = FF7Materia::EmptyId;

        switch (mslotsel) {
            case 6: new_id = FF7Materia::MegaAll;
                    break;
            case 5: new_id = FF7Materia::LongRange;
                    break;
            case 4: new_id = FF7Materia::PreEmptive;
                    break;
            case 3: new_id = FF7Materia::MasterSummon;
                    break;
            case 2: new_id = FF7Materia::EnemySkill;
                    break;
            case 1: new_id = FF7Materia::MasterCommand;
                    break;
            case 0: materiaSlotClicked(0);
                    new_id = FF7Materia::MasterMagic;
                    break;
        }

        data.materias[mslotsel].id = new_id;
        data.materias[mslotsel].ap[0] = quint8Max;
        data.materias[mslotsel].ap[1] = quint8Max;
        data.materias[mslotsel].ap[2] = quint8Max;

        Q_EMIT mslotChanged(mslotsel);
        Q_EMIT materiaChanged(data.materias[mslotsel]);
/* Remove for 2.0 */Q_EMIT Materias_changed(data.materias[mslotsel]);
    }
    update_materia_slots();
    cbFrontRow->setCheckState(Qt::Unchecked);
}

void CharEditor::setEditableComboBoxes(bool editable)
{
    weapon_selection->setEditable(editable);
    armor_selection->setEditable(editable);
    accessory_selection->setEditable(editable);
    materia_edit->setEditableMateriaCombo(editable);
}

QWidget* CharEditor::makeStatWidget(QSpinBox* statBaseSpinBox, QSpinBox* statSourceSpinBox, QLabel* statLabel, QLabel* statMateriaBonusLabel, QLabel* statTotalLabel)
{
    int width = charWidth * 3;

    statBaseSpinBox->setMaximum(quint8Max);
    statBaseSpinBox->setWrapping(true);
    statBaseSpinBox->setAlignment(Qt::AlignCenter);
    statBaseSpinBox->setSizePolicy(sbSizePolicy);

    if (statSourceSpinBox) {
        statSourceSpinBox->setMaximum(quint8Max);
        statSourceSpinBox->setWrapping(true);
        statSourceSpinBox->setAlignment(Qt::AlignCenter);
        statSourceSpinBox->setSizePolicy(sbSizePolicy);
    }

    statLabel->setFixedWidth(width);
    statLabel->setSizePolicy(sbSizePolicy);

    statMateriaBonusLabel->setFixedWidth(width);
    statMateriaBonusLabel->setSizePolicy(sbSizePolicy);

    statTotalLabel->setFixedWidth(width);
    statTotalLabel->setSizePolicy(sbSizePolicy);

    auto lblEquals = new QLabel(QStringLiteral("= "));
    lblEquals->setFixedWidth(fontMetrics().horizontalAdvance(QStringLiteral("= ")));

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(statLabel);
    layout->addWidget(statBaseSpinBox);

    if (statSourceSpinBox) {
        auto lblPlus_1 = new QLabel(QStringLiteral(" + "));
        lblPlus_1->setAlignment(Qt::AlignCenter);
        auto lblPlus_2 = new QLabel(QStringLiteral(" + "));
        lblPlus_2->setAlignment(Qt::AlignCenter);
        lblEquals->setFixedWidth(fontMetrics().horizontalAdvance(QStringLiteral(" = ")));
        layout->addWidget(lblPlus_1);
        layout->addWidget(statSourceSpinBox);
        layout->addWidget(lblPlus_2);
    }

    layout->addWidget(statMateriaBonusLabel);
    layout->addWidget(lblEquals);
    layout->addWidget(statTotalLabel);

    auto widget = new QWidget();
    widget->setSizePolicy(sbSizePolicy);
    widget->setLayout(layout);

    return widget;
}

QFrame * CharEditor::makeStatFrame()
{

    auto statLeftLayout = new QVBoxLayout;
    statLeftLayout->addWidget(makeStatWidget(sbBaseHp, nullptr, lblBaseHp, lblBaseHpBonus, lblMaxHp), 0);
    statLeftLayout->addWidget(makeStatWidget(sbStr, sbStrSourceUse, lblStr, lblStrMateriaBonus, lblStrTotal), 0);
    statLeftLayout->addWidget(makeStatWidget(sbVit, sbVitSourceUse, lblVit, lblVitMateriaBonus, lblVitTotal), 0);
    statLeftLayout->addWidget(makeStatWidget(sbMag, sbMagSourceUse, lblMag, lblMagMateriaBonus, lblMagTotal), 0);

    int lblWidth = charWidth * 4;

    sbBaseHp->setMaximum(qint16Max);
    sbBaseHp->setSizePolicy(sbSizePolicy);
    lblBaseHpBonus->setFixedWidth(lblWidth);

    auto statRightLayout = new QVBoxLayout;
    statRightLayout->addWidget(makeStatWidget(sbBaseMp, nullptr, lblBaseMp, lblBaseMpBonus, lblMaxMp), 0);
    statRightLayout->addWidget(makeStatWidget(sbSpi, sbSpiSourceUse, lblSpi, lblSpiMateriaBonus, lblSpiTotal), 0);
    statRightLayout->addWidget(makeStatWidget(sbDex, sbDexSourceUse, lblDex, lblDexMateriaBonus, lblDexTotal), 0);
    statRightLayout->addWidget(makeStatWidget(sbLck, sbLckSourceUse, lblLck, lblLckMateriaBonus, lblLckTotal), 0);

    sbBaseMp->setMaximum(qint16Max);
    sbBaseMp->setSizePolicy(sbSizePolicy);
    lblBaseMpBonus->setFixedWidth(lblWidth);

    auto statBox = new QFrame(this);
    auto statLayout = new QHBoxLayout(statBox);
    statLayout->addLayout(statLeftLayout, 0);
    statLayout->addLayout(statRightLayout, 0);
    statLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    return statBox;
}

QHBoxLayout * CharEditor::makeMateriaSlotPair(QPushButton* button1, QPushButton* button2, QFrame *frame1, QFrame *frame2, QLabel* linkLabel)
{
    auto scale = std::clamp<float>(lineHeight / 16, 1.0F, 3.0F);
    QSize slotSize = QSize(int(32 * scale), int(32 * scale));
    QSize frameSize = QSize(int(34 * scale), int(34 * scale));
    QSize materiaSize = QSize(int(24 * scale), int(24 * scale));
    QSize linkSize = QSize(int(12 * scale), int(16 * scale));
    button1->setFixedSize(slotSize);
    button1->setIconSize(materiaSize);
    button1->setStyleSheet(FF7Item::styleMateriaSlotNoGrowth());
    button1->setHidden(1);

    auto slotLayout = new QHBoxLayout;
    slotLayout->setContentsMargins(0, 0, 0, 0);
    slotLayout->addWidget(button1);

    frame1->setFixedSize(frameSize);
    frame1->setFrameShape(QFrame::NoFrame);
    frame1->setFrameShadow(QFrame::Plain);
    frame1->setLayout(slotLayout);

    linkLabel->setFixedSize(linkSize);

    button2->setFixedSize(slotSize);
    button2->setIconSize(materiaSize);
    button2->setStyleSheet(FF7Item::styleMateriaSlotNoGrowth());
    button2->setHidden(1);

    auto slotLayout2 = new QHBoxLayout;
    slotLayout2->setContentsMargins(0, 0, 0, 0);
    slotLayout2->addWidget(button2);

    frame2->setFixedSize(frameSize);
    frame2->setFrameShape(QFrame::NoFrame);
    frame2->setFrameShadow(QFrame::Plain);
    frame2->setLayout(slotLayout2);

    auto finalLayout = new QHBoxLayout;
    finalLayout->setContentsMargins(0, 0, 0, 0);
    finalLayout->addWidget(frame1);
    finalLayout->addWidget(linkLabel);
    finalLayout->addWidget(frame2);
    finalLayout->setSpacing(0);

    return finalLayout;
}

QWidget * CharEditor::makeLimitLayout()
{

    sb_uses_limit_1_1 = new QSpinBox;
    sb_uses_limit_1_1->setMaximum(qint16Max);
    sb_uses_limit_1_1->setWrapping(true);
    sb_uses_limit_1_1->setAlignment(Qt::AlignCenter);
    sb_uses_limit_1_1->setSizePolicy(sbSizePolicy);

    auto layout_1_1 = new QHBoxLayout;
    layout_1_1->setContentsMargins(0, 0, 0, 0);
    layout_1_1->addWidget(lbl_1_1);
    layout_1_1->addWidget(sb_uses_limit_1_1);

    sb_uses_limit_2_1 = new QSpinBox;
    sb_uses_limit_2_1->setWrapping(true);
    sb_uses_limit_2_1->setMaximum(qint16Max);
    sb_uses_limit_2_1->setAlignment(Qt::AlignCenter);
    sb_uses_limit_2_1->setSizePolicy(sbSizePolicy);

    auto layout_2_1 = new QHBoxLayout;
    layout_2_1->setContentsMargins(0, 0, 0, 0);
    layout_2_1->addWidget(lbl_2_1);
    layout_2_1->addWidget(sb_uses_limit_2_1);

    sb_uses_limit_3_1 = new QSpinBox;
    sb_uses_limit_3_1->setMaximum(qint16Max);
    sb_uses_limit_3_1->setWrapping(true);
    sb_uses_limit_3_1->setAlignment(Qt::AlignCenter);
    sb_uses_limit_3_1->setSizePolicy(sbSizePolicy);

    auto layout_3_1 = new QHBoxLayout;
    layout_3_1->setContentsMargins(0, 0, 0, 0);
    layout_3_1->addWidget(lbl_3_1);
    layout_3_1->addWidget(sb_uses_limit_3_1);

    auto used_limits_layout = new QVBoxLayout;
    used_limits_layout->setContentsMargins(0, 0, 0, 0);
    used_limits_layout->addWidget(sbLimitLevel);
    used_limits_layout->addWidget(lbl_uses);
    used_limits_layout->addLayout(layout_1_1);
    used_limits_layout->addLayout(layout_2_1);
    used_limits_layout->addLayout(layout_3_1);
    used_limits_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding));

    slider_limit = new QSlider(Qt::Horizontal);
    slider_limit->setMaximum(quint8Max);
    slider_limit->setMaximumHeight(lineHeight);

    lcdLimitValue = new QLCDNumber(3);
    lcdLimitValue->setSegmentStyle(QLCDNumber::Flat);

    auto limit_bar_layout = new QHBoxLayout;
    limit_bar_layout->setContentsMargins(0, 0, 0, 0);
    limit_bar_layout->addWidget(lbl_limit_bar);
    limit_bar_layout->addWidget(slider_limit);
    limit_bar_layout->addWidget(lcdLimitValue);

    auto limit_use_list = new QHBoxLayout;
    limit_use_list->addLayout(used_limits_layout);
    limit_use_list->setSpacing(3);
    limit_use_list->addWidget(list_limits);

    auto finalLayout = new QVBoxLayout;
    finalLayout->setContentsMargins(6, 6, 0, 0);
    finalLayout->addLayout(limit_bar_layout);
    finalLayout->setSpacing(6);
    finalLayout->addLayout(limit_use_list);
    finalLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding));

    auto widget = new QWidget(this);
    widget->setLayout(finalLayout);
    return widget;
}

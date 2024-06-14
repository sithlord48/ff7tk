//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QWidget>
#include <ff7tkwidgets_export.h>
#include <Type_FF7CHAR>

class QCheckBox;
class QComboBox;
class QLCDNumber;
class QLineEdit;
class QProgressBar;
class QToolBox;
class QSpinBox;
class QLabel;
class QHFrame;
class QHBoxLayout;
class QVBoxLayout;
class QGroupBox;
class QListWidget;
class QFrame;
class QSlider;
class QPushButton;

class MateriaEditor;

/** \class CharEditor
 *  \brief Widget to allow editing of a character using FF7Char for data.
 */
class FF7TKWIDGETS_EXPORT CharEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CharEditor(QWidget *parent = nullptr);
    void setChar(const FF7CHAR &Chardata, const QString &Processed_Name = "");

    bool AutoLevel();
    bool AutoStatCalc();
    bool Editable();
    bool showPlaceholderMateria();
    bool AdvancedMode();
    void MaxStats();
    void MaxEquip();
    quint8 id();
    quint8 level();
    quint8 str();
    quint8 vit();
    quint8 mag();
    quint8 spi();
    quint8 dex();
    quint8 lck();
    quint8 strBonus();
    quint8 vitBonus();
    quint8 magBonus();
    quint8 spiBonus();
    quint8 dexBonus();
    quint8 lckBonus();
    qint8 limitLevel();
    quint8 limitBar();
    QString name();
    quint8 weapon();
    quint8 armor();
    quint8 accessory();
    quint16 curHp();
    quint16 maxHp();
    quint16 curMp();
    quint16 maxMp();
    quint16 kills();
    quint8 row();
    quint8 levelProgress();
    quint8 sadnessfury();
    quint16 limits();
    quint16 timesused1();
    quint16 timesused2();
    quint16 timesused3();
    quint16 baseHp();
    quint16 baseMp();
    quint32 exp();
    quint32 expNext();
    materia char_materia(int mat);

protected:
    void changeEvent(QEvent *e) override;

signals:

    /**
     * @brief Emitted when the character's id changes
     * @param id New Id of the character
     */
    void idChanged(qint8 id);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::idChanged") ]]void id_changed(qint8);

    /**
     * @brief Emitted when the character's level changes
     * @param level New level of the character
     */
    void levelChanged(qint8 level);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::levelChanged") ]]void level_changed(qint8);

    /**
     * @brief Emitted when the character's strength changes
     * @param strength New strength of the character
     */
    void strengthChanged(quint8 strength);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::strengthChanged") ]]void str_changed(quint8);

    /**
     * @brief Emitted when the character's vitality changes
     * @param vitality New vitality of the character
     */
    void vitalityChanged(quint8 vitality);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::vitalityChanged") ]]void vit_changed(quint8);

    /**
     * @brief Emitted when the character's magic changes
     * @param magic New magic of the character
     */
    void magicChanged(quint8 magic);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::magicChanged") ]]void mag_changed(quint8);

    /**
     * @brief Emitted when the character's spirit changes
     * @param spirit New spirit of the character
     */
    void spiritChanged(quint8 spirit);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::spiritChanged") ]]void spi_changed(quint8);

    /**
     * @brief Emitted when the character's dexterity changes
     * @param dexterity New dexterity of the character
     */
    void dexterityChanged(quint8 dexterity);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::dexterityChanged") ]]void dex_changed(quint8);
    /**
     * @brief Emitted when the character's luck changes
     * @param luck New luck of the character
     */
    void luckChanged(quint8 luck);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::luckChanged") ]]void lck_changed(quint8);

    /**
     * @brief Emitted when the character's strengthBonus changes
     * @param strengthBonus New strengthBonus of the character
     */
    void strengthBonusChanged(quint8 strengthBonus);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::strengthBonusChanged") ]]void strBonus_changed(quint8);

    /**
     * @brief Emitted when the character's vitalityBonus changes
     * @param vitalityBonus New vitalityBonus of the character
     */
    void vitalityBonusChanged(quint8 vitalityBonus);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::vitalityBonusChanged") ]]void vitBonus_changed(quint8);

    /**
     * @brief Emitted when the character's magicBonus changes
     * @param magicBonus New magicBonus of the character
     */
    void magicBonusChanged(quint8 magicBonus);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::magicBonusChanged") ]]void magBonus_changed(quint8);

    /**
     * @brief Emitted when the character's spiritBonus changes
     * @param spiritBonus New spiritBonus of the character
     */
    void spiritBonusChanged(quint8 spiritBonus);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::spiritBonusChanged") ]]void spiBonus_changed(quint8);

    /**
     * @brief Emitted when the character's dexterityBonus changes
     * @param dexterityBonus New dexterityBonus of the character
     */
    void dexterityBonusChanged(quint8 dexterityBonus);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::dexterityBonusChanged") ]]void dexBonus_changed(quint8);

    /**
     * @brief Emitted when the character's luckBonus changes
     * @param luckBonus New luckBonus of the character
     */
    void luckBonusChanged(quint8 luckBonus);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::luckBonusChanged") ]]void lckBonus_changed(quint8);


    /**
     * @brief Emitted when the character's limitLevel changes
     * @param limitLevel New limitLevel of the character
     */
    void limitLevelChanged(qint8 limitLevel);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::limitLevelChanged") ]]void limitLevel_changed(qint8);

    /**
     * @brief Emitted when the character's limitBar changes
     * @param limitBar New limitBar of the character
     */
    void limitBarChanged(qint8 limitBar);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::limitBarChanged") ]]void limitBar_changed(quint8);

    /**
     * @brief Emitted when the character's name changes
     * @param name New name of the character
     */
    void nameChanged(QString name);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::nameChanged") ]]void name_changed(QString);

    /**
     * @brief Emitted when the character's weapon changes
     * @param weapon New weapon of the character
     */
    void weaponChanged(quint8 weapon);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::weaponChanged") ]]void weapon_changed(quint8);

    /**
     * @brief Emitted when the character's armor changes
     * @param armor New armor of the character
     */
    void armorChanged(quint8 armor);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::armorChanged") ]]void armor_changed(quint8);

    /**
     * @brief Emitted when the character's accessory changes
     * @param accessory New accessory of the character
     */
    void accessoryChanged(quint8 accessory);

    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::accessoryChanged") ]]void accessory_changed(quint8);

    /**
     * @brief Emitted when the character's current hit points changes
     * @param curHp New current hit points of the character
     */
    void curHpChanged(quint16 curHp);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::curHpChanged") ]]void curHp_changed(quint16);

    /**
     * @brief Emitted when the character's current maximum hit points changes
     * @param maxHp New maximum hit points of the character
     */
    void maxHpChanged(quint16 maxHp);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::maxHpChanged") ]]void maxHp_changed(quint16);

    /**
     * @brief Emitted when the character's current magic points changes
     * @param curMp New current magic points of the character
     */
    void curMpChanged(quint16 curMp);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::curMpChanged") ]]void curMp_changed(quint16);

    /**
     * @brief Emitted when the character's current maximum magic points changes
     * @param maxMp New maximum magic points of the character
     */
    void maxMpChanged(quint16 maxMp);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::maxMpChanged") ]]void maxMp_changed(quint16);

    /**
     * @brief Emitted when the character's kills changes
     * @param kills New name of the character
     */
    void killsChanged(quint16 kills);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::killsChanged") ]]void kills_changed(quint16);

    /**
     * @brief Emitted when the character's row changes
     * @param row New row of the character
     */
    void rowChanged(quint8 row);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::rowChanged") ]]void row_changed(quint8);

    /**
     * @brief Emitted when the character's levelProgress changes
     * @param levelProgress New levelProgresss of the character
     */
    void levelProgressChanged(quint8 levelProgress);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::levelProgressChanged") ]]void levelProgress_changed(quint8);

    /**
     * @brief Emitted when the character's sadness / fury state changes
     * @param state New sadness / fury state of the character
     */
    void stateChanged(quint8 state);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::stateChanged") ]]void sadnessfury_changed(quint8);

    /**
     * @brief Emitted when the character's limits changes
     * @param limits New limits of the character
     */
    void limitsChanged(quint16 limits);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::limitsChanged") ]]void limits_changed(quint16);

    /**
     * @brief Emitted when the number of times the character's used the 1-1 limit break changes
     * @param times New times the character has used the 1-1 limit break
     */
    void times1UsedChanged(quint16 times);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::times1UsedChanged") ]]void timesused1_changed(quint16);

    /**
     * @brief Emitted when the number of times the character's used the 2-1 limit break changes
     * @param times New times the character has used the 2-1 limit break
     */
    void times2UsedChanged(quint16 times);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::times2UsedChanged") ]]void timesused2_changed(quint16);

    /**
     * @brief Emitted when the number of times the character's used the 3-1 limit break changes
     * @param times New times the character has used the 3-1 limit break
     */
    void times3UsedChanged(quint16 times);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::times3UsedChanged") ]]void timesused3_changed(quint16);

    /**
     * @brief Emitted when the character's base hit points changes
     * @param baseHp New base hit points of the character
     */
    void baseHpChanged(quint16 baseHp);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::baseHpChanged") ]]void baseHp_changed(quint16);

    /**
     * @brief Emitted when the character's base magic points changes
     * @param baseMp New base magic points of the character
     */
    void baseMpChanged(quint16 baseMp);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::baseMpChanged") ]]void baseMp_changed(quint16);

    /**
     * @brief Emitted when the character's experience changes
     * @param exp New experience of the character
     */
    void expChanged(quint32 exp);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::expChanged") ]]void exp_changed(quint32);

    /**
     * @brief Emitted when the current materia slot being viwed changes
     * @param mslot New materia slot being viewed
     */
    void mslotChanged(int mslot);

    /**
     * @brief Emitted when the character's materia changes
     * @param mat New materia of the character (at the current mslot)
     */
    void materiaChanged(materia mat);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::materiaChanged") ]]void Materias_changed(materia);

    /**
     * @brief Emitted when the character's amount of experience needed to reach the next level changes
     * @param expNext New amount of experience needed to reach the next level
     */
    void expNextChanged(quint32 expNext);
    [[ deprecated ("will be removed in ff7tk 2.0, Use CharEditor::expNextChanged") ]]void expNext_changed(quint32);

public slots:
    void setAutoLevel(bool);
    void setAutoStatCalc(bool);
    void setEditable(bool);
    void setShowPlaceholderMateria(bool);
    void setAdvancedMode(bool);
    void setToolBoxStyle(const QString &styleSheet);
    void setSliderStyle(const QString &style);
    void setEditableComboBoxes(bool);

private:
    void setId(int);
    void setLevel(int);
    void setStr(int);
    void setVit(int);
    void setMag(int);
    void setSpi(int);
    void setDex(int);
    void setLck(int);
    void setStrBonus(int);
    void setVitBonus(int);
    void setMagBonus(int);
    void setSpiBonus(int);
    void setDexBonus(int);
    void setLckBonus(int);
    void setLimitLevel(int);
    void setLimitBar(int);
    void setName(const QString &name);
    void setWeapon(int);
    void setArmor(int);
    void setAccessory(int);
    void setRow(bool front_row);
    void setLevelProgress(int);
    void setSadnessFury(int);
    void setLimits(int);
    void setTimesused1(int);
    void setTimesused2(int);
    void setTimesused3(int);
    void setBaseHp(int);
    void setBaseMp(int);
    void setExp(int);
    void setExpNext(int);
    void setCurMp(int);
    void setCurHp(int);
    void setMaxMp(int);
    void setMaxHp(int);
    void setKills(int);
    void cb_fury_toggled(bool);
    void cb_sadness_toggled(bool);
    void cb_idChanger_toggled(bool);
    void calc_limit_value(QModelIndex);
    void Level_Changed(int);// used for tracking growth of char
    void Exp_Changed(int);// used for tracking growth of char
    void materiaSlotClicked(int slotClicked);
    void matAp_changed(qint32);
    void matId_changed(qint8);
    void init_display();
    void init_connections();
    void disconnectAll();
    void calc_stats();//calc stat changes if autostatcalc == true;
    void level_up(int);
    void update_tnl_bar();
    void elemental_info();
    void status_info();
    void update_materia_slots();
    void updateMateriaToolTips();
    void setSlotFrame();
    /**
     * @brief Creates all items that have text or tooltips, Future calls updates the text on these widgets.
     *  This is called once durring the constructor and again for languageChangeEvents to retranslate the text.
     */
    void updateText();

    /**
     * @brief Create a Widget containing all the Items to calculate a stat
     * @param statBaseSpinBox: QSpinBox* for the Base Stat.
     * @param statSourceSpinBox: QSpinBox* for the Source Use for Stat, a nullptr will remove this from the layout.
     * @param statLabel: Label containing the name of the stat
     * @param statMateriaBonusLabel: Label containing bonuses to the stat given by equipment and / or materia
     * @param statTotalLabel: Label containing the total value of the stat
     * @return Constructed Widget that contains all Items used to calculate a stat.
     */
    QWidget* makeStatWidget(QSpinBox* statBaseSpinBox = nullptr, QSpinBox* statSourceSpinBox = nullptr
            , QLabel* statLabel = nullptr, QLabel* statMateriaBonusLabel = nullptr, QLabel* statTotalLabel = nullptr);

    /**
     * @brief Create the a widget containing all the various stats Calls makeStatWidget once for each stat.
     * @return Widget containing all the controls for all the stats
     */
    QFrame* makeStatFrame();

    /**
     * @brief Create a pair of materia slots.
     * @param button1: First Materia Slot
     * @param button2: Second Materia Slot
     * @param frame1: Frame that will contain button1
     * @param frame2: Frame that will contain button2
     * @param linkLabel: Label Where the link will be shown if materia slots are linked
     * @return: One set of materia slots.
     */
    QHBoxLayout * makeMateriaSlotPair(QPushButton* button1 = nullptr, QPushButton* button2 = nullptr, QFrame *frame1 = nullptr, QFrame *frame2 = nullptr, QLabel* linkLabel = nullptr);

    /**
     * @brief Creates the widget for the limit related controls.
     * @return Widget containing the controls for the limit items.
     */
    QWidget * makeLimitLayout();
//Data
    bool load{false};
    bool autolevel{true};
    bool autostatcalc{true};
    bool editable{true};
    bool showplaceholderMateria{false};
    bool advancedMode{false};
    int mslotsel{-1};
    qint32 ap{0};
    FF7CHAR data;
    QString _name;
//GUI PARTS
    QLabel *lblAvatar = nullptr;
    QLineEdit *lineName = nullptr;
    QSpinBox *sbLevel = nullptr;
    QSpinBox *sbCurrentMp = nullptr;
    QSpinBox *sbCurrentHp = nullptr;

    QLabel *lblBaseHp = nullptr;
    QSpinBox *sbBaseHp = nullptr;
    QLabel *lblBaseHpBonus = nullptr;

    QLabel *lblBaseMp = nullptr;
    QSpinBox *sbBaseMp = nullptr;
    QLabel *lblBaseMpBonus = nullptr;

    QSpinBox *sbKills = nullptr;
    QLabel *lblCurrentHp = nullptr;
    QLabel *lblMaxHp = nullptr;
    QLabel *lblCurrentMp = nullptr;
    QLabel *lblMaxMp = nullptr;
    QCheckBox *cbFury = nullptr;
    QCheckBox *cbSadness = nullptr;
    QCheckBox *cbFrontRow = nullptr;
    QComboBox *comboId = nullptr;

    QSpinBox *sbTotalExp = nullptr;
    QLabel *lbl_level_next = nullptr;
    QProgressBar *bar_tnl = nullptr;
    QLabel *lbl_limit_bar = nullptr;
    QSlider *slider_limit = nullptr;
    QLCDNumber *lcdLimitValue = nullptr;

    QLabel *lblStr = nullptr;
    QSpinBox *sbStr = nullptr;
    QSpinBox *sbStrSourceUse = nullptr;
    QLabel *lblStrMateriaBonus = nullptr;
    QLabel *lblStrTotal = nullptr;

    QLabel *lblVit = nullptr;
    QSpinBox *sbVit = nullptr;
    QSpinBox *sbVitSourceUse = nullptr;
    QLabel *lblVitMateriaBonus = nullptr;
    QLabel *lblVitTotal = nullptr;

    QLabel *lblMag = nullptr;
    QSpinBox *sbMag = nullptr;
    QSpinBox *sbMagSourceUse = nullptr;
    QLabel *lblMagMateriaBonus = nullptr;
    QLabel *lblMagTotal = nullptr;

    QLabel *lblSpi = nullptr;
    QSpinBox *sbSpi = nullptr;
    QSpinBox *sbSpiSourceUse = nullptr;
    QLabel *lblSpiMateriaBonus = nullptr;
    QLabel *lblSpiTotal = nullptr;

    QLabel *lblDex = nullptr;
    QSpinBox *sbDex = nullptr;
    QSpinBox *sbDexSourceUse = nullptr;
    QLabel *lblDexMateriaBonus = nullptr;
    QLabel *lblDexTotal = nullptr;

    QLabel *lblLck = nullptr;
    QSpinBox *sbLck = nullptr;
    QSpinBox *sbLckSourceUse = nullptr;
    QLabel *lblLckMateriaBonus = nullptr;
    QLabel *lblLckTotal = nullptr;

    QSpinBox *sbLimitLevel = nullptr;
    QSpinBox *sb_uses_limit_1_1 = nullptr;
    QSpinBox *sb_uses_limit_2_1 = nullptr;
    QSpinBox *sb_uses_limit_3_1 = nullptr;
    QListWidget *list_limits = nullptr;
    QLabel *lbl_uses = nullptr;
    QLabel *lbl_1_1 = nullptr;
    QLabel *lbl_2_1 = nullptr;
    QLabel *lbl_3_1 = nullptr;
    QLabel *lbl_0x34 = nullptr;
    QLabel *lbl_0x35 = nullptr;
    QLabel *lbl_0x36 = nullptr;
    QLabel *lbl_0x37 = nullptr;
    QLabel *lblWeaponStats = nullptr;
    QLabel *lblArmorStats = nullptr;
    QComboBox *weapon_selection = nullptr;
    QComboBox *armor_selection = nullptr;
    QComboBox *accessory_selection = nullptr;
    MateriaEditor *materia_edit = nullptr;
    QGroupBox *elemental_box = nullptr;
    QGroupBox *status_box = nullptr;
    QListWidget *elemental_effects = nullptr;
    QListWidget *status_effects = nullptr;
    QFrame *weapon_materia_box = nullptr;
    QFrame *armor_materia_box = nullptr;
    QGroupBox *weapon_box = nullptr;
    QGroupBox *armor_box = nullptr;
    QGroupBox *accessory_box = nullptr;
    QList<QFrame *> materiaSlotFrames;
    QList<QPushButton *> materiaSlots;
    QLabel *weapon_m_link_1 = nullptr;
    QLabel *weapon_m_link_2 = nullptr;
    QLabel *weapon_m_link_3 = nullptr;
    QLabel *weapon_m_link_4 = nullptr;
    QLabel *armor_m_link_1 = nullptr;
    QLabel *armor_m_link_2 = nullptr;
    QLabel *armor_m_link_3 = nullptr;
    QLabel *armor_m_link_4 = nullptr;
    QToolBox *toolbox = nullptr;
    QFrame *unknown_box = nullptr;
    QLCDNumber *lcd_0x34 = nullptr;
    QLCDNumber *lcd_0x35 = nullptr;
    QLCDNumber *lcd_0x36 = nullptr;
    QLCDNumber *lcd_0x37 = nullptr;
    QCheckBox *cb_idChanger = nullptr;
    const int charWidth;
    const int lineHeight;
    const QSizePolicy sbSizePolicy;
    //Static Limits
    inline static const int quint8Max = 255;
    inline static const int qint16Max = 32767;
    inline static const int quint16Max = 65535;
    inline static const int expMax = 2147483647;
    inline static const QString comboStyle = QStringLiteral("QComboBox { combobox-popup: 0}");
    inline static const QString transparentBackgroundStyle = QStringLiteral("QFrame{background-color:rgba(0,0,0,0);}");
};

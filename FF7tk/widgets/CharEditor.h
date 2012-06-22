#ifndef CHAREDITOR_H
#define CHAREDITOR_H

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QMenu>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QListWidget>
#include <QProgressBar>
#include <QSlider>
#include <QLCDNumber>

//set path to FF7Item FF7Materia and FF7Char
#include "static_data/FF7Item.h"
#include "static_data/FF7Materia.h"
#include "static_data/FF7Char.h"

#include "static_data/Type_FF7CHAR.h"
#include "widgets/MateriaEditor.h"

class CharEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CharEditor(QWidget *parent = 0);
    void setChar(FF7CHAR Chardata,QString Processed_Name="");
    bool AutoLevel();
    bool AutoStatCalc();
    bool Editable();
    qint8 id();
    qint8 level();
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

signals:
    void id_changed(qint8);
    void level_changed(qint8);
    void str_changed(quint8);
    void vit_changed(quint8);
    void mag_changed(quint8);
    void spi_changed(quint8);
    void dex_changed(quint8);
    void lck_changed(quint8);
    void strBonus_changed(quint8);
    void vitBonus_changed(quint8);
    void magBonus_changed(quint8);
    void spiBonus_changed(quint8);
    void dexBonus_changed(quint8);
    void lckBonus_changed(quint8);
    void limitLevel_changed(qint8);
    void limitBar_changed(quint8);
    void name_changed(QString);
    void weapon_changed(quint8);
    void armor_changed(quint8);
    void accessory_changed(quint8);
    void curHp_changed(quint16);
    void maxHp_changed(quint16);
    void curMp_changed(quint16);
    void maxMp_changed(quint16);
    void kills_changed(quint16);
    void row_changed(quint8);
    void levelProgress_changed(quint8);
    void sadnessfury_changed(quint8);

    void limits_changed(quint16);
    void timesused1_changed(quint16);
    void timesused2_changed(quint16);
    void timesused3_changed(quint16);
    void baseHp_changed(quint16);
    void baseMp_changed(quint16);
    void exp_changed(quint32);
    void Materias_changed(int,materia);
    void expNext_changed(quint32);

public slots:
    void charMenu(QPoint);
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
    void setName(QString);
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
    //void setZ_4(int,int);
    //void setMaterias(materia,int);
    void setCurMp(int);
    void setCurHp(int);
    void setMaxMp(int);
    void setMaxHp(int);
    void setKills(int);
    void setAutoLevel(bool);
    void setAutoStatCalc(bool);
    void setEditable(bool);

private slots:
    void cb_fury_toggled(bool);
    void cb_sadness_toggled(bool);
    void calc_limit_value(QModelIndex);
    void Level_Changed(int);// used for tracking growth of char
    void Exp_Changed(int);// used for tracking growth of char
private:
    void init_display(void);
    void init_connections(void);
    void calc_stats(void);//calc stat changes if autostatcalc == true;
    void level_up(int);
    void update_tnl_bar();
    void elemental_info();
    void status_info();

    QLabel *lbl_avatar;
    QLineEdit *line_name;
    QSpinBox *sb_level;
    QSpinBox *sb_curMp;
    QSpinBox *sb_maxMp;
    QSpinBox *sb_curHp;
    QSpinBox *sb_maxHp;
    QSpinBox *sb_kills;
    QLabel *lbl_level;
    QLabel *lbl_hp;
    QLabel *lbl_hp_slash;
    QLabel *lbl_mp;
    QLabel *lbl_mp_slash;
    QLabel *lbl_kills;
    QLabel *lbl_id;
    QCheckBox *cb_fury;
    QCheckBox *cb_sadness;
    QCheckBox *cb_front_row;
    QComboBox *combo_id;

    QLabel * lbl_total_xp;
    QSpinBox * sb_total_exp;
    QLabel * lbl_level_progress;
    QLabel * lbl_level_next;
    QLCDNumber *lcd_tnl;
    QProgressBar *bar_tnl;
    QLabel * lbl_limit_bar;
    QSlider *slider_limit;
    QLCDNumber *lcd_limit_value;

    QLabel *lbl_str;
    QSpinBox *sb_str;
    QSpinBox *sb_str_bonus;
    QLabel *lbl_str_mat_bonus;
    QLabel *lbl_str_total;

    QLabel *lbl_vit;
    QSpinBox *sb_vit;
    QSpinBox *sb_vit_bonus;
    QLabel *lbl_vit_mat_bonus;
    QLabel *lbl_vit_total;

    QLabel *lbl_mag;
    QSpinBox *sb_mag;
    QSpinBox *sb_mag_bonus;
    QLabel *lbl_mag_mat_bonus;
    QLabel *lbl_mag_total;

    QLabel *lbl_spi;
    QSpinBox *sb_spi;
    QSpinBox *sb_spi_bonus;
    QLabel *lbl_spi_mat_bonus;
    QLabel *lbl_spi_total;

    QLabel *lbl_dex;
    QSpinBox *sb_dex;
    QSpinBox *sb_dex_bonus;
    QLabel *lbl_dex_mat_bonus;
    QLabel *lbl_dex_total;

    QLabel *lbl_lck;
    QSpinBox *sb_lck;
    QSpinBox *sb_lck_bonus;
    QLabel *lbl_lck_mat_bonus;
    QLabel *lbl_lck_total;

    QLabel * lbl_base_hp;
    QSpinBox *sb_base_hp;
    QLabel * lbl_base_hp_bonus;

    QLabel * lbl_base_mp;
    QSpinBox *sb_base_mp;
    QLabel * lbl_base_mp_bonus;

    QLabel *lbl_limit_level;
    QSpinBox *sb_limit_level;
    QSpinBox *sb_uses_limit_1_1;
    QSpinBox *sb_uses_limit_2_1;
    QSpinBox *sb_uses_limit_3_1;
    QListWidget *list_limits;
    QLabel *lbl_uses;
    QLabel *lbl_1_1;
    QLabel *lbl_2_1;
    QLabel *lbl_3_1;

    QComboBox*weapon_selection;
    QComboBox *armor_selection;
    QComboBox *accessory_selection;
    MateriaEditor *materia_edit;
    QGroupBox *elemental_box;
    QGroupBox *status_box;
    QListWidget *elemental_effects;
    QListWidget *status_effects;

//Data
   FF7Char Chars;
   FF7Item Items;
   //FF7Materia Materias;
   FF7CHAR data;
   QString _name;
   bool autolevel;
   bool autostatcalc;
   bool editable;
};

#endif // CHAREDITOR_H

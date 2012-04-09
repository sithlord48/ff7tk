#ifndef CHAREDITOR_H
#define CHAREDITOR_H

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QMenu>


//set path to FF7Item FF7Materia and FF7Char
#include "static_data/FF7Item.h"
#include "static_data/FF7Materia.h"
#include "static_data/FF7Char.h"

#include "static_data/Type_FF7CHAR.h"

class CharEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CharEditor(QWidget *parent = 0);
    void setChar(FF7CHAR Chardata,QString Processed_Name="");

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
    //void Flags_changed(int,quint8);
    void limits_changed(quint16);
    void timesused1_changed(quint16);
    void timesused2_changed(quint16);
    void timesused3_changed(quint16);
    void baseHp_changed(quint16);
    void baseMp_changed(quint16);
    //void Z_4_changed(int,quint8);
    void exp_changed(quint32);
    //void Materias_changed(int,materia);
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
   // void setFlags(int,int);
    void setLimits(int);
    void setTimesused1(int);
    void setTimesused2(int);
    void setTimesused3(int);
    void setBaseHp(int);
    void setBaseMp(int);
    //void setZ_4[4](int);
  void setExp(int);
    //void setMaterias(materia,int);
    void setExpNext(int);

    void setCurMp(int);
    void setCurHp(int);
    void setMaxMp(int);
    void setMaxHp(int);
    void setKills(int);

private:
    void init_display(void);
    void init_connections(void);
    QLabel *lbl_avatar;
    QLineEdit * line_name;
    QSpinBox *sb_level;
    QSpinBox *sb_curMp;
    QSpinBox *sb_maxMp;
    QSpinBox *sb_curHp;
    QSpinBox *sb_maxHp;
    QSpinBox *sb_kills;
    QLabel * lbl_level;
    QLabel * lbl_hp;
    QLabel * lbl_hp_slash;
    QLabel * lbl_mp;
    QLabel * lbl_mp_slash;
    QLabel * lbl_kills;
//Data
   FF7Char Chars;
   FF7CHAR data;
   QString _name;
};

#endif // CHAREDITOR_H

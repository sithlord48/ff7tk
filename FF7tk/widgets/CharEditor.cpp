#include "CharEditor.h"
#include <QMessageBox>
CharEditor::CharEditor(QWidget *parent) :
    QWidget(parent)
{
    init_display();
    init_connections();
}
void CharEditor::init_display()
{
    lbl_avatar = new QLabel;
    lbl_avatar->setFixedSize(86,98);
    lbl_avatar->setContextMenuPolicy(Qt::CustomContextMenu);
    line_name = new QLineEdit;
    lbl_level = new QLabel(tr("Level"));
    lbl_kills = new QLabel(tr("Kills"));
    lbl_hp = new QLabel(tr("HP"));
    lbl_mp = new QLabel(tr("MP"));
    lbl_mp_slash = new QLabel("/");
    lbl_hp_slash = new QLabel("/");
    sb_level = new QSpinBox;
    sb_curMp = new QSpinBox;
    sb_curHp = new QSpinBox;
    sb_maxMp = new QSpinBox;
    sb_maxHp = new QSpinBox;
    sb_kills = new QSpinBox;
    cb_fury=new QCheckBox(tr("Fury"));
    cb_sadness = new QCheckBox(tr("Sadness"));
    cb_front_row = new QCheckBox(tr("Front Row"));
    lbl_id = new QLabel(tr("ID"));
    combo_id = new QComboBox;
    for(int i=0;i<11;i++){combo_id->addItem(Chars.Icon(i),Chars.defaultName(i));}

    //QMessageBox::information(this,"PointSize",QString("Pointsize:%1").arg(this->font().pointSize()));

    lbl_str = new QLabel(tr("Str"));
    lbl_str->setFixedWidth(this->font().pointSize()*3);
    sb_str = new QSpinBox;
    sb_str->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_str_plus_1 = new QLabel(tr("+"));
    lbl_str_plus_1->setFixedWidth(this->font().pointSize());
    sb_str_bonus = new QSpinBox;
    sb_str_bonus->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_str_plus_2 = new QLabel(tr("+"));
    lbl_str_plus_2->setFixedWidth(this->font().pointSize());
    lbl_str_mat_bonus = new QLabel;
    lbl_str_mat_bonus->setFixedWidth(this->font().pointSize()*3);
    QLabel *lbl_str_equals = new QLabel(tr("="));
    lbl_str_equals->setFixedWidth(this->font().pointSize());
    lbl_str_total = new QLabel;
    lbl_str_total->setFixedWidth(this->font().pointSize()*5);

    lbl_vit = new QLabel(tr("Vit"));
    lbl_vit->setFixedWidth(this->font().pointSize()*3);
    sb_vit = new QSpinBox;
    sb_vit->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_vit_plus_1 = new QLabel(tr("+"));
    lbl_vit_plus_1->setFixedWidth(this->font().pointSize());
    sb_vit_bonus = new QSpinBox;
    sb_vit_bonus->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_vit_plus_2 = new QLabel(tr("+"));
    lbl_vit_plus_2->setFixedWidth(this->font().pointSize());
    lbl_vit_mat_bonus = new QLabel;
    lbl_vit_mat_bonus->setFixedWidth(this->font().pointSize()*3);
    QLabel *lbl_vit_equals = new QLabel(tr("="));
    lbl_vit_plus_1->setFixedWidth(this->font().pointSize());
    lbl_vit_total = new QLabel;
    lbl_vit_total->setFixedWidth(this->font().pointSize()*5);


    lbl_mag = new QLabel(tr("Mag"));
    lbl_mag->setFixedWidth(this->font().pointSize()*3);
    sb_mag = new QSpinBox;
    sb_mag->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_mag_plus_1 = new QLabel(tr("+"));
    lbl_mag_plus_1->setFixedWidth(this->font().pointSize());
    sb_mag_bonus = new QSpinBox;
    sb_mag_bonus->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_mag_plus_2 = new QLabel(tr("+"));
    lbl_mag_plus_2->setFixedWidth(this->font().pointSize());
    lbl_mag_mat_bonus = new QLabel;
    lbl_mag_mat_bonus->setFixedWidth(this->font().pointSize()*3);
    QLabel *lbl_mag_equals = new QLabel(tr("="));
    lbl_mag_plus_1->setFixedWidth(this->font().pointSize());
    lbl_mag_total = new QLabel;
    lbl_mag_total->setFixedWidth(this->font().pointSize()*5);


    lbl_spi = new QLabel(tr("Spi"));
    lbl_spi->setFixedWidth(this->font().pointSize()*3);
    sb_spi = new QSpinBox;
    sb_spi->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_spi_plus_1 = new QLabel(tr("+"));
    lbl_spi_plus_1->setFixedWidth(this->font().pointSize());
    sb_spi_bonus = new QSpinBox;
    sb_spi_bonus->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_spi_plus_2 = new QLabel(tr("+"));
    lbl_spi_plus_2->setFixedWidth(this->font().pointSize());
    lbl_spi_mat_bonus = new QLabel;
    lbl_spi_mat_bonus->setFixedWidth(this->font().pointSize()*3);
    QLabel *lbl_spi_equals = new QLabel(tr("="));
    lbl_spi_plus_1->setFixedWidth(this->font().pointSize());
    lbl_spi_total = new QLabel;
    lbl_spi_total->setFixedWidth(this->font().pointSize()*5);


    lbl_dex = new QLabel(tr("Dex"));
    lbl_dex->setFixedWidth(this->font().pointSize()*3);
    sb_dex = new QSpinBox;
    sb_dex->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_dex_plus_1 = new QLabel(tr("+"));
    lbl_dex_plus_1->setFixedWidth(this->font().pointSize());
    sb_dex_bonus = new QSpinBox;
    sb_dex_bonus->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_dex_plus_2 = new QLabel(tr("+"));
    lbl_dex_plus_2->setFixedWidth(this->font().pointSize());
    lbl_dex_mat_bonus = new QLabel;
    lbl_dex_mat_bonus->setFixedWidth(this->font().pointSize()*3);
    QLabel *lbl_dex_equals = new QLabel(tr("="));
    lbl_dex_plus_1->setFixedWidth(this->font().pointSize());
    lbl_dex_total = new QLabel;
    lbl_dex_total->setFixedWidth(this->font().pointSize()*5);


    lbl_lck = new QLabel(tr("Lck"));
    lbl_lck->setFixedWidth(this->font().pointSize()*3);
    sb_lck = new QSpinBox;
    sb_lck->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_lck_plus_1 = new QLabel(tr("+"));
    lbl_lck_plus_1->setFixedWidth(this->font().pointSize());
    sb_lck_bonus = new QSpinBox;
    sb_lck_bonus->setFixedWidth(this->font().pointSize()*5);
    QLabel *lbl_lck_plus_2 = new QLabel(tr("+"));
    lbl_lck_plus_2->setFixedWidth(this->font().pointSize());
    lbl_lck_mat_bonus = new QLabel;
    lbl_lck_mat_bonus->setFixedWidth(this->font().pointSize()*3);
    QLabel *lbl_lck_equals = new QLabel(tr("="));
    lbl_lck_plus_1->setFixedWidth(this->font().pointSize());
    lbl_lck_total = new QLabel;
    lbl_lck_total->setFixedWidth(this->font().pointSize()*5);

    list_limits = new QListWidget;
    lbl_limit_level = new QLabel(tr("Limit Level"));
    sb_limit_level = new QSpinBox;
    sb_limit_level->setFixedWidth(this->font().pointSize()*4);

    QHBoxLayout *limit_level_layout = new QHBoxLayout;
    limit_level_layout->setContentsMargins(0,0,0,0);
    limit_level_layout->addWidget(lbl_limit_level);
    limit_level_layout->addWidget(sb_limit_level);


    sb_level->setMaximum(99);
    sb_curMp->setMaximum(32767);
    sb_curHp->setMaximum(32767);
    sb_maxMp->setMaximum(32767);
    sb_maxHp->setMaximum(32767);
    sb_kills->setMaximum(65535);
    sb_str->setMaximum(255);
    sb_str_bonus->setMaximum(255);
    sb_vit->setMaximum(255);
    sb_vit_bonus->setMaximum(255);
    sb_mag->setMaximum(255);
    sb_mag_bonus->setMaximum(255);
    sb_spi->setMaximum(255);
    sb_spi_bonus->setMaximum(255);
    sb_dex->setMaximum(255);
    sb_dex_bonus->setMaximum(255);
    sb_lck->setMaximum(255);
    sb_lck_bonus->setMaximum(255);
    sb_limit_level->setMaximum(4);

    QHBoxLayout * name_level_layout= new QHBoxLayout;
    name_level_layout->addWidget(line_name);
    QSpacerItem *name_spacer = new QSpacerItem(20,0,QSizePolicy::Fixed,QSizePolicy::Fixed);
    name_level_layout->addSpacerItem(name_spacer);
    name_level_layout->addWidget(lbl_level);
    name_level_layout->addWidget(sb_level);

    QHBoxLayout *hp_layout = new QHBoxLayout;
    hp_layout->addWidget(lbl_hp);
    hp_layout->addWidget(sb_curHp);
    hp_layout->addWidget(lbl_hp_slash);
    hp_layout->addWidget(sb_maxHp);
    QSpacerItem *hp_spacer = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    hp_layout->addSpacerItem(hp_spacer);

    QHBoxLayout *mp_layout = new QHBoxLayout;
    mp_layout->addWidget(lbl_mp);
    mp_layout->addWidget(sb_curMp);
    mp_layout->addWidget(lbl_mp_slash);
    mp_layout->addWidget(sb_maxMp);
    QSpacerItem *mp_spacer = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    mp_layout->addSpacerItem(mp_spacer);

    QHBoxLayout *kills_layout = new QHBoxLayout;
    kills_layout->addWidget(lbl_kills);
    kills_layout->addWidget(sb_kills);
    QSpacerItem *kills_spacer = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Fixed);
    kills_layout->addSpacerItem(kills_spacer);


    QVBoxLayout *name_hp_mp_kills_layout = new QVBoxLayout;
    name_hp_mp_kills_layout->addLayout(name_level_layout);
    name_hp_mp_kills_layout->addLayout(hp_layout);
    name_hp_mp_kills_layout->addLayout(mp_layout);
    name_hp_mp_kills_layout->addLayout(kills_layout);


    QVBoxLayout *fury_sadness_layout = new QVBoxLayout;
    fury_sadness_layout->setContentsMargins(0,0,0,0);
    fury_sadness_layout->setSpacing(2);
    fury_sadness_layout->addWidget(cb_fury);
    fury_sadness_layout->addWidget(cb_sadness);


    QFrame *frm_fury_sadness =new QFrame;
    frm_fury_sadness->setLayout(fury_sadness_layout);

    QHBoxLayout *id_layout = new QHBoxLayout;
    id_layout->setContentsMargins(0,0,0,0);
    id_layout->addWidget(lbl_id);
    id_layout->addWidget(combo_id);

    QVBoxLayout *sadness_row_id_layout =new QVBoxLayout;
    sadness_row_id_layout->addWidget(frm_fury_sadness);
    sadness_row_id_layout->addWidget(cb_front_row);
    sadness_row_id_layout->addLayout(id_layout);


    QHBoxLayout *avatar_name_layout = new QHBoxLayout;
    avatar_name_layout->addWidget(lbl_avatar);
    avatar_name_layout->addLayout(name_hp_mp_kills_layout);
    avatar_name_layout->addLayout(sadness_row_id_layout);


    QHBoxLayout *str_layout = new QHBoxLayout;
    str_layout->setContentsMargins(0,0,0,0);
    str_layout->addWidget(lbl_str);
    str_layout->addWidget(sb_str);
    str_layout->addWidget(lbl_str_plus_1);
    str_layout->addWidget(sb_str_bonus);
    str_layout->addWidget(lbl_str_plus_2);
    str_layout->addWidget(lbl_str_mat_bonus);
    str_layout->addWidget(lbl_str_equals);
    str_layout->addWidget(lbl_str_total);

    QHBoxLayout *vit_layout = new QHBoxLayout;
    vit_layout->setContentsMargins(0,0,0,0);
    vit_layout->addWidget(lbl_vit);
    vit_layout->addWidget(sb_vit);
    vit_layout->addWidget(lbl_vit_plus_1);
    vit_layout->addWidget(sb_vit_bonus);
    vit_layout->addWidget(lbl_vit_plus_2);
    vit_layout->addWidget(lbl_vit_mat_bonus);
    vit_layout->addWidget(lbl_vit_equals);
    vit_layout->addWidget(lbl_vit_total);

    QHBoxLayout *mag_layout = new QHBoxLayout;
    mag_layout->setContentsMargins(0,0,0,0);
    mag_layout->addWidget(lbl_mag);
    mag_layout->addWidget(sb_mag);
    mag_layout->addWidget(lbl_mag_plus_1);
    mag_layout->addWidget(sb_mag_bonus);
    mag_layout->addWidget(lbl_mag_plus_2);
    mag_layout->addWidget(lbl_mag_mat_bonus);
    mag_layout->addWidget(lbl_mag_equals);
    mag_layout->addWidget(lbl_mag_total);

    QHBoxLayout *spi_layout = new QHBoxLayout;
    spi_layout->setContentsMargins(0,0,0,0);
    spi_layout->addWidget(lbl_spi);
    spi_layout->addWidget(sb_spi);
    spi_layout->addWidget(lbl_spi_plus_1);
    spi_layout->addWidget(sb_spi_bonus);
    spi_layout->addWidget(lbl_spi_plus_2);
    spi_layout->addWidget(lbl_spi_mat_bonus);
    spi_layout->addWidget(lbl_spi_equals);
    spi_layout->addWidget(lbl_spi_total);

    QHBoxLayout *dex_layout = new QHBoxLayout;
    dex_layout->setContentsMargins(0,0,0,0);
    dex_layout->addWidget(lbl_dex);
    dex_layout->addWidget(sb_dex);
    dex_layout->addWidget(lbl_dex_plus_1);
    dex_layout->addWidget(sb_dex_bonus);
    dex_layout->addWidget(lbl_dex_plus_2);
    dex_layout->addWidget(lbl_dex_mat_bonus);
    dex_layout->addWidget(lbl_dex_equals);
    dex_layout->addWidget(lbl_dex_total);

    QHBoxLayout *lck_layout = new QHBoxLayout;
    lck_layout->setContentsMargins(0,0,0,0);
    lck_layout->addWidget(lbl_lck);
    lck_layout->addWidget(sb_lck);
    lck_layout->addWidget(lbl_lck_plus_1);
    lck_layout->addWidget(sb_lck_bonus);
    lck_layout->addWidget(lbl_lck_plus_2);
    lck_layout->addWidget(lbl_lck_mat_bonus);
    lck_layout->addWidget(lbl_lck_equals);
    lck_layout->addWidget(lbl_lck_total);


    QVBoxLayout *stat_layout = new QVBoxLayout;
    stat_layout->setContentsMargins(0,3,0,0);
    stat_layout->addLayout(str_layout);
    stat_layout->addLayout(vit_layout);
    stat_layout->addLayout(mag_layout);
    stat_layout->addLayout(spi_layout);
    stat_layout->addLayout(dex_layout);
    stat_layout->addLayout(lck_layout);


    QGroupBox *stat_box = new QGroupBox;
    stat_box->setFixedHeight(this->font().pointSize()*16);
    stat_box->setLayout(stat_layout);

    QVBoxLayout *limit_box = new QVBoxLayout;
    limit_box->addLayout(limit_level_layout);
    limit_box->addWidget(list_limits);

    QHBoxLayout *lower_section = new QHBoxLayout;
    lower_section->setContentsMargins(0,0,0,0);
    lower_section->addWidget(stat_box);
    lower_section->addLayout(limit_box);


    QVBoxLayout *Final = new QVBoxLayout;
    Final->setContentsMargins(0,0,0,0);
    Final->addLayout(avatar_name_layout);
    Final->addLayout(lower_section);

    this->setLayout(Final);


    list_limits->setFixedHeight(this->font().pointSize()*14);
    list_limits->addItems(Chars.limits(0));
    list_limits->item(0)->setCheckState(Qt::Unchecked);
    list_limits->item(1)->setCheckState(Qt::Unchecked);
    list_limits->item(2)->setCheckState(Qt::Unchecked);
    list_limits->item(3)->setCheckState(Qt::Unchecked);
    list_limits->item(4)->setCheckState(Qt::Unchecked);
    list_limits->item(5)->setCheckState(Qt::Unchecked);
    list_limits->item(6)->setCheckState(Qt::Unchecked);
}
void CharEditor::init_connections()
{
    connect(sb_level,SIGNAL(valueChanged(int)),this,SLOT(setLevel(int)));
    connect(sb_curMp,SIGNAL(valueChanged(int)),this,SLOT(setCurMp(int)));
    connect(sb_curHp,SIGNAL(valueChanged(int)),this,SLOT(setCurHp(int)));
    connect(sb_maxMp,SIGNAL(valueChanged(int)),this,SLOT(setMaxMp(int)));
    connect(sb_maxHp,SIGNAL(valueChanged(int)),this,SLOT(setMaxHp(int)));
    connect(sb_kills,SIGNAL(valueChanged(int)),this,SLOT(setKills(int)));
    connect(line_name,SIGNAL(textChanged(QString)),this,SLOT(setName(QString)));
    connect(cb_front_row,SIGNAL(toggled(bool)),this,SLOT(setRow(bool)));
    connect(cb_fury,SIGNAL(toggled(bool)),this,SLOT(cb_fury_toggled(bool)));
    connect(cb_sadness,SIGNAL(toggled(bool)),this,SLOT(cb_sadness_toggled(bool)));
    connect(sb_str,SIGNAL(valueChanged(int)),this,SLOT(setStr(int)));
    connect(sb_str_bonus,SIGNAL(valueChanged(int)),this,SLOT(setStrBonus(int)));
    connect(sb_vit,SIGNAL(valueChanged(int)),this,SLOT(setVit(int)));
    connect(sb_vit_bonus,SIGNAL(valueChanged(int)),this,SLOT(setVitBonus(int)));
    connect(sb_mag,SIGNAL(valueChanged(int)),this,SLOT(setMag(int)));
    connect(sb_mag_bonus,SIGNAL(valueChanged(int)),this,SLOT(setMagBonus(int)));
    connect(sb_spi,SIGNAL(valueChanged(int)),this,SLOT(setSpi(int)));
    connect(sb_spi_bonus,SIGNAL(valueChanged(int)),this,SLOT(setSpiBonus(int)));
    connect(sb_dex,SIGNAL(valueChanged(int)),this,SLOT(setDex(int)));
    connect(sb_dex_bonus,SIGNAL(valueChanged(int)),this,SLOT(setDexBonus(int)));
    connect(sb_lck,SIGNAL(valueChanged(int)),this,SLOT(setLck(int)));
    connect(sb_lck_bonus,SIGNAL(valueChanged(int)),this,SLOT(setLckBonus(int)));

    connect(lbl_avatar,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(charMenu(QPoint)));
}
void CharEditor::setChar(FF7CHAR Chardata,QString Processed_Name)
{
    data = Chardata;
    _name=Processed_Name;
}

void CharEditor::setLevel(int level)
{
    if(data.level == level){return;}
    else
    {
        if(level<0){data.level=0;}
        else if(level>99){data.level=99;}
        else{data.level=level;}
        emit level_changed(data.level);
        QMessageBox::information(this,"EMIT",QString("Level_Changed:%1").arg(QString::number(data.level)));
    }
}
void CharEditor::cb_sadness_toggled(bool sad)
{
    if(sad)
    {
        setSadnessFury(0x20);
        cb_fury->blockSignals(true);
        cb_fury->setChecked(Qt::Unchecked);
        cb_fury->blockSignals(false);
    }
    else{setSadnessFury(0);}
}
void CharEditor::cb_fury_toggled(bool fury)
{
    if(fury)
    {
        setSadnessFury(0x10);
        cb_sadness->blockSignals(true);
        cb_sadness->setChecked(Qt::Unchecked);
        cb_sadness->blockSignals(false);
    }
    else{setSadnessFury(0);}
}
void CharEditor::setMaxHp(int maxHp)
{
    if(data.maxHP == maxHp){return;}
    else
    {
        if(maxHp<0){data.maxHP=0;}
        else if(maxHp >32767){data.maxHP=32767;}
        else{data.maxHP=maxHp;}
        emit maxHp_changed(data.maxHP);
        QMessageBox::information(this,"EMIT",QString("MaxHp_Changed:%1").arg(QString::number(data.maxHP)));
    }
}
void CharEditor::setCurHp(int curHp)
{
    if(data.curHP == curHp){return;}
    else
    {
        if(curHp<0){data.curHP=0;}
        else if(curHp >32767){data.curHP=32767;}
        else{data.curHP=curHp;}
        emit curHp_changed(data.curHP);
        QMessageBox::information(this,"EMIT",QString("CurHp_Changed:%1").arg(QString::number(data.curHP)));
    }
}
void CharEditor::setMaxMp(int maxMp)
{
    if(data.maxMP == maxMp){return;}
    else
    {
        if(maxMp<0){data.maxMP=0;}
        else if(maxMp >32767){data.maxMP=32767;}
        else{data.maxMP=maxMp;}
        emit maxMp_changed(data.maxMP);
        QMessageBox::information(this,"EMIT",QString("MaxMp_Changed:%1").arg(QString::number(data.maxMP)));
    }
}
void CharEditor::setCurMp(int curMp)
{
    if(data.curMP == curMp){return;}
    else
    {
        if(curMp<0){data.curMP=0;}
        else if(curMp >32767){data.curMP=32767;}
        else{data.curMP=curMp;}
        emit curMp_changed(data.curMP);
        QMessageBox::information(this,"EMIT",QString("CurMp_Changed:%1").arg(QString::number(data.curMP)));
    }
}
void CharEditor::setKills(int kills)
{
    if(data.kills == kills){return;}
    else
    {
        if(kills<0){data.kills=0;}
        else if(kills >65535){data.kills=65535;}
        else{data.kills=kills;}
        emit kills_changed(data.kills);
        QMessageBox::information(this,"EMIT",QString("Kills_Changed:%1").arg(QString::number(data.kills)));
    }
}
void CharEditor::setName(QString name)
{
    if(_name==name){return;}
    else
    {
        if(name==""){_name = QByteArray(12,0xFF);}
        else{_name = name;}
        emit name_changed(_name);
        QMessageBox::information(this,"EMIT",QString("Name_Changed:%1").arg(name));
    }
}
void CharEditor::setId(int id)
{
    if(data.id ==id){return;}
    else
    {
        if(id<0){data.id = 0;}
        else if(id>0x0B){data.id=0xFF;}
        else{data.id = id;}
        emit id_changed(data.id);
        QMessageBox::information(this,"EMIT",QString("Id_Changed:%1").arg(QString::number(data.id)));
    }
}
void CharEditor::setStr(int strength)
{
    if(data.strength ==strength){return;}
    else
    {
        if(strength<0){data.strength=0;}
        else if(strength>0xFF){data.strength=0xFF;}
        else{data.strength = strength;}
        emit str_changed(data.strength);
        QMessageBox::information(this,"EMIT",QString("str_Changed:%1").arg(QString::number(data.strength)));
    }
}
void CharEditor::setVit(int vitality)
{
    if(data.vitality ==vitality){return;}
    else
    {
        if(vitality<0){data.vitality = 0;}
        else if(vitality>0xFF){data.vitality=0xFF;}
        else{data.vitality = vitality;}
        emit vit_changed(data.vitality);
        QMessageBox::information(this,"EMIT",QString("vit_Changed:%1").arg(QString::number(data.vitality)));
    }
}
void CharEditor::setMag(int magic)
{
    if(data.magic ==magic){return;}
    else
    {
        if(magic<0){data.magic = 0;}
        else if(magic>0xFF){data.magic=0xFF;}
        else{data.magic = magic;}
        emit mag_changed(data.magic);
        QMessageBox::information(this,"EMIT",QString("mag_Changed:%1").arg(QString::number(data.magic)));
    }
}
void CharEditor::setSpi(int spirit)
{
    if(data.spirit ==spirit){return;}
    else
    {
        if(spirit<0){data.spirit = 0;}
        else if(spirit>0xFF){data.spirit=0xFF;}
        else{data.spirit = spirit;}
        emit spi_changed(data.spirit);
        QMessageBox::information(this,"EMIT",QString("spi_Changed:%1").arg(QString::number(data.spirit)));
    }
}
void CharEditor::setDex(int dexterity)
{
    if(data.dexterity ==dexterity){return;}
    else
    {
        if(dexterity<0){data.dexterity = 0;}
        else if(dexterity>0xFF){data.dexterity=0xFF;}
        else{data.dexterity = dexterity;}
        emit dex_changed(data.dexterity);
        QMessageBox::information(this,"EMIT",QString("dex_Changed:%1").arg(QString::number(data.dexterity)));
    }
}
void CharEditor::setLck(int luck)
{
    if(data.luck ==luck){return;}
    else
    {
        if(luck<0){data.luck = 0;}
        else if(luck>0xFF){data.luck=0xFF;}
        else{data.luck = luck;}
        emit lck_changed(data.luck);
        QMessageBox::information(this,"EMIT",QString("lck_Changed:%1").arg(QString::number(data.luck)));
    }
}
void CharEditor::setStrBonus(int strength_bonus)
{
    if(data.strength_bonus ==strength_bonus){return;}
    else
    {
        if(strength_bonus<0){data.strength_bonus = 0;}
        else if(strength_bonus>0xFF){data.strength_bonus=0xFF;}
        else{data.strength_bonus = strength_bonus;}
        emit strBonus_changed(data.strength_bonus);
        QMessageBox::information(this,"EMIT",QString("strBonus_Changed:%1").arg(QString::number(data.strength_bonus)));
    }
}
void CharEditor::setVitBonus(int vitality_bonus)
{
    if(data.vitality_bonus ==vitality_bonus){return;}
    else
    {
        if(vitality_bonus<0){data.vitality_bonus = 0;}
        else if(vitality_bonus>0xFF){data.vitality_bonus=0xFF;}
        else{data.vitality_bonus = vitality_bonus;}
        emit vitBonus_changed(data.vitality_bonus);
        QMessageBox::information(this,"EMIT",QString("vitBonus_Changed:%1").arg(QString::number(data.vitality_bonus)));
    }
}
void CharEditor::setMagBonus(int magic_bonus)
{
    if(data.magic_bonus ==magic_bonus){return;}
    else
    {
        if(magic_bonus<0){data.magic_bonus = 0;}
        else if(magic_bonus>0xFF){data.magic_bonus=0xFF;}
        else{data.magic_bonus = magic_bonus;}
        emit magBonus_changed(data.magic_bonus);
        QMessageBox::information(this,"EMIT",QString("magBonus_Changed:%1").arg(QString::number(data.magic_bonus)));
    }
}
void CharEditor::setSpiBonus(int spirit_bonus)
{
    if(data.spirit_bonus ==spirit_bonus){return;}
    else
    {
        if(spirit_bonus<0){data.spirit_bonus = 0;}
        else if(spirit_bonus>0xFF){data.spirit_bonus=0xFF;}
        else{data.spirit_bonus = spirit_bonus;}
        emit spiBonus_changed(data.spirit_bonus);
        QMessageBox::information(this,"EMIT",QString("spiBonus_Changed:%1").arg(QString::number(data.spirit_bonus)));
    }
}
void CharEditor::setDexBonus(int dexterity_bonus)
{
    if(data.dexterity_bonus ==dexterity_bonus){return;}
    else
    {
        if(dexterity_bonus<0){data.dexterity_bonus = 0;}
        else if(dexterity_bonus>0xFF){data.dexterity_bonus=0xFF;}
        else{data.dexterity_bonus = dexterity_bonus;}
        emit dexBonus_changed(data.dexterity_bonus);
        QMessageBox::information(this,"EMIT",QString("dexBonus_Changed:%1").arg(QString::number(data.dexterity_bonus)));
    }
}
void CharEditor::setLckBonus(int luck_bonus)
{
    if(data.luck ==luck_bonus){return;}
    else
    {
        if(luck_bonus<0){data.luck_bonus = 0;}
        else if(luck_bonus>0xFF){data.luck_bonus=0xFF;}
        else{data.luck_bonus = luck_bonus;}
        emit lckBonus_changed(data.luck_bonus);
        QMessageBox::information(this,"EMIT",QString("lckBonus_Changed:%1").arg(QString::number(data.luck_bonus)));
    }
}
void CharEditor::setLimitLevel(int limitlevel)
{
    if(data.limitlevel ==limitlevel){return;}
    else
    {
        if(limitlevel<0){data.limitlevel = 0;}
        else if(limitlevel>4){data.limitlevel=4;}
        else{data.limitlevel = limitlevel;}
        emit limitLevel_changed(data.limitlevel);
        QMessageBox::information(this,"EMIT",QString("limitLevel_Changed:%1").arg(QString::number(data.limitlevel)));
    }
}
void CharEditor::setLimitBar(int limitbar)
{
    if(data.limitbar ==limitbar){return;}
    else
    {
        if(limitbar<0){data.limitbar = 0;}
        else if(limitbar>0xFF){data.limitbar=0xFF;}
        else{data.limitbar = limitbar;}
        emit limitBar_changed(data.limitbar);
        QMessageBox::information(this,"EMIT",QString("limitBar_Changed:%1").arg(QString::number(data.limitbar)));
    }
}
void CharEditor::setWeapon(int weapon)
{
    if(weapon == data.weapon){return;}
    else
    {
        if(weapon<0){data.weapon=0;}
        else if(weapon>Chars.num_weapons(data.id)){data.weapon=Chars.num_weapons(data.id);}
        else {data.weapon=weapon;}
        emit weapon_changed(data.weapon);
        QMessageBox::information(this,"EMIT",QString("weapon_Changed:%1").arg(QString::number(data.weapon)));
    }
}
void CharEditor::setArmor(int armor)
{
    if(armor == data.armor){return;}
    else
    {
        if(armor<0){data.armor=0;}
        else if(armor>32){data.armor=0xFF;}
        else {data.armor= armor; }
        emit armor_changed(data.armor);
        QMessageBox::information(this,"EMIT",QString("armor_Changed:%1").arg(QString::number(data.armor)));
    }
}
void CharEditor::setAccessory(int accessory)
{
    if(accessory == data.accessory){return;}
    else
    {
        if(accessory<0){data.accessory=0;}
        else if(accessory>32){data.accessory=0xFF;}
        else {data.accessory = accessory;}
        emit accessory_changed(data.accessory);
        QMessageBox::information(this,"EMIT",QString("accessory_Changed:%1").arg(QString::number(data.accessory)));
    }
}
void CharEditor::setSadnessFury(int sad_fury)
{
    if(sad_fury == data.flags[0]){return;}
    else
    {
        if(sad_fury==0x10){data.flags[0]=0x10;}
        else if( sad_fury==0x20 ){data.flags[0]=0x20;}
        else{data.flags[0]=0;}
        emit sadnessfury_changed(data.flags[0]);
    }
    QMessageBox::information(this,"EMIT",QString("sad_fury_Changed:%1").arg(QString::number(data.flags[0])));

}
void CharEditor::setRow(bool front_row)
{
    if( (front_row) && (data.flags[1]==0xFF) ){return;}
    else if((!front_row) && (data.flags[1]==0xFE)){return;}
    else
    {
        if(front_row){data.flags[1]=0xFF;}
        else{data.flags[1]=0xFE;}
        emit row_changed(data.flags[1]);
        QMessageBox::information(this,"EMIT",QString("row_Changed:%1").arg(QString::number(data.flags[1])));
    }
}

void CharEditor::setLevelProgress(int level_progress)
{//Level progress bar (0-63) game ingores values <4 4-63 are visible as "progress"
    if(level_progress ==data.flags[2]){return;}
    else
    {
        if(level_progress<0){data.flags[2]=0;}
        else if(level_progress >63){data.flags[2]=63;}
        else{data.flags[2]=level_progress;}
        emit levelProgress_changed(data.flags[2]);
        //QMessageBox::information(this,"EMIT",QString("Level_Progress_Changed:%1").arg(QString::number(data.flags[2])));
    }
}

void CharEditor::setLimits(int limits)
{
    if(limits ==data.limits){return;}
    else
    {
        if(limits <0){data.limits=0;}
        else if(limits>127){data.limits=127;}
        else {data.limits = limits;}
        emit limits_changed(data.limits);
        QMessageBox::information(this,"EMIT",QString("Limits_Changed:%1").arg(QString::number(data.limits,2)));
    }
}
void CharEditor::setTimesused1(int timesused)
{
    if(timesused ==data.timesused1){return;}
    else
    {
        if(timesused <0){data.timesused1=0;}
        else if(timesused>65535){data.timesused1=65535;}
        else{data.timesused1 = timesused;}
    }
}

void CharEditor::setTimesused2(int timesused)
{
    if(timesused ==data.timesused2){return;}
    else
    {
        if(timesused <0){data.timesused2=0;}
        else if(timesused>65535){data.timesused2=65535;}
        else{data.timesused2 = timesused;}
    }
}
void CharEditor::setTimesused3(int timesused)
{
    if(timesused ==data.timesused3){return;}
    else
    {
        if(timesused <0){data.timesused3=0;}
        else if(timesused>65535){data.timesused3=65535;}
        else{data.timesused3 = timesused;}
    }
}
void CharEditor::setBaseHp(int baseHp)
{
    if(data.baseHP == baseHp){return;}
    else
    {
        if(baseHp<0){data.baseHP=0;}
        else if(baseHp >32767){data.baseHP=32767;}
        else{data.baseHP=baseHp;}
        emit baseHp_changed(data.baseHP);
        QMessageBox::information(this,"EMIT",QString("baseHp_Changed:%1").arg(QString::number(data.baseHP)));
    }
}
void CharEditor::setBaseMp(int baseMp)
{
    if(data.baseMP == baseMp){return;}
    else
    {
        if(baseMp<0){data.baseMP=0;}
        else if(baseMp >32767){data.baseMP=32767;}
        else{data.baseMP=baseMp;}
        emit baseMp_changed(data.baseMP);
        QMessageBox::information(this,"EMIT",QString("baseMp_Changed:%1").arg(QString::number(data.baseMP)));
    }
}
void CharEditor::setExp(int exp)
{
    if(data.exp == quint32(exp)){return;}
    else
    {
        if(exp<0){data.exp=0;}
        else{data.exp=exp;}
        emit exp_changed(data.exp);
        QMessageBox::information(this,"EMIT",QString("exp_Changed:%1").arg(QString::number(data.exp)));
    }
}
void CharEditor::setExpNext(int expNext)
{
    if(data.expNext == quint32(expNext)){return;}
    else
    {
        if(expNext<0){data.expNext=0;}
        else{data.expNext=expNext;}
        emit expNext_changed(data.expNext);
        QMessageBox::information(this,"EMIT",QString("expNext_Changed:%1").arg(QString::number(data.expNext)));
    }
}
void CharEditor::charMenu(QPoint pos)
{
    QMenu menu(this);
    QAction *sel;


    menu.addAction(Chars.Icon(0),Chars.defaultName(0));
    menu.addAction(Chars.Icon(1),Chars.defaultName(1));
    menu.addAction(Chars.Icon(2),Chars.defaultName(2));
    menu.addAction(Chars.Icon(3),Chars.defaultName(3));
    menu.addAction(Chars.Icon(4),Chars.defaultName(4));
    menu.addAction(Chars.Icon(5),Chars.defaultName(5));
    menu.addAction(Chars.Icon(6),Chars.defaultName(6));
    menu.addAction(Chars.Icon(7),Chars.defaultName(7));
    menu.addAction(Chars.Icon(8),Chars.defaultName(8));

    sel = menu.exec(lbl_avatar->mapToGlobal(pos));
    if(sel==0){return;}

    else{return;}
}//End Of Map Context Menu


//void setFlags(int,int);
//void setZ_4[4](int);
//void setMaterias(materia,int);

/****************************************************************************/
//    copyright 2012  Chris Rizzitello <sithlord48@gmail.com>               //
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
#include "MateriaEditor.h"
MateriaEditor::MateriaEditor(QWidget *parent):QWidget(parent)
{
    this->init_display();
    this->init_data();
}
/*
MateriaEditor::MateriaEditor(QWidget *parent, quint8 materia_id,qint32 materia_ap):QWidget(parent)
{
   this->init_display();
   //we need to initlize the data
   this->init_data();
   this->setMateria(materia_id,materia_ap);
}
*/
void MateriaEditor::init_display(void)
{
    lbl_ap = new QLabel(this);
    sb_ap = new QSpinBox(this);
    sb_ap->setWrapping(1);
    combo_materia = new QComboBox(this);
    for(int i=0;i<91;i++)
    {
        if(data->Name(i)!="DON'T USE"){combo_materia->addItem(data->Icon(i),data->Name(i));}
        else{continue;}
    }
    QHBoxLayout *name_ap_layout =  new QHBoxLayout(this);
    name_ap_layout->addWidget(combo_materia);
    name_ap_layout->addStretch(-1);
    name_ap_layout->addWidget(sb_ap);
    name_ap_layout->addWidget(lbl_ap);
    frm_name_ap =new QFrame(this);
    frm_name_ap->setLayout(name_ap_layout);

    box_stars = new QGroupBox(this);
    btn_star1 = new QPushButton(this);
    btn_star2 = new QPushButton(this);
    btn_star3 = new QPushButton(this);
    btn_star4 = new QPushButton(this);
    btn_star5 = new QPushButton(this);
    btn_star1->setFixedSize(32,32);
    btn_star2->setFixedSize(32,32);
    btn_star3->setFixedSize(32,32);
    btn_star4->setFixedSize(32,32);
    btn_star5->setFixedSize(32,32);
    btn_star1->setIconSize(QSize(32,32));
    btn_star2->setIconSize(QSize(32,32));
    btn_star3->setIconSize(QSize(32,32));
    btn_star4->setIconSize(QSize(32,32));
    btn_star5->setIconSize(QSize(32,32));
    btn_star1->setFlat(true);
    btn_star2->setFlat(true);
    btn_star3->setFlat(true);
    btn_star4->setFlat(true);
    btn_star5->setFlat(true);


    QHBoxLayout *stars = new QHBoxLayout;
    stars->addWidget(btn_star1);
    stars->addWidget(btn_star2);
    stars->addWidget(btn_star3);
    stars->addWidget(btn_star4);
    stars->addWidget(btn_star5);
    box_stars->setLayout(stars);
    /* Init Skills Area */
    box_skills = new QGroupBox(this);
    lbl_skill1 = new QLabel(this);
    lbl_skill2 = new QLabel(this);
    lbl_skill3 = new QLabel(this);
    lbl_skill4 = new QLabel(this);
    lbl_skill5 = new QLabel(this);

    box_stats = new QGroupBox(this);
    lbl_stats = new QLabel(this);

    eskill_list = new QListWidget;
    QVBoxLayout *eskill_layout = new QVBoxLayout;
    eskill_layout->addWidget(eskill_list);

    QVBoxLayout *skill_layout = new QVBoxLayout;
    skill_layout->addWidget(lbl_skill1);
    skill_layout->addWidget(lbl_skill2);
    skill_layout->addWidget(lbl_skill3);
    skill_layout->addWidget(lbl_skill4);
    skill_layout->addWidget(lbl_skill5);
    skill_layout->addItem(eskill_layout);
    box_skills->setLayout(skill_layout);
    box_skills->setTitle(tr("Skills"));
    eskill_list->setHidden(1);

    QHBoxLayout *stat_layout = new QHBoxLayout;
    stat_layout->addWidget(lbl_stats);
    box_stats->setTitle(tr("Stat Changes"));
    box_stats->setLayout(stat_layout);


    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(frm_name_ap);
    main_layout->addWidget(box_stars);
    main_layout->addWidget(box_skills);
    main_layout->addWidget(box_stats);

    QHBoxLayout *Final = new QHBoxLayout(this);
    Final->addLayout(main_layout);
    this->setLayout(Final);

    connect(btn_star1,SIGNAL(clicked()),this,SLOT(btn_star1_clicked()));
    connect(btn_star2,SIGNAL(clicked()),this,SLOT(btn_star2_clicked()));
    connect(btn_star3,SIGNAL(clicked()),this,SLOT(btn_star3_clicked()));
    connect(btn_star4,SIGNAL(clicked()),this,SLOT(btn_star4_clicked()));
    connect(btn_star5,SIGNAL(clicked()),this,SLOT(btn_star5_clicked()));

    connect(combo_materia,SIGNAL(currentIndexChanged(int)),this,SLOT(materia_changed(int)));
    connect(sb_ap,SIGNAL(valueChanged(int)),this,SLOT(ap_changed(int)));
}
void MateriaEditor::init_data()
{
    data = new FF7Materia;
    //Fill Eskill List.
    QListWidgetItem *newItem;
    for(int i=0;i<24;i++)
    {
        newItem = new QListWidgetItem;
        newItem->setText(data->Eskill(i));
        newItem->setCheckState(Qt::Unchecked);
        eskill_list->addItem(newItem);
    }
    eskill_list->setSelectionMode(QAbstractItemView::NoSelection);
    _id= 0x00;
    _current_ap= 0x00;
}

void MateriaEditor::setMateria(quint8 materia_id,qint32 materia_ap)
{
    if (materia_id <91)
    {//valid Materia..
        _id = materia_id;
        _type_icon = QPixmap::fromImage(data->Image(_id));
        _full_star_icon = QPixmap::fromImage(data->Image_FullStar(_id));
        _empty_star_icon = QPixmap::fromImage(data->Image_EmptyStar(_id));
        _current_name=data->Name(_id);
        _type = data->Type(_id);
        _max_level = data->Levels(_id);
        for(int i=0;i<_max_level;i++){_level_ap[i]=data->Ap(_id,i);}
        sb_ap->setMaximum(_level_ap[_max_level-1]);
    }
    else
    {//invalid Materia ID Clear the Forum. reset data to empty
        _id=0xFF;
        _current_ap=16777215;
    }
    this->setName();
    this->setAP(materia_ap);
    this->setLevel();
    this->setStats();
    this->adjustSize();
}
void MateriaEditor::setAP(qint32 ap)
{
    if(_id==0xFF){return;}
    else if(_id==0x2C)
    {
        eskill_list->setHidden(0);
        this->adjustSize();
        //set eskill ap stuff here
    }
    else{eskill_list->setHidden(1);}
    if( (ap <16777215) && (ap<_level_ap[_max_level-1]) )
    {
        _current_ap = ap;
        sb_ap->setValue(_current_ap);
    }
    else
    {
        if( (_id==0x11) || (_id ==0x30) || (_id==0x49) ||(_id==0x5A) || (_id==0x2C) ){return;}
        _current_ap = 16777215;
        sb_ap->setValue(_level_ap[_max_level-1]);
    }

    lbl_ap->setText(QString::number(_current_ap));//for debug
    lbl_ap->adjustSize();
}
void MateriaEditor::setName()
{  
    if(_id==0xFF){combo_materia->setCurrentIndex(-1);}
    else
    {
        if(_id<22){combo_materia->setCurrentIndex(_id);}
        else if(_id<38){combo_materia->setCurrentIndex(_id -1);}
        else if(_id<45){combo_materia->setCurrentIndex(_id -2);}
        else if(_id<63){combo_materia->setCurrentIndex(_id -5);}
        else if(_id<66){combo_materia->setCurrentIndex(_id -6);}
        else{combo_materia->setCurrentIndex(_id -8);}
    }
}
void MateriaEditor::setStats()
{
    if(_id==0xFF){lbl_stats->clear();}
    else{lbl_stats->setText(data->Stat_String(_id));}
    lbl_stats->adjustSize();
    //Hide If Eskill..
    if(_id==0x2C){box_stats->setHidden(1);}
    else{box_stats->setHidden(0);}
}
void MateriaEditor::setLevel()
{
    _current_level=0;
    for(int i=0;i<_max_level;i++){if(_current_ap >= _level_ap[i]){_current_level++;}}
    setStars();
    setSkills();
}
void MateriaEditor::setStars()
{
    //Hide if its eskill Materia
    if(_id==0x2C){box_stars->setHidden(1);return;}
    else{box_stars->setHidden(0);}

    btn_star1->setHidden(1);
    btn_star2->setHidden(1);
    btn_star3->setHidden(1);
    btn_star4->setHidden(1);
    btn_star5->setHidden(1);
    if(_id==0xFF){return;}
    if(_type !=0)
    {
        btn_star1->setIcon(_empty_star_icon);
        btn_star2->setIcon(_empty_star_icon);
        btn_star3->setIcon(_empty_star_icon);
        btn_star4->setIcon(_empty_star_icon);
        btn_star5->setIcon(_empty_star_icon);

        switch(_current_level)
        {//no break on purpose

        case 5: btn_star5->setIcon(_full_star_icon);
        case 4: btn_star4->setIcon(_full_star_icon);
        case 3: btn_star3->setIcon(_full_star_icon);
        case 2: btn_star2->setIcon(_full_star_icon);
        case 1: btn_star1->setIcon(_full_star_icon);

        };
        switch(_max_level)
        {//no break on purpose.
            case 5: btn_star5->setHidden(0);
            case 4: btn_star4->setHidden(0);
            case 3: btn_star3->setHidden(0);
            case 2: btn_star2->setHidden(0);
            case 1: btn_star1->setHidden(0);
        };
    }
    else{return;}
}
void MateriaEditor::setSkills()
{

    lbl_skill1->clear();
    lbl_skill2->clear();
    lbl_skill3->clear();
    lbl_skill4->clear();
    lbl_skill5->clear();
    if(_id==0xFF){return;}
    if(_id==0x2C)
    {
        lbl_skill1->setVisible(0);
        lbl_skill2->setVisible(0);
        lbl_skill3->setVisible(0);
        lbl_skill4->setVisible(0);
        lbl_skill5->setVisible(0);
    }
    else
    {
        lbl_skill1->setVisible(1);
        lbl_skill2->setVisible(1);
        lbl_skill3->setVisible(1);
        lbl_skill4->setVisible(1);
        lbl_skill5->setVisible(1);
    }
    switch (_current_level)
    {// no breaks on purpose
        case 5: lbl_skill5->setText(data->Skills(_id,4));
        case 4: lbl_skill4->setText(data->Skills(_id,3));
        case 3: lbl_skill3->setText(data->Skills(_id,2));
        case 2: lbl_skill2->setText(data->Skills(_id,1));
        case 1: lbl_skill1->setText(data->Skills(_id,0));
    }
    box_skills->adjustSize();
}

void MateriaEditor::btn_star1_clicked(){setAP(_level_ap[0]);setLevel();}
void MateriaEditor::btn_star2_clicked(){setAP(_level_ap[1]);setLevel();}
void MateriaEditor::btn_star3_clicked(){setAP(_level_ap[2]);setLevel();}
void MateriaEditor::btn_star4_clicked(){setAP(_level_ap[3]);setLevel();}
void MateriaEditor::btn_star5_clicked(){setAP(16777215);setLevel();}
void MateriaEditor::materia_changed(int new_id)
{
    if(new_id<22){new_id +=0;}
    else if(new_id<37){new_id +=1;}
    else if(new_id<43){new_id +=2;}
    else if(new_id<58){new_id +=5;}
    else if(new_id<60){new_id +=6;}
    else if(new_id<83){new_id +=8;}
    else{new_id = 0xFF;}//assume reset.
    setMateria(new_id,_current_ap);
}
/*
qint32 MateriaEditor::raw_data(void)
{
    qint32 materia;
    materia = _id |= _current_ap <<8;
    return materia;
}
*/
qint32 MateriaEditor::ap(void){return _current_ap;}
qint8 MateriaEditor::id(void){return _id;}
void MateriaEditor::ap_changed(qint32 ap){setAP(ap);}

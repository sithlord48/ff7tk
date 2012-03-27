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
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "MateriaPreview.h"
MateriaPreview::MateriaPreview(QWidget *parent):QWidget(parent)
{
    this->init_display();
    this->init_data();
}
/*
MateriaPreview::MateriaPreview(QWidget *parent, quint8 materia_id,qint32 materia_ap):QWidget(parent)
{
   this->init_display();
   //we need to initlize the data
   this->init_data();
   this->setMateria(materia_id,materia_ap);
}
*/
void MateriaPreview::init_display(void)
{
    lbl_type = new QLabel(this);
    lbl_type->setScaledContents(0);
    lbl_name = new QLabel(this);
    lbl_ap = new QLabel(this);

    QHBoxLayout *name_ap_layout =  new QHBoxLayout(this);
    name_ap_layout->addWidget(lbl_type);
    name_ap_layout->addWidget(lbl_name);
    name_ap_layout->addStretch(-1);
    name_ap_layout->addWidget(lbl_ap);
    frm_name_ap =new QFrame(this);
    frm_name_ap->setLayout(name_ap_layout);

    box_stars = new QGroupBox(this);
    lbl_star1 = new QLabel(this);
    lbl_star2 = new QLabel(this);
    lbl_star3 = new QLabel(this);
    lbl_star4 = new QLabel(this);
    lbl_star5 = new QLabel(this);
    lbl_star1->setFixedSize(32,32);
    lbl_star2->setFixedSize(32,32);
    lbl_star3->setFixedSize(32,32);
    lbl_star4->setFixedSize(32,32);
    lbl_star5->setFixedSize(32,32);
    lbl_star1->setScaledContents(1);
    lbl_star2->setScaledContents(1);
    lbl_star3->setScaledContents(1);
    lbl_star4->setScaledContents(1);
    lbl_star5->setScaledContents(1);


    QHBoxLayout *stars = new QHBoxLayout;
    stars->addWidget(lbl_star1);
    stars->addWidget(lbl_star2);
    stars->addWidget(lbl_star3);
    stars->addWidget(lbl_star4);
    stars->addWidget(lbl_star5);
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

    QVBoxLayout *skill_layout = new QVBoxLayout;
    skill_layout->addWidget(lbl_skill1);
    skill_layout->addWidget(lbl_skill2);
    skill_layout->addWidget(lbl_skill3);
    skill_layout->addWidget(lbl_skill4);
    skill_layout->addWidget(lbl_skill5);
    box_skills->setLayout(skill_layout);
    box_skills->setTitle(tr("Skills"));

    QHBoxLayout *stat_layout = new QHBoxLayout;
    stat_layout->addWidget(lbl_stats);
    box_stats->setTitle(tr("Stat Changes"));
    box_stats->setLayout(stat_layout);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(frm_name_ap);
    main_layout->addWidget(box_stars);
    main_layout->addWidget(box_skills);
    main_layout->addWidget(box_stats);
    this->setLayout(main_layout);
}
void MateriaPreview::init_data(){data = new FF7Materia;}
void MateriaPreview::setMateria(quint8 materia_id,qint32 materia_ap)
{
   if (materia_id <91){_id = materia_id;}
   else {return;}

   _type = data->Type(_id);
   if (materia_ap > 16777215){_ap = 16777215;}
   else {_ap = materia_ap;}
   this->setName(_id);
   this->setStats(_id);
   this->setAP(_ap);

   _level=0;
   for(int i=0;i<data->Levels(_id);i++){if(_ap >= data->Ap(_id,i)){_level++;}}
   this->setStars(data->Levels(_id),_level,_type);
   this->setSkills(_id,_level);

   this->adjustSize();
}
void MateriaPreview::setAP(qint32 current_ap)
{
    lbl_ap->setText(QString::number(current_ap));
    lbl_ap->adjustSize();
}
void MateriaPreview::setName(quint8 materia_id)
{
    lbl_type->setPixmap(QPixmap::fromImage(data->Image(materia_id)));
    lbl_type->adjustSize();
    lbl_name->setText(data->Name(materia_id));
    lbl_name->adjustSize();

}
void MateriaPreview::setStats(quint8 materia_id)
{
    lbl_stats->setText(data->Stat_String(materia_id));
    lbl_stats->adjustSize();
}
void MateriaPreview::setStars(quint8 max_level, quint8 current_level, quint8 type)
{
    lbl_star1->setHidden(1);
    lbl_star2->setHidden(1);
    lbl_star3->setHidden(1);
    lbl_star4->setHidden(1);
    lbl_star5->setHidden(1);

    if(type !=0)
    {
        lbl_star1->setPixmap(QPixmap::fromImage(data->Image_EmptyStar(_id)));
        lbl_star2->setPixmap(QPixmap::fromImage(data->Image_EmptyStar(_id)));
        lbl_star3->setPixmap(QPixmap::fromImage(data->Image_EmptyStar(_id)));
        lbl_star4->setPixmap(QPixmap::fromImage(data->Image_EmptyStar(_id)));
        lbl_star5->setPixmap(QPixmap::fromImage(data->Image_EmptyStar(_id)));

        switch(current_level)
        {//no break on purpose
            case 5: lbl_star5->setPixmap(QPixmap::fromImage(data->Image_FullStar(_id)));
            case 4: lbl_star4->setPixmap(QPixmap::fromImage(data->Image_FullStar(_id)));
            case 3: lbl_star3->setPixmap(QPixmap::fromImage(data->Image_FullStar(_id)));
            case 2: lbl_star2->setPixmap(QPixmap::fromImage(data->Image_FullStar(_id)));
            case 1: lbl_star1->setPixmap(QPixmap::fromImage(data->Image_FullStar(_id)));
        };
        switch(max_level)
        {//no break on purpose.
            case 5: lbl_star5->setHidden(0);
            case 4: lbl_star4->setHidden(0);
            case 3: lbl_star3->setHidden(0);
            case 2: lbl_star2->setHidden(0);
            case 1: lbl_star1->setHidden(0);
        };
    }
    else{return;}
}
void MateriaPreview::setSkills(quint8 materia_id, quint8 current_level)
{

    this->lbl_skill1->setHidden(1);
    this->lbl_skill2->setHidden(1);
    this->lbl_skill3->setHidden(1);
    this->lbl_skill4->setHidden(1);
    this->lbl_skill5->setHidden(1);

    switch (current_level)
    {// no breaks on purpose
        case 5: this->lbl_skill5->setHidden(0); this->lbl_skill5->setText(data->Skills(materia_id,4));
        case 4: this->lbl_skill4->setHidden(0);this->lbl_skill4->setText(data->Skills(materia_id,3));
        case 3: this->lbl_skill3->setHidden(0);this->lbl_skill3->setText(data->Skills(materia_id,2));
        case 2: this->lbl_skill2->setHidden(0);this->lbl_skill2->setText(data->Skills(materia_id,1));
        case 1: this->lbl_skill1->setHidden(0);this->lbl_skill1->setText(data->Skills(materia_id,0));
    }
    this->box_skills->adjustSize();
}
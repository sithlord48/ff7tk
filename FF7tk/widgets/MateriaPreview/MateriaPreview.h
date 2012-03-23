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
#ifndef MATERIAPREVIEW_H
  #define MATERIAPREVIEW_H

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>

/* SET FF7Materia PATH ACCORDINGLY*/
#include "static_data/FF7Materia.h"

class MateriaPreview : public QWidget
{
    Q_OBJECT
    
public:
    MateriaPreview(QWidget *parent=0);
    //MateriaPreview(QWidget *parent=0,quint8 materia_id=0,qint32 ap=0);
    void setMateria(quint8 materia_id=0,qint32 materia_ap=0);
    void setAP (qint32 current_ap=0);
    void setStars(quint8 max_level=0,quint8 current_level=0,quint8 type=0);
    void setName(quint8 materia_id=0);
    void setStats(quint8 materia_id=0);
    void setSkills(quint8 materia_id=0, quint8 current_level=0);
private:
    void init_display(void);
    void init_data(void);
    QLabel *lbl_type;
    QLabel *lbl_name;
    QLabel *lbl_ap;
    QFrame *frm_name_ap;
    QLabel *lbl_star1;
    QLabel *lbl_star2;
    QLabel *lbl_star3;
    QLabel *lbl_star4;
    QLabel *lbl_star5;
    QGroupBox *box_stars;
    QGroupBox *box_skills;

    QLabel *lbl_skill1;
    QLabel *lbl_skill2;
    QLabel *lbl_skill3;
    QLabel *lbl_skill4;
    QLabel *lbl_skill5;
    QGroupBox *box_stats;
    QLabel *lbl_stats;

    FF7Materia *data;
    quint8 _id;
    quint8 _type; //1-magic,2-summon,3-independent,4-support,5-command,0-unknown
    qint8 _level;
    qint32 _ap;
};
#endif //MateriaPreview

/****************************************************************************/
//    copyright 2012 - 2023  Chris Rizzitello <sithlord48@gmail.com>        //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include <FF7Materia.h>

FF7Materia *FF7Materia::get()
{
    static FF7Materia m;
    return &m;
}

const FF7Materia::MATERIA &FF7Materia::Materias(int id)
{
    if (id >= 0 && id <= 90)
        return get()->d->_materiaList.at(id);
    return get()->d->_emptyMateria;
}

materia FF7Materia::encodeMateria(int id, qint32 ap)
{
    materia temp;
    ap = qToLittleEndian(ap);
    if ( (id >= 0 )  && (id <= 90 ) && ((ap >= 0) && (ap <= 16777215))) {
        temp.id = id;
        temp.ap[0] = (ap & 0xff);
        temp.ap[1] = (ap & 0xff00) >> 8;
        temp.ap[2] = (ap & 0xff0000) >> 16;
    } else {
        temp.id = FF7Materia::EmptyId;
        temp.ap[0] = 0xFF;
        temp.ap[1] = 0xFF;
        temp.ap[2] = 0xFF;
    }
    return temp;
}

int FF7Materia::materiaID(materia mat)
{
    return idClamp(mat.id);
}

const QList<int> FF7Materia::placeHolderIdList()
{
    QList<int> phList;
    for (const MATERIA &m : get()->d->_materiaList) {
        if(m.name.startsWith(get()->d->_placeHolderFilter))
            phList.append(m.id);
    }
    return phList;
}

QString FF7Materia::enemySkill(int skill)
{
    skill = std::clamp(skill, 0, int(get()->d->_enemySkills.size()) -1);
    return tr(get()->d->_enemySkills.at(skill).toUtf8());
}

QString FF7Materia::masterCommandSkill(int skill)
{
    skill = std::clamp(skill, 0, int(get()->d->_masterCommandList.size()) -1);
    return tr(get()->d->_masterCommandList.at(skill).toUtf8());
}

QString FF7Materia::masterSummonSkill(int skill)
{
    skill = std::clamp(skill, 0, int(get()->d->_masterSummonList.size()) -1);
    return tr(get()->d->_masterSummonList.at(skill).toUtf8());
}

QString FF7Materia::masterMagicSkill(int skill)
{
    skill = std::clamp(skill, 0, int(get()->d->_masterMagicList.size()) -1);
    return tr(get()->d->_masterMagicList.at(skill).toUtf8());
}

QStringList FF7Materia::skills(int id)
{
    QStringList translated_list;
    for(const QString &skill : Materias(idClamp(id)).skills)
        translated_list.append(tr(skill.toUtf8()));
    return translated_list;
}

QStringList FF7Materia::status(int id)
{
    QStringList translated_list;
    for(const QString& stat : Materias(idClamp(id)).status)
        translated_list.append(tr(stat.toUtf8()));
    return translated_list;
}

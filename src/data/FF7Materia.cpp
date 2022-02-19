/****************************************************************************/
//    copyright 2012 - 2020  Chris Rizzitello <sithlord48@gmail.com>        //
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

#include <QQmlEngine>

FF7Materia *FF7Materia::get()
{
    static FF7Materia m;
    return &m;
}

QObject *FF7Materia::qmlSingletonRegister(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)
    engine->setObjectOwnership(get(), QQmlEngine::CppOwnership);
    return get();
}


FF7Materia::FF7Materia(QObject *parent)
    : QObject(parent)
    , d(new FF7MateriaPrivate)
{
}

FF7Materia::~FF7Materia()
{
    delete d;
}


const FF7Materia::MATERIA &FF7Materia::Materias(int id)
{
    if (id >= 0 && id <= 0x5A) {
        return get()->d->_materiaList.at(id);
    }
    return get()->d->_emptyMateria;
}

qint32 FF7Materia::ap(int id, int lvl)
{
    lvl = std::clamp(lvl, 0, 4);
    return Materias(id).ap.at(lvl);
}


QString FF7Materia::name(int id)
{
    return tr(Materias(id).name.toLocal8Bit());
}

QString FF7Materia::statString(int id)
{
    return tr(Materias(id).stats.toLocal8Bit());
}

QString FF7Materia::enemySkill(int id)
{
    id = std::clamp(id, 0, int(get()->d->_enemySkills.size()) -1);
    return tr(get()->d->_enemySkills.at(id).toLocal8Bit());
}

QString FF7Materia::masterCommandSkill(int id)
{
    id = std::clamp(id, 0, int(get()->d->_masterCommandList.size()) -1);
    return tr(get()->d->_masterCommandList.at(id).toLocal8Bit());
}

QString FF7Materia::masterSummonSkill(int id)
{
    id = std::clamp(id, 0, int(get()->d->_masterSummonList.size()) -1);
    return tr(get()->d->_masterSummonList.at(id).toLocal8Bit());
}

QString FF7Materia::masterMagicSkill(int id)
{
    id = std::clamp(id, 0, int(get()->d->_masterMagicList.size()) -1);
    return tr(get()->d->_masterMagicList.at(id).toLocal8Bit());
}

QString FF7Materia::element(int id)
{
    return tr(Materias(id).elemental.toLocal8Bit());
}

QStringList FF7Materia::skills(int id)
{
    QStringList translated_list;
    for(const QString &skill : Materias(id).skills) {
        translated_list.append(tr(skill.toLocal8Bit()));
    }
    return translated_list;
}

QStringList FF7Materia::status(int id)
{
    QStringList translated_list;
    for(const QString& stat : Materias(id).status) {
        translated_list.append(tr(stat.toLocal8Bit()));
    }
    return translated_list;
}
QString FF7Materia::iconResource(int id)
{
    QString temp = Materias(id).imageString;
    return temp.remove(QStringLiteral(":/"));
}

QString FF7Materia::fullStarResource(int id)
{
    QString temp = Materias(id).fullStarString;
    return temp.remove(QStringLiteral(":/"));
}

QString FF7Materia::emptyStartResource(int id)
{
    QString temp = Materias(id).emptyStarString;
    return temp.remove(QStringLiteral(":/"));
}


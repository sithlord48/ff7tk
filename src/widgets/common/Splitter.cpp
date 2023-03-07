/****************************************************************************/
//    Copyright (C) 2009-2022 Arzel Jérôme <myst6re@gmail.com>              //
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
#include "Splitter.h"

Splitter::Splitter(QWidget *parent) :
    QSplitter(parent)
{
}

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent) :
    QSplitter(orientation, parent)
{
}

bool Splitter::isCollapsed(int index)
{
    if (index <= -1 || index >= count() || !isCollapsible(index)) {
        return false;
    }

    QList<int> s = sizes();
    return s.at(index) == 0;
}

void Splitter::setCollapsed(int index, bool collapsed)
{
    if (index <= -1 || index >= count() || !isCollapsible(index)) {
        return;
    }

    QList<int> s = sizes();
    if ((s.at(index) == 0) == collapsed) {
        return; // Already in the right state
    }
    if (collapsed) {
        _lastSizes.insert(index, s.at(index));
        s[index] = 0;
    } else {
        s[index] = _lastSizes.value(index, 1);
    }
    setSizes(s);
}

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
#pragma once

#include <QSplitter>
#include <QMap>
#include <ff7tkqtwidgets_export.h>

class FF7TKQTWIDGETS_EXPORT Splitter : public QSplitter
{
    Q_OBJECT
public:
    explicit Splitter(QWidget *parent = nullptr);
    explicit Splitter(Qt::Orientation orientation, QWidget *parent = nullptr);
    bool isCollapsed(int index);
public slots:
    void setCollapsed(int index, bool collapsed);
    inline void toggleCollapsed(int index) {
        setCollapsed(index, !isCollapsed(index));
    }
private:
    QMap<int, int> _lastSizes;
};

//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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

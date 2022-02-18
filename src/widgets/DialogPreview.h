/****************************************************************************/
//    copyright 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>         //
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

#include <QLabel>

#ifndef ff7tkwidgets_export_h
    #include <ff7tkwidgets_export.h>
#endif

class FF7TKWIDGETS_EXPORT DialogPreview : public QLabel
{
    Q_OBJECT

public:
    /**
     * @brief Describes a corner the the dialog preview
     */
    enum CORNER {
        TOPLEFT=0,
        TOPRIGHT=1,
        BOTTOMRIGHT=2,
        BOTTOMLEFT=3,
    };
    Q_ENUM(CORNER);

    DialogPreview(QWidget *parent = nullptr);
    ~DialogPreview() = default;
    const QColor& color(DialogPreview::CORNER);
    void setColor(DialogPreview::CORNER corner, const QColor &newColor = QColor());
    void setEnabled(bool enabled);

signals:
    /**
     * @brief A Color has Changed
     * @param corner the corner where the change happend
     * @param color the new color
     * @sa CORNER
     */
    void colorChanged(DialogPreview::CORNER corner, const QColor& color= QColor());

private:
    DialogPreview::CORNER getQuad(const QPoint& point = QPoint());
    QList<QColor> colors = {"transparent", "transparent", "transparent", "transparent"};
    int m_cquad=-1;
protected:
    void paintEvent(QPaintEvent *ev) override;
    bool event(QEvent *ev) override;
};


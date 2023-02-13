/****************************************************************************/
//    Copyright (C) 2009-2022 Arzel Jérôme <myst6re@gmail.com>              //
//    Copyright (C) 2023 Chris Rizzitello <sithlord48@gmail.com>            //
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

#include <QWidget>
#include <QEvent>
#include <ff7tkqtwidgets_export.h>

class FF7TKQTWIDGETS_EXPORT OrientationWidget : public QWidget
{
    Q_OBJECT
public:
    enum Style { Grid, Arrow};
    enum Direction {North, East, South, West};
    enum RotationDirection {ClockWise, CounterClockWise};
    explicit OrientationWidget(QWidget *parent = nullptr);
    explicit OrientationWidget(quint8 value, Direction zeroDirection = West, RotationDirection rotationDirection = CounterClockWise, Style style = Style::Grid, QWidget *parent = nullptr);
    quint8 value() const;
    bool isReadOnly() const;
    void setReadOnly(bool ro);
    virtual QSize minimumSizeHint() const override;
    virtual QSize sizeHint() const override;
signals:
    void valueChanged(int i);
    void valueEdited(int i);
public slots:
    void setValue(int value);
    void setStyle(OrientationWidget::Style style);
    void setRotationDirection(OrientationWidget::RotationDirection rotationDirection);
    void setZeroDirection(OrientationWidget::Direction zeroDirection);
private:
    void byte2degree(quint8 v);
    quint8 degree2byte() const;
    QPointF centerCircle() const;
    double radiusCircle() const;
    bool isInCircle(const QPointF &pos);
    void moveCursor(const QPointF &pos);
    void mouseEvent(QMouseEvent *e);
    int _value;
    bool _readOnly;
    Direction _zeroDirection;
    RotationDirection _rotationDirection;
    Style _style;
    QString _lblString;
    void paintGrid(QPainter *p, double radius);
    void paintArrow(QPainter *p, double radius);
    void updateLabel();
protected:
    virtual void changeEvent(QEvent *e) override;
    virtual void paintEvent(QPaintEvent *e) override;
    virtual inline void mousePressEvent(QMouseEvent *e) override {
        mouseEvent(e);
    }
    virtual inline void mouseMoveEvent(QMouseEvent *e) override {
        mouseEvent(e);
    }
};

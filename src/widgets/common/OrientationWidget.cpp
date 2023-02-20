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
#include <OrientationWidget.h>

#include <QMouseEvent>
#include <QPainter>
#include <QTextOption>

OrientationWidget::OrientationWidget(QWidget *parent) :
    QWidget(parent), _value(0), _readOnly(false), _zeroDirection(West), _rotationDirection(CounterClockWise), _style(Style::Grid)
{
    updateLabel();
}

OrientationWidget::OrientationWidget(quint8 value, Direction zeroDirection, RotationDirection rotationDirection, Style style, QWidget *parent)
    : QWidget(parent), _value(0), _readOnly(false), _zeroDirection(zeroDirection), _rotationDirection(rotationDirection), _style(style)
{
    updateLabel();
    byte2degree(value);
}

quint8 OrientationWidget::value() const
{
    return degree2byte();
}

void OrientationWidget::setValue(int value)
{
    byte2degree(quint8(value));
    Q_EMIT valueChanged(value);
    update();
}

void OrientationWidget::setStyle(Style style)
{
    if(_style == style)
        return;
    _style = style;
    update();
}

void OrientationWidget::setRotationDirection(RotationDirection rotationDirection)
{
    if(_rotationDirection == rotationDirection)
        return;
    _rotationDirection = rotationDirection;
    int divisor = _rotationDirection == CounterClockWise ? -360 : 360;
    setValue(quint8((divisor - _value) * 256 / divisor));
    update();
}

void OrientationWidget::setZeroDirection(Direction zeroDirection)
{
    if(_zeroDirection == zeroDirection)
        return;
    _zeroDirection = zeroDirection;
    updateLabel();
    update();
}

void OrientationWidget::byte2degree(quint8 v)
{
    int divisor = _rotationDirection == CounterClockWise ? 360 : -360;
    _value = (256 - v) * divisor / 256;
}

quint8 OrientationWidget::degree2byte() const
{
    int divisor = _rotationDirection == CounterClockWise ? 360 : -360;
    return quint8((divisor - _value) * 256 / divisor);
}

bool OrientationWidget::isReadOnly() const
{
    return _readOnly;
}

void OrientationWidget::setReadOnly(bool ro)
{
    _readOnly = ro;
}

QSize OrientationWidget::minimumSizeHint() const
{
    return QSize(75, 75);
}

QSize OrientationWidget::sizeHint() const
{
    return minimumSizeHint();
}

void OrientationWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    double radius = radiusCircle() - (radiusCircle() * 0.03);
    QPointF centerCircle = this->centerCircle();
    auto font = p.font();
    font.setPixelSize(radius * 0.25);
    p.setFont(font);
    p.setPen(QPen(palette().text(), radius * 0.03));
    p.setBrush(palette().window());
    p.drawEllipse(centerCircle, radius, radius);
    p.translate(centerCircle);
    switch(_zeroDirection) {
        case North: p.rotate(90); break;
        case East: p.rotate(180); break;
        case South: p.rotate(270); break;
        case West:  p.rotate(0); break;
    }
    switch(_style) {
        case Arrow: return paintArrow(&p, radius);
        default: return paintGrid(&p, radius);
    }
}

void OrientationWidget::mouseEvent(QMouseEvent *e)
{
    if (_readOnly) {
        e->ignore();
        return;
    }

    const QPointF &relativePos = e->position();

    if (isInCircle(relativePos)) {
        moveCursor(relativePos);
    }
}

void OrientationWidget::paintGrid(QPainter *p, double radius)
{
    p->rotate(_value);
    p->drawLines({QLineF(QPointF(-radius, 0), QPointF(radius, 0)), QLineF(QPointF(0, -radius), QPointF(0, radius))});

    int value = qAbs(_value);
    int height = p->fontMetrics().height();
    double X = -radius * 0.94;

    if(_zeroDirection == North) {
        p->translate(X, -height);
        if (value <= 180) {
            p->translate(-X, height);
            p->rotate(180);
        }
    } else if (_zeroDirection == East) {
        p->translate(0, 0);
        p->rotate(180);
        if (value >= 90 && value < 270) {
            p->translate(-X, height);
            p->rotate(180);
        }
    } else if (_zeroDirection == South) {
        p->rotate(180);
        if (value <= 180) {
            p->translate(-X, height);
            p->rotate(180);
        }
    } else if(_zeroDirection == West) {
        p->translate(X, -height);
        if (value >= 90 && value < 270) {
            p->translate(-X, height);
            p->rotate(180);
        }
    }

    p->drawText(QRectF(0, 0, radius * 0.9, height), _lblString, QTextOption(Qt::AlignCenter));
}

void OrientationWidget::paintArrow(QPainter *p, double radius)
{
    for (int i = 0; i < 12; ++i) {
        p->drawLine(-radius + (radius * 0.03), 0, -radius + (radius * 0.15), 0);
        p->rotate(30.0);
    }
    p->rotate(_value);

    p->setPen(QPen(palette().text(), radius * 0.09));
    p->drawLine(QLineF(QPointF(-radius * 0.4, 0), QPointF(radius/2, 0)));
    p->setPen(QPen(palette().text(), radius * 0.01));
    p->setBrush(palette().text());
    p->drawPolygon({QPointF((-radius * 0.80)  , 0),  QPointF((radius * 0.12) , - radius * 0.15), QPointF(-radius * 0.25 , 0), QPointF((radius * 0.12), radius * 0.15)}, Qt::WindingFill);
}

void OrientationWidget::updateLabel()
{
    switch (_zeroDirection) {
        case North: _lblString = tr("Down"); break;
        case East: _lblString = tr("Left"); break;
        case South: _lblString = tr("Up"); break;
        case West: _lblString = tr("Right"); break;
    }
}

void OrientationWidget::changeEvent(QEvent *e)
{
    switch(e->type()) {
        case QEvent::LanguageChange: updateLabel();
        case QEvent::PaletteChange: update();
    default: break;
    }
}

QPointF OrientationWidget::centerCircle() const
{
    return QPointF(width()/2.0, height()/2.0);
}

double OrientationWidget::radiusCircle() const
{
    return (qMin(width(), height()) - 1)/2.0;
}

bool OrientationWidget::isInCircle(const QPointF &pos)
{
    QPointF centerCircle = this->centerCircle();
    qreal sizeX=pos.x() - centerCircle.x(), sizeY=pos.y() - centerCircle.y();
    double distance = sqrt(sizeX*sizeX + sizeY*sizeY);
    return distance <= radiusCircle();
}

void OrientationWidget::moveCursor(const QPointF &pos)
{
    QPointF centerCircle = this->centerCircle();
    qreal sizeX = pos.x() - centerCircle.x(), sizeY = pos.y() - centerCircle.y();
    int offset = _zeroDirection == North ? 90
                 : _zeroDirection == East ? 180
                 : _zeroDirection == South ? -90 : 0;
    double angle;

    if (sizeX != 0.0) {
        angle = atan2(qAbs(sizeY), qAbs(sizeX)) * 57.29577951;// rad2deg
    } else {
        angle = 0;
    }
    if (sizeX == 0.0 && sizeY == 0.0)
        return;

    int topAngle = _zeroDirection == North ? 0
                 : _zeroDirection == East ? 270
                 : _zeroDirection == South ? 180 : 90;

    int bottomAngle = _zeroDirection == North ? 180
                   : _zeroDirection == East ? 90
                   : _zeroDirection == South ? 0 : 270;
    int angleModifier = (_zeroDirection == North || _zeroDirection == South) ? 180 : 0;
    int angleFlipModifier = (_zeroDirection == North || _zeroDirection == South) ? 0 : 180;

    if (sizeX < 0 && sizeY <= 0) {
        _value = angleModifier + int(angle+offset);
    } else if (sizeX == 0.0 && sizeY < 0) {
        _value = topAngle;
    } else if (sizeX > 0 && sizeY < 0) {
        _value = 180 - int(angle+offset);
    } else if (sizeX == 0.0 && sizeY > 0) {
        _value = bottomAngle;
    } else if (sizeX < 0 && sizeY > 0) {
        _value = 360 - int(angle+offset);
    } else if (sizeX > 0 && sizeY >= 0) {
        _value = angleFlipModifier + int(angle+offset);
    }

    quint8 value = degree2byte();
    setValue(value);
    Q_EMIT valueEdited(value);
}
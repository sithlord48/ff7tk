//    SPDX-FileCopyrightText: 2012 - 2022 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <DialogPreview.h>

#include <QColorDialog>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

DialogPreview::DialogPreview(QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
    setMinimumSize(60, 30);
}

const QColor &DialogPreview::color(DialogPreview::CORNER corner)
{
    return colors.at(corner);
}

void DialogPreview::setColor(DialogPreview::CORNER corner, const QColor &newColor)
{
    if(newColor == colors.at(corner))
        return;
    colors.replace(corner, newColor);
    update();
    Q_EMIT colorChanged(corner, newColor);
}

void DialogPreview::setEnabled(bool enabled)
{
    setMouseTracking(enabled);
    QWidget::setEnabled(enabled);
}

DialogPreview::CORNER DialogPreview::getQuad(const QPoint &point)
{
    if(point.isNull())
        return CORNER::TOPLEFT;
    const int hwidth = width() / 2;
    const int hheight = height () / 2;
    const int x = point.x();
    const int y = point.y();
    if ( x <= hwidth && y <= hheight)
        return CORNER::TOPLEFT;
    if (x >= hwidth && y <= hheight)
        return CORNER::TOPRIGHT;
    if (x <= hwidth && y >= hheight)
        return CORNER::BOTTOMLEFT;
    else
        return CORNER::BOTTOMRIGHT;
}

void DialogPreview::paintEvent(QPaintEvent *ev)
{
    QImage image(2, 2, QImage::Format_ARGB32);
    image.setPixel(0, 0, colors.at(CORNER::TOPLEFT).rgb());
    image.setPixel(0, 1, colors.at(CORNER::BOTTOMLEFT).rgb());
    image.setPixel(1, 0, colors.at(CORNER::TOPRIGHT).rgb());
    image.setPixel(1, 1, colors.at(CORNER::BOTTOMRIGHT).rgb());
    QImage gradient = image.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPainter painter(this);
    painter.fillRect(ev->rect(), gradient);
    if(isEnabled()) {
        QRect highlight_rect = {0,0,0,0};
        int hh = height() /2;
        int hw = width() /2;
        if(m_cquad == 0)
            highlight_rect = {0,0, hw, hh};
        if(m_cquad == 1)
            highlight_rect = {hw, 0, hw , hh};
        if(m_cquad == 2)
            highlight_rect = {hw, hh , hw, hh};
        if(m_cquad == 3)
            highlight_rect = {0, hh, hw, hh};
        painter.setCompositionMode(QPainter::CompositionMode::CompositionMode_SourceOver);
        painter.setOpacity(0.35F);
        painter.fillRect(highlight_rect, palette().highlight());
    }
}

bool DialogPreview::event(QEvent *ev)
{
    if(ev->type() == QEvent::Leave && isEnabled()) {
        m_cquad = -1;
        repaint();
        return true;
    }

    if(ev->type() == QEvent::MouseMove) {
        auto e = static_cast<QMouseEvent*>(ev);
        int quad = static_cast<int>(getQuad(e->pos()));
        if(m_cquad != quad) {
            m_cquad = quad;
            repaint();
        }
        return true;
    }

    if(ev->type() == QEvent::MouseButtonPress && isEnabled()) {
        auto e = static_cast<QMouseEvent*>(ev);
        auto quad = getQuad(e->pos());
        QColor color = QColorDialog::getColor(colors.at(quad), this);
        if(color.isValid())
            setColor(quad, color);
        return true;
    }
    return QWidget::event(ev);
}

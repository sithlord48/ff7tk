//    SPDX-FileCopyrightText: 2010 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <SaveIcon.h>

#include <QByteArray>
#include <QList>
#include <QTimer>

QTimer SaveIcon::m_timer;

SaveIcon::SaveIcon()
    : m_nbFrames(0)
{
    connect(&m_timer, &QTimer::timeout, this, &SaveIcon::nextFrame);
}

SaveIcon::SaveIcon(const QByteArray &data, quint8 nbFrames)
{
    connect(&m_timer, &QTimer::timeout, this, &SaveIcon::nextFrame);
    setAll(data, nbFrames);
}

SaveIcon::SaveIcon(const QList<QByteArray> &data)
{
    connect(&m_timer, &QTimer::timeout, this, &SaveIcon::nextFrame);
    setAll(data);
}

void SaveIcon::setAll(const QByteArray &data, quint8 nbFrames)
{
    m_data = data;
    m_nbFrames = nbFrames;
    if(nbFrames > 1) {
        m_timer.start(160);
    } else {
        Q_EMIT nextIcon(icon());
    }
}

void SaveIcon::setAll(const QList<QByteArray> &data)
{
    m_data.clear();
    m_nbFrames = quint8(data.size());

    for(int i= 0; i < m_nbFrames; i++)
        m_data.append(data.at(i));

    if(m_nbFrames>1) {
        m_timer.start(160);
    } else {
        Q_EMIT nextIcon(icon());
    }
}

const QByteArray &SaveIcon::save()
{
    return m_data;
}

QPixmap SaveIcon::icon(bool chocobo_world_icon)
{
    if (m_data.isEmpty())
        return QPixmap();
    if (chocobo_world_icon)
        return chocoWorldIcon();
    return psxIcon();
}

QPixmap SaveIcon::psxIcon()
{
    quint16 i;
    quint8 y = 0, x = 0;
    //palette
    const char *access_data = m_data.constData();
    QList<QRgb> colors;
    quint16 color;
    for (i = 0 ; i < 16 ; ++i) {
        memcpy(&color, access_data, 2);
        colors.append(qRgb(int((color & 31) * 8.2258), int((color >> 5 & 31) * 8.2258), int((color >> 10 & 31) * 8.2258)));
        access_data += 2;
    }

    QImage image(16, 16, QImage::Format_RGB32);
    quint16 firstPos = 32 + m_curFrame * 128, lastPos = firstPos + 128;

    if (m_data.size() < lastPos)
        return QPixmap();

    for (i = firstPos ; i < lastPos ; ++i) {
        quint8 index = quint8(m_data.at(i));
        image.setPixel(x, y, colors.at(index & 0xF));
        if (x == 15) {
            x = 0;
            ++y;
        } else {
            ++x;
        }
        image.setPixel(x, y, colors.at(index >> 4));

        if (x == 15) {
            x = 0;
            ++y;
        } else {
            ++x;
        }
    }
    return QPixmap::fromImage(image);
}

QPixmap SaveIcon::chocoWorldIcon()
{
    if (m_data.size() != 288)
        return QPixmap();

    QImage image(32, 32, QImage::Format_Mono);
    quint8 j;
    quint8 y = 0, x = 0;

    for (quint16 i = 160 ; i < 288 ; ++i) {
        quint8 curPx = quint8(m_data.at(i));
        for (j = 0 ; j < 8 ; ++j) {
            image.setPixel(x, y, !((curPx >> j) & 1));
            if (x == 31) {
                x = 0;
                ++y;
            } else {
                ++x;
            }
        }
    }
    return QPixmap::fromImage(image);
}

void SaveIcon::nextFrame()
{
    if (m_nbFrames == 0)
        return;

    m_curFrame = (m_curFrame + 1) % m_nbFrames;
    QPixmap pix = icon();

    if (!pix.isNull())
        Q_EMIT nextIcon(pix);
}

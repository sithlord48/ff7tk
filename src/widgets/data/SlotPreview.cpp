/****************************************************************************/
//    copyright 2012 -2022  Chris Rizzitello <sithlord48@gmail.com>         //
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
#include <SlotPreview.h>
#include <SaveIcon>

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QToolButton>
#include <QVBoxLayout>

SlotPreview::SlotPreview(int index, QWidget *parent)
    : QLabel(parent)
    , m_index(index)
{
    QFontMetrics formFont(QFont(QStringLiteral("Verdana"), 18, 75, false));
    m_lineHeight = formFont.height();
    setFixedSize(QSize( int((m_lineHeight *5.2) * 4.311), int(m_lineHeight * 5.2)));
    setCursor(Qt::PointingHandCursor);

    btn_remove = new QToolButton(this);
    btn_remove->setIcon(QIcon::fromTheme(QString("edit-clear"), QPixmap(":/common/edit-clear")));
    btn_remove->setToolTip(tr("Clear Slot"));
    connect(btn_remove, &QToolButton::clicked, this, [this] { Q_EMIT btn_remove_clicked(m_index); });

    btn_copy = new QToolButton(this);
    btn_copy->setIcon(QIcon::fromTheme(QString("edit-copy"), QPixmap(":/common/edit-copy")));
    btn_copy->setToolTip(tr("Copy Slot"));
    connect(btn_copy, &QToolButton::clicked, this, [this] { Q_EMIT btn_copy_clicked(m_index); });

    btn_paste = new QToolButton(this);
    btn_paste->setIcon(QIcon::fromTheme(QString("edit-paste"), QPixmap(":/common/edit-paste")));
    btn_paste->setToolTip(tr("Paste Into Slot"));
    connect(btn_paste, &QToolButton::clicked, this, [this] { Q_EMIT btn_paste_clicked(m_index); });

    const QList<QToolButton*> buttons = findChildren<QToolButton *>();

    int btnWH = int (m_lineHeight * 0.8);
    QSize btnSize = QSize(btnWH, btnWH);
    QSize iconSize = QSize (btnWH - 4, btnWH - 4);
    for (auto btn : buttons) {
        btn->setFixedSize(btnSize);
        btn->setIconSize(iconSize);
        btn->setCursor(Qt::BitmapCursor);
    }
    btn_copy->setHidden(true);
    btn_remove->setHidden(true);

    auto btnLayout = new QHBoxLayout;
    btnLayout->setAlignment(Qt::AlignRight);
    btnLayout->setContentsMargins(3, 0, 3, 0);
    btnLayout->addWidget(btn_copy, Qt::AlignRight);
    btnLayout->addWidget(btn_paste, Qt::AlignRight);
    btnLayout->addWidget(btn_remove, Qt::AlignRight);
    btnLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

    auto layout = new QVBoxLayout(this);
    layout->addLayout(btnLayout);
    layout->addStretch();
    setLayout(layout);
}

void SlotPreview::setMode(MODE mode)
{
    if(mode == m_mode)
        return;

    switch (mode) {
        case FF7SAVE: btn_copy->setHidden(false);
        case PSXGAME: btn_remove->setHidden(false);
        case EMPTY: btn_paste->setHidden(false);
    }
    m_mode = mode;
    repaint();
}

void SlotPreview::setBackground(const QImage &image)
{
    m_background = image;
}

void SlotPreview::setPSXText(const QString &text)
{
    m_psxText = text;
}

void SlotPreview::setParty(QPixmap p1, QPixmap p2, QPixmap p3)
{
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
}

int SlotPreview::index(void)
{
    return m_index;
}

void SlotPreview::setName(QString name)
{
    if(m_name == name)
        return;
    m_name = name;
}

void SlotPreview::setLevel(int lvl)
{
    m_level = QString(tr("Level:%1")).arg(QString::number(lvl));
}

void SlotPreview::setLocation(QString loc)
{
    m_location = loc;
}

void SlotPreview::setGil(int gil)
{
    m_gil = QString(tr("Gil:%1")).arg(QString::number(gil));
}

void SlotPreview::setTime(int hr, int min)
{
    m_time = QString(tr("Time:%1:%2")).arg(QString::number(hr), QString("%1").arg(QString::number(min), 2, QChar('0')));
}

void SlotPreview::setPsxIcon(const QByteArray &icon_data, quint8 frames)
{
    if(!m_psxIcon) {
        m_psxIcon = new SaveIcon();
        connect(m_psxIcon, &SaveIcon::nextIcon, this, [this]{ update(); });
    }
    m_psxIcon->setAll(icon_data, frames);
}

void SlotPreview::setPsxIcon(const QList<QByteArray> &icon_data)
{
    if(!m_psxIcon) {
        m_psxIcon = new SaveIcon();
        connect(m_psxIcon, &SaveIcon::nextIcon, this, [this]{ update(); });
    }
    m_psxIcon->setAll(icon_data);
}

void SlotPreview::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        Q_EMIT clicked(m_index);
}

void SlotPreview::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.translate(3,3);
    p.setPen(QPen(QBrush(Qt::black), 3));
    if (m_mode == FF7SAVE)
        p.setBrush(m_background);
    p.drawRect(QRect(0, 0, width() - 6, height() - 6));

    auto f = font();
    f.setFamily(QStringLiteral("Verdana"));
    f.setWeight(QFont::Thin);
    //Slot Text
    f.setPointSize(16);
    p.setFont(f);
    p.setPen( m_mode == FF7SAVE ? Qt::white : palette().text().color());

    int padding = 6;
    p.drawText(contentsMargins().left() + padding, contentsMargins().top() + fontMetrics().height() + padding, tr("Slot: %1").arg(QString::number(m_index + 1)));

    if (m_mode == PSXGAME) {
        int w = int(m_lineHeight * 3.5);
        p.translate(12, (height() * 0.25) - (contentsMargins().top() * 2) - 6 );
        p.drawPixmap(0, 0, w, w, m_psxIcon->icon().scaled(w,w,Qt::KeepAspectRatio, Qt::SmoothTransformation));

        auto nl = QStringLiteral("\n");
        QString str = m_psxText;
        QString desc;
        if(str.contains(nl))
            desc = str.split(nl).first();
        str.remove(desc);
        str.append(nl);
        f.setPointSize(12);
        p.setFont(f);
        p.setPen(palette().text().color());
        p.drawText(w + 2 , 4 , width() - (w + 20), m_lineHeight , Qt::AlignLeft, desc.simplified());
        p.drawText(w + 2, m_lineHeight + 6, width() - (w + 24), m_lineHeight * 2 , Qt::AlignJustify, str);
    } else if (m_mode == FF7SAVE) {
        int w = m_lineHeight * 3;
        int h = m_lineHeight * 3.75;
        p.translate(12, (height() * 0.25) - (contentsMargins().top() * 2) - 6 );
        p.drawPixmap(0, 0, w, h, m_p1);
        p.drawPixmap(w+6, 0, w, h, m_p2);
        p.drawPixmap(w+w+12, 0, w, h, m_p3);
        f.setPointSize(16);
        p.setFont(f);
        p.setPen(Qt::white);
        p.drawText(270, 0, 175, m_lineHeight, Qt::AlignCenter, m_name);
        p.drawText(450, 0, 155, m_lineHeight, Qt::AlignCenter,m_time);
        p.drawText(270, 40, 125, m_lineHeight, Qt::AlignCenter,m_level);
        p.drawText(400, 40, 205, m_lineHeight, Qt::AlignCenter,m_gil);
        p.drawText(270, 75, 335, m_lineHeight, Qt::AlignCenter, m_location);
    } else {
        QColor pColor = palette().text().color().value() > QColor(Qt::lightGray).value() ? Qt::yellow : QColor("orange");
        QString str = tr("-Empty Slot-");
        f.setPointSize(20);
        p.setFont(f);
        p.setPen(pColor);
        p.drawText(0,0, width(), height(), Qt::AlignCenter, str);
    }
    QWidget::paintEvent(e);
}

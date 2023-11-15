//    SPDX-FileCopyrightText: 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QLabel>
#include <ff7tkqtwidgets_export.h>

class FF7TKQTWIDGETS_EXPORT DialogPreview : public QLabel
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


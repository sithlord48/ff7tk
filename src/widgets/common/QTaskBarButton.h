//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QObject>
#include <QImage>
#include <ff7tkqtwidgets_export.h>

#if defined(Q_OS_WIN)
    #include <shobjidl.h>
    #include <QApplication>
    #include <QWidget>
    #define QTASKBAR_WIN
#elif defined(Q_OS_DARWIN)
    #define QTASKBAR_APPLE
#endif

class FF7TKQTWIDGETS_EXPORT QTaskBarButton : public QObject
{
    Q_OBJECT
public:
    enum State {
        Invisible, Normal, Indeterminate, Paused, Error
    };

    explicit QTaskBarButton(QObject *parent = nullptr);
    virtual ~QTaskBarButton() override;
    void setOverlayIcon(const QImage &image = QImage(), const QString &text = QString());
    void setState(State state);
    int maximum() const;
    int minimum() const;
    State state() const;
    int value() const;
signals:
    void valueChanged(int value);
public slots:
    void reset();
    void setMaximum(int maximum);
    void setMinimum(int minimum);
    void setRange(int minimum, int maximum);
    void setValue(int value);
private:
#ifdef QTASKBAR_WIN
    WId _winId;
    ITaskbarList3 *pITask;
#endif // Q_OS_WIN
    int _minimum;
    int _maximum;
    int _value;
    State _state;
};

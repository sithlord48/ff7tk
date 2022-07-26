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

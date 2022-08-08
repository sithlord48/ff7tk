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
/****************************************************************************/
#pragma once

#include <QLineEdit>
#include <ff7tkqtwidgets_export.h>

class FF7TKQTWIDGETS_EXPORT HexLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit HexLineEdit(QWidget *parent = nullptr);
    explicit HexLineEdit(const QByteArray &contents, QWidget *parent = nullptr);
    QByteArray data() const;
    void setMaxLength(int maxLength);
public slots:
    void setData(const QByteArray &contents);
signals:
    void dataChanged(const QByteArray &data);
    void dataEdited(const QByteArray &data);
private:
    QString text() const;
    void setInputMask(const QString &inputMask);
    bool _noEmit;
    QString _hexRegEx = QStringLiteral("([A-F]|[0-9]|[a-f])*");
private slots:
    void emitDataEdited();
    void setText(const QString &);
};

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
#include <HexLineEdit.h>

HexLineEdit::HexLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , _noEmit(false)
{
    connect(this, &HexLineEdit::textEdited, this, &HexLineEdit::emitDataEdited);
}

HexLineEdit::HexLineEdit(const QByteArray &contents, QWidget *parent)
    : QLineEdit(parent)
    , _noEmit(false)
{
    setData(contents);
}

QByteArray HexLineEdit::data() const
{
    return QByteArray::fromHex(text().toLatin1()).leftJustified(maxLength()/2, '\0', true);
}

void HexLineEdit::setData(const QByteArray &contents)
{
    _noEmit = true;
    setMaxLength(contents.size() * 2);
    setInputMask(QString(contents.size() * 2, 'H'));
    _noEmit = false;
    setText(QString::fromLatin1(contents.toHex()));
    Q_EMIT dataChanged(contents);
}

void HexLineEdit::emitDataEdited()
{
    if (_noEmit)
        return;
    Q_EMIT dataEdited(data());
}

QString HexLineEdit::text() const
{
    return QLineEdit::text();
}

void HexLineEdit::setText(const QString &text)
{
    QLineEdit::setText(text);
}

void HexLineEdit::setMaxLength(int maxLength)
{
    QLineEdit::setMaxLength(maxLength);
}

void HexLineEdit::setInputMask(const QString &inputMask)
{
    QLineEdit::setInputMask(inputMask);
}

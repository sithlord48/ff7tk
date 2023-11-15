//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <HexLineEdit.h>
#include <QRegularExpressionValidator>

HexLineEdit::HexLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , _noEmit(false)
{
    setValidator(new QRegularExpressionValidator(QRegularExpression(_hexRegEx), this));
    connect(this, &HexLineEdit::textEdited, this, &HexLineEdit::emitDataEdited);
}

HexLineEdit::HexLineEdit(const QByteArray &contents, QWidget *parent)
    : HexLineEdit(parent)
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


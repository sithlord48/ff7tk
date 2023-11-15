//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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

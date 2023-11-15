//    SPDX-FileCopyrightText: 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QDialog>
#include <ff7tkwidgets_export.h>

class FF7Save;
class QDialogButtonBox;
class QVBoxLayout;

class FF7TKWIDGETS_EXPORT MetadataCreator : public QDialog
{
    Q_OBJECT
public:
    explicit MetadataCreator(QWidget *parent = nullptr, FF7Save *ff7save = nullptr);
private slots:
    void initDisplay();
    void onAccepted();

private:
    QString getOpenFileName(QWidget  *parent = nullptr, const QString &title = QString(), const QString &path = QString(), const QString &nameFilters = QString(), const QString &initSelection = QString());
    QString getExistingDirectory(QWidget *parent = nullptr, const QString &title = QString(), const QString &path = QString(), const QString &initSelection = QString());
    QVBoxLayout *makeLineLayout();
    //Data Parts
    bool load;
    FF7Save *ff7;
    QStringList InFiles;
    QString OutPath;
    QString UserID;
    QDialogButtonBox *btnBox = nullptr;
};

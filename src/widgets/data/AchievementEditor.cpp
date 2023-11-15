//    SPDX-FileCopyrightText: 2013 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <AchievementEditor.h>

#include <QGridLayout>
#include <QEvent>
#include <QListWidget>

AchievementEditor::AchievementEditor(QWidget *parent) :
    QWidget(parent)
{
    initDisplay();
    connect(achievementList, &QListWidget::clicked, this, &AchievementEditor::itemToggled);
}

void AchievementEditor::initDisplay()
{
    achievementList = new QListWidget;
    achievementList->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));
    auto layout = new QGridLayout;
    for (int i = 63; i > 27; --i) {
        QPixmap pix(QStringLiteral(":/achievements/%1").arg(QString::number(i)));
        auto newItem = new QListWidgetItem(QIcon(pix), achievements.name(i), achievementList, 0);
        newItem->setCheckState(Qt::Unchecked);
    }
    layout->addWidget(achievementList);
    setLayout(layout);
}

bool AchievementEditor::openFile(const QString &fileName)
{
    bool open = achievements.openFile(fileName);
    for (int i = 0; i < 36; ++i) {
        if (achievements.achievementUnlocked(63 - i))
            achievementList->item(i)->setCheckState(Qt::Checked);
        else
            achievementList->item(i)->setCheckState(Qt::Unchecked);
    }
    return open;
}

void AchievementEditor::itemToggled(const QModelIndex &index)
{
    if (achievementList->item(index.row())->checkState() == Qt::Checked)
        achievements.setAchievementUnlocked(63 - index.row(), true);
    else
        achievements.setAchievementUnlocked(63 - index.row(), false);
}

bool AchievementEditor::saveFile(const QString &fileName)
{
    return achievements.saveFile(fileName);
}


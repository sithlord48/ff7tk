//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <SlotSelect.h>

#include <QFrame>
#include <QIcon>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>

#include <SlotPreview>
#include <FF7Char>
#include <FF7Save>


SlotSelect::SlotSelect(FF7Save *data, bool loadVisible, QWidget *parent)
    : QDialog(parent)
    , btnNew(new QPushButton(QIcon::fromTheme(QString("document-open"), QPixmap()), tr("Load Another File")))
    , ff7(data)
{
    connect(btnNew, &QPushButton::clicked, this, &SlotSelect::newFile);
    setWindowFlags(((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowCloseButtonHint)); //remove close button
    setWindowTitle(tr("Select A Slot"));

    preview_layout = new QVBoxLayout;
    auto frm_preview = new QFrame;
    frm_preview->setLayout(preview_layout);
    frm_preview->setContentsMargins(0, 0, 0, 0);
    preview_layout->setContentsMargins(0, 0, 0, 0);
    preview_layout->setSpacing(3);
    for (int i = 0; i < 15; i++) {
        preview[i] = new SlotPreview(i, this);
        preview_layout->addWidget(preview[i]);
        setSlotPreview(i);
    }
    auto list_preview = new QScrollArea;
    list_preview->setWidget(frm_preview);
    list_preview->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout *dialog_layout = new QVBoxLayout;
    dialog_layout->setContentsMargins(0, 0, 0, 0);
    dialog_layout->setSpacing(5);
    dialog_layout->addWidget(list_preview);
    dialog_layout->addWidget(btnNew);
    showLoad(loadVisible);
    setLayout(dialog_layout);
    setFixedWidth(int(preview[1]->width() + contentsMargins().left() + contentsMargins().right() + list_preview->verticalScrollBar()->sizeHint().width()  + fontMetrics().horizontalAdvance(QChar(':'))));
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    if(parent)
        move(parent->x() + ((parent->width() - width()) / 2), parent->y() + ((parent->sizeHint().height() - sizeHint().height()) /2));
}

void SlotSelect::button_clicked(int s)
{
    done(s);
}

void SlotSelect::remove_slot(int s)
{
    if (!FF7SaveInfo::isTypePC(ff7->format())) {
        if (ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_INUSE)
                && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED)) {
            return;
        }
        int size = ff7->psx_block_size(s);
        for (int i = 0;  i < size; i++) {
            int t = ff7->psx_block_next(s);
            ff7->clearSlot(s);
            ReIntSlot(s);
            s = t;
        }
    } else {
        ff7->clearSlot(s);
        ReIntSlot(s);
    }
}

void SlotSelect::copy_slot(int s)
{
    //We can not Copy Non FF7 Slots Since we don't modify their region data and it will result in a duplicate index entry.
    if (!ff7->isFF7(s))
        return;
    ff7->copySlot(s);
}

void SlotSelect::paste_slot(int s)
{
    if (!FF7SaveInfo::isTypePC(ff7->format())) {
        if (ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK)
         || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)) {
            return;
        }

        if ((!ff7->isFF7(s)) && (ff7->psx_block_size(s) > 1)) {
            int old_s = s;
            int size = ff7->psx_block_size(s);
            for (int i = 0; i < size; i++) {
                int t = ff7->psx_block_next(s);
                ff7->clearSlot(s);
                ReIntSlot(s);
                s = t;
            }
            s = old_s;
        }
    }
    ff7->pasteSlot(s);
    ReIntSlot(s);
}

void SlotSelect::ReIntSlot(int s)
{
    preview[s]->~SlotPreview();
    preview[s] = new SlotPreview(s, this);
    preview_layout->insertWidget(s, preview[s]);
    setSlotPreview(s);
}

void SlotSelect::setSlotPreview(int s)
{
    if (ff7->isSlotEmpty(s)) {
        preview[s]->setMode(SlotPreview::EMPTY);
    } else if (ff7->isFF7(s)) {
        preview[s]->setMode(SlotPreview::FF7SAVE);
        //show real Dialog background.
        QImage image(2, 2, QImage::Format_ARGB32);
        image.setPixel(0, 0, ff7->dialogColorUL(s).rgb());
        image.setPixel(1, 0, ff7->dialogColorUR(s).rgb());
        image.setPixel(0, 1, ff7->dialogColorLL(s).rgb());
        image.setPixel(1, 1, ff7->dialogColorLR(s).rgb());
        QImage gradient = image.scaled(preview[s]->width(), preview[s]->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        preview[s]->setBackground(gradient);
        preview[s]->setParty(FF7Char::pixmap(ff7->descParty(s, 0)), FF7Char::pixmap(ff7->descParty(s, 1)), FF7Char::pixmap(ff7->descParty(s, 2)));
        preview[s]->setLocation(ff7->descLocation(s));
        preview[s]->setName(ff7->descName(s));
        preview[s]->setLevel(ff7->descLevel(s));
        preview[s]->setGil(int(ff7->descGil(s)));
        preview[s]->setTime((ff7->descTime(s) / 3600), (ff7->descTime(s) / 60 % 60));
    } else {
        // all other psx saves.
        preview[s]->setMode(SlotPreview::PSXGAME);
        preview[s]->setPsxIcon(ff7->slotIcon(s));
        QString Slottext;

        if (ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK)
                || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK)
                || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)
                || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK)) {
            switch (ff7->psx_block_type(s)) {
                case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK):   Slottext.append(tr("       Mid-Linked Block")); break;
                case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK):  Slottext.append(tr("    Mid-Linked Block (Deleted)")); break;
                case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK):  Slottext.append(tr("      End Of Linked Blocks")); break;
                case char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK): Slottext.append(tr("      End Of Linked Blocks (Deleted)")); break;
                default: Slottext.append(tr("ERROR")); break;
            }
        }
        Slottext.append(ff7->psxDesc(s));

        if (ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK)
                && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK)
                && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)
                && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK)) {
            Slottext.append(tr("\n\t Game Uses %n Save Block(s)", nullptr, ff7->psx_block_size(s)));
        }

        if (ff7->psx_block_next(s) != 0xFF)
            Slottext.append(tr("\n\t   Next Data Chunk @ Slot:%1").arg(QString::number(ff7->psx_block_next(s) + 1)));

        preview[s]->setPSXText(Slottext);
    }

    connect(preview[s], &SlotPreview::clicked, this, &SlotSelect::button_clicked);
    connect(preview[s], &SlotPreview::remove, this, &SlotSelect::remove_slot);
    connect(preview[s], &SlotPreview::copy, this, &SlotSelect::copy_slot);
    connect(preview[s], &SlotPreview::paste, this, &SlotSelect::paste_slot);
}

void SlotSelect::newFile(void)
{
    done(-1);
}

void SlotSelect::showLoad(bool show)
{
    btnNew->setVisible(show);
    if (show)
        setMinimumHeight(442);
    else
        setMinimumHeight(420);
}

//    SPDX-FileCopyrightText: 2012 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QDialog>
#include <ff7tkwidgets_export.h>

class QVBoxLayout;
class QWidget;

class SlotPreview;
class FF7Save;

/** \class SlotSelect
 *  \brief Display a preview of the contents of a PSX memory card file or FF7 PC save.
 *
 * When the dialog is run it will return the slot selected (0-14) or -1 if the load button was pushed.
 * Copy Paste and Remove are are internal so no need to worry about doing those.
 * Copy will currently only copies FF7 Saves.
 */
class FF7TKWIDGETS_EXPORT SlotSelect : public QDialog
{
    Q_OBJECT
public:
    enum RESULT {
        CANCEL = -2,
        LOAD_NEW = -1
    };
    /** \brief create a new SlotSelect Dialog.
     *  \param data Pointer to a FF7Save object
     *  \param loadVisiable show the load file button
     *  \param parent Dialogs Parent
     */
    explicit SlotSelect(FF7Save *data = nullptr, bool loadVisiable = false, QWidget *parent = nullptr);
private slots:
    void button_clicked(int s);
    void remove_slot(int s);
    void copy_slot(int s);
    void paste_slot(int s);
    void newFile(void);
    void reject() override;
private:
    void setSlotPreview(int s);
    void showLoad(bool shown);
    void ReIntSlot(int s);
    QVBoxLayout *preview_layout;
    SlotPreview *preview[15];
    QPushButton *btnNew;
    //Private Data
    FF7Save *ff7;
};

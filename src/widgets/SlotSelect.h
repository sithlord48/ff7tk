/****************************************************************************/
//    copyright 2012 - 2020 Chris Rizzitello <sithlord48@gmail.com>         //
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

#include <QDialog>

#ifndef ff7tkwidgets_export_h
    #include <ff7tkwidgets_export.h>
#endif

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

    /** \brief create a new SlotSelect Dialog.
     *  \param scale Scale Fixed contents by this number (hidpi screens)
     *  \param data Pointer to a FF7Save object
     *  \param loadVisiable show the load file button
     *  \param parent Dialogs Parent
     */
    explicit SlotSelect(qreal scale = 1, FF7Save *data = nullptr, bool loadVisiable = false, QWidget *parent = nullptr);
private slots:
    void button_clicked(int s);
    void remove_slot(int s);
    void copy_slot(int s);
    void paste_slot(int s);
    void newFile(void);
private:
    void setSlotPreview(int s);
    void showLoad(bool shown);
    void ReIntSlot(int s);
    QVBoxLayout *preview_layout;
    SlotPreview *preview[15];
    QPushButton *btnNew;
    //Private Data
    FF7Save *ff7;
    qreal _scale;
};

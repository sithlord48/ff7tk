/****************************************************************************/
//    copyright 2012 -2021  Chris Rizzitello <sithlord48@gmail.com>         //
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
#include <FF7Save.h>
// This Class should contain NO Gui Parts
#include <QColor>
#include <QDateTime>
#include <QMap>
#include <QTextCodec>
#include <QFile>
#include <QFileInfo>
#include <QMessageAuthenticationCode>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QVector>
#include <QtEndian>
#include <FF7Text.h>

// I'm not installing this header.
#include "crypto/aes.h"

FF7Save::FF7Save()
{
    fileHasChanged = false;
    for (int i = 0; i < 15; i++)
        slotChanged[i] = false;
    buffer_slot.checksum = 0x4D1D;
}

FF7SaveInfo::FORMAT FF7Save::fileDataFormat(QFile &file)
{
    if(!file.isOpen())
        return FF7SaveInfo::FORMAT::UNKNOWN;

    auto file_size = file.size();
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~Set File Type Vars ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    //decide the file type
    if ((file_size == FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PC)) && (file.peek(25).startsWith(FF7SaveInfo::instance()->fileIdentifier(FF7SaveInfo::FORMAT::PC))) && file.fileName().endsWith(QStringLiteral("ff7")))
        return FF7SaveInfo::FORMAT::PC;
    if ((file_size == FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::SWITCH)) && (file.peek(25).startsWith(FF7SaveInfo::instance()->fileIdentifier(FF7SaveInfo::FORMAT::SWITCH))) && file.fileName().startsWith(QStringLiteral("ff7")))
        return FF7SaveInfo::FORMAT::SWITCH;
    if ((file_size == FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::VMC)) && (file.peek(25).startsWith(FF7SaveInfo::instance()->fileIdentifier(FF7SaveInfo::FORMAT::VMC))))
        return FF7SaveInfo::FORMAT::VMC;
    if (((FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PS3) - FF7SaveInfo::instance()->fileHeaderSize(FF7SaveInfo::FORMAT::PS3)) % FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX) == 0) && (file.peek(25)).startsWith(FF7SaveInfo::instance()->fileIdentifier(FF7SaveInfo::FORMAT::PS3)))
    {
        char psvType = file.peek(0x40).at(FF7SaveInfo::instance()->extraPSVOffsets(FF7SaveInfo::PSVINFO::SAVETYPE));
        if (psvType == 0x14) {
            return FF7SaveInfo::FORMAT::PS3;
        } else {
            QTextStream(stdout) << tr("Unable to open PSV of Type %2: 0x%1")
                                   .arg(psvType, 2, 16, QChar('0'))
                                   .arg(psvType == 0x14 ? QStringLiteral("PSX")
                                                        : psvType == 0x2C ? QStringLiteral ("PS2")
                                                                          : QStringLiteral("Unknown"));
            return FF7SaveInfo::FORMAT::UNKNOWN;
        }
    }
    if ((file_size == FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSP)) && (file.peek(25)).startsWith(FF7SaveInfo::instance()->fileIdentifier(FF7SaveInfo::FORMAT::PSP)))
        return FF7SaveInfo::FORMAT::PSP;
    if ((file_size == FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::VGS)) && (file.peek(25)).startsWith(FF7SaveInfo::instance()->fileIdentifier(FF7SaveInfo::FORMAT::VGS)))
        return FF7SaveInfo::FORMAT::VGS;
    if ((file_size == FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::DEX)) && (file.peek(25)).startsWith(FF7SaveInfo::instance()->fileIdentifier(FF7SaveInfo::FORMAT::DEX)))
        return FF7SaveInfo::FORMAT::DEX;
    if (file_size % FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX) == 0)
        return FF7SaveInfo::FORMAT::PSX;
    if ((file_size - FF7SaveInfo::instance()->fileHeaderSize(FF7SaveInfo::FORMAT::PGE)) % FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX) == 0)
        return FF7SaveInfo::FORMAT::PGE;
    if ((file_size - FF7SaveInfo::instance()->fileHeaderSize(FF7SaveInfo::FORMAT::PDA)) % FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX) == 0)
        return FF7SaveInfo::FORMAT::PDA;
    return FF7SaveInfo::FORMAT::UNKNOWN;
}

bool FF7Save::loadFile(const QString &fileName)
{
    // Return true if File Loaded and false if file not loaded.
    if (fileName.isEmpty())
        return false;   // bail on empty string.

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    FF7SaveInfo::FORMAT fileFormat = fileDataFormat(file);
    if (fileFormat == FF7SaveInfo::FORMAT::UNKNOWN)
        return false;

    setFormat(fileFormat);
    /*~~~~~~~~~~Start Load~~~~~~~~~~*/
    setFileHeader(file.read(FF7SaveInfo::instance()->fileHeaderSize(fileFormat)));
    for (int i = 0; i < FF7SaveInfo::instance()->slotCount(fileFormat); i++) {
        setSlotHeader(i, file.read(FF7SaveInfo::instance()->slotHeaderSize(fileFormat)));
        setSlotFF7Data(i, file.read(FF7SaveInfo::instance()->slotSize()));
        setSlotFooter(i, file.read(FF7SaveInfo::instance()->slotFooterSize(fileFormat)));
    }
    /*~~~~~~~End Load~~~~~~~~~~~~~~*/
    if (FF7SaveInfo::instance()->isTypePC(fileFormat)) {
        for (int i = 0; i < 15; i++) {
            if (slot[i].checksum != 0x0000 && slot[i].checksum != 0x4D1D)
                SG_Region_String[i] = QString("BASCUS-94163FF7-S%1").arg(QString::number(i + 1), 2, QChar('0'));
            else
                SG_Region_String[i].clear();
        }
    } else if (FF7SaveInfo::instance()->isTypeVMC(fileFormat)) {
        QByteArray mc_header;
        int offset = FF7SaveInfo::instance()->vmcHeaderOffset(fileFormat);
        file.seek(offset);
        mc_header = file.read(FF7SaveInfo::instance()->fileHeaderSize(fileFormat));
        for (int i = 0; i < 15; i++) {
            int index = (128 * i) + 138;
            SG_Region_String[i] = QString(mc_header.mid(index, 20));
        }
    } else if (FF7SaveInfo::instance()->isTypeSSS(fileFormat)) {
        if (fileFormat == FF7SaveInfo::FORMAT::PSX) {
            SG_Region_String[0] = QFileInfo(file).fileName();
        } else {
            file.seek(FF7SaveInfo::instance()->psxSaveNameOffset(fileFormat));
            SG_Region_String[0] = QString(file.read(20));
        }
        for (int i = 1; i < 15; i++)
            clearSlot(i);
    } else if (fileFormat == FF7SaveInfo::FORMAT::PDA) {
        file.seek(0);
        SG_Region_String[0] = file.read(20);
    } else {
        return false;
    }
    file.close();
    filename = fileName;
    setFileModified(false, 0);
    return true;
}
QByteArray FF7Save::fileHeader(void)
{
    return _fileHeader;
}

bool FF7Save::setFileHeader(QByteArray data)
{
    if (data.size() != FF7SaveInfo::instance()->fileHeaderSize(fileFormat)) {
        return false;
    }
    if (FF7SaveInfo::instance()->fileHeaderSize(fileFormat) > 0) {
        _fileHeader = data;
    }
    return true;
}

QByteArray FF7Save::slotHeader(int s)
{
    return QByteArray(reinterpret_cast<char *>(&hf[s].sl_header), FF7SaveInfo::instance()->slotHeaderSize(fileFormat));
}
bool FF7Save::setSlotHeader(int s, QByteArray data)
{
    if (s < 0 || s > 14) {
        return false;
    }
    if (data.size() != FF7SaveInfo::instance()->slotHeaderSize(fileFormat)) {
        return false;
    }
    memcpy(&hf[s].sl_header, data, size_t(FF7SaveInfo::instance()->slotHeaderSize(fileFormat)));
    setFileModified(true, s);
    return true;
}

QByteArray FF7Save::slotFooter(int s)
{
    return QByteArray(reinterpret_cast<char *>(&hf[s].sl_footer), FF7SaveInfo::instance()->slotFooterSize(fileFormat));
}
bool FF7Save::setSlotFooter(int s, QByteArray data)
{
    if (s < 0 || s > 14) {
        return false;
    }
    if (data.size() != FF7SaveInfo::instance()->slotFooterSize(fileFormat)) {
        return false;
    }
    memcpy(&hf[s].sl_footer, data, size_t(FF7SaveInfo::instance()->slotFooterSize(fileFormat)));
    setFileModified(true, s);
    return true;
}
QByteArray FF7Save::slotPsxRawData(int s)
{
    if (filename.isEmpty()) {
        return QByteArray();
    } else if (FF7SaveInfo::instance()->isTypePC(fileFormat)) {
        return QByteArray();
    } else if (FF7SaveInfo::instance()->isTypeSSS(fileFormat)) {
        QFile file(fileName());
        if (!file.open(QIODevice::ReadOnly))
            return QByteArray();
        QByteArray temp(file.readAll());
        file.close();
        temp.remove(0, FF7SaveInfo::instance()->fileHeaderSize(fileFormat));
        return temp;
    } else {
        QByteArray temp;
        int blocks = psx_block_size(s);
        for (int i = 0; i < blocks; i++) {
            temp.append(slotHeader(s));
            temp.append(slotFF7Data(s));
            temp.append(slotFooter(s));
            s = psx_block_next(s);
        }
        return temp;
    }
}
bool FF7Save::setSlotPsxRawData(int s, QByteArray data)
{
    if ( s < 0 || s > 14 || data.isEmpty())
        return false;

    int blocks = data.length() / FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX);

    for (int i = 0; i < blocks ; i++) {
        //done once for each block
        int offset = (i * FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX));
        int next = psx_block_next(s);
        setSlotHeader(s, data.mid(offset, FF7SaveInfo::instance()->slotHeaderSize(FF7SaveInfo::FORMAT::PSX)));
        offset += FF7SaveInfo::instance()->slotHeaderSize(FF7SaveInfo::FORMAT::PSX);
        setSlotFF7Data(s, data.mid(offset, FF7SaveInfo::instance()->slotSize()));
        offset += FF7SaveInfo::instance()->slotSize();
        setSlotFooter(s, data.mid(offset, FF7SaveInfo::instance()->slotFooterSize(FF7SaveInfo::FORMAT::PSX)));
        s = next;
    }
    setFileModified(true, s);
    return true;
}
bool FF7Save::saveFile(const QString &fileName, int slot)
{
    if (fileName.isEmpty())
        return false;

    checksumSlots();
    //fix our headers before saving
    if (FF7SaveInfo::instance()->isTypePC(fileFormat))
        fix_pc_bytemask(slot);
    else if (fileFormat == FF7SaveInfo::FORMAT::PSX)
        fix_psx_header(slot);
    else if (fileFormat == FF7SaveInfo::FORMAT::PS3)
        fix_psv_header(slot);
    else if (fileFormat == FF7SaveInfo::FORMAT::PSP)
        fix_vmp_header();
    else if (fileFormat == FF7SaveInfo::FORMAT::PGE)
        fix_pge_header(slot);
    else if (fileFormat == FF7SaveInfo::FORMAT::PDA)
        fix_pda_header(slot);
    else
        fix_vmc_header();

    // write the file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite))
        return false;

    file.write(fileHeader(), FF7SaveInfo::instance()->fileHeaderSize(fileFormat));
    for (int si = 0; si < FF7SaveInfo::instance()->slotCount(fileFormat); si++) {
        file.write(slotHeader(si), FF7SaveInfo::instance()->slotHeaderSize(fileFormat));
        file.write(slotFF7Data(si), FF7SaveInfo::instance()->slotSize());
        file.write(slotFooter(si), FF7SaveInfo::instance()->slotFooterSize(fileFormat));
    }
    file.close();
    filename = fileName;
    if (fileFormat == (FF7SaveInfo::FORMAT::PC)) {
        QString metadata = fileName;
        metadata.chop(metadata.length() - metadata.lastIndexOf("/"));
        metadata.append("/metadata.xml");
        if ((QFile(metadata).exists()))
            fixMetaData();
    }
    setFileModified(false, slot);
    return true;
}
bool FF7Save::exportFile(const QString &fileName, FF7SaveInfo::FORMAT newFormat, int s)
{
    if (fileName.isEmpty())
        return false;

    if (newFormat == fileFormat)
        return saveFile(fileName, s);

    if (FF7SaveInfo::instance()->isTypePC(newFormat))
        return exportPCFormat(fileName, newFormat);

    if (FF7SaveInfo::instance()->isTypeVMC(newFormat))
        return exportVMCFormat(fileName, newFormat);

    if (FF7SaveInfo::instance()->isTypeSSS(newFormat))
        return exportSlot(fileName, newFormat, s);

    return false;
}

bool FF7Save::exportPCFormat(const QString &fileName, FF7SaveInfo::FORMAT exportFormat)
{
    if (fileName.isEmpty() || !FF7SaveInfo::instance()->isTypePC(exportFormat))
        return false;

    if (!FF7SaveInfo::instance()->isTypePC(exportFormat))
        return false;

    QByteArray prev_fileHeader = _fileHeader;
    QString prev_fileName = filename;
    QString prev_regionString[15];
    FF7SLOT prev_slots[15];
    FF7HEADFOOT prev_slot_hf[15];
    bool prev_slotChanged[15];
    for(int i =0; i < 15; i++) {
        prev_regionString[i] = SG_Region_String[i];
        prev_slots[i] = slot[i];
        prev_slotChanged[i] = slotChanged[i];
        prev_slot_hf[i] = hf[i];
    }

    if (!FF7SaveInfo::instance()->isTypePC(fileFormat)) {
        for (int i = 0; i < 15; i++) {
            if (isFF7(i))
                setControlMode(i, CONTROL_NORMAL);
        }
    }

    setFormat(exportFormat);
    fix_pc_bytemask(0);//set first slot to 0

    for (int i = 0; i < 15; i++) { //clean up saves and fix time for Pal Saves.
        if (isNTSC(i))
            continue;
        else if (isPAL(i)) {
            //PAL FF7 DATA , FIX PLAY TIME THEN SAVE
            slot[i].time = quint32(slot[i].time * 1.2);
            slot[i].desc.time = slot[i].time;
        } else {
            clearSlot(i);
        }
    }

    bool successStatus = saveFile(fileName);
    setFormat(fileFormat);
    filename = prev_fileName;
    _fileHeader = prev_fileHeader;
    for(int i =0; i < 15; i++) {
        SG_Region_String[i] = prev_regionString[i];
        slot[i] = prev_slots[i];
        slotChanged[i] = prev_slotChanged[i];
        hf[i] = prev_slot_hf[i];
    }
    return successStatus;
}

bool FF7Save::exportVMCFormat(const QString &fileName, FF7SaveInfo::FORMAT exportFormat)
{
    if (fileName.isEmpty() || !FF7SaveInfo::instance()->isTypeVMC(exportFormat))
        return false;

    FF7SaveInfo::FORMAT prev_format = fileFormat;
    QByteArray prev_fileHeader = _fileHeader;
    QString prev_fileName = filename;
    QString prev_regionString[15];
    FF7SLOT prev_slots[15];
    FF7HEADFOOT prev_slot_hf[15];
    bool prev_slotChanged[15];
    for(int i =0; i < 15; i++) {
        prev_regionString[i] = SG_Region_String[i];
        prev_slots[i] = slot[i];
        prev_slotChanged[i] = slotChanged[i];
        prev_slot_hf[i] = hf[i];
    }

    if (FF7SaveInfo::instance()->isTypePC(prev_format)) {
        for (int i = 0; i < 15; i++) {
            if (isFF7(i))
                setControlMode(i, CONTROL_NORMAL);
        }
    }

    setFormat(exportFormat);
    if (  prev_format == FF7SaveInfo::FORMAT::VMC
       || prev_format == FF7SaveInfo::FORMAT::PSP
       || prev_format == FF7SaveInfo::FORMAT::PGE
       || prev_format == FF7SaveInfo::FORMAT::VGS
       || prev_format == FF7SaveInfo::FORMAT::DEX) {
          _fileHeader.replace(FF7SaveInfo::instance()->vmcHeaderOffset(exportFormat), FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX)
                              , _bufferFileHeader.mid(FF7SaveInfo::instance()->vmcHeaderOffset(prev_format), FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX)));
    }

    if (exportFormat != FF7SaveInfo::FORMAT::PSP) {
        fix_vmc_header();
    } else {
        fix_vmp_header();
    }

    bool successStatus = saveFile(fileName);
    setFormat(prev_format);
    filename = prev_fileName;
    _fileHeader = prev_fileHeader;
    for(int i =0; i < 15; i++) {
        SG_Region_String[i] = prev_regionString[i];
        slot[i] = prev_slots[i];
        slotChanged[i] = prev_slotChanged[i];
        if(slotChanged[i])
            setFileModified(true, i);
        hf[i] = prev_slot_hf[i];
    }
    return successStatus;
}

bool FF7Save::exportSlot(const QString &fileName, FF7SaveInfo::FORMAT exportFormat, int s)
{
    if (fileName.isEmpty() || !FF7SaveInfo::instance()->isTypeSSS(exportFormat))
        return false;

    int blocks = psx_block_size(s);
    FF7SaveInfo::FORMAT prev_format = fileFormat;
    QString prev_fileName = filename;
    QByteArray prev_fileHeader = fileHeader();
    QByteArray prev_slotHeader = slotHeader(s);
    QByteArray prev_slotFooter = slotFooter(s);
    bool fmodded = isSlotModified(s);

    setFormat(exportFormat);
    if(isFF7(s)) {
        if (FF7SaveInfo::instance()->isTypePC(prev_format))
            setControlMode(s, CONTROL_NORMAL);
        int slot = 0;
        if (exportFormat != FF7SaveInfo::FORMAT::PS3) {
            slot = fileName.mid(fileName.lastIndexOf('S') +1, 2).toInt() - 1;
        } else {
            QString rslot = fileName.mid(fileName.lastIndexOf("533") +3, 3);
            slot = (10 * rslot.mid(0,1).toInt()) + (rslot.mid(2, 1).toInt() -1);
        }
        if (slot < 0 || slot > 14)
            return false;
        setSlotHeader(s, FF7SaveInfo::instance()->slotHeader(exportFormat, slot));
        setSlotFooter(s, FF7SaveInfo::instance()->slotFooter(exportFormat));
        checksumSlots();
    }
    if (exportFormat == FF7SaveInfo::FORMAT::PSX)
        fix_psx_header(s);
    else if (exportFormat == FF7SaveInfo::FORMAT::PGE)
        fix_pge_header(s);
    else if (exportFormat == FF7SaveInfo::FORMAT::PDA)
        fix_pda_header(s);
    else if (exportFormat == FF7SaveInfo::FORMAT::PS3)
        fix_psv_header(s, blocks);
    else { /* Do Nothing */}

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    file.write(fileHeader(), FF7SaveInfo::instance()->fileHeaderSize(exportFormat));
    int j = s;
    for (int i = 0; i < blocks; i++) {
        file.write(slotHeader(j), FF7SaveInfo::instance()->slotHeaderSize(exportFormat));
        file.write(slotFF7Data(j), FF7SaveInfo::instance()->slotSize());
        file.write(slotFooter(j), FF7SaveInfo::instance()->slotFooterSize(exportFormat));
        j = psx_block_next(j);
    }
    file.close();

    setFormat(prev_format);
    filename = prev_fileName;
    setFileHeader(prev_fileHeader);
    setSlotHeader(s, prev_slotHeader);
    setSlotFooter(s, prev_slotFooter);
    setFileModified(fmodded, s);
    return true;
}

void FF7Save::importSlot(int s, QString fileName, int fileSlot)
{
    if (s < 0 || s > 14 || filename.isEmpty())
        return;

    FF7SaveInfo::FORMAT inType = FF7SaveInfo::FORMAT::UNKNOWN;
    int offset = 0;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    inType = fileDataFormat(file);
    if (inType == FF7SaveInfo::FORMAT::UNKNOWN) {
        file.close();
        return;
    }

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~Set File Type Vars ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    //decide the file type
    if (FF7SaveInfo::instance()->isTypePC(inType)) {
        offset = FF7SaveInfo::instance()->fileHeaderSize(inType);
        offset += (FF7SaveInfo::instance()->slotSize() * fileSlot);
    } else if (FF7SaveInfo::instance()->isTypeVMC(inType)){
        offset = FF7SaveInfo::instance()->fileHeaderSize(inType) + FF7SaveInfo::instance()->slotHeaderSize(inType);
        offset += (FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX) * fileSlot);
    } else if (FF7SaveInfo::instance()->isTypeSSS(inType)) {
        if(inType == FF7SaveInfo::FORMAT::PSX)
            offset = FF7SaveInfo::instance()->slotHeaderSize(inType);
        else
            offset = FF7SaveInfo::instance()->slotHeaderSize(inType) + FF7SaveInfo::instance()->fileHeaderSize(inType);
    }

    file.seek(offset);
    setSlotFF7Data(s, file.read(FF7SaveInfo::instance()->slotSize()));
    /*~~~~~~~End Load~~~~~~~~~~~~~~*/

    /*~~~~~Set Region Data~~~~~~~~~*/
    if (FF7SaveInfo::instance()->isTypePC(inType)) {
        QString newRegion;
        if (slot[s].checksum != 0x0000 && slot[s].checksum != 0x4D1D)
            newRegion = QString("BASCUS-94163FF7-S%1").arg(QString::number(s).toInt(), 2, 10, QChar('0').toUpper());
        setRegion(s, newRegion);
    } else if (FF7SaveInfo::instance()->isTypeVMC(inType)) {
        QByteArray mc_header;
        int headerSize = FF7SaveInfo::instance()->fileHeaderSize(inType);
        offset = FF7SaveInfo::instance()->fileHeaderSize(inType) - FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX);
        file.seek(offset);
        mc_header = file.read(headerSize);
        int index = 0;
        index = (128 * fileSlot) + 138;
        setRegion(s, QString(mc_header.mid(index, 20)));
    } else if (FF7SaveInfo::instance()->isTypeSSS(inType)) {
        QString newRegion;
        if(inType == FF7SaveInfo::FORMAT::PSX) {
            newRegion = QFileInfo(file).fileName();
        } else {
            file.seek(FF7SaveInfo::instance()->psxSaveNameOffset(inType));
            newRegion = QString(file.read(20));
        }
        setRegion(s, newRegion);
    } else {
        //Unknown or Unspecified Type Abort.
        file.close();
        return;
    }
    file.close();
    setFileModified(true, s);
}

void FF7Save::clearSlot(int rmslot)
{
    if (isSlotEmpty(rmslot))
        return;

    setSlotHeader(rmslot, QByteArray(FF7SaveInfo::instance()->slotHeaderSize(fileFormat), 0x00));
    setSlotFF7Data(rmslot, QByteArray(FF7SaveInfo::instance()->slotSize(), 0x00));
    setSlotFooter(rmslot, QByteArray(FF7SaveInfo::instance()->slotFooterSize(fileFormat), 0x00));
    SG_Region_String[rmslot].clear();
    if (FF7SaveInfo::instance()->isTypeVMC(fileFormat)) {
        //clean the mem card header if needed.
        int index = (128 + (128 * rmslot));
        index += FF7SaveInfo::instance()->fileHeaderSize(fileFormat) - FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX);
        QByteArray temp(128, 0x00);
        temp[0] = '\xA0';
        temp[8] = '\xFF';
        temp[9] = '\xFF';
        temp[0x7F] = '\xA0';
        _fileHeader.replace(index, 128, temp);
        setFileModified(true, rmslot);
    }
}
bool FF7Save::exportCharacter(int s, int char_num, QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite))
        return false;

    file.write(rawCharacterData(s, char_num), 132);
    file.close();
    return true;
}
void FF7Save::importCharacter(int s, int char_num, QByteArray new_char)
{
    memcpy(&slot[s].chars[char_num], new_char.data(), 132);
    setFileModified(true, s);
}

void FF7Save::checksumSlots()
{
    for (int i = 0; i < FF7SaveInfo::instance()->slotCount(fileFormat); i++) {
        if (isFF7(i)) {
            quint16 checksum = ff7Checksum(i);
            if (checksum == 0x4D1D)
                slot[i].checksum = 0x0000;
            else
                slot[i].checksum = checksum;
        }
    }
}

quint16 FF7Save::ff7Checksum(int s)
{
    QByteArray data = slotFF7Data(s).mid(4, 4336);
    int i = 0;
    quint16 r = 0xFFFF, len = 4336, pbit = 0x8000;
    while (len--) {
        int t = data.at(i++);
        r ^= t << 8;
        for (int d = 0; d < 8; d++) {
            if (r & pbit)
                r = quint16(r << 1) ^ 0x1021;
            else
                r <<= 1;
        }
        r &= (1 << 16) - 1;
    }
    return ((r ^ 0xFFFF) & 0xFFFF);
}

quint16 FF7Save::itemDecode(quint16 itemraw)
{
    quint16 item;
#ifdef Q_BYTE_ORDER
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    item = itemraw;
#elif Q_BYTE_ORDER == Q_BIG_ENDIAN
    item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
#else
    int one = 1;
    if (*(char *)&one) {
        /******************************************************************************************/
        /* Little-Endian (Do Nothing, No Change)                                                  */
        /* ITEMRAW:                                                                               */
        /* Itemraw Format: QQQQQQQXXXXXXXXX                                                       */
        /* ITEM:                                                                                  */
        /* Item Format: QQQQQQQXXXXXXXXX                                                          */
        /******************************************************************************************/
        item = itemraw;
    } else {
        /***********************************--*****************************************************/
        /* Big-Endian (Do things, Format Change)                                                  */
        /* ITEMRAW:                                                                               */
        /* Itemraw Format: XXXXXXXXQQQQQQQX                                                       */
        /* ITEM:                                                                                  */
        /* Left Shift&Mask itemraw 8bits:  QQQQQQQX00000000 & 1111111100000000 = QQQQQQQX00000000 */
        /* Right Shift&Mask itemraw 8bits: 00000000XXXXXXXX & 0000000011111111 = 00000000XXXXXXXX */
        /* Then OR them:                   QQQQQQQX00000000 | 00000000XXXXXXXX = QQQQQQQXXXXXXXXX */
        /* Item Format: QQQQQQQXXXXXXXXX                                                          */
        /******************************************************************************************/
        item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
    }
#endif
#else
    int one = 1;
    if (*(char *)&one) {
        item = itemraw;
    } else {
        item = ((itemraw & 0xFF) << 8) | ((itemraw >> 8) & 0xFF);
    }
#endif

    return item;
}
quint16 FF7Save::itemEncode(quint16 id, quint8 qty)
{
    quint16 item, itemraw;
#ifdef Q_BYTE_ORDER
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
    itemraw = item;
#elif Q_BYTE_ORDER == Q_BIG_ENDIAN
    item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
    itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
#else
    int one = 1;
    if (*(char *)&one) {
        /******************************************************************************************/
        /* Little-Endian                                                                          */
        /* ITEM:                                                                                  */
        /* Item Format: QQQQQQQXXXXXXXXX                                                          */
        /* Left Shift&Mask qty 9bits: QQQQQQQ000000000 & 1111111000000000 = QQQQQQQ000000000      */
        /* Right Mask id 9bits:              XXXXXXXXX & 0000000111111111 = 0000000XXXXXXXXX      */
        /* Then OR them:              QQQQQQQ000000000 | 0000000XXXXXXXXX = QQQQQQQXXXXXXXXX      */
        /* ITEMRAW:                                                                               */
        /* Itemraw Format: QQQQQQQXXXXXXXXX                                                       */
        /******************************************************************************************/
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = item;
    } else {
        /******************************************************************************************/
        /* Big-Endian                                                                             */
        /* ITEM:                                                                                  */
        /* Left Shift&Mask qty 9bits:   QQQQQQQ000000000 & 1111111000000000 = QQQQQQQ000000000    */
        /* Right Mask id 9bits:         0000000XXXXXXXXX & 0000000111111111 = 0000000XXXXXXXXX    */
        /* Then OR them:                QQQQQQQ000000000 | 0000000XXXXXXXXX = QQQQQQQXXXXXXXXX    */
        /* Item Format: QQQQQQQXXXXXXXXX                                                          */
        /* ITEMRAW:                                                                               */
        /* Left Shift&Mask item 8bits:  QQQQQQQX00000000 & 1111111100000000 = QQQQQQQX00000000    */
        /* Right Shift&Mask item 8bits: 00000000XXXXXXXX & 0000000011111111 = 00000000XXXXXXXX    */
        /* Then OR them:                QQQQQQQX00000000 | 00000000XXXXXXXX = QQQQQQQXXXXXXXXX    */
        /* Itemraw Format: XXXXXXXXQQQQQQQX                                                       */
        /******************************************************************************************/
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
    }
#endif
#else
    int one = 1;
    if (*(char *)&one) {
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = item;
    } else {
        item = ((qty << 9) & 0xFE00) | (id & 0x1FF);
        itemraw = ((item & 0xFF) << 8) | ((item >> 8) & 0xFF);
    }
#endif

    return itemraw;
}
void FF7Save::setItem(int s, int item_num, quint16 rawitem)
{
    if (region(s).contains("SLPS-00700") && (itemQty(rawitem) > 99) && (itemId(rawitem != 0x1FF))) {
        rawitem = itemEncode(itemId(rawitem), 99);
    }
    //Item Qty over 99 on SLPS-00700 Causes an Error Durring Battle and break all items.
    //Above Is to Check for and fix, since im sure no one wants to lose all their items.
    slot[s].items[item_num] = rawitem;
    setFileModified(true, s);
}
void FF7Save::setItem(int s, int item_num, quint16 new_id, quint8 new_qty)
{
    if (region(s).contains("SLPS-00700") && (new_qty > 99) && (new_id != 0x1FF)) {
        //Item Qty over 99 on SLPS-00700 Causes an Error Durring Battle and break all items!
        //Check for and fix, No one wants to lose all their items.
        new_qty = 99;
    }
    slot[s].items[item_num] = itemEncode(new_id, new_qty);
    setFileModified(true, s);
}

quint16 FF7Save::item(int s, int item_num)
{
    return slot[s].items[item_num];
}
QList<quint16> FF7Save::items(int s)
{
    QList<quint16> item_list;
    for (int i = 0; i < 320; i++) {
        item_list.append(slot[s].items[i]);
    }
    return item_list;
}

void FF7Save::setItems(int s, QList<quint16> items)
{
    if (region(s).contains("SLPS-00700")) {
        for (int i = 0; i < 320; i++) {
            if ((itemQty(items.at(i)) > 99) && (itemId(items.at(i)) != 0x1FF)) {
                slot[s].items[i] = itemEncode(itemId(items.at(i)), 99);
            } else {
                slot[s].items[i] = items.at(i);
            }
        }
    } else {
        for (int i = 0; i < 320; i++) {
            slot[s].items[i] = items.at(i);
        }
    }
    setFileModified(true, s);
}

quint16 FF7Save::itemId(quint16 rawitem)
{
    return quint16((itemDecode(rawitem)) & 0x1FF);
}
quint16 FF7Save::itemId(int s, int item_num)
{
    return quint16((itemDecode(slot[s].items[item_num])) & 0x1FF);
}
quint8 FF7Save::itemQty(int s, int item_num)
{
    return quint8(((itemDecode(slot[s].items[item_num])) & 0xFE00) >> 9);
}
quint8 FF7Save::itemQty(quint16 rawitem)
{
    return quint8(((itemDecode(rawitem)) & 0xFE00) >> 9);
}

void FF7Save::fix_pc_bytemask(int s)
{
    QByteArray newHeader = FF7SaveInfo::instance()->fileHeader(FF7SaveInfo::FORMAT::PC);
    //calc 0x04 of the header (selected slot) no idea why they choose this way to do it but slot15 = 0xC2 , slot 14= 0xb2  and so on till slot2 = 0x01 and slot 01 0x00
    switch (s) {
    case 0: newHeader.replace(4, 1, QByteArray(1, 0x00)); break;
    case 1: newHeader.replace(4, 1, QByteArray(1, 0x01)); break;
    default: newHeader.replace(4, 1, QByteArray(1, char(16 * (s - 2)) + 2)); break;
    }
    //calc 0x05 of the header (slots 1-8 empty?)
    char mask = 0x00;
    for (int i = 0; i < 8; i++) {
        if (isFF7(i)) {
            mask |= (1 << i);
        }
    }
    newHeader.replace(5, 1, QByteArray(1, mask));
    mask = 0; // reset for the next byte
    //calc 0x06 of the header (slot 9-15 empty?)
    for (int i = 8; i < 15; i++) {
        if (isFF7(i)) {
            mask |= (1 << (i - 8));
        }
    }
    newHeader.replace(6, 1, QByteArray(1, mask));
    _fileHeader = newHeader;
}

void FF7Save::fix_psx_header(int s)
{
    if (isFF7(s)) {
        //Time Has to be fixed in the header part of description string.
        if ((slot[s].time / 3600) > 99) {
            hf[s].sl_header[27] = 0x58;
            hf[s].sl_header[29] = 0x58;
        } else {
            hf[s].sl_header[27] = quint8((slot[s].time / 3600) / 10) + 0x4F;
            hf[s].sl_header[29] = ((slot[s].time / 3600) % 10) + 0x4F;
        }
        hf[s].sl_header[33] = ((slot[s].time / 60 % 60) / 10) + 0x4F;
        hf[s].sl_header[35] = ((slot[s].time / 60 % 60) % 10) + 0x4F;
    }
}

void FF7Save::fix_pge_header(int s)
{
    QByteArray newHeader(0x80, '\x00');
    newHeader.replace(0, 10, (QByteArray::fromRawData("\x51\x00\x00\x00\x00\x20\x00\x00\xFF\xFF", 10)));
    newHeader.replace(FF7SaveInfo::instance()->psxSaveNameOffset(FF7SaveInfo::FORMAT::PGE), region(s).length(), region(s).toLatin1());
    int xor_byte = 0x00;
    for (int x = 0; x < 127; x++)
        xor_byte ^= newHeader.at(x);
    newHeader.replace(127, 1, QByteArray(1, char(xor_byte)));
    if (isFF7(s)) {
        QString temp = region(s).mid(region(s).lastIndexOf("S") + 1, 2);
        setSlotHeader(s, FF7SaveInfo::instance()->slotHeader(FF7SaveInfo::FORMAT::PSX, temp.toInt() - 1));
        fix_psx_header(s);
    }
    setFileHeader(newHeader.mid(0, 0x80));
}

void FF7Save::fix_pda_header(int s)
{
    QString desc = psxDesc(s).normalized(QString::NormalizationForm_KD);
    QByteArray newHeader(0x36, '\x00');
    newHeader.replace(FF7SaveInfo::instance()->psxSaveNameOffset(FF7SaveInfo::FORMAT::PDA), region(s).length(), region(s).toLatin1());
    newHeader.replace(0x15, desc.length(), desc.toLatin1());
    if (isFF7(s)) {
        QString temp = region(s).mid(region(s).lastIndexOf("S") + 1, 2);
        setSlotHeader(s, FF7SaveInfo::instance()->slotHeader(FF7SaveInfo::FORMAT::PSX, temp.toInt() - 1));
        fix_psx_header(s);
    }
    setFileHeader(newHeader.mid(0, 0x36));
}

void FF7Save::fix_psv_header(int s, int blocks)
{
    const int signatureOffset = FF7SaveInfo::instance()->fileSignatureOffset(FF7SaveInfo::FORMAT::PS3);
    const int signatureSize = FF7SaveInfo::instance()->fileSignatureSize(FF7SaveInfo::FORMAT::PS3);
    if (!isFF7(s))
        fix_psx_header(s);//adjust time.
    QByteArray data = fileHeader();
    data.replace(FF7SaveInfo::instance()->psxSaveNameOffset(FF7SaveInfo::FORMAT::PS3), 0x20, QByteArray(0x20, '\x00'));
    data.replace(FF7SaveInfo::instance()->psxSaveNameOffset(FF7SaveInfo::FORMAT::PS3), SG_Region_String[s].size(), SG_Region_String[s].toLatin1());
    QByteArray bSize(3, '\x00');
    switch((blocks * FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX))) {
        default: bSize.setRawData("\x00\x20\x00", 3); break;
        case 0x4000:bSize.setRawData("\x00\x40\x00", 3); break;
        case 0x6000:bSize.setRawData("\x00\x60\x00", 3); break;
        case 0x8000:bSize.setRawData("\x00\x80\x00", 3); break;
        case 0x10000:bSize.setRawData("\x10\x00\x00", 3); break;
        case 0x12000:bSize.setRawData("\x10\x20\x00", 3); break;
        case 0x14000:bSize.setRawData("\x10\x40\x00", 3); break;
        case 0x16000:bSize.setRawData("\x10\x60\x00", 3); break;
        case 0x18000:bSize.setRawData("\x10\x80\x00", 3); break;
        case 0x20000:bSize.setRawData("\x20\x00\x00", 3); break;
    }
    data.replace(FF7SaveInfo::instance()->extraPSVOffsets(FF7SaveInfo::PSVINFO::SIZEDISPLAY), bSize.size(), bSize);
    data.replace(FF7SaveInfo::instance()->extraPSVOffsets(FF7SaveInfo::PSVINFO::SAVESIZE), bSize.size(), bSize);
    data.replace(signatureOffset, signatureSize, QByteArray(signatureSize, '\x00'));
    int j = s;
    for (int i = 0; i < blocks; i++) {
        data.append(slotHeader(j));
        data.append(slotFF7Data(j));
        data.append(slotFooter(j));
        j = psx_block_next(j);
    }
    QByteArray keySeed = fileHeader().mid(FF7SaveInfo::instance()->fileSeedOffset(FF7SaveInfo::FORMAT::PS3), signatureSize);
    data.replace(signatureOffset, signatureSize, generatePsSaveSignature(data, keySeed));
    setFileHeader(data.mid(0,FF7SaveInfo::instance()->fileHeaderSize(FF7SaveInfo::FORMAT::PS3)));
}

void FF7Save::fix_vmp_header()
{
    const int signatureOffset = FF7SaveInfo::instance()->fileSignatureOffset(FF7SaveInfo::FORMAT::PSP);
    const int signatureSize = FF7SaveInfo::instance()->fileSignatureSize(FF7SaveInfo::FORMAT::PSP);
    fix_vmc_header();
    QByteArray data = fileHeader();
    data.replace(signatureOffset, signatureSize, QByteArray(signatureSize, '\x00'));
    for(int i=0; i < 15; i++) {
        data.append(slotHeader(i));
        data.append(slotFF7Data(i));
        data.append(slotFooter(i));
    }
    QByteArray keySeed = fileHeader().mid(FF7SaveInfo::instance()->fileSeedOffset(FF7SaveInfo::FORMAT::PSP), signatureSize);
    setFileHeader(fileHeader().replace(signatureOffset, signatureSize, generatePsSaveSignature(data, keySeed)));
}

void FF7Save::fix_vmc_header(void)
{
    //Set The Index Section Up.
    int index = FF7SaveInfo::instance()->vmcHeaderOffset(format());
    QByteArray mc_header_2 = fileHeader();
    mc_header_2.replace(index, 2, FF7SaveInfo::instance()->fileIdentifier(FF7SaveInfo::FORMAT::VMC));
    char xor_byte = '\x00';
    for (int x = index; x < index + 127; x++) {
        xor_byte ^= mc_header_2[x];
    }
    mc_header_2.replace(index + 127, 1, QByteArray(1, char(xor_byte)));

    for (int i = 0; i < 15; i++) {
        index = (128 + (128 * i));
        index += FF7SaveInfo::instance()->fileHeaderSize(fileFormat) - FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX);
        if (isFF7(i)) {
            mc_header_2.replace(index, 10, (QByteArray::fromRawData("\x51\x00\x00\x00\x00\x20\x00\x00\xFF\xFF", 10)));
            mc_header_2.replace(index + 10, region(i).length(), region(i).toLatin1());
            xor_byte = 0x00;
            for (int x = 0; x < 127; x++) {
                xor_byte ^= mc_header_2[x + index];
            }
            index += 127;
            mc_header_2.replace(index, 1, QByteArray(1, char(xor_byte)));
            QString temp = region(i).mid(region(i).lastIndexOf("S") + 1, 2);
            setSlotHeader(i, FF7SaveInfo::instance()->slotHeader(FF7SaveInfo::FORMAT::PSX, temp.toInt() - 1));
            fix_psx_header(i);
        } else {
            if (psx_block_type(i) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_INUSE) || psx_block_type(i) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK) || psx_block_type(i) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)) {
                mc_header_2.replace(index, 128, _fileHeader.mid(index, 128));
            } else if ((region(i).isEmpty() || region(i).isNull())) {
                mc_header_2.replace(index, 10, QByteArray::fromRawData("\xA0\x00\x00\x00\x00\x00\x00\x00\xFF\xFF", 10));
                index += 127;
                mc_header_2.replace(index, 1, QByteArray(1, '\xA0'));
            } else {
                //Write What Ever is in the Header (Non ff7 data)
                mc_header_2.replace(index, 128, _fileHeader.mid(index, 128));
            }
        }
        if (fileFormat == FF7SaveInfo::FORMAT::DEX) {
            for (int t = 0; t < 15; t++) {
                mc_header_2.replace(t + 0x16, 1, QByteArray(1, char(psx_block_type(t))));
                mc_header_2.replace(t + 0x26, 1, QByteArray(1, char(psx_block_next(t))));
            }
        }
    }
    _bufferFileHeader = _fileHeader;
    setFileHeader(mc_header_2);
}

void FF7Save::setSaveNumber(int s, int saveNum)
{
    if (!isFF7(s))
        return;

    SG_Region_String[s] = region(s).mid(0, region(s).size() - 2).append(QString("%1").arg(QString::number(saveNum + 1), 2, QChar('0')));
    switch(format()) {
        default: break;
        case FF7SaveInfo::FORMAT::VMC:
        case FF7SaveInfo::FORMAT::DEX:
        case FF7SaveInfo::FORMAT::VGS: fix_vmc_header(); break;
        case FF7SaveInfo::FORMAT::PSP: fix_vmp_header(); break;
        case FF7SaveInfo::FORMAT::PS3: fix_psv_header(s); break;
        case FF7SaveInfo::FORMAT::PGE: fix_pge_header(s); break;
        case FF7SaveInfo::FORMAT::PDA: fix_pda_header(s); break;
   }
}

QString FF7Save::region(int s)
{
    return SG_Region_String[s];
}
void FF7Save::setRegion(int s, const QString &new_region)
{
    if ((new_region == "USA") || (new_region == "NTSC-U") || (new_region == "1")) {
        SG_Region_String[s] = QString("BASCUS-94163FF7-S%1").arg(QString::number(s + 1), 2, QChar('0'));
    } else if ((new_region == "UK") || (new_region == "PAL-E") || (new_region == "2")) {
        SG_Region_String[s] = QString("BESCES-00867FF7-S%1").arg(QString::number(s + 1), 2, QChar('0'));
    } else if ((new_region == "French") || (new_region == "PAL-FR") || (new_region == "3")) {
        SG_Region_String[s] = QString("BESCES-00868FF7-S%1").arg(QString::number(s + 1), 2, QChar('0'));
    } else if ((new_region == "German") || (new_region == "PAL-DE") || (new_region == "4")) {
        SG_Region_String[s] = QString("BESCES-00869FF7-S%1").arg(QString::number(s + 1), 2, QChar('0'));
    } else if ((new_region == "Spanish") || (new_region == "PAL-ES") || (new_region == "5")) {
        SG_Region_String[s] = QString("BESCES-00900FF7-S%1").arg(QString::number(s + 1), 2, QChar('0'));
    } else if ((new_region == "Japanese") || (new_region == "NTSC-J") || (new_region == "6")) {
        SG_Region_String[s] = QString("BISLPS-00700FF7-S%1").arg(QString::number(s + 1), 2, QChar('0'));
    } else if ((new_region == "International") || (new_region == "NTSC-JI") || (new_region == "7")) {
        SG_Region_String[s] = QString("BISLPS-01057FF7-S%1").arg(QString::number(s + 1), 2, QChar('0'));
    } else {
        SG_Region_String[s] = new_region;
    }

    if (FF7SaveInfo::instance()->isTypeVMC(fileFormat)) {
        if (isFF7(s)) {
            vmcRegionEval(s);
        }
        fix_vmc_header();
    }
    setFileModified(true, s);
}

void FF7Save::copySlot(int s)
{
    buffer_slot = slot[s];
    buffer_region = SG_Region_String[s];
}

void FF7Save::pasteSlot(int s)
{
    slot[s] = buffer_slot;
    SG_Region_String[s] = buffer_region;
    SG_Region_String[s].replace(SG_Region_String[s].length() - 2, 2, QString("%1").arg(QString::number(s + 1), 2, QChar('0')));
    if (FF7SaveInfo::instance()->isTypeVMC(fileFormat)) {
        vmcRegionEval(s);
        fix_vmc_header();
    }
    setFileModified(true, s);
}

char FF7Save::psx_block_type(int s)
{
    switch (fileFormat) {
    case FF7SaveInfo::FORMAT::PDA:
    case FF7SaveInfo::FORMAT::UNKNOWN:
    case FF7SaveInfo::FORMAT::PC:
    case FF7SaveInfo::FORMAT::SWITCH:
    case FF7SaveInfo::FORMAT::PSX:
    case FF7SaveInfo::FORMAT::PS3: return 0x00;
    case FF7SaveInfo::FORMAT::PGE: return _fileHeader.at(0);
    default:
        int index = 128 + (128 * s);
        index += FF7SaveInfo::instance()->vmcHeaderOffset(fileFormat);
        return _fileHeader[index];
    }
}

void FF7Save::setPsx_block_type(int s, char block_type)
{
    switch (fileFormat) {
    case FF7SaveInfo::FORMAT::PDA:
    case FF7SaveInfo::FORMAT::UNKNOWN:
    case FF7SaveInfo::FORMAT::PC:
    case FF7SaveInfo::FORMAT::SWITCH:
    case FF7SaveInfo::FORMAT::PSX:
    case FF7SaveInfo::FORMAT::PS3: return;
    case FF7SaveInfo::FORMAT::PGE: _fileHeader.replace(0, 1, QByteArray(1, block_type)); break;
    default:
        int index = 128 + (128 * s);
        index += FF7SaveInfo::instance()->vmcHeaderOffset(fileFormat);
        _fileHeader.replace(index, 1, QByteArray(1, block_type));
    }
}

void FF7Save::setPsx_block_next(int s, int next)
{
    if (next < 0 || next > 14 || s < 0 || s > 14 || next == s)
        return;


    switch (fileFormat) {
    case FF7SaveInfo::FORMAT::PDA:
    case FF7SaveInfo::FORMAT::UNKNOWN:
    case FF7SaveInfo::FORMAT::PC:
    case FF7SaveInfo::FORMAT::SWITCH:
    case FF7SaveInfo::FORMAT::PSX:
    case FF7SaveInfo::FORMAT::PS3: return;
    case FF7SaveInfo::FORMAT::PGE: _fileHeader.replace(8, 1, QByteArray(1, next)); break;
    default:
        int index = 128 + (128 * s);
        index += FF7SaveInfo::instance()->vmcHeaderOffset(fileFormat) + 8;
        _fileHeader.replace(index, 1, QByteArray(1, next));
    }
}

quint8 FF7Save::psx_block_next(int s)
{
    switch (fileFormat) {
    case FF7SaveInfo::FORMAT::PDA:
    case FF7SaveInfo::FORMAT::UNKNOWN:
    case FF7SaveInfo::FORMAT::PC:
    case FF7SaveInfo::FORMAT::SWITCH:
    case FF7SaveInfo::FORMAT::PSX:
    case FF7SaveInfo::FORMAT::PS3: return 0x00;
    case FF7SaveInfo::FORMAT::PGE: return quint8(_fileHeader.at(0x08));
    default:
        int index = 128 + (128 * s);
        index += FF7SaveInfo::instance()->vmcHeaderOffset(fileFormat) + 8;
        return quint8(_fileHeader.at(index));
    }
}

void FF7Save::setPsx_block_size(int s, int blockSize)
{
    switch (fileFormat) {
    case FF7SaveInfo::FORMAT::PDA:
    case FF7SaveInfo::FORMAT::UNKNOWN:
    case FF7SaveInfo::FORMAT::PC:
    case FF7SaveInfo::FORMAT::SWITCH:
    case FF7SaveInfo::FORMAT::PSX:
    case FF7SaveInfo::FORMAT::PS3: return;
    default: break;
    }

    if (s < 0 || s > 14 || blockSize > 15) 
        return;

    quint32 filesize = quint32(blockSize * FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX));
    int index = 0;
    if (fileFormat != FF7SaveInfo::FORMAT::PGE) {
        index += 128 + (128 * s);
        index += FF7SaveInfo::instance()->vmcHeaderOffset(fileFormat);
    }
    _fileHeader.replace(index + 0x04, 1, QByteArray(1, char(filesize & 0xff)));
    _fileHeader.replace(index + 0x05, 1, QByteArray(1, char((filesize & 0xff00) >> 8)));
    _fileHeader.replace(index + 0x06, 1, QByteArray(1, char((filesize & 0xff0000) >> 16)));
}

quint8 FF7Save::psx_block_size(int s)
{
    switch (fileFormat) {
    case FF7SaveInfo::FORMAT::UNKNOWN:
    case FF7SaveInfo::FORMAT::PC:
    case FF7SaveInfo::FORMAT::SWITCH: return 1;
    case FF7SaveInfo::FORMAT::PSX: return quint8(QFile(fileName()).size() / FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX));
    case FF7SaveInfo::FORMAT::PS3: return quint8((QFile(fileName()).size() - 0x84) / FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX));
    case FF7SaveInfo::FORMAT::PGE: return quint8((QFile(fileName()).size() - 0x80) / FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX));
    case FF7SaveInfo::FORMAT::PDA: return quint8((QFile(fileName()).size() - 0x36) / FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX));
    default:
        int index = 128 + (128 * s);
        index += FF7SaveInfo::instance()->vmcHeaderOffset(fileFormat);
        qint32 value = _fileHeader[index + 0x04] | (_fileHeader[index + 0x05] << 8) | (_fileHeader[index + 0x06] << 16);
        return quint8 (value / FF7SaveInfo::instance()->fileSize(FF7SaveInfo::FORMAT::PSX));
    }
}

QString FF7Save::psxDesc(int s)
{
    QByteArray desc = slotHeader(s).mid(4, 64);
    int index;
    if ((index = desc.indexOf('\x00')) != -1)
        desc.truncate(index);
    return QTextCodec::codecForName("Shift-JIS")->toUnicode(desc);
}

void FF7Save::setPsxDesc(QString newDesc, int s)
{
    QByteArray temp = QTextCodec::codecForName("Shift-JIS")->fromUnicode(newDesc);

    QByteArray codedText;
    codedText.fill('\x00', 64);
    codedText.replace(0, temp.size(), temp);

    QByteArray header = slotHeader(s);
    header.replace(4, 64, codedText);
    if (setSlotHeader(s, header))
        setFileModified(true, s);
}

bool FF7Save::isFileModified(void)
{
    return fileHasChanged;
}
bool FF7Save::isSlotModified(int s)
{
    return slotChanged[s];
}

bool FF7Save::isSlotEmpty(int s)
{
    bool check = true;
    if (FF7SaveInfo::instance()->isTypeVMC(format()) && !FF7SaveInfo::instance()->isTypePC(format()))
            check = (psx_block_type(s) == '\xA0');
    return check && ff7Checksum(s) == 0x4D1D;
}
bool FF7Save::isFF7(int s)
{
    if (region(s).contains("00867") || region(s).contains("00869") ||
            region(s).contains("00900") || region(s).contains("94163") ||
            region(s).contains("00700") || region(s).contains("01057") ||
            region(s).contains("00868")) {
        return true;
    } else {
        return false;
    }
}

bool FF7Save::isPAL(int s)
{
    if (region(s).contains("00867") || region(s).contains("00869") ||
            region(s).contains("00900") || region(s).contains("00868")) {
        return true;
    } else {
        return false;
    }
}

bool FF7Save::isNTSC(int s)
{
    if (region(s).contains("00700") || region(s).contains("94163") || region(s).contains("01057")) {
        return true;
    } else {
        return false;
    }
}
bool FF7Save::isJPN(int s)
{
    if (region(s).contains("00700") || region(s).contains("01057")) {
        return true;
    } else {
        return false;
    }
}
int FF7Save::lenFile(void)
{
    return FF7SaveInfo::instance()->fileSize(fileFormat);
}
int FF7Save::lenFileHeader(void)
{
    return FF7SaveInfo::instance()->fileHeaderSize(fileFormat);   //Return File Header length
}

int FF7Save::lenCoreSave(void)
{
    return FF7SaveInfo::instance()->slotSize();   //Return Slot length (data portion)
}
int FF7Save::lenSlotHeader(void)
{
    return FF7SaveInfo::instance()->slotHeaderSize(fileFormat);   //Return slot header length
}
int FF7Save::lenSlotFooter(void)
{
    return FF7SaveInfo::instance()->slotFooterSize(fileFormat);   //Return slot footer length
}

int FF7Save::lenSlot()
{
    return lenSlotHeader() + lenCoreSave() + lenSlotFooter();
}

int FF7Save::numberOfSlots(void)
{
    return FF7SaveInfo::instance()->slotCount(fileFormat);   //Return number of slots in the file_footer_dex
}

void FF7Save::newGame(int s, const QString &region, const QString &fileName)
{
    if (fileName.isEmpty() || fileName.isNull()) {
        memcpy(&slot[s], defaultSave, size_t(FF7SaveInfo::instance()->slotSize()));
    } else {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly))
            return;
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        QByteArray temp; // create a temp to be used when needed
        int index = 0x200;
        temp = ff7file.mid(index, FF7SaveInfo::instance()->slotSize());
        memcpy(&slot[s], temp, size_t(FF7SaveInfo::instance()->slotSize()));
    }
    setRegion(s, region);
    if (isJPN(s)) {
        QByteArray emptyName = QByteArray('\xFF', 13);
        for (int c = 0; c < 9; c++)
            setCharName(s, c, emptyName);   // clear all names.

        FF7TEXT::instance()->setJapanese(true);
        setCharName(s, 0, QString::fromUtf8("元ソルジャー"));
        setCharName(s, 1, QString::fromUtf8("バレット"));
        setCharName(s, 2, QString::fromUtf8("ティファ"));
        setCharName(s, 3, QString::fromUtf8("エアリス"));
        setCharName(s, 4, QString::fromUtf8("レッド⑬"));
        setCharName(s, 5, QString::fromUtf8("ユフィ"));
        setCharName(s, 6, QString::fromUtf8("昔のクラウド"));
        setCharName(s, 7, QString::fromUtf8("セフィロス"));
        setCharName(s, 8, QString::fromUtf8("シド"));
        setDescName(s, QString::fromUtf8("元ソルジャー"));
        setDescLocation(s, QString::fromUtf8("１番街駅ホーム"));
        setLocation(s, QString::fromUtf8("１番街駅ホーム"));
    } else if (this->region(s).isEmpty()) {
        setRegion(s, QString("BASCUS-94163FF7-S%1").arg(QString::number(s + 1), 2, QChar('0')));
        FF7TEXT::instance()->setJapanese(false);
    }
    setFileModified(true, s);
}

void FF7Save::newGamePlus(int s, QString CharFileName, QString fileName)
{
    if (fileName.isEmpty() || fileName.isNull()) {
        memcpy(&buffer_slot, defaultSave, size_t(FF7SaveInfo::instance()->slotSize()));
    } else {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly)) {
            return;
        }
        QByteArray ff7file;
        ff7file = file.readAll(); //put all data in temp raw file
        QByteArray temp; // create a temp to be used when needed
        int index = 0x200;
        temp = ff7file.mid(index, FF7SaveInfo::instance()->slotSize());
        memcpy(&buffer_slot, temp, size_t(FF7SaveInfo::instance()->slotSize()));
    }
    buffer_region = region(s);
    memcpy(&buffer_slot.desc, &slot[s].desc, 0x44); // keep a old preview
    memcpy(&buffer_slot.colors, &slot[s].colors, 12); // keep old colors.

    for (int i = 0; i < 9; i++) { // keep all old character info.
        if ((i == 6) || (i == 7)) { // except we have to export cait sith and vincent.the game needs y.cloud/seppie,for the flash back.
            QString outFile;
            if (i == 6) { //export cait sith. cait sith's stats are only generated when he joins the party.
                outFile.append(CharFileName);
                outFile.append("-cait_sith");
                if (!FF7SaveInfo::instance()->isTypeSSS(fileFormat)) {
                    outFile.append("-");
                    QString str;
                    str.setNum(s + 1, 10);
                    outFile.append(str);
                }
            } else if (i == 7) { // export vincent. vincent's stats are only generated when he joins the party.
                outFile.append(CharFileName);
                outFile.append("-vincent");
                if (!FF7SaveInfo::instance()->isTypeSSS(fileFormat)) {
                    outFile.append("-");
                    QString str;
                    str.setNum(s + 1, 10);
                    outFile.append(str);
                }
            }
            outFile.append(".char");
            exportCharacter(s, i, outFile);

        } else {
            memcpy(&buffer_slot.chars[i], &slot[s].chars[i], 0x84);   // normal character
        }
    }
    memcpy(&buffer_slot.items, &slot[s].items, 640); // copy items
    memcpy(&buffer_slot.materias, &slot[s].materias, 800); // copy materia
    buffer_slot.gil = slot[s].gil; // copy gil
    buffer_slot.battles = slot[s].battles; // copy battle count
    buffer_slot.runs = slot[s].runs; // copy run count
    buffer_slot.gp = slot[s].gp; // copy gp
    //copy chocobo info.
    buffer_slot.stables = slot[s].stables;
    buffer_slot.stablesoccupied = slot[s].stablesoccupied;
    buffer_slot.chocobomask = slot[s].chocobomask;
    for (int i = 0; i < 4; i++) {
        buffer_slot.chocobos[i] = slot[s].chocobos[i];
    }
    memcpy(&buffer_slot.chocobonames, slot[s].chocobonames, 36);
    memcpy(&buffer_slot.chocostaminas, slot[s].chocostaminas, 12);
    for (int i = 0; i < 2; i++) {
        buffer_slot.choco56[i] = slot[s].choco56[i];
    }
    // copy options
    buffer_slot.battlespeed = slot[s].battlespeed;
    buffer_slot.battlemspeed = slot[s].battlemspeed;
    buffer_slot.options = slot[s].options;
    memcpy(&buffer_slot.controller_map, slot[s].controller_map, 16);
    buffer_slot.fieldmspeed = slot[s].fieldmspeed;
    //~~ buffer now ready to be copied~
    slot[s] = buffer_slot;
    setLocation(s, QT_TRANSLATE_NOOP("FF7Save", "New Game +"));
    setFileModified(true, s);
}
quint8 FF7Save::disc(int s)
{
    return slot[s].disc;
}
void FF7Save::setDisc(int s, int disc)
{
    if (disc < 1 || disc > 3) {
        return;
    } else {
        slot[s].disc = disc;
        setFileModified(true, s);
    }
}
quint16 FF7Save::mainProgress(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].mprogress);
    }
}
void FF7Save::setMainProgress(int s, int mProgress)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        mProgress = std::clamp(mProgress, 0, 0xFFFF);
        mProgress = qToLittleEndian(mProgress);
        if (mProgress != slot[s].mprogress) {
            slot[s].mprogress = mProgress;
            setFileModified(true, s);
        }
    }
}

QList<QByteArray> FF7Save::slotIcon(int s)
{
    QList<QByteArray> icon;

    if (slotHeader(s).at(2) >= 0x11) {
        icon.append(slotHeader(s).mid(96, 160));
        if (slotHeader(s).at(2) >= 0x12) {
            icon.append(slotHeader(s).mid(256, 128));
            if (slotHeader(s).at(2) == 0x13) {
                icon.append(slotHeader(s).mid(384, 128));
            }
        }
    } else {
        QByteArray tmp;
        tmp.fill(00, 0x200);
        icon.append(tmp);
    }
    return icon;
}
QString FF7Save::charName(int s, int char_num)
{
    FF7TEXT::instance()->setJapanese(isJPN(s));
    QByteArray text;
    for (int n = 0; n < 12; n++) {
        text.append(slot[s].chars[char_num].name[n]);
    }
    return FF7TEXT::instance()->toPC(text);
}
void FF7Save::setCharName(int s, int char_num, QString new_name)
{
    FF7TEXT::instance()->setJapanese(isJPN(s));
    for (int i = 0; i < 12; i++) {
        slot[s].chars[char_num].name[i] = 0xFF;
    }
    QByteArray temp = FF7TEXT::instance()->toFF7(new_name);
    memcpy(slot[s].chars[char_num].name, temp, temp.length());
    setFileModified(true, s);
}

QString FF7Save::descName(int s)
{
    FF7TEXT::instance()->setJapanese(isJPN(s));
    QByteArray text;
    for (int n = 0; n < 16; n++) {
        text.append(slot[s].desc.name[n]);
    }
    return FF7TEXT::instance()->toPC(text);
}
void FF7Save::setDescName(int s, QString new_name)
{
    FF7TEXT::instance()->setJapanese(isJPN(s));
    for (int i = 0; i < 16; i++) {
        slot[s].desc.name[i] = 0xFF;
    }
    QByteArray temp = FF7TEXT::instance()->toFF7(new_name);
    memcpy(slot[s].desc.name, temp, temp.length());
    setFileModified(true, s);
}

QString FF7Save::descLocation(int s)
{
    FF7TEXT::instance()->setJapanese(isJPN(s));
    QByteArray text;
    for (int n = 0; n < 24; n++) {
        text.append(slot[s].desc.location[n]);
    }
    return FF7TEXT::instance()->toPC(text);
}

void FF7Save::setDescLocation(int s, QString new_desc_location)
{
    FF7TEXT::instance()->setJapanese(isJPN(s));
    for (int i = 0; i < 32; i++)
        slot[s].desc.location[i] = 0xFF;
    QByteArray temp = FF7TEXT::instance()->toFF7(new_desc_location);
    memcpy(slot[s].desc.location, temp, temp.length());
    setFileModified(true, s);
}

quint8 FF7Save::descLevel(int s)
{
    return slot[s].desc.level;
}
quint8 FF7Save::descParty(int s, int char_num)
{
    return slot[s].desc.party[char_num];
}
quint16 FF7Save::descCurHP(int s)
{
    return qFromLittleEndian(slot[s].desc.curHP);
}
quint16 FF7Save::descMaxHP(int s)
{
    return qFromLittleEndian(slot[s].desc.maxHP);
}
quint16 FF7Save::descCurMP(int s)
{
    return qFromLittleEndian(slot[s].desc.curMP);
}
quint16 FF7Save::descMaxMP(int s)
{
    return qFromLittleEndian(slot[s].desc.maxMP);
}
quint32 FF7Save::descGil(int s)
{
    return qFromLittleEndian(slot[s].desc.gil);
}
void FF7Save::setDescLevel(int s, int new_level)
{
    slot[s].desc.level = new_level;
    setFileModified(true, s);
}

void FF7Save::setDescParty(int s, int char_num, quint8 new_id)
{
    slot[s].desc.party[char_num] = new_id;
    setFileModified(true, s);
}
void FF7Save::setDescCurHP(int s, quint16 new_curHP)
{
    slot[s].desc.curHP = qToLittleEndian(new_curHP);
    setFileModified(true, s);
}
void FF7Save::setDescMaxHP(int s, quint16 new_maxHP)
{
    slot[s].desc.maxHP = qToLittleEndian(new_maxHP);
    setFileModified(true, s);
}
void FF7Save::setDescCurMP(int s, quint16 new_curMP)
{
    slot[s].desc.curMP = qToLittleEndian(new_curMP);
    setFileModified(true, s);
}
void FF7Save::setDescMaxMP(int s, quint16 new_maxMP)
{
    slot[s].desc.maxMP = qToLittleEndian(new_maxMP);
    setFileModified(true, s);
}
void FF7Save::setDescGil(int s, quint32 new_gil)
{
    slot[s].desc.gil = qToLittleEndian(new_gil);
    setFileModified(true, s);
}

quint32 FF7Save::descTime(int s)
{
    return qFromLittleEndian(slot[s].desc.time);
}
void FF7Save::setDescTime(int s, quint32 new_time)
{
    slot[s].desc.time = qToLittleEndian(new_time);
    setFileModified(true, s);
}

quint32 FF7Save::time(int s)
{
    return qFromLittleEndian(slot[s].time);
}

void FF7Save::setTime(int s, quint32 new_time)
{
    slot[s].time = qToLittleEndian(new_time);
    setDescTime(s, new_time); //set Desc also.
    setFileModified(true, s);
}

QString FF7Save::location(int s)
{
    FF7TEXT::instance()->setJapanese(isJPN(s));
    QByteArray text;
    for (int n = 0; n < 24; n++) {
        text.append(slot[s].location[n]);
    }
    return FF7TEXT::instance()->toPC(text);
}
void FF7Save::setLocation(int s, QString new_location)
{
    FF7TEXT::instance()->setJapanese(isJPN(s));
    for (int i = 0; i < 24; i++)
        slot[s].location[i] = 0xFF;
    QByteArray temp = FF7TEXT::instance()->toFF7(new_location);
    memcpy(slot[s].location, temp, size_t(temp.length()));
    //and the description.
    setDescLocation(s, new_location);
    setFileModified(true, s);
}
quint8 FF7Save::love(int s, bool battle, FF7Save::LOVER who)
{
    if (battle) {
        switch (who) {
        case FF7Save::LOVE_BARRET: return slot[s].b_love.barret;
        case FF7Save::LOVE_TIFA: return slot[s].b_love.tifa;
        case FF7Save::LOVE_AERIS: return slot[s].b_love.aeris;
        case FF7Save::LOVE_YUFFIE: return slot[s].b_love.yuffie;
        }
    } else {
        switch (who) {
        case FF7Save::LOVE_BARRET: return slot[s].love.barret;
        case FF7Save::LOVE_TIFA: return slot[s].love.tifa;
        case FF7Save::LOVE_AERIS: return slot[s].love.aeris;
        case FF7Save::LOVE_YUFFIE: return slot[s].love.yuffie;
        }
    }
    return 0;
}
void FF7Save::setLove(int s, bool battle, FF7Save::LOVER who, quint8 love)
{
    if (battle) {
        switch (who) {
        case FF7Save::LOVE_BARRET: slot[s].b_love.barret = love; setFileModified(true, s); break;
        case FF7Save::LOVE_TIFA: slot[s].b_love.tifa = love; setFileModified(true, s); break;
        case FF7Save::LOVE_AERIS:  slot[s].b_love.aeris = love; setFileModified(true, s); break;
        case FF7Save::LOVE_YUFFIE:  slot[s].b_love.yuffie = love; setFileModified(true, s); break;
        }
    } else {
        switch (who) {
        case FF7Save::LOVE_BARRET: slot[s].love.barret = love; setFileModified(true, s); break;
        case FF7Save::LOVE_TIFA: slot[s].love.tifa = love; setFileModified(true, s); break;
        case FF7Save::LOVE_AERIS:  slot[s].love.aeris = love; setFileModified(true, s); break;
        case FF7Save::LOVE_YUFFIE:  slot[s].love.yuffie = love; setFileModified(true, s); break;
        }
    }
}
bool  FF7Save::materiaCave(int s, FF7Save::MATERIACAVE cave)
{
    switch (cave) {
    case FF7Save::CAVE_MIME: return (slot[s].materiacaves & (1 << 0));
    case FF7Save::CAVE_HPMP: return (slot[s].materiacaves & (1 << 1));
    case FF7Save::CAVE_QUADMAGIC: return (slot[s].materiacaves & (1 << 2));
    case FF7Save::CAVE_KOTR: return (slot[s].materiacaves & (1 << 3));
    }
    return false;
}
void FF7Save::setMateriaCave(int s, FF7Save::MATERIACAVE cave, bool isEmpty)
{
    switch (cave) {
    case FF7Save::CAVE_MIME:
        if (isEmpty) {
            slot[s].materiacaves |= (1 << 0);
        } else {
            slot[s].materiacaves &= ~(1 << 0);
        }
        setFileModified(true, s);
        break;

    case FF7Save::CAVE_HPMP:
        if (isEmpty) {
            slot[s].materiacaves |= (1 << 1);
        } else {
            slot[s].materiacaves &= ~(1 << 1);
        }
        setFileModified(true, s);
        break;

    case FF7Save::CAVE_QUADMAGIC:
        if (isEmpty) {
            slot[s].materiacaves |= (1 << 2);
        } else {
            slot[s].materiacaves &= ~(1 << 2);
        }
        setFileModified(true, s);
        break;

    case FF7Save::CAVE_KOTR:
        if (isEmpty) {
            slot[s].materiacaves |= (1 << 3);
        } else {
            slot[s].materiacaves &= ~(1 << 3);
        }
        setFileModified(true, s);
        break;
    }
}
quint16 FF7Save::speedScore(int s, int rank)
{
    switch (rank) {
    case 1: return qFromLittleEndian(slot[s].coster_1);
    case 2: return qFromLittleEndian(slot[s].coster_2);
    case 3: return qFromLittleEndian(slot[s].coster_3);
    default:  return 0;
    }
}
void FF7Save::setSpeedScore(int s, int rank, quint16 score)
{
    score = qToLittleEndian(score);
    switch (rank) {
    case 1: slot[s].coster_1 = score; setFileModified(true, s); break;
    case 2: slot[s].coster_2 = score; setFileModified(true, s); break;
    case 3: slot[s].coster_3 = score; setFileModified(true, s); break;
    default: break;
    }
}

QString FF7Save::chocoName(int s, int choco_num)
{
    FF7TEXT::instance()->setJapanese(isJPN(s));
    QByteArray text;
    for (int n = 0; n < 6; n++) {
        text.append(slot[s].chocobonames[choco_num][n]);
    }
    return FF7TEXT::instance()->toPC(text);
}
void FF7Save::setChocoName(int s, int choco_num, QString new_name)
{
    FF7TEXT::instance()->setJapanese(isJPN(s));
    QByteArray temp = FF7TEXT::instance()->toFF7(new_name);
    for (int i = 0; i < 6; i++) {
        slot[s].chocobonames[choco_num][i] = 0xFF;
    }
    memcpy(slot[s].chocobonames[choco_num], temp, size_t(temp.length()));
    setFileModified(true, s);
}
void FF7Save::setPartyMateria(int s, int mat_num, quint8 id, qint32 ap)
{
    ap = qToLittleEndian(ap);
    //if invalid set to 0xFF
    if ((id < 91) && ((ap >= 0) && (ap <= 16777215))) {
        //Valid Id and Ap provided.
        slot[s].materias[mat_num].id = id;
        int a = (ap & 0xff);
        int b = (ap & 0xff00) >> 8;
        int c = (ap & 0xff0000) >> 16;
        slot[s].materias[mat_num].ap[0] = a;
        slot[s].materias[mat_num].ap[1] = b;
        slot[s].materias[mat_num].ap[2] = c;
    } else {
        //invalid ID set Empty
        slot[s].materias[mat_num].id = 0xFF;
        slot[s].materias[mat_num].ap[0] = 0xFF;
        slot[s].materias[mat_num].ap[1] = 0xFF;
        slot[s].materias[mat_num].ap[2] = 0xFF;
    }
    setFileModified(true, s);
}
quint8 FF7Save::partyMateriaId(int s, int mat_num)
{
    return slot[s].materias[mat_num].id;
}
qint32 FF7Save::partyMateriaAp(int s, int mat_num)
{
    qint32 ap_temp = slot[s].materias[mat_num].ap[0] | (slot[s].materias[mat_num].ap[1] << 8) | slot[s].materias[mat_num].ap[2] << 16;
    return qFromLittleEndian(ap_temp);
}
void FF7Save::setStolenMateria(int s, int mat_num, quint8 id, qint32 ap)
{
    ap = qToLittleEndian(ap);
    if ((id < 91) && ((ap >= 0) && (ap <= 16777215))) {
        //Valid Id and Ap provided.
        slot[s].stolen[mat_num].id = id;
        int a = (ap & 0xff);
        int b = (ap & 0xff00) >> 8;
        int c = (ap & 0xff0000) >> 16;
        slot[s].stolen[mat_num].ap[0] = a;
        slot[s].stolen[mat_num].ap[1] = b;
        slot[s].stolen[mat_num].ap[2] = c;
    } else {
        //invalid ID set Empty
        slot[s].stolen[mat_num].id = 0xFF;
        slot[s].stolen[mat_num].ap[0] = 0xFF;
        slot[s].stolen[mat_num].ap[1] = 0xFF;
        slot[s].stolen[mat_num].ap[2] = 0xFF;
    }
    setFileModified(true, s);
}
quint8 FF7Save::stolenMateriaId(int s, int mat_num)
{
    return slot[s].stolen[mat_num].id;
}

qint32 FF7Save::stolenMateriaAp(int s, int mat_num)
{
    qint32 ap_temp = slot[s].stolen[mat_num].ap[0] | (slot[s].stolen[mat_num].ap[1] << 8) | slot[s].stolen[mat_num].ap[2] << 16;
    return qFromLittleEndian(ap_temp);
}
QColor FF7Save::dialogColorUL(int s)
{
    return QColor(slot[s].colors[0][0], slot[s].colors[0][1], slot[s].colors[0][2]);
}
QColor FF7Save::dialogColorUR(int s)
{
    return QColor(slot[s].colors[1][0], slot[s].colors[1][1], slot[s].colors[1][2]);
}
QColor FF7Save::dialogColorLL(int s)
{
    return QColor(slot[s].colors[2][0], slot[s].colors[2][1], slot[s].colors[2][2]);
}
QColor FF7Save::dialogColorLR(int s)
{
    return QColor(slot[s].colors[3][0], slot[s].colors[3][1], slot[s].colors[3][2]);
}

void FF7Save::setDialogColorUL(int s, QColor color)
{
    slot[s].colors[0][0] = color.red();
    slot[s].colors[0][1] = color.green();
    slot[s].colors[0][2] = color.blue();
    setFileModified(true, s);
}
void FF7Save::setDialogColorUR(int s, QColor color)
{
    slot[s].colors[1][0] = color.red();
    slot[s].colors[1][1] = color.green();
    slot[s].colors[1][2] = color.blue();
    setFileModified(true, s);
}
void FF7Save::setDialogColorLL(int s, QColor color)
{
    slot[s].colors[2][0] = color.red();
    slot[s].colors[2][1] = color.green();
    slot[s].colors[2][2] = color.blue();
    setFileModified(true, s);
}
void FF7Save::setDialogColorLR(int s, QColor color)
{
    slot[s].colors[3][0] = color.red();
    slot[s].colors[3][1] = color.green();
    slot[s].colors[3][2] = color.blue();
    setFileModified(true, s);
}
void FF7Save::setCharacter(int s, int char_num, const FF7CHAR &new_char)
{
    slot[s].chars[char_num] = new_char;
}

FF7CHAR FF7Save::character(int s, int char_num)
{
    return slot[s].chars[char_num];
}

QByteArray FF7Save::rawCharacterData(int s, int char_num)
{
    QByteArray temp;
    temp.setRawData(reinterpret_cast <char *>(&slot[s].chars[char_num]), 132);
    return temp;
}
quint8 FF7Save::charID(int s, int char_num)
{
    return slot[s].chars[char_num].id;
}
quint8 FF7Save::charLevel(int s, int char_num)
{
    return slot[s].chars[char_num].level;
}
quint8 FF7Save::charStr(int s, int char_num)
{
    return slot[s].chars[char_num].strength;
}
quint8 FF7Save::charVit(int s, int char_num)
{
    return slot[s].chars[char_num].vitality;
}
quint8 FF7Save::charMag(int s, int char_num)
{
    return slot[s].chars[char_num].magic;
}
quint8 FF7Save::charSpi(int s, int char_num)
{
    return slot[s].chars[char_num].spirit;
}
quint8 FF7Save::charDex(int s, int char_num)
{
    return slot[s].chars[char_num].dexterity;
}
quint8 FF7Save::charLck(int s, int char_num)
{
    return slot[s].chars[char_num].luck;
}
quint8 FF7Save::charStrBonus(int s, int char_num)
{
    return slot[s].chars[char_num].strength_bonus;
}
quint8 FF7Save::charVitBonus(int s, int char_num)
{
    return slot[s].chars[char_num].vitality_bonus;
}
quint8 FF7Save::charMagBonus(int s, int char_num)
{
    return slot[s].chars[char_num].magic_bonus;
}
quint8 FF7Save::charSpiBonus(int s, int char_num)
{
    return slot[s].chars[char_num].spirit_bonus;
}
quint8 FF7Save::charDexBonus(int s, int char_num)
{
    return slot[s].chars[char_num].dexterity_bonus;
}
quint8 FF7Save::charLckBonus(int s, int char_num)
{
    return slot[s].chars[char_num].luck_bonus;
}
qint8 FF7Save::charLimitLevel(int s, int char_num)
{
    return slot[s].chars[char_num].limitlevel;
}
quint8 FF7Save::charLimitBar(int s, int char_num)
{
    return slot[s].chars[char_num].limitbar;
}
quint8 FF7Save::charWeapon(int s, int char_num)
{
    return slot[s].chars[char_num].weapon;
}
quint8 FF7Save::charArmor(int s, int char_num)
{
    return slot[s].chars[char_num].armor;
}
quint8 FF7Save::charAccessory(int s, int char_num)
{
    return slot[s].chars[char_num].accessory;
}
quint8 FF7Save::charFlag(int s, int char_num, int flag_num)
{
    return slot[s].chars[char_num].flags[flag_num];
}
quint16 FF7Save::charLimits(int s, int char_num)
{
    return qFromLittleEndian(slot[s].chars[char_num].limits);
}
quint16 FF7Save::charKills(int s, int char_num)
{
    return qFromLittleEndian(slot[s].chars[char_num].kills);
}

quint16 FF7Save::charTimesLimitUsed(int s, int char_num, int level)
{
    switch (level) {
    case 1: return qFromLittleEndian(slot[s].chars[char_num].timesused1);
    case 2: return qFromLittleEndian(slot[s].chars[char_num].timesused2);
    case 3: return qFromLittleEndian(slot[s].chars[char_num].timesused3);
    default: return 0;
    }
}

quint16 FF7Save::charCurrentHp(int s, int char_num)
{
    return qFromLittleEndian(slot[s].chars[char_num].curHP);
}
quint16 FF7Save::charBaseHp(int s, int char_num)
{
    return qFromLittleEndian(slot[s].chars[char_num].baseHP);
}
quint16 FF7Save::charCurrentMp(int s, int char_num)
{
    return qFromLittleEndian(slot[s].chars[char_num].curMP);
}
quint16 FF7Save::charBaseMp(int s, int char_num)
{
    return qFromLittleEndian(slot[s].chars[char_num].baseMP);
}
quint8 FF7Save::charUnknown(int s, int char_num, int unknown_num)
{
    return slot[s].chars[char_num].z_4[unknown_num];
}
quint16 FF7Save::charMaxHp(int s, int char_num)
{
    return qFromLittleEndian(slot[s].chars[char_num].maxHP);
}
quint16 FF7Save::charMaxMp(int s, int char_num)
{
    return qFromLittleEndian(slot[s].chars[char_num].maxMP);
}
quint32 FF7Save::charCurrentExp(int s, int char_num)
{
    return qFromLittleEndian(slot[s].chars[char_num].exp);
}
quint32 FF7Save::charNextExp(int s, int char_num)
{
    return qFromLittleEndian(slot[s].chars[char_num].expNext);
}

void  FF7Save::setCharID(int s, int char_num, qint8 new_id)
{
    slot[s].chars[char_num].id = new_id;
    setFileModified(true, s);
}
void  FF7Save::setCharLevel(int s, int char_num, qint8 new_level)
{
    slot[s].chars[char_num].level = new_level;
    setFileModified(true, s);
}
void  FF7Save::setCharStr(int s, int char_num, quint8 str)
{
    slot[s].chars[char_num].strength = str;
    setFileModified(true, s);
}
void  FF7Save::setCharVit(int s, int char_num, quint8 vit)
{
    slot[s].chars[char_num].vitality = vit;
    setFileModified(true, s);
}
void  FF7Save::setCharMag(int s, int char_num, quint8 mag)
{
    slot[s].chars[char_num].magic = mag;
    setFileModified(true, s);
}
void  FF7Save::setCharSpi(int s, int char_num, quint8 spi)
{
    slot[s].chars[char_num].spirit = spi;
    setFileModified(true, s);
}
void  FF7Save::setCharDex(int s, int char_num, quint8 dex)
{
    slot[s].chars[char_num].dexterity = dex;
    setFileModified(true, s);
}
void  FF7Save::setCharLck(int s, int char_num, quint8 lck)
{
    slot[s].chars[char_num].luck = lck;
    setFileModified(true, s);
}
void  FF7Save::setCharStrBonus(int s, int char_num, quint8 strbonus)
{
    slot[s].chars[char_num].strength_bonus = strbonus;
    setFileModified(true, s);
}
void  FF7Save::setCharVitBonus(int s, int char_num, quint8 vitbonus)
{
    slot[s].chars[char_num].vitality_bonus = vitbonus;
    setFileModified(true, s);
}
void  FF7Save::setCharMagBonus(int s, int char_num, quint8 magbonus)
{
    slot[s].chars[char_num].magic_bonus = magbonus;
    setFileModified(true, s);
}
void  FF7Save::setCharSpiBonus(int s, int char_num, quint8 spibonus)
{
    slot[s].chars[char_num].spirit_bonus = spibonus;
    setFileModified(true, s);
}
void  FF7Save::setCharDexBonus(int s, int char_num, quint8 dexbonus)
{
    slot[s].chars[char_num].dexterity_bonus = dexbonus;
    setFileModified(true, s);
}
void  FF7Save::setCharLckBonus(int s, int char_num, quint8 lckbonus)
{
    slot[s].chars[char_num].luck_bonus = lckbonus;
    setFileModified(true, s);
}
void  FF7Save::setCharLimitLevel(int s, int char_num, qint8 limitlevel)
{
    slot[s].chars[char_num].limitlevel = limitlevel;
    setFileModified(true, s);
}
void  FF7Save::setCharLimitBar(int s, int char_num, quint8 limitbar)
{
    slot[s].chars[char_num].limitbar = limitbar;
    setFileModified(true, s);
}
void  FF7Save::setCharWeapon(int s, int char_num, quint8 weapon)
{
    slot[s].chars[char_num].weapon = weapon;
    setFileModified(true, s);
}
void  FF7Save::setCharArmor(int s, int char_num, quint8 armor)
{
    slot[s].chars[char_num].armor = armor;
    setFileModified(true, s);
}
void  FF7Save::setCharAccessory(int s, int char_num, quint8 accessory)
{
    slot[s].chars[char_num].accessory = accessory;
    setFileModified(true, s);
}
void  FF7Save::setCharFlag(int s, int char_num, int flag_num, quint8 flag_value)
{
    slot[s].chars[char_num].flags[flag_num] = flag_value;
    setFileModified(true, s);
}
void  FF7Save::setCharLimits(int s, int char_num, quint16 new_limits)
{
    slot[s].chars[char_num].limits = qToLittleEndian(new_limits);
    setFileModified(true, s);
}
void  FF7Save::setCharKills(int s, int char_num, quint16 newKills)
{
    slot[s].chars[char_num].kills = qToLittleEndian(newKills);
    setFileModified(true, s);
}
void  FF7Save::setCharTimeLimitUsed(int s, int char_num, int level, quint16 timesused)
{
    timesused = qToLittleEndian(timesused);
    switch (level) {
    case 1: slot[s].chars[char_num].timesused1 = timesused; setFileModified(true, s); break;
    case 2: slot[s].chars[char_num].timesused2 = timesused; setFileModified(true, s); break;
    case 3: slot[s].chars[char_num].timesused3 = timesused; setFileModified(true, s); break;
    }
}
void  FF7Save::setCharCurrentHp(int s, int char_num, quint16 curHp)
{
    slot[s].chars[char_num].curHP = qToLittleEndian(curHp);
    setFileModified(true, s);
}
void  FF7Save::setCharBaseHp(int s, int char_num, quint16 baseHp)
{
    slot[s].chars[char_num].baseHP = qToLittleEndian(baseHp);
    setFileModified(true, s);
}
void  FF7Save::setCharCurrentMp(int s, int char_num, quint16 curMp)
{
    slot[s].chars[char_num].curMP = qToLittleEndian(curMp);
    setFileModified(true, s);
}
void  FF7Save::setCharBaseMp(int s, int char_num, quint16 baseMp)
{
    slot[s].chars[char_num].baseMP = qToLittleEndian(baseMp);
    setFileModified(true, s);
}
void  FF7Save::setCharUnknown(int s, int char_num, int unknown_num, quint8 value)
{
    slot[s].chars[char_num].z_4[unknown_num] = value;
    setFileModified(true, s);
}
void  FF7Save::setCharMaxHp(int s, int char_num, quint16 maxHp)
{
    slot[s].chars[char_num].maxHP = qToLittleEndian(maxHp);
    setFileModified(true, s);
}
void  FF7Save::setCharMaxMp(int s, int char_num, quint16 maxMp)
{
    slot[s].chars[char_num].maxMP = qToLittleEndian(maxMp);
    setFileModified(true, s);
}
void  FF7Save::setCharCurrentExp(int s, int char_num, quint32 exp)
{
    slot[s].chars[char_num].exp = qToLittleEndian(exp);
    setFileModified(true, s);
}
void  FF7Save::setCharNextExp(int s, int char_num, quint32 next)
{
    slot[s].chars[char_num].expNext = qToLittleEndian(next);
    setFileModified(true, s);
}

void FF7Save::setCharMateria(int s, int who, int mat_num, quint8 id, qint32 ap)
{
    ap = qToLittleEndian(ap);
    if ((id < 91) && ((ap >= 0) && (ap <= 16777215))) {
        //Valid Id and Ap provided.
        slot[s].chars[who].materias[mat_num].id = id;
        int a = (ap & 0xff);
        int b = (ap & 0xff00) >> 8;
        int c = (ap & 0xff0000) >> 16;
        slot[s].chars[who].materias[mat_num].ap[0] = a;
        slot[s].chars[who].materias[mat_num].ap[1] = b;
        slot[s].chars[who].materias[mat_num].ap[2] = c;
    } else {
        //invalid ID set Empty
        slot[s].chars[who].materias[mat_num].id = 0xFF;
        slot[s].chars[who].materias[mat_num].ap[0] = 0xFF;
        slot[s].chars[who].materias[mat_num].ap[1] = 0xFF;
        slot[s].chars[who].materias[mat_num].ap[2] = 0xFF;
    }
    setFileModified(true, s);
}
void FF7Save::setCharMateria(int s, int who, int mat_num, materia mat)
{
    slot[s].chars[who].materias[mat_num] = mat;
    setFileModified(true, s);
}
quint8 FF7Save::charMateriaId(int s, int who, int mat_num)
{
    return slot[s].chars[who].materias[mat_num].id;
}
qint32 FF7Save::charMateriaAp(int s, int who, int mat_num)
{
    qint32 ap_temp = slot[s].chars[who].materias[mat_num].ap[0] | (slot[s].chars[who].materias[mat_num].ap[1] << 8) | slot[s].chars[who].materias[mat_num].ap[2] << 16;
    return qToLittleEndian(ap_temp);
}
FF7CHOCOBO FF7Save::chocobo(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return slot[s].chocobos[chocoSlot];
    } else if (chocoSlot == 4) {
        return slot[s].choco56[0];
    } else if (chocoSlot == 5) {
        return slot[s].choco56[1];
    } else {
        FF7CHOCOBO bob;
        QByteArray temp;
        temp.fill(0, 16);
        memcpy(&bob, temp, 16);
        return bob;
    }
}

quint16 FF7Save::chocoStamina(int s, int chocoSlot)
{
    return qFromLittleEndian(slot[s].chocostaminas[chocoSlot]);
}
quint16 FF7Save::chocoSpeed(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return qFromLittleEndian(slot[s].chocobos[chocoSlot].speed);
    } else if (chocoSlot == 4) {
        return qFromLittleEndian(slot[s].choco56[0].speed);
    } else if (chocoSlot == 5) {
        return qFromLittleEndian(slot[s].choco56[1].speed);
    } else {
        return 0;
    }
}
quint16 FF7Save::chocoMaxSpeed(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return qFromLittleEndian(slot[s].chocobos[chocoSlot].maxspeed);
    } else if (chocoSlot == 4) {
        return qFromLittleEndian(slot[s].choco56[0].maxspeed);
    } else if (chocoSlot == 5) {
        return qFromLittleEndian(slot[s].choco56[1].maxspeed);
    } else {
        return 0;
    }
}
quint16 FF7Save::chocoSprintSpeed(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return qFromLittleEndian(slot[s].chocobos[chocoSlot].sprintspd);
    } else if (chocoSlot == 4) {
        return qFromLittleEndian(slot[s].choco56[0].sprintspd);
    } else if (chocoSlot == 5) {
        return qFromLittleEndian(slot[s].choco56[1].sprintspd);
    } else {
        return 0;
    }
}
quint16 FF7Save::chocoMaxSprintSpeed(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return qFromLittleEndian(slot[s].chocobos[chocoSlot].maxsprintspd);
    } else if (chocoSlot == 4) {
        return qFromLittleEndian(slot[s].choco56[0].maxsprintspd);
    } else if (chocoSlot == 5) {
        return qFromLittleEndian(slot[s].choco56[1].maxsprintspd);
    } else {
        return 0;
    }
}
quint8 FF7Save::chocoSex(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return slot[s].chocobos[chocoSlot].sex;
    } else if (chocoSlot == 4) {
        return slot[s].choco56[0].sex;
    } else if (chocoSlot == 5) {
        return slot[s].choco56[1].sex;
    } else {
        return 0;
    }
}
quint8 FF7Save::chocoType(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return slot[s].chocobos[chocoSlot].type;
    } else if (chocoSlot == 4) {
        return slot[s].choco56[0].type;
    } else if (chocoSlot == 5) {
        return slot[s].choco56[1].type;
    } else {
        return 0;
    }
}
quint8 FF7Save::chocoCoop(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return slot[s].chocobos[chocoSlot].coop;
    } else if (chocoSlot == 4) {
        return slot[s].choco56[0].coop;
    } else if (chocoSlot == 5) {
        return slot[s].choco56[1].coop;
    } else {
        return 0;
    }
}
quint8 FF7Save::chocoAccel(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return slot[s].chocobos[chocoSlot].accel;
    } else if (chocoSlot == 4) {
        return slot[s].choco56[0].accel;
    } else if (chocoSlot == 5) {
        return slot[s].choco56[1].accel;
    } else {
        return 0;
    }
}
quint8 FF7Save::chocoIntelligence(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return slot[s].chocobos[chocoSlot].intelligence;
    } else if (chocoSlot == 4) {
        return slot[s].choco56[0].intelligence;
    } else if (chocoSlot == 5) {
        return slot[s].choco56[1].intelligence;
    } else {
        return 0;
    }
}
quint8 FF7Save::chocoRaceswon(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return slot[s].chocobos[chocoSlot].raceswon;
    } else if (chocoSlot == 4) {
        return slot[s].choco56[0].raceswon;
    } else if (chocoSlot == 5) {
        return slot[s].choco56[1].raceswon;
    } else {
        return 0;
    }
}
quint8 FF7Save::chocoPCount(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return slot[s].chocobos[chocoSlot].pcount;
    } else if (chocoSlot == 4) {
        return slot[s].choco56[0].pcount;
    } else if (chocoSlot == 5) {
        return slot[s].choco56[1].pcount;
    } else {
        return 0;
    }
}
quint8 FF7Save::chocoPersonality(int s, int chocoSlot)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        return slot[s].chocobos[chocoSlot].personality;
    } else if (chocoSlot == 4) {
        return slot[s].choco56[0].personality;
    } else if (chocoSlot == 5) {
        return slot[s].choco56[1].personality;
    } else {
        return 0;
    }
}
bool FF7Save::chocoCantMate(int s, int chocoSlot)
{
    return slot[s].chocomated & (1 << chocoSlot);
}

void FF7Save::setChocoStamina(int s, int chocoSlot, quint16 stamina)
{
    slot[s].chocostaminas[chocoSlot] = qToLittleEndian(stamina);
    setFileModified(true, s);
}
void FF7Save::setChocoSpeed(int s, int chocoSlot, quint16 speed)
{
    speed = qToLittleEndian(speed);
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].speed = speed;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].speed = speed;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].speed = speed;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoMaxSpeed(int s, int chocoSlot, quint16 maxspeed)
{
    maxspeed = qToLittleEndian(maxspeed);
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].maxspeed = maxspeed;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].maxspeed = maxspeed;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].maxspeed = maxspeed;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoSprintSpeed(int s, int chocoSlot, quint16 sprintSpeed)
{
    sprintSpeed = qToLittleEndian(sprintSpeed);
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].sprintspd = sprintSpeed;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].sprintspd = sprintSpeed;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].sprintspd = sprintSpeed;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoMaxSprintSpeed(int s, int chocoSlot, quint16 maxsprintSpeed)
{
    maxsprintSpeed = qToLittleEndian(maxsprintSpeed);
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].maxsprintspd = maxsprintSpeed;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].maxsprintspd = maxsprintSpeed;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].maxsprintspd = maxsprintSpeed;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoSex(int s, int chocoSlot, quint8 value)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].sex = value;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].sex = value;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].sex = value;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoType(int s, int chocoSlot, quint8 value)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].type = value;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].type = value;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].type = value;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoCoop(int s, int chocoSlot, quint8 value)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].coop = value;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].coop = value;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].coop = value;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoAccel(int s, int chocoSlot, quint8 value)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].accel = value;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].accel = value;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].accel = value;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoIntelligence(int s, int chocoSlot, quint8 value)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].intelligence = value;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].intelligence = value;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].intelligence = value;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoRaceswon(int s, int chocoSlot, quint8 value)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].raceswon = value;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].raceswon = value;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].raceswon = value;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoPCount(int s, int chocoSlot, quint8 value)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].pcount = value;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].pcount = value;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].pcount = value;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoPersonality(int s, int chocoSlot, quint8 value)
{
    if (chocoSlot > -1 && chocoSlot < 4) {
        slot[s].chocobos[chocoSlot].personality = value;
        setFileModified(true, s);
    } else if (chocoSlot == 4) {
        slot[s].choco56[0].personality = value;
        setFileModified(true, s);
    } else if (chocoSlot == 5) {
        slot[s].choco56[1].personality = value;
        setFileModified(true, s);
    }
}
void FF7Save::setChocoCantMate(int s, int chocoSlot, bool cantMate)
{
    if (cantMate) {
        slot[s].chocomated |= (1 << chocoSlot);
    } else {
        slot[s].chocomated &= ~(1 << chocoSlot);
    }
    setFileModified(true, s);
}
quint32 FF7Save::gil(int s)
{
    return qFromLittleEndian(slot[s].gil);
}
void FF7Save::setGil(int s, quint32 gil)
{
    gil = std::max<quint32>(gil, 0);
    gil = qToLittleEndian(gil);
    slot[s].gil = gil;
    setDescGil(s, gil); //Update Desc
    setFileModified(true, s);
}
quint16 FF7Save::gp(int s)
{
    return qFromLittleEndian(slot[s].gp);
}
void FF7Save::setGp(int s, int gp)
{
    gp = std::clamp(gp, 0, 65535);
    gp = qToLittleEndian(gp);
    slot[s].gp = gp;
    setFileModified(true, s);
}
quint16 FF7Save::battles(int s)
{
    return qFromLittleEndian(slot[s].battles);
}
void FF7Save::setBattles(int s, int battles)
{

    battles = std::clamp(battles, 0, 65535);
    battles = qToLittleEndian(battles);
    slot[s].battles = battles;
    setFileModified(true, s);
}
quint16 FF7Save::runs(int s)
{
    return qFromLittleEndian(slot[s].runs);
}
void FF7Save::setRuns(int s, int runs)
{
    runs = std::clamp(runs, 0, 65535);
    runs = qToLittleEndian(runs);
    slot[s].runs = runs;
    setFileModified(true, s);
}
quint8 FF7Save::party(int s, int pos)
{
    return slot[s].party[pos];
}
void FF7Save::setParty(int s, int pos, int new_id)
{
    if (pos >= 0 && pos < 3) {
        if (new_id >= 0 && new_id < 12) {
            slot[s].party[pos] = new_id;
            slot[s].f_party[pos] = new_id;
        } else {
            slot[s].party[pos] = 0xFF;
            slot[s].f_party[pos] = 0xFF;
        }
        setFileModified(true, s);
    }
}
QString FF7Save::snowboardTime(int s, int course)
{
    quint32 time = 0;
    switch (course) {
    case 0:
        time = qFromLittleEndian(slot[s].SnowBegFastTime);
        break;
    case 1:
        time = qFromLittleEndian(slot[s].SnowExpFastTime);
        break;
    case 2:
        time = qFromLittleEndian(slot[s].SnowCrazyFastTime);
        break;
    default: break;
    }
    return QString("%1").arg(time, 8, 16, QChar('0'));
}
void FF7Save::setSnowboardTime(int s, int course, QString value)
{
    switch (course) {
    case 0:
        slot[s].SnowBegFastTime = value.toUInt(0, 16);
        setFileModified(true, s);
        break;
    case 1:
        slot[s].SnowExpFastTime = value.toUInt(0, 16);
        setFileModified(true, s);
        break;
    case 2:
        slot[s].SnowCrazyFastTime = value.toUInt(0, 16);
        setFileModified(true, s);
        break;
    default: break;
    }
}

quint8 FF7Save::snowboardScore(int s, int course)
{
    switch (course) {
    case 0: return slot[s].SnowBegScore;
    case 1: return slot[s].SnowExpScore;
    case 2: return slot[s].SnowCrazyScore;
    default: return 0;
    }
}

void FF7Save::setSnowboardScore(int s, int course, quint8 score)
{
    switch (course) {
    case 0:  slot[s].SnowBegScore = score; setFileModified(true, s); break;
    case 1:  slot[s].SnowExpScore = score; setFileModified(true, s); break;
    case 2:  slot[s].SnowCrazyScore = score; setFileModified(true, s); break;
    default: break;
    }

}
quint16 FF7Save::bikeHighScore(int s)
{
    return qFromLittleEndian(slot[s].BikeHighScore);
}
void FF7Save::setBikeHighScore(int s, quint16 score)
{
    slot[s].BikeHighScore = qToLittleEndian(score);
    setFileModified(true, s);
}
quint16 FF7Save::battlePoints(int s)
{
    return qFromLittleEndian(slot[s].battlepoints);
}
void FF7Save::setBattlePoints(int s, quint16 bp)
{
    bp = qToLittleEndian(bp);
    if (s < 0 || s > 14) {
        return;
    } else if (slot[s].battlepoints == bp) {
        return;
    } else {
        slot[s].battlepoints = bp;
        setFileModified(true, s);
    }
}

QString FF7Save::md5sum(QString fileName, QString UserID)
{
    QByteArray ff7file;
    QFile  file(fileName);
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly)) {
            ff7file = file.readAll();
        }
    }
    if (UserID != "") {
        int digitcount = 0;
        for (int i = 0; i < UserID.length(); i++) {
            if (UserID.at(i).isDigit()) {
                digitcount ++;
            }
        }
        if (digitcount == UserID.length()) {
            //make sure the id is all digits.
            ff7file.append(UserID.toLatin1());//append the user's ID
        }
    }

    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(ff7file);
    return md5.result().toHex().toLower();
}
void FF7Save::setFileModified(bool changed, int s)
{
    fileHasChanged = changed;
    if (changed)
        slotChanged[s] = true;
    else {
        for (int i = 0; i < 15; i++)
            slotChanged[i] = changed;
    }
    emit fileChanged(fileHasChanged);
}
QVector< SubContainer > FF7Save::parseXML(const QString &fileName, const QString &metadataPath, const QString &UserID)
{
    //typedef QVector< QString > SubContainer;
    QVector< SubContainer > vector(10, SubContainer(16));
    QString Md5 = md5sum(fileName, UserID);
    QString timestamp = filetimestamp(fileName);
    QString number = fileblock(fileName);                           //Get file block number
    if (number == "-1") {/*return 0;*/}                             //Fail if not a number
    else {
        number = QString::number(number.toInt() + 1);
    }

    QFile *file2 = new QFile(metadataPath);                         //Open metadata.xml
    if (!file2->open(QIODevice::ReadOnly)) {/*return 0;*/}          //If open fail, show an error message.
    QDomDocument doc("metadata");
    bool setdoc = doc.setContent(file2);
    file2->close();
    if (!setdoc) {/*return 0;*/}
    QDomElement docElem = doc.documentElement();                    //Get the root element
    if (docElem.tagName() != "gamestatus") {/*return 0;*/}          //Check file format
    QDomNodeList nodeList = docElem.elementsByTagName("savefiles"); //Get savefiles node
    for (int ii = 0; ii < nodeList.count(); ii++) {                 //Check each node one by one.
        QDomElement el = nodeList.at(ii).toElement();               //Get the current one as QDomElement
        QDomNode pEntries = el.firstChild();                        //Get all data for the element, by looping through all child elements
        int iii = 0;
        while (!pEntries.isNull() && iii <= 15) {
            QDomElement peData = pEntries.toElement();
            vector[ii][iii] = peData.text();
            if (el.attribute("block") == number) {
                if (iii == 15) {
                    vector[ii][iii] = Md5;
                } else if (isSlotModified(iii)) {
                    vector[ii][iii] = timestamp;   //We check the slot mod tracker to make the time update on all modified slots
                } else if (region(iii).isEmpty()) {
                    vector[ii][iii] = "";   //Clear timestamp for empty slot
                } else if (vector[ii][iii] == "") {
                    vector[ii][iii] = timestamp;   //Write the stamp (if no stamp is present and the slot isn't empty)
                }
            }
            pEntries = pEntries.nextSibling();
            iii++;
        }
    }
    return vector;
}

QVector< SubContainer > FF7Save::createMetadata(const QString &fileName, const QString &UserID)
{
    QVector< SubContainer > vector(10, SubContainer(16));
    QString Md5 = md5sum(fileName, UserID);

    QString timestamp = filetimestamp(fileName);
    QString number = fileblock(fileName);//Get file block number
    if (number == "-1") {
        return vector;
    }
    //Do foreach block
    for (int i = 0; i < 10; i++) {
        //if i is the current number then do each slot and md5
        if (i == number.toInt()) {
            for (int j = 0; j < 16; j++) {
                if (j == 15) {
                    vector[i][j] = Md5;
                } else if (isSlotModified(j)) {
                    vector[i][j] = timestamp;   //We check the slot mod tracker to make the time update on all modified slots
                } else if (region(j).isEmpty()) {
                    vector[i][j] = "";   //Clear timestamp for empty slot
                } else if (vector[i][j] == "") {
                    vector[i][j] = timestamp;   //Write the stamp (if no stamp is present and the slot isn't empty)
                }
            }
        }
    }
    return vector;
}
bool FF7Save::fixMetaData(QString fileName, QString UserID)
{
    if (fileName.isEmpty())
        fileName = filename;

    QString Path = fileName;
    Path.chop(Path.length() - Path.lastIndexOf("/"));
    QString metadataPath = Path;
    metadataPath.append("/metadata.xml");

    QFile Metadata(metadataPath);
    //is a New PC saveFile then
    QVector< SubContainer > vector(10, SubContainer(16));

    if (Metadata.exists()) {
        //get our user id no trailing / (removed above)
        Path.remove(0, Path.lastIndexOf("_") + 1);
        UserID = Path;
        vector = parseXML(fileName, metadataPath, UserID);
    } else {
        vector = createMetadata(fileName, UserID);
    }
    if (!Metadata.open(QIODevice::ReadWrite)) {
        return 0;
    }
    QTextStream out(&Metadata);
    Metadata.seek(0);//Set pointer to the Beggining
    out << QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    out << QString("<gamestatus>\n");
    //Do foreach block
    for (int i = 0; i < 10; i++) {
        out << (QString("  <savefiles block=\"%1\">\n").arg(QString::number(i + 1)));
        //Do foreach slot
        for (int j = 0; j < 15; j++) {
            out << (QString("    <timestamp slot=\"%1\">%2</timestamp>\n").arg(QString::number(j + 1), vector[i][j]));
        }
        out << (QString("    <signature>%1</signature>\n").arg(vector[i][15]));
        out << QString("  </savefiles>\n");
    }
    out << QString("</gamestatus>\n");
    Metadata.resize(Metadata.pos());
    Metadata.close();
    return 1;
}

QByteArray FF7Save::generatePsSaveSignature(QByteArray data, QByteArray keySeed)
{
    FF7SaveInfo::FORMAT saveFormat = format();
    if (saveFormat != FF7SaveInfo::FORMAT::PSP && saveFormat != FF7SaveInfo::FORMAT::PS3)
        return QByteArray();

    /* do signing stuff */
    const int signatureSize = FF7SaveInfo::instance()->fileSignatureSize(saveFormat);
    QByteArray buffer = keySeed;
    QByteArray decryptedKeySeed(0x40, '\x00');

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx,
                    reinterpret_cast<const uint8_t*>(FF7SaveInfo::instance()->signingKey(saveFormat).data()),
                    reinterpret_cast<const uint8_t*>(FF7SaveInfo::instance()->signingIV(saveFormat).data()));

    AES_ECB_decrypt(&ctx, reinterpret_cast<uint8_t*>(buffer.data()));

    decryptedKeySeed.replace(0, 0x10, buffer);
    buffer.replace(0, 0x10, keySeed);
    AES_ECB_encrypt(&ctx, reinterpret_cast<uint8_t*>(buffer.data()));
    decryptedKeySeed.replace(0x10, 0x10, buffer.data());
    XorWithIv(reinterpret_cast<uint8_t*>(decryptedKeySeed.data()), reinterpret_cast<const uint8_t*>(FF7SaveInfo::instance()->signingIV(saveFormat).constData()));
    buffer.resize(signatureSize);
    buffer.fill('\xFF', signatureSize);
    buffer.replace(0, 4, keySeed.mid(0x10, 4));
    QByteArray temp = decryptedKeySeed.mid(0x10);
    XorWithIv(reinterpret_cast<uint8_t*>(temp.data()), reinterpret_cast<const uint8_t*>(buffer.constData()));

    decryptedKeySeed.replace(0x10, 0x10, temp);
    temp = decryptedKeySeed;
    temp.resize(signatureSize);
    decryptedKeySeed.fill('\x00', 0x40);
    decryptedKeySeed.replace(0, signatureSize, temp);
    XorWithByte(reinterpret_cast<uint8_t*>(decryptedKeySeed.data()), 0x36, 0x40);

    QCryptographicHash sha1(QCryptographicHash::Sha1);
    sha1.addData(decryptedKeySeed);
    sha1.addData(data);
    buffer = sha1.result();

    XorWithByte(reinterpret_cast<uint8_t*>(decryptedKeySeed.data()), 0x6A, 0x40);

    sha1.reset();
    sha1.addData(decryptedKeySeed);
    sha1.addData(buffer);
    return sha1.result();
}
QString FF7Save::fileName(void)
{
    return filename;
}

QString FF7Save::fileblock(const QString &fileName)
{
    QString number = fileName;
    number.remove(0, number.lastIndexOf("/") + 5); //5=(/save)
    number.chop(4);
    bool isNumber = false;
    number = QString::number(number.toInt(&isNumber));
    if (isNumber) {
        return number;
    } else {
        return "-1";   //fail if not a number.
    }
}
QString FF7Save::filetimestamp(QString fileName)
{
    QFile tempFile(fileName);
    if (tempFile.exists()) {
        QFileInfo file(fileName);
        return QString::number(file.lastModified().toMSecsSinceEpoch());
    } else {
        return "";
    }
}
QByteArray FF7Save::slotFF7Data(int s)
{
    if (s < 0 || s > 14) {
        return QByteArray(0x00);
    }
    QByteArray temp;
    temp.setRawData(reinterpret_cast<char *>(&slot[s]), FF7SaveInfo::instance()->slotSize());
    return temp;
}
bool FF7Save::setSlotFF7Data(int s, QByteArray data)
{
    if (s < 0 || s > 14) {
        return false;
    }
    if (data.size() != FF7SaveInfo::instance()->slotSize()) {
        return false;
    }
    memcpy(&slot[s], data, FF7SaveInfo::instance()->slotSize());
    setFileModified(true, s);
    return true;
}

bool FF7Save::setSlotFF7Data(int s, const FF7SLOT &data)
{
    if (s < 0 || s > 14) {
        return false;
    }
    slot[s] = data;
    setFileModified(true, s);
    return true;
}

bool FF7Save::turtleParadiseFlyerSeen(int s, int flyer)
{
    if (s < 0 || s > 14) {
        return false;
    } else if (flyer < 0 || flyer > 7) {
        return false;
    } else {
        return ((slot[s].turtleflyers) & (1 << flyer));
    }
}
quint8 FF7Save::turtleParadiseFlyersSeen(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].turtleflyers;
    }
}

void FF7Save::setTurtleParadiseFlyerSeen(int s, int flyer, bool seen)
{
    if (s < 0 || s > 14) {
        return;
    } else if (flyer < 0 || flyer > 7) {
        return;
    } else {
        if (seen) {
            slot[s].turtleflyers |= (1 << flyer);
        } else {
            slot[s].turtleflyers &= ~(1 << flyer);
        }
        setFileModified(true, s);
    }
}
void FF7Save::setTurtleParadiseFlyersSeen(int s, quint8 flyersSeen)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        slot[s].turtleflyers = flyersSeen;
        setFileModified(true, s);
    }
}
bool FF7Save::itemMask1(int s, int bit)
{
    //the Bit Number to offset.
    if (bit < 0 || bit > 7) {
        return false;
    } else {
        return ((slot[s].itemsmask_1) & (1 << bit));
    }
}
void FF7Save::setItemMask1(int s, int bit, bool pickedUp)
{
    if (s < 0 || s > 14) {
        return;
    } else if (bit < 0 || bit > 7) {
        return;
    } else {
        if (pickedUp) {
            slot[s].itemsmask_1 |= (1 << bit);
        } else {
            slot[s].itemsmask_1 &= ~(1 << bit);
        }
        setFileModified(true, s);
    }
}

bool FF7Save::bmProgress1(int s, int bit)
{
    //the Bit Number to offset.
    if (bit < 0 || bit > 7) {
        return false;
    } else {
        return ((slot[s].bm_progress1) & (1 << bit));
    }
}
void FF7Save::setBmProgress1(int s, int bit, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else if (bit < 0 || bit > 7) {
        return;
    } else {
        if (isTrue) {
            slot[s].bm_progress1 |= (1 << bit);
        } else {
            slot[s].bm_progress1 &= ~(1 << bit);
        }
        setFileModified(true, s);
    }
}
void FF7Save::setBmProgress1(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        value = std::clamp(value, 0, 0xFF);
        if (value != slot[s].bm_progress1) {
            slot[s].bm_progress1 = value;
            setFileModified(true, s);
        }
    }
}
bool FF7Save::bmProgress2(int s, int bit)
{
    //the Bit Number to offset.
    if (bit < 0 || bit > 7) {
        return false;
    } else {
        return ((slot[s].bm_progress2) & (1 << bit));
    }
}
void FF7Save::setBmProgress2(int s, int bit, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else if (bit < 0 || bit > 7) {
        return;
    } else {
        if (isTrue) {
            slot[s].bm_progress2 |= (1 << bit);
        } else {
            slot[s].bm_progress2 &= ~(1 << bit);
        }
        setFileModified(true, s);
    }
}
void FF7Save::setBmProgress2(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        value = std::clamp(value, 0, 0xFF);
        if (value != slot[s].bm_progress3) {
            slot[s].bm_progress2 = value;
            setFileModified(true, s);
        }
    }
}
bool FF7Save::bmProgress3(int s, int bit)
{
    //the Bit Number to offset.
    if (bit < 0 || bit > 7) {
        return false;
    } else {
        return ((slot[s].bm_progress3) & (1 << bit));
    }
}
void FF7Save::setBmProgress3(int s, int bit, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else if (bit < 0 || bit > 7) {
        return;
    } else {
        if (isTrue) {
            slot[s].bm_progress3 |= (1 << bit);
        } else {
            slot[s].bm_progress3 &= ~(1 << bit);
        }
        setFileModified(true, s);
    }
}
void FF7Save::setBmProgress3(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        value = std::clamp(value, 0, 0xFF);
        if (value != slot[s].bm_progress3) {
            slot[s].bm_progress3 = value;
            setFileModified(true, s);
        }
    }
}

bool FF7Save::midgarTrainFlags(int s, int bit)
{
    //the Bit Number to offset.
    if (bit < 0 || bit > 7) {
        return false;
    } else {
        return ((slot[s].midgartrainflags) & (1 << bit));
    }
}
void FF7Save::setMidgarTrainFlags(int s, int bit, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else if (bit < 0 || bit > 7) {
        return;
    } else {
        if (isTrue) {
            slot[s].midgartrainflags |= (1 << bit);
        } else {
            slot[s].midgartrainflags &= ~(1 << bit);
        }
        setFileModified(true, s);
    }
}
void FF7Save::setMidgarTrainFlags(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        value = std::clamp(value, 0, 0xFF);
        if (value != slot[s].midgartrainflags) {
            slot[s].midgartrainflags = value;
            setFileModified(true, s);
        }
    }
}

QByteArray FF7Save::keyItems(int s)
{
    if (s < 0 || s > 14) {
        return QByteArray("\x00");
    } else {
        QByteArray temp;
        temp.setRawData(reinterpret_cast<char *>(&slot[s].keyitems), sizeof(slot[s].keyitems));
        return temp;
    }
}
bool FF7Save::keyItem(int s, int keyItem)
{
    if (s < 0 || s > 14) {
        return false;
    } else if (keyItem < 0 || keyItem > 51) {
        return false;
    } else {
        return ((slot[s].keyitems[keyItem / 8]) & (1 << (keyItem % 8)));
    }
}
void FF7Save::setKeyItem(int s, int keyItem, bool pickedUp)
{
    if (s < 0 || s > 14) {
        return ;
    } else if (keyItem < 0 || keyItem > 51) {
        return;
    } else {
        if (pickedUp) {
            slot[s].keyitems[keyItem / 8] |= (1 << (keyItem % 8));
        } else {
            slot[s].keyitems[keyItem / 8] &= ~(1 << (keyItem % 8));
        }
        setFileModified(true, s);
    }

}
bool FF7Save::setKeyItems(int s, QByteArray data)
{
    if (data.size() != sizeof(slot[s].keyitems)) {
        return false;
    } else {
        memcpy(&slot[s].keyitems, data, sizeof(slot[s].keyitems));
        setFileModified(true, s);
        return true;
    }
}
QByteArray FF7Save::unknown(int s, int z)
{
    if (s < 0 || s > 14) {
        return QByteArray(0x00);
    }
    QByteArray temp;
    switch (z) {
    case 1: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_1), sizeof(slot[s].z_1)); break;
    case 2: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_2), sizeof(slot[s].z_2)); break;
    case 3: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_3), sizeof(slot[s].z_3)); break;
    case 4: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_4), sizeof(slot[s].z_4)); break;
    case 5: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_5), sizeof(slot[s].z_5)); break;
    case 6: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_6), sizeof(slot[s].z_6)); break;
    case 7: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_7), sizeof(slot[s].z_7)); break;
    case 8: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_8), sizeof(slot[s].z_8)); break;
    case 9: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_9), sizeof(slot[s].z_9)); break;
    case 10: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_10), sizeof(slot[s].z_10)); break;
    case 11: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_11), sizeof(slot[s].z_11)); break;
    case 12: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_12), sizeof(slot[s].z_12)); break;
    case 13: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_13), sizeof(slot[s].z_13)); break;
    case 14: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_14), sizeof(slot[s].z_14)); break;
    case 15: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_15), sizeof(slot[s].z_15)); break;
    case 16: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_16), sizeof(slot[s].z_16)); break;
    case 17: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_17), sizeof(slot[s].z_17)); break;
    case 18: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_18), sizeof(slot[s].z_18)); break;
    case 19: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_19), sizeof(slot[s].z_19)); break;
    case 20: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_20), sizeof(slot[s].z_20)); break;
    case 21: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_21), sizeof(slot[s].z_21)); break;
    case 22: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_22), sizeof(slot[s].z_22)); break;
    case 23: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_23), sizeof(slot[s].z_23)); break;
    case 24: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_24), sizeof(slot[s].z_24)); break;
    case 25: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_25), sizeof(slot[s].z_25)); break;
    case 26: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_26), sizeof(slot[s].z_26)); break;
    case 27: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_27), sizeof(slot[s].z_27)); break;
    case 28: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_28), sizeof(slot[s].z_28)); break;
    case 29: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_29), sizeof(slot[s].z_29)); break;
    case 30: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_30), sizeof(slot[s].z_30)); break;
    case 31: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_31), sizeof(slot[s].z_31)); break;
    case 32: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_32), sizeof(slot[s].z_32)); break;
    case 33: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_33), sizeof(slot[s].z_33)); break;
    case 34: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_34), sizeof(slot[s].z_34)); break;
    case 35: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_35), sizeof(slot[s].z_35)); break;
    case 36: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_36), sizeof(slot[s].z_36)); break;
    case 37: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_37), sizeof(slot[s].z_37)); break;
    case 38: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_38), sizeof(slot[s].z_38)); break;
    case 39: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_39), sizeof(slot[s].z_39)); break;
    case 40: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_40), sizeof(slot[s].z_40)); break;
    case 41: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_41), sizeof(slot[s].z_41)); break;
    case 42: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_42), sizeof(slot[s].z_42)); break;
    case 43: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_43), sizeof(slot[s].z_43)); break;
    case 44: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_44), sizeof(slot[s].z_44)); break;
    case 45: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_45), sizeof(slot[s].z_45)); break;
    case 46: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_46), sizeof(slot[s].z_46)); break;
    case 47: temp.setRawData(reinterpret_cast<char *>(&slot[s].z_47), sizeof(slot[s].z_47)); break;
    default: temp.setRawData(0x00, 1); break;
    }
    return temp;
}

bool FF7Save::setUnknown(int s, int z, QByteArray data)
{
    if (s < 0 || s > 14) {
        return false;
    }
    bool result;
    switch (z) {
    case 1:
        if (data.size() != sizeof(slot[s].z_1)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_1, data, sizeof(slot[s].z_1));
            result = true;
            break;
        }
    case 2:
        if (data.size() != sizeof(slot[s].z_2)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_2, data, sizeof(slot[s].z_2));
            result = true;
            break;
        }
    case 3:
        if (data.size() != sizeof(slot[s].z_3)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_3, data, sizeof(slot[s].z_3));
            result = true;
            break;
        }
    case 4:
        if (data.size() != sizeof(slot[s].z_4)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_4, data, sizeof(slot[s].z_4));
            result = true;
            break;
        }
    case 5:
        if (data.size() != sizeof(slot[s].z_5)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_5, data, sizeof(slot[s].z_5));
            result = true;
            break;
        }
    case 6:
        if (data.size() != sizeof(slot[s].z_6)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_6, data, sizeof(slot[s].z_6));
            result = true;
            break;
        }
    case 7:
        if (data.size() != sizeof(slot[s].z_7)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_7, data, sizeof(slot[s].z_7));
            result = true;
            break;
        }
    case 8:
        if (data.size() != sizeof(slot[s].z_8)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_8, data, sizeof(slot[s].z_8));
            result = true;
            break;
        }
    case 9:
        if (data.size() != sizeof(slot[s].z_9)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_9, data, sizeof(slot[s].z_9));
            result = true;
            break;
        }
    case 10:
        if (data.size() != sizeof(slot[s].z_10)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_10, data, sizeof(slot[s].z_10));
            result = true;
            break;
        }
    case 11:
        if (data.size() != sizeof(slot[s].z_11)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_11, data, sizeof(slot[s].z_11));
            result = true;
            break;
        }
    case 12:
        if (data.size() != sizeof(slot[s].z_12)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_12, data, sizeof(slot[s].z_12));
            result = true;
            break;
        }
    case 13:
        if (data.size() != sizeof(slot[s].z_13)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_13, data, sizeof(slot[s].z_13));
            result = true;
            break;
        }
    case 14:
        if (data.size() != sizeof(slot[s].z_14)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_14, data, sizeof(slot[s].z_14));
            result = true;
            break;
        }
    case 15:
        if (data.size() != sizeof(slot[s].z_15)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_15, data, sizeof(slot[s].z_15));
            result = true;
            break;
        }
    case 16:
        if (data.size() != sizeof(slot[s].z_16)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_16, data, sizeof(slot[s].z_16));
            result = true;
            break;
        }
    case 17:
        if (data.size() != sizeof(slot[s].z_17)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_17, data, sizeof(slot[s].z_17));
            result = true;
            break;
        }
    case 18:
        if (data.size() != sizeof(slot[s].z_18)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_18, data, sizeof(slot[s].z_18));
            result = true;
            break;
        }
    case 19:
        if (data.size() != sizeof(slot[s].z_19)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_19, data, sizeof(slot[s].z_19));
            result = true;
            break;
        }
    case 20:
        if (data.size() != sizeof(slot[s].z_20)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_20, data, sizeof(slot[s].z_20));
            result = true;
            break;
        }
    case 21:
        if (data.size() != sizeof(slot[s].z_21)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_21, data, sizeof(slot[s].z_21));
            result = true;
            break;
        }
    case 22:
        if (data.size() != sizeof(slot[s].z_22)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_22, data, sizeof(slot[s].z_22));
            result = true;
            break;
        }
    case 23:
        if (data.size() != sizeof(slot[s].z_23)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_23, data, sizeof(slot[s].z_23));
            result = true;
            break;
        }
    case 24:
        if (data.size() != sizeof(slot[s].z_24)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_24, data, sizeof(slot[s].z_24));
            result = true;
            break;
        }
    case 25:
        if (data.size() != sizeof(slot[s].z_25)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_25, data, sizeof(slot[s].z_25));
            result = true;
            break;
        }
    case 26:
        if (data.size() != sizeof(slot[s].z_26)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_26, data, sizeof(slot[s].z_26));
            result = true;
            break;
        }
    case 27:
        if (data.size() != sizeof(slot[s].z_27)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_27, data, sizeof(slot[s].z_27));
            result = true;
            break;
        }
    case 28:
        if (data.size() != sizeof(slot[s].z_28)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_28, data, sizeof(slot[s].z_28));
            result = true;
            break;
        }
    case 29:
        if (data.size() != sizeof(slot[s].z_29)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_29, data, sizeof(slot[s].z_29));
            result = true;
            break;
        }
    case 30:
        if (data.size() != sizeof(slot[s].z_30)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_30, data, sizeof(slot[s].z_30));
            result = true;
            break;
        }
    case 31:
        if (data.size() != sizeof(slot[s].z_31)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_31, data, sizeof(slot[s].z_31));
            result = true;
            break;
        }
    case 32:
        if (data.size() != sizeof(slot[s].z_32)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_32, data, sizeof(slot[s].z_32));
            result = true;
            break;
        }
    case 33:
        if (data.size() != sizeof(slot[s].z_33)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_33, data, sizeof(slot[s].z_33));
            result = true;
            break;
        }
    case 34:
        if (data.size() != sizeof(slot[s].z_34)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_34, data, sizeof(slot[s].z_34));
            result = true;
            break;
        }
    case 35:
        if (data.size() != sizeof(slot[s].z_35)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_35, data, sizeof(slot[s].z_35));
            result = true;
            break;
        }
    case 36:
        if (data.size() != sizeof(slot[s].z_36)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_36, data, sizeof(slot[s].z_36));
            result = true;
            break;
        }
    case 37:
        if (data.size() != sizeof(slot[s].z_37)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_37, data, sizeof(slot[s].z_37));
            result = true;
            break;
        }
    case 38:
        if (data.size() != sizeof(slot[s].z_38)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_38, data, sizeof(slot[s].z_38));
            result = true;
            break;
        }
    case 39:
        if (data.size() != sizeof(slot[s].z_39)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_39, data, sizeof(slot[s].z_39));
            result = true;
            break;
        }
    case 40:
        if (data.size() != sizeof(slot[s].z_40)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_40, data, sizeof(slot[s].z_40));
            result = true;
            break;
        }
    case 41:
        if (data.size() != sizeof(slot[s].z_41)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_41, data, sizeof(slot[s].z_41));
            result = true;
            break;
        }
    case 42:
        if (data.size() != sizeof(slot[s].z_42)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_42, data, sizeof(slot[s].z_42));
            result = true;
            break;
        }
    case 43:
        if (data.size() != sizeof(slot[s].z_43)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_43, data, sizeof(slot[s].z_43));
            result = true;
            break;
        }
    case 44:
        if (data.size() != sizeof(slot[s].z_44)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_44, data, sizeof(slot[s].z_44));
            result = true;
            break;
        }
    case 45:
        if (data.size() != sizeof(slot[s].z_45)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_45, data, sizeof(slot[s].z_45));
            result = true;
            break;
        }
    case 46:
        if (data.size() != sizeof(slot[s].z_46)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_46, data, sizeof(slot[s].z_46));
            result = true;
            break;
        }
    case 47:
        if (data.size() != sizeof(slot[s].z_47)) {
            result = false;
            break;
        } else {
            memcpy(&slot[s].z_47, data, sizeof(slot[s].z_47));
            result = true;
            break;
        }
    default: result = false; break;
    }
    setFileModified(true, s);
    return result;
}

bool FF7Save::soundMode(int s)
{
    return (slot[s].options & (1 << 0));
}

void FF7Save::setSoundMode(int s, int mode)
{
    if (!(mode && soundMode(s))) {
        switch (mode) {
        case SOUND_MONO: slot[s].options &= ~(1 << 0); break;
        case SOUND_STEREO: slot[s].options |= (1 << 0);   break;
        default: slot[s].options &= ~(1 << 0) ; break;
        }
        setFileModified(true, s);
    }
}
void FF7Save::setSoundMode(int s, bool mode)
{
    if (!(mode && soundMode(s))) {
        if (mode) {
            slot[s].options |= (1 << 0);
        } else {
            slot[s].options &= ~(1 << 0);
        }
        setFileModified(true, s);
    }
}

bool FF7Save::controlMode(int s)
{
    return (slot[s].options & (1 << 2));
}
void FF7Save::setControlMode(int s, int mode)
{
    if (!(mode && controlMode(s))) {
        switch (mode) {
        case CONTROL_NORMAL: slot[s].options &= ~(1 << 2); break;
        case CONTROL_CUSTOM: slot[s].options |= (1 << 2);   break;
        default: slot[s].options &= ~(1 << 2) ; break;
        }
        setFileModified(true, s);
    }
}

void FF7Save::setControlMode(int s, bool mode)
{
    if (!(mode && controlMode(s))) {
        if (mode) {
            slot[s].options |= (1 << 2);
        } else {
            slot[s].options &= ~(1 << 2);
        }
        setFileModified(true, s);
    }
}
bool FF7Save::cursorMode(int s)
{
    return (slot[s].options & (1 << 4));
}

void FF7Save::setCursorMode(int s, int mode)
{
    if (!(mode && cursorMode(s))) {
        switch (mode) {
        case CURSOR_INITIAL: slot[s].options &= ~(1 << 4); break;
        case CURSOR_MEMORY: slot[s].options |= (1 << 4);   break;
        default: slot[s].options &= ~(1 << 2) ; break;
        }
        setFileModified(true, s);
    }
}
void FF7Save::setCursorMode(int s,  bool mode)
{
    if (mode != cursorMode(s)) {
        if (mode) {
            slot[s].options |= (1 << 4);
        } else {
            slot[s].options &= ~(1 << 4);
        }
        setFileModified(true, s);
    }
}
int FF7Save::atbMode(int s)
{
    if ((slot[s].options & (1 << 6))) {
        return 1;
    } else if ((slot[s].options & (1 << 7))) {
        return 2;
    } else {
        return 0;
    }
}

void FF7Save::setAtbMode(int s, int mode)
{
    if (mode != atbMode(s)) {
        switch (mode) {
        case ATB_ACTIVE: slot[s].options &= ~(1 << 6); slot[s].options &= ~(1 << 7); break;
        case ATB_RECOMMENED:  slot[s].options |= (1 << 6); slot[s].options &= ~(1 << 7); break;
        case ATB_WAIT: slot[s].options &= ~(1 << 6); slot[s].options |= (1 << 7); break;
        default: slot[s].options &= ~(1 << 6); slot[s].options &= ~(1 << 7); break;
        }
        setFileModified(true, s);
    }
}
bool FF7Save::cameraMode(int s)
{
    return (slot[s].options & (1 << 8));
}

void FF7Save::setCameraMode(int s, int mode)
{
    if (!(mode && cameraMode(s))) {
        switch (mode) {
        case CAMERA_AUTO: slot[s].options &= ~(1 << 8); break;
        case CAMERA_FIXED: slot[s].options |= (1 << 8); break;
        }
        setFileModified(true, s);
    }
}
void FF7Save::setCameraMode(int s, bool mode)
{
    if (!(mode && cameraMode(s))) {
        if (mode) {
            slot[s].options |= (1 << 8);
        } else {
            slot[s].options &= ~(1 << 8);
        }
        setFileModified(true, s);
    }
}
int FF7Save::magicOrder(int s)
{
    if ((slot[s].options & (1 << 10)) && (slot[s].options & (1 << 11))) {
        return 3;
    }
    if ((slot[s].options & (1 << 10)) && (slot[s].options & (1 << 12))) {
        return 5;
    } else if (slot[s].options & (1 << 10)) {
        return 1;
    } else if ((slot[s].options & (1 << 11))) {
        return 2;
    } else if ((slot[s].options & (1 << 12))) {
        return 4;
    } else {
        return 0;
    }
}

void FF7Save::setMagicOrder(int s, int order)
{
    if (order != magicOrder(s))
        switch (order) {
        case MAGIC_RAI: slot[s].options &= ~(1 << 10); slot[s].options &= ~(1 << 11); slot[s].options &= ~(1 << 12); break;
        case MAGIC_RIA: slot[s].options |= (1 << 10); slot[s].options &= ~(1 << 11); slot[s].options &= ~(1 << 12); break;
        case MAGIC_AIR: slot[s].options &= ~(1 << 10); slot[s].options |= (1 << 11); slot[s].options &= ~(1 << 12); break;
        case MAGIC_ARI: slot[s].options |= (1 << 10); slot[s].options |= (1 << 11); slot[s].options &= ~(1 << 12); break;
        case MAGIC_IRA: slot[s].options &= ~(1 << 10); slot[s].options &= ~(1 << 11); slot[s].options |= (1 << 12); break;
        case MAGIC_IAR: slot[s].options |= (1 << 10); slot[s].options &= ~(1 << 11); slot[s].options |= (1 << 12); break;
        default: slot[s].options &= ~(1 << 10); slot[s].options &= ~(1 << 11); slot[s].options &= ~(1 << 12); break;
        }
    setFileModified(true, s);
}

bool FF7Save::battleHelp(int s)
{
    return ((slot[s].options) & (1 << 14));
}

void FF7Save::setBattleHelp(int s, bool shown)
{
    if (!(shown && battleHelp(s))) {
        if (shown) {
            slot[s].options |= (1 << 14);
        } else {
            slot[s].options &= ~(1 << 14);
        }
        setFileModified(true, s);
    }
}

int FF7Save::battleSpeed(int s)
{
    return slot[s].battlespeed;
}
void FF7Save::setBattleSpeed(int s, int speed)
{
    speed = std::clamp(speed, 0, 255);
    if (speed != slot[s].battlespeed) {
        slot[s].battlespeed = speed;
        setFileModified(true, s);
    }
}

int FF7Save::messageSpeed(int s)
{
    return slot[s].fieldmspeed;
}
void FF7Save::setMessageSpeed(int s, int speed)
{
    speed = std::clamp(speed, 0, 255);
    if (speed != slot[s].fieldmspeed) {
        slot[s].fieldmspeed = speed;
        setFileModified(true, s);
    }
}

int FF7Save::battleMessageSpeed(int s)
{
    return slot[s].battlemspeed;
}
void FF7Save::setBattleMessageSpeed(int s, int speed)
{
    speed = std::clamp(speed, 0, 255);
    if (speed != slot[s].battlemspeed) {
        slot[s].battlemspeed = speed;
        setFileModified(true, s);
    }
}
bool FF7Save::fieldHelp(int s)
{
    return ((slot[s].field_help) & (1 << 0));
}
void FF7Save::setFieldHelp(int s, bool shown)
{
    if (!(shown && fieldHelp(s))) {
        if (shown) {
            slot[s].field_help |= (1 << 0);
        } else {
            slot[s].field_help &= ~(1 << 0);
        }
        setFileModified(true, s);
    }
}
bool FF7Save::battleTargets(int s)
{
    return ((slot[s].tut_sub) & (1 << 6));
}
void FF7Save::setBattleTargets(int s, bool shown)
{
    if (!(shown && battleTargets(s))) {
        if (shown) {
            slot[s].tut_sub |= (1 << 6);
        } else {
            slot[s].tut_sub &= ~(1 << 6);
        }
        setFileModified(true, s);
    }
}

quint16 FF7Save::options(int s)
{
    return  qFromLittleEndian(slot[s].options);
}
void FF7Save::setOptions(int s, int opt)
{
    if (opt != options(s)) {
        opt = qToLittleEndian(opt);
        slot[s].options = opt;
        setFileModified(true, s);
    }
}
QByteArray FF7Save::controllerMapping(int s)
{
    QByteArray temp;
    for (int i = 0; i < 16; i++) {
        temp.append(slot[s].controller_map[i]);
    }
    return temp;
}
quint8 FF7Save::controllerMapping(int s, int action)
{
    return slot[s].controller_map[action];
}

void FF7Save::setControllerMapping(int s, QByteArray map)
{
    if (map.length() > 16) {
        map.chop(16);
    }
    if (map != controllerMapping(s)) {
        memcpy(&slot[s].controller_map, map, 16);
        setFileModified(true, s);
    }
}
void FF7Save::setControllerMapping(int s, int action,  int button)
{
    if (button < 0 || button > 15) {
        return;
    } else {
        if (slot[s].controller_map[action] != button) {
            slot[s].controller_map[action] = button;
            setFileModified(true, s);
        }
    }
}
bool FF7Save::phsVisible(int s, int who)
{
    if (s < 0 || s > 14) {
        return false;
    }
    if (who < 0 || who > 8) {
        return false;
    } else {
        return ((slot[s].phsvisible) & (1 << who));
    }
}
void FF7Save::setPhsVisible(int s, int who, bool checked)
{
    if (s < 0 || s > 14) {
        return;
    } else if (who < 0 || who > 8) {
        return;
    } else {
        if (checked) {
            slot[s].phsvisible |= (1 << who);
        } else {
            slot[s].phsvisible &= ~(1 << who);
        }
        setFileModified(true, s);
    }
}
void FF7Save::setPhsVisible(int s, quint16 phs_visible)
{
    if (s < 0 || s > 14) {
        return;
    }
    if (phs_visible != slot[s].phsvisible) {
        phs_visible = qToLittleEndian(phs_visible);
        slot[s].phsvisible = phs_visible;
        setFileModified(true, s);
    }
}
quint16 FF7Save::phsVisible(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].phsvisible);
    }
}

bool FF7Save::phsAllowed(int s, int who)
{
    if (s < 0 || s > 14) {
        return false;
    }
    if (who < 0 || who > 8) {
        return false;
    } else {
        return ((slot[s].phsallowed) & (1 << who));
    }
}
quint16 FF7Save::phsAllowed(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].phsallowed);
    }
}

void FF7Save::setPhsAllowed(int s, int who, bool checked)
{
    if (s < 0 || s > 14) {
        return;
    } else if (who < 0 || who > 8) {
        return;
    } else {
        if (checked) {
            slot[s].phsallowed |= (1 << who);
        } else {
            slot[s].phsallowed &= ~(1 << who);
        }
        setFileModified(true, s);
    }
}
void FF7Save::setPhsAllowed(int s, quint16 phs_visible)
{
    if (s < 0 || s > 14) {
        return;
    }
    if (phs_visible != slot[s].phsallowed) {
        phs_visible = qToLittleEndian(phs_visible);
        slot[s].phsallowed = phs_visible;
        setFileModified(true, s);
    }
}
bool FF7Save::menuVisible(int s, int index)
{
    if (s < 0 || s > 14) {
        return false;
    }
    if (index < 0 || index > 9) {
        return false;
    } else {
        return ((slot[s].menu_visible) & (1 << index));
    }
}
void FF7Save::setMenuVisible(int s, int index, bool checked)
{
    if (s < 0 || s > 14) {
        return;
    } else if (index < 0 || index > 9) {
        return;
    } else {
        if (checked) {
            slot[s].menu_visible |= (1 << index);
        } else {
            slot[s].menu_visible &= ~(1 << index);
        }
        setFileModified(true, s);
    }
}
void FF7Save::setMenuVisible(int s, quint16 menu_visible)
{
    if (s < 0 || s > 14) {
        return;
    }
    if (menu_visible != slot[s].menu_visible) {
        menu_visible = qToLittleEndian(menu_visible);
        slot[s].menu_visible = menu_visible;
        setFileModified(true, s);
    }
}
quint16 FF7Save::menuVisible(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].menu_visible);
    }
}

bool FF7Save::menuLocked(int s, int index)
{
    if (s < 0 || s > 14) {
        return false;
    }
    if (index < 0 || index > 9) {
        return false;
    } else {
        return ((slot[s].menu_locked) & (1 << index));
    }
}
void FF7Save::setMenuLocked(int s, int index, bool checked)
{
    if (s < 0 || s > 14) {
        return;
    } else if (index < 0 || index > 9) {
        return;
    } else {
        if (checked) {
            slot[s].menu_locked |= (1 << index);
        } else {
            slot[s].menu_locked &= ~(1 << index);
        }
        setFileModified(true, s);
    }
}
void FF7Save::setMenuLocked(int s, quint16 menu_locked)
{
    if (s < 0 || s > 14) {
        return;
    }
    if (menu_locked != slot[s].menu_locked) {
        menu_locked = qToLittleEndian(menu_locked);
        slot[s].menu_locked = menu_locked;
        setFileModified(true, s);
    }
}
quint16 FF7Save::menuLocked(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].menu_locked);
    }
}
quint16 FF7Save::locationId(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].locationid);
    }
}

void FF7Save::setLocationId(int s, quint16 locationID)
{
    if (s < 0 || s > 14) {
        return;
    } else if (locationID == locationId(s)) {
        return;
    } else {
        locationID = qToLittleEndian(locationID);
        slot[s].locationid = locationID;
        setFileModified(true, s);
    }
}
quint16 FF7Save::mapId(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].mapid);
    }
}

void FF7Save::setMapId(int s, quint16 mapID)
{
    if (s < 0 || s > 14) {
        return;
    } else if (mapID == mapId(s)) {
        return;
    } else {
        mapID = qToLittleEndian(mapID);
        slot[s].mapid = mapID;
        setFileModified(true, s);
    }
}
qint16 FF7Save::locationX(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].coord.x);
    }
}

void FF7Save::setLocationX(int s, qint16 x)
{
    if (s < 0 || s > 14) {
        return;
    } else if (x == locationX(s)) {
        return;
    } else {
        x = qToLittleEndian(x);
        slot[s].coord.x = x;
        setFileModified(true, s);
    }
}
qint16 FF7Save::locationY(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].coord.y);
    }
}

void FF7Save::setLocationY(int s, qint16 y)
{
    if (s < 0 || s > 14) {
        return;
    } else if (y == locationY(s)) {
        return;
    } else {
        y = qToLittleEndian(y);
        slot[s].coord.y = y;
        setFileModified(true, s);
    }
}
quint16 FF7Save::locationT(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].coord.t);
    }
}

void FF7Save::setLocationT(int s, quint16 t)
{
    if (s < 0 || s > 14) {
        return;
    } else if (t == locationT(s)) {
        return;
    } else {
        t = qToLittleEndian(t);
        slot[s].coord.t = t;
        setFileModified(true, s);
    }
}
quint8 FF7Save::locationD(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].coord.d);
    }
}

void FF7Save::setLocationD(int s, quint8 d)
{
    if (s < 0 || s > 14) {
        return;
    } else if (d == locationD(s)) {
        return;
    } else {
        d = qToLittleEndian(d);
        slot[s].coord.d = d;
        setFileModified(true, s);
    }
}

quint16 FF7Save::condorFunds(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].condorfunds);
    }
}
void FF7Save::setCondorFunds(int s, quint16 value)
{
    if (value == condorFunds(s)) {
        return;
    } else {
        value = qToLittleEndian(value);
        slot[s].condorfunds = value;
        setFileModified(true, s);
    }
}
quint8 FF7Save::condorWins(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return  slot[s].condorwins;
    }
}
void FF7Save::setCondorWins(int s, quint8 wins)
{
    if (wins == condorWins(s)) {
        return;
    } else {
        slot[s].condorwins = wins;
        setFileModified(true, s);
    }
}
quint8 FF7Save::condorLosses(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return  slot[s].condorlosses;
    }
}
void FF7Save::setCondorLosses(int s, quint8 losses)
{
    if (losses == condorLosses(s)) {
        return;
    } else {
        slot[s].condorlosses = losses;
        setFileModified(true, s);
    }
}

QList<FF7CHOCOBO> FF7Save::chocobos(int s)
{
    QList<FF7CHOCOBO> chocos;
    for (int i = 0; i < 6; i++) {
        chocos.append(chocobo(s, i));
    }
    return chocos;
}

QList<quint16> FF7Save::chocobosStaminas(int s)
{
    QList<quint16> stamina;
    for (int i = 0; i < 6; i++) {
        stamina.append(this->chocoStamina(s, i));
    }
    return stamina;
}

QList<QString> FF7Save::chocobosNames(int s)
{
    QList<QString> names;
    for (int i = 0; i < 6; i++) {
        names.append(chocoName(s, i));
    }
    return names;
}
QList<bool> FF7Save::chocoboCantMates(int s)
{
    QList<bool> mates;
    for (int i = 0; i < 6; i++) {
        mates.append(chocoCantMate(s, i));
    }
    return mates;
}
qint8 FF7Save::stablesOwned(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].stables;
    }
}
void FF7Save::setStablesOwned(int s, qint8 value)
{
    if (s < 0 || s > 14) {
        return;
    } else if (value < 0 || value > 6) {
        return;
    } else {
        slot[s].stables = value;
        setFileModified(true, s);
    }
}

qint8 FF7Save::stablesOccupied(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].stablesoccupied;
    }
}
void FF7Save::setStablesOccupied(int s, qint8 value)
{
    if (s < 0 || s > 14) {
        return;
    } else if (value < 0 || value > 6) {
        return;
    } else {
        slot[s].stablesoccupied = value;
        setFileModified(true, s);
    }
}

qint8 FF7Save::stableMask(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].chocobomask;
    }
}

void FF7Save::setStableMask(int s, qint8 value)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        slot[s].chocobomask = value;
        setFileModified(true, s);
    }
}

QList<qint8> FF7Save::chocoboPens(int s)
{
    QList<qint8> pens;
    for (int i = 0; i < 4; i++) {
        pens.append(slot[s].pennedchocos[i]);
    }
    return pens;
}
qint8 FF7Save::chocoboPen(int s, int pen)
{
    if (s < 0 || s > 14 || pen < 0 || pen > 3) {
        return 0;
    } else {
        return slot[s].pennedchocos[pen];
    }
}
void FF7Save::setChocoboPen(int s, int pen, int value)
{
    if (s < 0 || s > 14 || pen < 0 || pen > 3 || value < 0 || value > 8) {
        return;
    } else {
        slot[s].pennedchocos[pen] = value; setFileModified(true, s);
    }
}
quint32 FF7Save::countdownTimer(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return quint32(slot[s].timer[0] | (slot[s].timer[1] << 8) | (slot[s].timer[2] << 16));
    }
}
void FF7Save::setCountdownTimer(int s, quint32 time)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        time = qToLittleEndian(time);
        slot[s].timer[0] = (time & 0xff);
        slot[s].timer[1] = ((time & 0xff00) >> 8);
        slot[s].timer[2] = ((time & 0xff0000) >> 16);
        setFileModified(true, s);
    }
}
bool FF7Save::seenPandorasBox(int s)
{
    if (s < 0 || s > 14) {
        return false;
    } else {
        return (slot[s].seenpandora & (1 << 0));
    }
}
void FF7Save::setSeenPandorasBox(int s, bool seen)
{
    if (seen) {
        slot[s].seenpandora |= (1 << 0);
    } else {
        slot[s].seenpandora &= ~(1 << 0);
    }
    setFileModified(true, s);
}
quint16 FF7Save::steps(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return qFromLittleEndian(slot[s].steps);
    }
}
void FF7Save::setSteps(int s, int steps)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        steps = std::clamp(steps, 0, 0xFFFF);
        if (steps != slot[s].mprogress) {
            steps = qToLittleEndian(steps);
            slot[s].steps = steps;
            setFileModified(true, s);
        }
    }
}
quint8 FF7Save::churchProgress(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].aeris_church;
    }
}
void FF7Save::setChurchProgress(int s, int progress)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        progress = std::clamp(progress, 0, 0xFF);
        if (progress != slot[s].aeris_church) {
            slot[s].aeris_church = progress;
            setFileModified(true, s);
        }
    }
}

quint8 FF7Save::donProgress(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].donprogress;
    }
}
void FF7Save::setDonProgress(int s, int progress)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        progress = std::clamp(progress, 0, 0xFF);
        if (progress != slot[s].donprogress) {
            slot[s].donprogress = progress;
            setFileModified(true, s);
        }
    }
}
bool FF7Save::startBombingMission(int s)
{
    if (s < 0 || s > 14) {
        return false;
    } else {
        if (slot[s].intbombing == 0x14) {
            return true;
        } else {
            return false;
        }
    }
}
void FF7Save::setStartBombingMission(int s, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else {

        if (isTrue && slot[s].intbombing != 0x14) {
            slot[s].intbombing = 0x14;
            setFileModified(true, s);
        } else {
            if (slot[s].intbombing != 0x56) {
                slot[s].intbombing = 0x56;
                setFileModified(true, s);
            }
        }
    }
}
quint32 FF7Save::uWeaponHp(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return quint32(slot[s].u_weapon_hp[0] | (slot[s].u_weapon_hp[1] << 8) | (slot[s].u_weapon_hp[2] << 16));
    }
}
void FF7Save::setUWeaponHp(int s, int hp)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        if (quint32(hp) != uWeaponHp(s)) {
            hp = qToLittleEndian(hp);
            int a = (hp & 0xff);
            int b = (hp & 0xff00) >> 8;
            int c = (hp & 0xff0000) >> 16;
            slot[s].u_weapon_hp[0] = a;
            slot[s].u_weapon_hp[1] = b;
            slot[s].u_weapon_hp[2] = c;
            setFileModified(true, s);
        }
    }
}
bool FF7Save::killedEmeraldWeapon(int s)
{
    if (s < 0 || s > 14) {
        return false;
    } else {
        if ((slot[s].ruby_emerald) & (1 << 4)) {
            return true;
        } else {
            return false;
        }
    }
}
void FF7Save::setKilledEmeraldWeapon(int s, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        if (isTrue != killedEmeraldWeapon(s)) {
            if (isTrue) {
                slot[s].ruby_emerald |= (1 << 4);
            } else {
                slot[s].ruby_emerald &= ~(1 << 4);
            }
            setFileModified(true, s);
        }
    }
}

bool FF7Save::killedRubyWeapon(int s)
{
    if (s < 0 || s > 14) {
        return false;
    } else {
        if ((slot[s].ruby_emerald) & (1 << 3)) {
            return true;
        } else {
            return false;
        }
    }
}

void FF7Save::setKilledRubyWeapon(int s, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        if (isTrue != killedRubyWeapon(s)) {
            if (isTrue) {
                slot[s].ruby_emerald |= (1 << 3);
            } else {
                slot[s].ruby_emerald &= ~(1 << 3);
            }
            setFileModified(true, s);
        }
    }
}
quint8 FF7Save::tutSave(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].tut_save;
    }
}
void FF7Save::setTutSave(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != slot[s].tut_save) {
        slot[s].tut_save = value;
        setFileModified(true, s);
    }
}
bool FF7Save::canFightNinjaInForest(int s)
{
    if (s < 0 || s > 14) {
        return false;
    } else {
        return (slot[s].yuffieforest) & (1 << 0);
    }
}
void FF7Save::setCanFightNinjaInForest(int s, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        if (isTrue != canFightNinjaInForest(s)) {
            if (isTrue) {
                slot[s].yuffieforest |= (1 << 0);
            } else {
                slot[s].yuffieforest &= ~(1 << 0);
            }
            setFileModified(true, s);
        }
    }
}
quint8 FF7Save::tutSub(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].tut_sub;
    }
}
bool FF7Save::tutSub(int s, int bit)
{
    //the Bit Number to offset.
    if (bit < 0 || bit > 7) {
        return false;
    } else {
        return ((slot[s].tut_sub) & (1 << bit));
    }
}
void FF7Save::setTutSub(int s, int bit, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else if (bit < 0 || bit > 7) {
        return;
    } else if (bit == 6) {
        setBattleTargets(s, isTrue);
    } else {
        if (isTrue) {
            slot[s].tut_sub |= (1 << bit);
        } else {
            slot[s].tut_sub &= ~(1 << bit);
        }
        setFileModified(true, s);
    }
}
void FF7Save::setTutSub(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        value = std::clamp(value, 0, 0xFF);
        if (value != slot[s].tut_sub) {
            slot[s].tut_sub = value;
            setFileModified(true, s);
        }
    }
}
bool FF7Save::yuffieUnlocked(int s)
{
    if (s < 0 || s > 14) {
        return false;
    } else {
        return (slot[s].reg_yuffie & (1 << 0));
    }
}
void FF7Save::setYuffieUnlocked(int s, bool isUnlocked)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        if (isUnlocked) {
            slot[s].reg_yuffie |= (1 << 0);
        } else {
            slot[s].reg_yuffie &= ~(1 << 0);
        }
        setFileModified(true, s);
    }
}

bool FF7Save::vincentUnlocked(int s)
{
    if (s < 0 || s > 14) {
        return false;
    } else {
        return (slot[s].reg_vinny & (1 << 2));
    }
}

void FF7Save::setVincentUnlocked(int s, bool isUnlocked)
{
    if (s < 0 || s > 14) {
        return;
    } else {
        if (isUnlocked) {
            slot[s].reg_vinny |= (1 << 2);
        } else {
            slot[s].reg_vinny &= ~(1 << 2);
        }
        setFileModified(true, s);
    }
}

bool FF7Save::worldChocobo(int s, int bit)
{
    //the Bit Number to offset.
    if (bit < 0 || bit > 7) {
        return false;
    } else {
        return ((slot[s].world_map_chocobos) & (1 << bit));
    }
}

void FF7Save::setWorldChocobo(int s, int bit, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else if (bit < 0 || bit > 7) {
        return;
    } else {
        if (isTrue) {
            slot[s].world_map_chocobos |= (1 << bit);
        } else {
            slot[s].world_map_chocobos &= ~(1 << bit);
        }
        setFileModified(true, s);
    }
}

bool FF7Save::worldVehicle(int s, int bit)
{
    //the Bit Number to offset.
    if (bit < 0 || bit > 7) {
        return false;
    } else {
        return ((slot[s].world_map_vehicles) & (1 << bit));
    }
}

void FF7Save::setWorldVehicle(int s, int bit, bool isTrue)
{
    if (s < 0 || s > 14) {
        return;
    } else if (bit < 0 || bit > 7) {
        return;
    } else {
        if (isTrue) {
            slot[s].world_map_vehicles |= (1 << bit);
        } else {
            slot[s].world_map_vehicles &= ~(1 << bit);
        }
        setFileModified(true, s);
    }
}
quint32 FF7Save::worldCoordsLeader(int s, bool firstChunk)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        if (firstChunk) {
            return slot[s].l_world;
        } else {
            return slot[s].l_world2;
        }
    }
}
int FF7Save::worldCoordsLeaderX(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return (slot[s].l_world & 0x7FFFF);
    }
}
int FF7Save::worldCoordsLeaderID(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].l_world >> 19) & 0x1F);
    }
}
int FF7Save::worldCoordsLeaderAngle(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].l_world) >> 24);
    }
}
int FF7Save::worldCoordsLeaderY(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].l_world2) & 0x3FFFF);
    }
}
int FF7Save::worldCoordsLeaderZ(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].l_world2) >> 18);
    }
}
void FF7Save::setWorldCoordsLeader(int s, bool firstChunk, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFFFF);
    if (firstChunk && quint32(value) != worldCoordsLeader(s, true)) {
        slot[s].l_world = quint32(value);
        setFileModified(true, s);
    } else {
        if (quint32(value) != worldCoordsLeader(s, false)) {
            slot[s].l_world2 = quint32(value);
            setFileModified(true, s);
        }
    }
}
void FF7Save::setWorldCoordsLeaderX(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 295000);
    if (value != worldCoordsLeaderX(s)) {
        slot[s].l_world = quint32(value | worldCoordsLeaderID(s) << 19 | worldCoordsLeaderAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsLeaderID(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsLeaderID(s)) {
        slot[s].l_world = quint32(worldCoordsLeaderX(s) | value << 19 | worldCoordsLeaderAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsLeaderAngle(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 360);
    if (value != worldCoordsLeaderAngle(s)) {
        slot[s].l_world = quint32(worldCoordsLeaderX(s) | worldCoordsLeaderID(s) << 19 | value << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsLeaderY(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 230000);
    if (value != worldCoordsLeaderY(s)) {
        slot[s].l_world2 = quint32(value | worldCoordsLeaderZ(s) << 18);
        setFileModified(true, s);
    }

}
void FF7Save::setWorldCoordsLeaderZ(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsLeaderZ(s)) {
        slot[s].l_world2 = quint32(worldCoordsLeaderY(s) | value << 18);
        setFileModified(true, s);
    }
}
quint32 FF7Save::worldCoordsTc(int s, bool firstChunk)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        if (firstChunk) {
            return slot[s].tc_world;
        } else {
            return slot[s].tc_world2;
        }
    }
}
int FF7Save::worldCoordsTcX(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return (slot[s].tc_world & 0x7FFFF);
    }
}
int FF7Save::worldCoordsTcID(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].tc_world >> 19) & 0x1F);
    }
}
int FF7Save::worldCoordsTcAngle(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].tc_world) >> 24);
    }
}
int FF7Save::worldCoordsTcY(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].tc_world2) & 0x3FFFF);
    }
}
int FF7Save::worldCoordsTcZ(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].tc_world2) >> 18);
    }
}
void FF7Save::setWorldCoordsTc(int s, bool firstChunk, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFFFF);
    if (firstChunk && quint32(value) != worldCoordsTc(s, true)) {
        slot[s].tc_world = quint32(value);
        setFileModified(true, s);
    } else {
        if (quint32(value) != worldCoordsTc(s, false)) {
            slot[s].tc_world2 = quint32(value);
            setFileModified(true, s);
        }
    }
}
void FF7Save::setWorldCoordsTcX(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 295000);
    if (value != worldCoordsTcX(s)) {
        slot[s].tc_world = quint32(value | worldCoordsTcID(s) << 19 | worldCoordsTcAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsTcID(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsTcID(s)) {
        slot[s].tc_world = quint32(worldCoordsTcX(s) | value << 19 | worldCoordsTcAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsTcAngle(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 360);
    if (value != worldCoordsTcAngle(s)) {
        slot[s].tc_world = quint32(worldCoordsTcX(s) | worldCoordsTcID(s) << 19 | value << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsTcY(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 230000);
    if (value != worldCoordsTcY(s)) {
        slot[s].tc_world2 = quint32(value | worldCoordsTcZ(s) << 18);
        setFileModified(true, s);
    }

}
void FF7Save::setWorldCoordsTcZ(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsTcZ(s)) {
        slot[s].tc_world2 = quint32(worldCoordsTcY(s) | value << 18);
        setFileModified(true, s);
    }
}
quint32 FF7Save::worldCoordsBh(int s, bool firstChunk)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        if (firstChunk) {
            return slot[s].bh_world;
        } else {
            return slot[s].bh_world2;
        }
    }
}
int FF7Save::worldCoordsBhX(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return (slot[s].bh_world & 0x7FFFF);
    }
}
int FF7Save::worldCoordsBhID(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].bh_world >> 19) & 0x1F);
    }
}
int FF7Save::worldCoordsBhAngle(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].bh_world) >> 24);
    }
}
int FF7Save::worldCoordsBhY(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].bh_world2) & 0x3FFFF);
    }
}
int FF7Save::worldCoordsBhZ(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].bh_world2) >> 18);
    }
}
void FF7Save::setWorldCoordsBh(int s, bool firstChunk, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFFFF);
    if (firstChunk && quint32(value) != worldCoordsBh(s, true)) {
        slot[s].bh_world = quint32(value);
        setFileModified(true, s);
    } else {
        if (quint32(value) != worldCoordsBh(s, false)) {
            slot[s].bh_world2 = quint32(value);
            setFileModified(true, s);
        }
    }
}
void FF7Save::setWorldCoordsBhX(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 295000);
    if (value != worldCoordsBhX(s)) {
        slot[s].bh_world = quint32(value | worldCoordsBhID(s) << 19 | worldCoordsBhAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsBhID(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsBhID(s)) {
        slot[s].bh_world = quint32(worldCoordsBhX(s) | value << 19 | worldCoordsBhAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsBhAngle(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 360);
    if (value != worldCoordsBhAngle(s)) {
        slot[s].bh_world = quint32(worldCoordsBhX(s) | worldCoordsBhID(s) << 19 | value << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsBhY(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 230000);
    if (value != worldCoordsBhY(s)) {
        slot[s].bh_world2 = quint32(value | worldCoordsBhZ(s) << 18);
        setFileModified(true, s);
    }

}
void FF7Save::setWorldCoordsBhZ(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsBhZ(s)) {
        slot[s].bh_world2 = quint32(worldCoordsBhY(s) | value << 18);
        setFileModified(true, s);
    }
}

quint32 FF7Save::worldCoordsSub(int s, bool firstChunk)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        if (firstChunk) {
            return slot[s].sub_world;
        } else {
            return slot[s].sub_world2;
        }
    }
}
int FF7Save::worldCoordsSubX(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return (slot[s].sub_world & 0x7FFFF);
    }
}
int FF7Save::worldCoordsSubID(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].sub_world >> 19) & 0x1F);
    }
}
int FF7Save::worldCoordsSubAngle(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].sub_world) >> 24);
    }
}
int FF7Save::worldCoordsSubY(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].sub_world2) & 0x3FFFF);
    }
}
int FF7Save::worldCoordsSubZ(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].sub_world2) >> 18);
    }
}
void FF7Save::setWorldCoordsSub(int s, bool firstChunk, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFFFF);
    if (firstChunk && quint32(value) != worldCoordsSub(s, true)) {
        slot[s].sub_world = quint32(value);
        setFileModified(true, s);
    } else {
        if (quint32(value) != worldCoordsSub(s, false)) {
            slot[s].sub_world2 = quint32(value);
            setFileModified(true, s);
        }
    }
}
void FF7Save::setWorldCoordsSubX(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 295000);
    if (value != worldCoordsSubX(s)) {
        slot[s].sub_world = quint32(value | worldCoordsSubID(s) << 19 | worldCoordsSubAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsSubID(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsSubID(s)) {
        slot[s].sub_world = quint32(worldCoordsSubX(s) | value << 19 | worldCoordsSubAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsSubAngle(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 360);
    if (value != worldCoordsSubAngle(s)) {
        slot[s].sub_world = quint32(worldCoordsSubX(s) | worldCoordsSubID(s) << 19 | value << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsSubY(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 230000);
    if (value != worldCoordsSubY(s)) {
        slot[s].sub_world2 = quint32(value | worldCoordsSubZ(s) << 18);
        setFileModified(true, s);
    }

}
void FF7Save::setWorldCoordsSubZ(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsSubZ(s)) {
        slot[s].sub_world2 = quint32(worldCoordsSubY(s) | value << 18);
        setFileModified(true, s);
    }
}

quint32 FF7Save::worldCoordsWchoco(int s, bool firstChunk)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        if (firstChunk) {
            return slot[s].wc_world;
        } else {
            return slot[s].wc_world2;
        }
    }
}
int FF7Save::worldCoordsWchocoX(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return (slot[s].wc_world & 0x7FFFF);
    }
}
int FF7Save::worldCoordsWchocoID(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].wc_world >> 19) & 0x1F);
    }
}
int FF7Save::worldCoordsWchocoAngle(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].wc_world) >> 24);
    }
}
int FF7Save::worldCoordsWchocoY(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].wc_world2) & 0x3FFFF);
    }
}
int FF7Save::worldCoordsWchocoZ(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].wc_world2) >> 18);
    }
}
void FF7Save::setWorldCoordsWchoco(int s, bool firstChunk, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFFFF);
    if (firstChunk && quint32(value) != worldCoordsWchoco(s, true)) {
        slot[s].wc_world = quint32(value);
        setFileModified(true, s);
    } else {
        if (quint32(value) != worldCoordsWchoco(s, false)) {
            slot[s].wc_world2 = quint32(value);
            setFileModified(true, s);
        }
    }
}
void FF7Save::setWorldCoordsWchocoX(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 295000);
    if (value != worldCoordsWchocoX(s)) {
        slot[s].wc_world = quint32(value | worldCoordsWchocoID(s) << 19 | worldCoordsWchocoAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsWchocoID(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsWchocoID(s)) {
        slot[s].wc_world = quint32(worldCoordsWchocoX(s) | value << 19 | worldCoordsWchocoAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsWchocoAngle(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 360);
    if (value != worldCoordsWchocoAngle(s)) {
        slot[s].wc_world = quint32(worldCoordsWchocoX(s) | worldCoordsWchocoID(s) << 19 | value << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsWchocoY(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 230000);
    if (value != worldCoordsWchocoY(s)) {
        slot[s].wc_world2 = quint32(value | worldCoordsWchocoZ(s) << 18);
        setFileModified(true, s);
    }

}
void FF7Save::setWorldCoordsWchocoZ(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsWchocoZ(s)) {
        slot[s].wc_world2 = quint32(worldCoordsWchocoY(s) | value << 18);
        setFileModified(true, s);
    }
}

quint32 FF7Save::worldCoordsDurw(int s, bool firstChunk)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        if (firstChunk) {
            return slot[s].durw_world;
        } else {
            return slot[s].durw_world2;
        }
    }
}
int FF7Save::worldCoordsDurwX(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return (slot[s].durw_world & 0x7FFFF);
    }
}
int FF7Save::worldCoordsDurwID(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].durw_world >> 19) & 0x1F);
    }
}
int FF7Save::worldCoordsDurwAngle(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].durw_world) >> 24);
    }
}
int FF7Save::worldCoordsDurwY(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].durw_world2) & 0x3FFFF);
    }
}
int FF7Save::worldCoordsDurwZ(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return ((slot[s].durw_world2) >> 18);
    }
}
void FF7Save::setWorldCoordsDurw(int s, bool firstChunk, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFFFF);
    if (firstChunk && quint32(value) != worldCoordsDurw(s, true)) {
        slot[s].durw_world = quint32(value);
        setFileModified(true, s);
    } else {
        if (quint32(value) != worldCoordsDurw(s, false)) {
            slot[s].durw_world2 = quint32(value);
            setFileModified(true, s);
        }
    }
}
void FF7Save::setWorldCoordsDurwX(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 295000);
    if (value != worldCoordsDurwX(s)) {
        slot[s].durw_world = quint32(value | worldCoordsDurwID(s) << 19 | worldCoordsDurwAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsDurwID(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsDurwID(s)) {
        slot[s].durw_world = quint32(worldCoordsDurwX(s) | value << 19 | worldCoordsDurwAngle(s) << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsDurwAngle(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 360);
    if (value != worldCoordsDurwAngle(s)) {
        slot[s].durw_world = quint32(worldCoordsDurwX(s) | worldCoordsDurwID(s) << 19 | value << 24);
        setFileModified(true, s);
    }
}
void FF7Save::setWorldCoordsDurwY(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 230000);
    if (value != worldCoordsDurwY(s)) {
        slot[s].durw_world2 = quint32(value | worldCoordsDurwZ(s) << 18);
        setFileModified(true, s);
    }

}
void FF7Save::setWorldCoordsDurwZ(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 0xFF);
    if (value != worldCoordsDurwZ(s)) {
        slot[s].durw_world2 = quint32(worldCoordsDurwY(s) | value << 18);
        setFileModified(true, s);
    }
}
quint16 FF7Save::craterSavePointMapID(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].cratersaveMapId;
    }
}
void FF7Save::setCraterSavePointMapID(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, 0, 999);
    slot[s].cratersaveMapId = value;
    setFileModified(true, s);
}
qint16 FF7Save::craterSavePointX(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].cratersaveX;
    }
}
void FF7Save::setCraterSavePointX(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, -32767, 32767);
    slot[s].cratersaveX = value;
    setFileModified(true, s);
}

qint16 FF7Save::craterSavePointY(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].cratersaveY;
    }
}
void FF7Save::setCraterSavePointY(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, -32767, 32767);
    slot[s].cratersaveY = value;
    setFileModified(true, s);
}
qint16 FF7Save::craterSavePointZ(int s)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].cratersaveZ;
    }
}
void FF7Save::setCraterSavePointZ(int s, int value)
{
    if (s < 0 || s > 14) {
        return;
    }
    value = std::clamp(value, -32767, 32767);
    slot[s].cratersaveZ = value;
    setFileModified(true, s);
}
void FF7Save::vmcRegionEval(int s)
{
    //used when saving a VMC file to adjust slot to save game#
    //compare our list to known ff7 region codes to find out what slot we should be writing to
    //use strings for each region incase the card contains more then one FF7 regions save.
    QStringList us = { QStringLiteral("FF7-S01"), QStringLiteral("FF7-S02"),
                       QStringLiteral("FF7-S03"), QStringLiteral("FF7-S04"),
                       QStringLiteral("FF7-S05"), QStringLiteral("FF7-S06"),
                       QStringLiteral("FF7-S07"), QStringLiteral("FF7-S08"),
                       QStringLiteral("FF7-S09"), QStringLiteral("FF7-S10"),
                       QStringLiteral("FF7-S11"), QStringLiteral("FF7-S12"),
                       QStringLiteral("FF7-S13"), QStringLiteral("FF7-S14"),
                       QStringLiteral("FF7-S15")};
    QStringList uk = us;
    QStringList fr = us;
    QStringList ge = us;
    QStringList es = us;
    QStringList jp = us;
    QStringList in = us;
    for (int i = 0; i < s; i++) {
        if (region(i).contains("BASCUS-94163"))
            us.replace(region(i).mid(17, 2).toInt() - 1, QString());
        else if (region(i).contains("BESCES-00867"))
            uk.replace(region(i).mid(17, 2).toInt() - 1, QString());
        else if (region(i).contains("BESCES-00868"))
            fr.removeAt(region(i).mid(17, 2).toInt() - 1);
        else if (region(i).contains("BESCES-00869"))
            ge.removeAt(region(i).mid(17, 2).toInt() - 1);
        else if (region(i).contains("BESCES-00900"))
            es.removeAt(region(i).mid(17, 2).toInt() - 1);
        else if (region(i).contains("BISLPS-00700"))
            jp.removeAt(region(i).mid(17, 2).toInt() - 1);
        else if (region(i).contains("BISLPS-01057"))
            in.removeAt(region(i).mid(17, 2).toInt() - 1);
    }
    QString newRegionString = region(s).mid(0, 12);
    if (region(s).contains("BASCUS-94163")) {
        for (int i = 0; i < 15; i++) {
            if (us.at(i) == QString()) {
                continue;
            } else {
                newRegionString.append(us.at(i));
                break;
            }
        }
    } else if (region(s).contains("BESCES-00867")) {
        for (int i = 0; i < 15; i++) {
            if (uk.at(i).isEmpty()) {
                continue;
            } else {
                newRegionString.append(uk.at(i));
                break;
            }
        }
    } else if (region(s).contains("BESCES-00868")) {
        for (int i = 0; i < 15; i++) {
            if (fr.at(i).isEmpty()) {
                continue;
            } else {
                newRegionString.append(fr.at(i));
                break;
            }
        }
    } else if (region(s).contains("BESCES-00869")) {
        for (int i = 0; i < 15; i++) {
            if (ge.at(i).isEmpty()) {
                continue;
            } else {
                newRegionString.append(ge.at(i));
                break;
            }
        }
    } else if (region(s).contains("BESCES-00900")) {
        for (int i = 0; i < 15; i++) {
            if (es.at(i).isEmpty()) {
                continue;
            } else {
                newRegionString.append(es.at(i));
                break;
            }
        }
    } else if (region(s).contains("BISLPS-00700")) {
        for (int i = 0; i < 15; i++) {
            if (jp.at(i).isEmpty()) {
                continue;
            } else {
                newRegionString.append(jp.at(i));
                break;
            }
        }
    } else if (region(s).contains("BISLPS-01057")) {
        for (int i = 0; i < 15; i++) {
            if (in.at(i).isEmpty()) {
                continue;
            } else {
                newRegionString.append(in.at(i));
                break;
            }
        }
    }
    SG_Region_String[s] = newRegionString;
}
bool FF7Save::subMiniGameVictory(int s)
{
    //0x0F38 in game saved as int 1 or int 0
    if (s < 0 || s > 14) {
        return false;
    }

    if (slot[s].wonsubgame == 1) {
        return true;
    } else {
        return false;
    }
}
void FF7Save::setSubMiniGameVictory(int s, bool won)
{
    if (s < 0 || s > 14) {
        return;
    }
    int temp = slot[s].wonsubgame;
    if (won) {
        slot[s].wonsubgame = 1;
    } else {
        slot[s].wonsubgame = 0;
    }
    if (temp != slot[s].wonsubgame) {
        setFileModified(true, s);
    }
}
quint8 FF7Save::chocoboRating(int s, int stable)
{
    if (s < 0 || s > 14) {
        return 0;
    } else {
        return slot[s].stablechocorating[stable];
    }
}
void FF7Save::setChocoboRating(int s, int stable, int rating)
{
    if (s < 0 || s > 14 || stable < 0 || stable > 5 || rating < 0 || rating > 8) {
        return;
    } else if (rating == slot[s].stablechocorating[stable]) {
        return;
    } else {
        slot[s].stablechocorating[stable] = rating;
        setFileModified(true, s);
    }
}
QList<quint8> FF7Save::chocoboRatings(int s)
{
    QList<quint8>ratings;
    if (s < 0 || s > 14) {
        for (int i = 0; i < 6; i++) {
            ratings.append(0);
        }
    } else {
        for (int i = 0; i < 6; i++) {
            ratings.append(slot[s].stablechocorating[i]);
        }
    }
    return ratings;
}
bool FF7Save::playedPianoOnFlashback(int s)
{
    if (s < 0 || s > 14) {
        return false;
    }
    return ((slot[s].z_36[0]) & (1 << 2));
}
void FF7Save::setPlayedPianoOnFlashback(int s, bool played)
{
    if (s < 0 || s > 14) {
        return;
    }
    if (played) {
        slot[s].z_36[0] |= (1 << 2);
    } else {
        slot[s].z_36[0] &= ~(1 << 2);
    }
    setFileModified(true, s);
}

FF7SaveInfo::FORMAT FF7Save::format()
{
    return fileFormat;
}

bool FF7Save::isBufferSlotPopulated()
{
    return buffer_slot.checksum != 0x4D1D;
}

void FF7Save::setFormat(FF7SaveInfo::FORMAT newFormat)
{
    if (newFormat != fileFormat) {
        fileFormat = newFormat;
        _bufferFileHeader = _fileHeader;
        if(fileFormat != FF7SaveInfo::FORMAT::PGE && fileFormat != FF7SaveInfo::FORMAT::PDA)
            _fileHeader = FF7SaveInfo::instance()->fileHeader(newFormat);
    }
}

/****************************************************************************/
//    copyright 2019-2020   Chris Rizzitello <sithlord48@gmail.com>         //
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

#include <QObject>
#include <QRegularExpression>

#ifndef ff7tk_export_h
    #include <ff7tk_export.h>
#endif
class QJSEngine;
class QQmlEngine;

class FF7TK_EXPORT FF7SaveInfo : public QObject
{
    Q_OBJECT
public:
    /**
     * \enum FORMAT
     * \brief Supported Data Types
     */
    enum class FORMAT {
        UNKNOWN = -1, //!< UNKNOWN FORMAT
        PSX = 0,  //!< PSX Save Data
        PC,       //!< PC Save Format
        VMC,      //!< Virtual Memory Card
        PSP,      //!< PSP Save Format
        PS3,      //!< PS3 Save Format
        DEX,      //!< Dex Format
        VGS,      //!< VGS Format
        SWITCH,   //!< Switch Format
        PGE,      //!< Psx Game Edit Style Single Save
        PDA,      //!< GS , Dantel Style Save
    };
    Q_ENUM(FORMAT)

    /** \enum PSXBLOCKTYPE
     *  \brief Used to set the type of block on a PSX memory card (image) when creating the index.
     */
    enum class PSXBLOCKTYPE : char {
        BLOCK_EMPTY = '\xA0', /**< 0xA0*/
        BLOCK_INUSE = '\x51', /**< 0x51*/
        BLOCK_DELETED = '\xA1', /**< 0xA1*/
        BLOCK_MIDLINK = '\x52', /**< 0x52*/
        BLOCK_DELETED_MIDLINK = '\xA2', /**< 0xA2*/
        BLOCK_ENDLINK = '\x53', /**< 0x53*/
        BLOCK_DELETED_ENDLINK = '\xA3', /**< 0xA3*/
    };
    Q_ENUM(PSXBLOCKTYPE)

    /** \enum PSVINFO
     *  \brief Extra Header Info used for PSV format
     */
    enum class PSVINFO  {
        SAVETYPE, /**< Type of Save in the file, 0x14 for ps1 0x2C for ps2*/
        SIZEDISPLAY, /**< Size shown in XMB 4 bytes 00 20 00 00 */
        SAVESIZE /**< Size of save data 4 bytes match SIZEDISPLAY's value */
    };
    Q_ENUM(PSVINFO)

    /**
     * @brief Get the FF7SaveInfo Instance.
     * @sa qmlSingletonRegister()
     */
    static FF7SaveInfo *instance();

    /**
     * @brief Register The FF7SaveInfo Singleton for QML
     */
    QObject *qmlSingletonRegister(QQmlEngine *engine, QJSEngine *scriptEngine);

    /**
     * @brief The Size of a Final Fantasy VII Save file
     * @param format : The Save Format you wish to know about
     * @return size of Filetype
     */
    Q_INVOKABLE int fileSize(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Size of the format's file header
     * @param format : The Save Format you wish to know about
     * @return size of File Header
     */
    Q_INVOKABLE int fileHeaderSize(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Size of the format's slot header
     * @param format : The Save Format you wish to know about
     * @return size of slotHeader
     */
    Q_INVOKABLE int slotHeaderSize(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Size of the format's slot footer
     * @param format : The Save Format you wish to know about
     * @return size of slotFooter
     */
    Q_INVOKABLE int slotFooterSize(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Number of save slots in format
     * @param format : The Save Format you wish to know about
     * @return number of save slots in format.
     */
    Q_INVOKABLE int slotCount(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Magic Numbers for Final Fantasy VII Save Files
     * @param format : The Save Format
     * @return Magic Numbers for this file type
     */
    Q_INVOKABLE QByteArray fileIdentifier(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Standard File Header for Format
     * @param format
     * @return A Default File header
     */
    Q_INVOKABLE QByteArray fileHeader(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Standard Slot Header for Format
     * @param format
     * @param slot: the slot value to use (PSX ICON)
     * @return A Default File header
     */
    Q_INVOKABLE QByteArray slotHeader(FF7SaveInfo::FORMAT format, int slot = 0) const;

    /**
     * @brief Standard Slot Footer for Format
     * @param format
     * @return A Default File footer
     */
    Q_INVOKABLE QByteArray slotFooter(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Key Used to Sign The Format
     * @param format
     * @return The Key used to sign the format or an QByteArray() if none.
     */
    Q_INVOKABLE QByteArray signingKey(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Extra off set data for psv format
     * @param info: FF7SaveInfo::PSVINFO that describes the info type to return.
     * @return offset for the type of info requested
     */
    Q_INVOKABLE int extraPSVOffsets(FF7SaveInfo::PSVINFO info) const;

    /**
     * @brief IV Used to Sign The Format
     * @param format
     * @return The IV used to sign the format or an QByteArray() if none.
     */
    Q_INVOKABLE QByteArray signingIV(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief The offset for the seed for signed saves
     * @param format
     * @return offset of the seed or -1 if none
     */
    Q_INVOKABLE int fileSeedOffset(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief The offset for the signature for signed saves
     * @param format
     * @return offset of the signature or -1 if none
     */
    Q_INVOKABLE int fileSignatureOffset(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief The size for the signature for signed saves
     * @param format
     * @return size of the signature
     */
    Q_INVOKABLE int fileSignatureSize(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Description of the File type
     * @param format
     * @return Description of format
     */
    Q_INVOKABLE QString typeDescription(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Size of an FF7Slot
     * @return size of 0X10F4
     */
    Q_INVOKABLE int slotSize() const;

    /**
     * @brief Get a constructed RegularExpression to check for valid save name
     * @param format: the format you wish to check .
     * @return Constructed RegularExpression
     */
    Q_INVOKABLE QRegularExpression validNames(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Valid Extensions for the File type
     * @param format
     * @return  List of valid Extensions for the chosen format.
     */
    Q_INVOKABLE QStringList typeExtension(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Get a constructed filter string for use in save/ load dialogs.
     * @param format: the format you want info about
     * @return Constructed Filter string for chosen format or All Files for UNKNOWN TYPE
     */
    Q_INVOKABLE QString typeFilter(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Get a constructed filter string for use in save/load Dialogs.
     * @return Constructed Filter string
     */
    Q_INVOKABLE QString knownTypesFilter() const;

    /**
     * @brief Check if a format is using the PC format internally
     * @param format - Format to check 
     * @return True if format is uses PC format internally
     */
    Q_INVOKABLE bool internalPC(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief Check if a format is a Virtual Memory card
     * @param format - Format to check
     * @return True if format is a Virtual Memory card type.
     */
    Q_INVOKABLE bool isVirtualMemoryCard(FF7SaveInfo::FORMAT format) const;

    /**
     * @brief mcHeaderOffset Retuns the offset of the vmc header. Valid only for VMC types saves.
     * @param format - Format to check
     * @return Offset where the Vmc header starts or -1 if invalid.
     */
    Q_INVOKABLE int vmcHeaderOffset(FF7SaveInfo::FORMAT format) const;
private:
    FF7SaveInfo *operator = (FF7SaveInfo &other) = delete;
    FF7SaveInfo(const FF7SaveInfo &other) = delete;
    explicit FF7SaveInfo(QObject *parent = nullptr);
    ~FF7SaveInfo();
    struct FF7SaveInfoPrivate;
    FF7SaveInfoPrivate *d;
};

/****************************************************************************/
//    copyright 2019-2022 Chris Rizzitello <sithlord48@gmail.com>           //
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
#include <FF7SaveInfo.h>

#include <QByteArrayList>

FF7SaveInfo *FF7SaveInfo::get()
{
    static FF7SaveInfo m;
    return &m;
}

FF7SaveInfo::FF7SaveInfo(QObject *parent) :
    QObject(parent)
    , d(new FF7SaveInfoPrivate)
{
}

FF7SaveInfo::~FF7SaveInfo()
{
    delete d;
}

int FF7SaveInfo::fileSize(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PSX: return get()->d->PSX_FILE_SIZE;
    case FORMAT::PC: return get()->d->PC_FILE_SIZE;
    case FORMAT::VMC: return get()->d->VMC_FILE_SIZE;
    case FORMAT::PSP: return get()->d->PSP_FILE_SIZE;
    case FORMAT::PS3: return get()->d->PS3_FILE_SIZE;
    case FORMAT::DEX: return get()->d->DEX_FILE_SIZE;
    case FORMAT::VGS: return get()->d->VGS_FILE_SIZE;
    case FORMAT::SWITCH: return get()->d->SWITCH_FILE_SIZE;
    case FORMAT::PGE: return get()->d->PGE_FILE_SIZE;
    case FORMAT::PDA: return get()->d->PDA_FILE_SIZE;
    default: return 0;
    }
}

int FF7SaveInfo::fileHeaderSize(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PC: return get()->d->PC_FILE_HEADER_SIZE;
    case FORMAT::VMC: return get()->d->VMC_FILE_HEADER_SIZE;
    case FORMAT::PSP: return get()->d->PSP_FILE_HEADER_SIZE;
    case FORMAT::PS3: return get()->d->PS3_FILE_HEADER_SIZE;
    case FORMAT::DEX: return get()->d->DEX_FILE_HEADER_SIZE;
    case FORMAT::VGS: return get()->d->VGS_FILE_HEADER_SIZE;
    case FORMAT::SWITCH: return get()->d->SWITCH_FILE_HEADER_SIZE;
    case FORMAT::PGE: return get()->d->PGE_FILE_HEADER_SIZE;
    case FORMAT::PDA: return get()->d->PDA_FILE_HEADER_SIZE;
    default: return 0;
    }
}

int FF7SaveInfo::slotHeaderSize(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PSX:
    case FORMAT::VMC:
    case FORMAT::PSP:
    case FORMAT::PS3:
    case FORMAT::DEX:
    case FORMAT::PGE:
    case FORMAT::PDA:
    case FORMAT::VGS: return get()->d->PSX_SLOT_HEADER_SIZE;
    default: return 0;
    }
}

int FF7SaveInfo::slotFooterSize(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PSX:
    case FORMAT::VMC:
    case FORMAT::PSP:
    case FORMAT::PS3:
    case FORMAT::DEX:
    case FORMAT::PGE:
    case FORMAT::PDA:
    case FORMAT::VGS: return get()->d->PSX_SLOT_FOOTER_SIZE;
    default: return 0;
    }
}

int FF7SaveInfo::slotCount(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PDA:
    case FORMAT::PGE:
    case FORMAT::PSX:
    case FORMAT::PS3: return 1;
    case FORMAT::VMC:
    case FORMAT::PSP:
    case FORMAT::DEX:
    case FORMAT::VGS:
    case FORMAT::SWITCH:
    case FORMAT::PC: return 15;
    default: return 0;
    }
}

QByteArray FF7SaveInfo::fileIdentifier(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PSX: return get()->d->PSX_FILE_ID;
    case FORMAT::PC: return get()->d->PC_FILE_ID;
    case FORMAT::VMC: return get()->d->VMC_FILE_ID;
    case FORMAT::PSP: return get()->d->PSP_FILE_ID;
    case FORMAT::PS3: return get()->d->PS3_FILE_ID;
    case FORMAT::DEX: return get()->d->DEX_FILE_ID;
    case FORMAT::VGS: return get()->d->VGS_FILE_ID;
    case FORMAT::SWITCH: return get()->d->SWITCH_FILE_ID;
    default: return QByteArray();
    }
}

QByteArray FF7SaveInfo::fileHeader(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PC:
    case FORMAT::SWITCH:
    case FORMAT::DEX:
    case FORMAT::VGS:
    case FORMAT::VMC: return QByteArray(fileIdentifier(format)).append(fileHeaderSize(format) - fileIdentifier(format).length(), 0x00);
    case FORMAT::PSP: return get()->d->PSP_FILE_HEADER;
    case FORMAT::PS3: return get()->d->PS3_FILE_HEADER;
    default: return QByteArray();
    }
}

QByteArray FF7SaveInfo::slotHeader(FF7SaveInfo::FORMAT format, int slot)
{
    slot = std::clamp(slot, 0, 14);
    switch (format) {
    case FORMAT::PDA:
    case FORMAT::PGE:
    case FORMAT::PSX:
    case FORMAT::PSP:
    case FORMAT::PS3:
    case FORMAT::DEX:
    case FORMAT::VGS:
    case FORMAT::VMC: return QByteArray(get()->d->PSX_SLOT_HEADER.at(slot)).append(256, 0x00);
    default: return QByteArray();
    }
}

QByteArray FF7SaveInfo::slotFooter(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PGE:
    case FORMAT::PDA:
    case FORMAT::PSX:
    case FORMAT::PSP:
    case FORMAT::PS3:
    case FORMAT::DEX:
    case FORMAT::VGS:
    case FORMAT::VMC: return QByteArray(get()->d->PSX_SLOT_FOOTER_SIZE, 0x00);
    default: return QByteArray();
    }
}

QByteArray FF7SaveInfo::signingKey(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PSP:
    case FORMAT::PS3: return get()->d->PS_SIGNING_KEY;
    default: return QByteArray();
    }
}

int FF7SaveInfo::extraPSVOffsets(FF7SaveInfo::PSVINFO info)
{
    switch (info) {
    case PSVINFO::SAVETYPE: return get()->d->PS3_FILE_TYPE_OFFSET;
    case PSVINFO::SIZEDISPLAY: return get()->d->PS3_FILE_DISP_SIZE_OFFSET;
    case PSVINFO::SAVESIZE: return get()->d->PS3_FILE_SIZE_OFFSET;
    default: return -1;
    }
}


QByteArray FF7SaveInfo::signingIV(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PSP:
    case FORMAT::PS3: return get()->d->PS_SIGNING_IV;
    default: return QByteArray();
    }
}

int FF7SaveInfo::fileSeedOffset(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PSP: return get()->d->PSP_SEED_OFFSET;
    case FORMAT::PS3: return get()->d->PS3_SEED_OFFSET;
    default: return -1;
    }
}

int FF7SaveInfo::fileSignatureOffset(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PSP: return get()->d->PSP_SIGNATURE_OFFSET;
    case FORMAT::PS3: return get()->d->PS3_SIGNATURE_OFFSET;
    default: return -1;
    }
}

int FF7SaveInfo::fileSignatureSize(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PSP:
    case FORMAT::PS3: return get()->d->PS_SIGNATURE_SIZE;
    default: return 0;
    }
}

int FF7SaveInfo::slotSize()
{
    return get()->d->_slotSize;
}

QRegularExpression FF7SaveInfo::validNames(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PC: return get()->d->PC_VALID_NAME_REGEX;
    case FORMAT::PSX: return get()->d->PSX_VALID_NAME_REGEX;
    case FORMAT::PSP: return get()->d->PSP_VALID_NAME_REGEX;
    case FORMAT::PS3: return get()->d->PS3_VALID_NAME_REGEX;
    case FORMAT::DEX: return get()->d->DEX_VALID_NAME_REGEX;
    case FORMAT::VGS: return get()->d->VGS_VALID_NAME_REGEX;
    case FORMAT::VMC: return get()->d->VMC_VALID_NAME_REGEX;
    case FORMAT::SWITCH: return get()->d->SWITCH_VALID_NAME_REGEX;
    case FORMAT::PGE: return get()->d->PGE_VALID_NAME_REGEX;
    case FORMAT::PDA: return get()->d->PDA_VALID_NAME_REGEX;
    default: return QRegularExpression();
    }
}

QString FF7SaveInfo::typeDescription(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PC: return tr(get()->d->PC_FILE_DESCRIPTION.toUtf8());
    case FORMAT::PSX: return tr(get()->d->PSX_FILE_DESCRIPTION.toUtf8());
    case FORMAT::PSP: return tr(get()->d->PSP_FILE_DESCRIPTION.toUtf8());
    case FORMAT::PS3: return tr(get()->d->PS3_FILE_DESCRIPTION.toUtf8());
    case FORMAT::DEX: return tr(get()->d->DEX_FILE_DESCRIPTION.toUtf8());
    case FORMAT::VGS: return tr(get()->d->VGS_FILE_DESCRIPTION.toUtf8());
    case FORMAT::VMC: return tr(get()->d->VMC_FILE_DESCRIPTION.toUtf8());
    case FORMAT::SWITCH: return tr(get()->d->SWITCH_FILE_DESCRIPTION.toUtf8());
    case FORMAT::PGE: return tr(get()->d->PGE_FILE_DESCRIPTION.toUtf8());
    case FORMAT::PDA: return tr(get()->d->PDA_FILE_DESCRIPTION.toUtf8());
    default: return QString();
    }
}

QStringList FF7SaveInfo::typeExtension(FF7SaveInfo::FORMAT format)
{
    switch (format) {
    case FORMAT::PC: return get()->d->PC_VALID_EXTENSIONS;
    case FORMAT::PSX: return get()->d->PSX_VALID_EXTENSIONS;
    case FORMAT::PSP: return get()->d->PSP_VALID_EXTENSIONS;
    case FORMAT::PS3: return get()->d->PS3_VALID_EXTENSIONS;
    case FORMAT::DEX: return get()->d->DEX_VALID_EXTENSIONS;
    case FORMAT::VGS: return get()->d->VGS_VALID_EXTENSIONS;
    case FORMAT::VMC: return get()->d->VMC_VALID_EXTENSIONS;
    case FORMAT::SWITCH: return get()->d->SWITCH_VALID_EXTENSIONS;
    case FORMAT::PGE: return get()->d->PGE_VALID_EXTENSIONS;
    case FORMAT::PDA: return get()->d->PDA_VALID_EXTENSIONS;
    default: return QStringList();
    }
}

QString FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT format)
{
    if (format == FORMAT::UNKNOWN)
        return tr("All Files (*)");
    return QStringLiteral("%1 (%2)").arg(typeDescription(format), typeExtension(format).join(QStringLiteral(" ")));
}

QString FF7SaveInfo::knownTypesFilter()
{
    QString space = QStringLiteral(" ");
    QString allTypes = QStringLiteral("%1 %2 %3 %4 %5 %6 %7 %8 %9 %10")
        .arg(get()->d->PC_VALID_EXTENSIONS.join(space)
        , get()->d->PSX_VALID_EXTENSIONS.join(space)
        , get()->d->PSP_VALID_EXTENSIONS.join(space)
        , get()->d->PS3_VALID_EXTENSIONS.join(space)
        , get()->d->DEX_VALID_EXTENSIONS.join(space)
        , get()->d->VGS_VALID_EXTENSIONS.join(space)
        , get()->d->VMC_VALID_EXTENSIONS.join(space)
        , get()->d->SWITCH_VALID_EXTENSIONS.join(space)
        , get()->d->PGE_VALID_EXTENSIONS.join(space)
        , get()->d->PDA_VALID_EXTENSIONS.join(space));

    return QStringLiteral("%1;;%2;;%3;;%4;;%5;;%6;;%7;;%8;;%9;;%10;;%11;;%12")
        .arg(tr("Known FF7 Save Types (%1)").arg(allTypes)
        , typeFilter(FORMAT::PC)
        , typeFilter(FORMAT::SWITCH)
        , typeFilter(FORMAT::VMC)
        , typeFilter(FORMAT::PSX)
        , typeFilter(FORMAT::PS3)
        , typeFilter(FORMAT::PSP)
        , typeFilter(FORMAT::DEX)
        , typeFilter(FORMAT::VGS)
        , typeFilter(FORMAT::PGE)
        , typeFilter(FORMAT::PDA)
        , typeFilter(FORMAT::UNKNOWN));
}

bool FF7SaveInfo::isTypePC(FF7SaveInfo::FORMAT format)
{
    switch(format) {
        case FORMAT::SWITCH:
        case FORMAT::PC: return true;
        default: return false;
    };
}

bool FF7SaveInfo::isTypeVMC(FF7SaveInfo::FORMAT format)
{
    switch(format) {
        case FORMAT::VMC:
        case FORMAT::VGS:
        case FORMAT::DEX:
        case FORMAT::PSP: return true;
        default: return false;
    };
}

bool FF7SaveInfo::isTypeSSS(FF7SaveInfo::FORMAT format)
{
    switch(format) {
        case FORMAT::PSX:
        case FORMAT::PS3:
        case FORMAT::PDA:
        case FORMAT::PGE: return true;
        default: return false;
    };
}

int FF7SaveInfo::vmcHeaderOffset(FF7SaveInfo::FORMAT format)
{
    switch (format) {
        case FORMAT::PSP: return get()->d->PSP_VMC_HEADER_OFFSET;
        case FORMAT::DEX: return get()->d->DEX_VMC_HEADER_OFFSET;
        case FORMAT::VGS: return get()->d->VGS_VMC_HEADER_OFFSET;
        case FORMAT::VMC: return get()->d->VMC_VMC_HEADER_OFFSET;
        case FORMAT::PGE: return get()->d->PGE_VMC_HEADER_OFFSET;
        default: return -1;
    }
}

int FF7SaveInfo::psxSaveNameOffset(FF7SaveInfo::FORMAT format)
{
    switch (format) {
        case FORMAT::PGE: return get()->d->PGE_FILE_NAME_OFFSET;
        case FORMAT::PDA: return get()->d->PDA_FILE_NAME_OFFSET;
        case FORMAT::PS3: return get()->d->PS3_FILE_NAME_OFFSET;
        default: return -1;
        }
}

QByteArray FF7SaveInfo::defaultSaveData()
{
    return get()->d->DEFAULT_SAVE;
}


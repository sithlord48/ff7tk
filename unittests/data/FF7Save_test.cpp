//    SPDX-FileCopyrightText: 2021 - 2022 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <QtTest>

#include "FF7Save_test.h"
#include "../../src/data/FF7Item.h"
#include "../../src/data/FF7Char.h"

void FF7Save_Test::initTestCase()
{
    ff7save = new FF7Save();
    ff7save->newGame(0);
    ff7save->setSlotPsxRawData(0, _slotData);
}

void FF7Save_Test::test_pcExport()
{
    QVERIFY(ff7save->exportFile(_saveFileNamePC, FF7SaveInfo::FORMAT::PC, 0));
    ff7save->loadFile(_saveFileNamePC);
}

void FF7Save_Test::test_vmcExport()
{
    QVERIFY(ff7save->exportFile(_saveFileNameVMC, FF7SaveInfo::FORMAT::VMC, 0));
    ff7save->loadFile(_saveFileNameVMC);
}

void FF7Save_Test::test_pspExport()
{
    QVERIFY(ff7save->exportFile(_saveFileNamePSP, FF7SaveInfo::FORMAT::PSP, 0));
    ff7save->loadFile(_saveFileNamePSP);
    //Check Sig
    QString expectedKey = QStringLiteral("6AF7D7EACA66BBEE0F0DA7B16E85BF48EFA863F0");
    QByteArray keySeed = ff7save->fileHeader().mid(FF7SaveInfo::fileSeedOffset(FF7SaveInfo::FORMAT::PSP), FF7SaveInfo::fileSignatureSize(FF7SaveInfo::FORMAT::PSP));
    QByteArray data = ff7save->fileHeader();
    for(int i=0; i < 15; i++) {
        data.append(ff7save->slotHeader(i));
        data.append(ff7save->slotFF7Data(i));
        data.append(ff7save->slotFooter(i));
    }
    QCOMPARE(ff7save->generatePsSaveSignature(data, keySeed).toHex().toUpper(), expectedKey);
}

void FF7Save_Test::test_ps3Export()
{
    QVERIFY(ff7save->exportFile(_saveFileNamePS3, FF7SaveInfo::FORMAT::PS3, 0));
    ff7save->loadFile(_saveFileNamePS3);
    //Check Sig
    QString expectedKey = QStringLiteral("7324B67D24BFC027A5CCB219A205B8D265DED5CF");
    QByteArray keySeed = ff7save->fileHeader().mid(FF7SaveInfo::fileSeedOffset(FF7SaveInfo::FORMAT::PS3), FF7SaveInfo::fileSignatureSize(FF7SaveInfo::FORMAT::PS3));
    QByteArray data = ff7save->fileHeader();
    data.append(ff7save->slotHeader(0));
    data.append(ff7save->slotFF7Data(0));
    data.append(ff7save->slotFooter(0));
    QCOMPARE(ff7save->generatePsSaveSignature(data, keySeed).toHex().toUpper(), expectedKey);
}

void FF7Save_Test::test_dexExport()
{
    QVERIFY(ff7save->exportFile(_saveFileNameDEX, FF7SaveInfo::FORMAT::DEX, 0));
    ff7save->loadFile(_saveFileNameDEX);
}

void FF7Save_Test::test_vgsExport()
{
    QVERIFY(ff7save->exportFile(_saveFileNameVGS, FF7SaveInfo::FORMAT::VGS, 0));
    ff7save->loadFile(_saveFileNameVGS);
}

void FF7Save_Test::test_switchExport()
{
    QVERIFY(ff7save->exportFile(_saveFileNameSWITCH, FF7SaveInfo::FORMAT::SWITCH, 0));
    ff7save->loadFile(_saveFileNameSWITCH);
}

void FF7Save_Test::test_pgeExport()
{
    QVERIFY(ff7save->exportFile(_saveFileNamePGE, FF7SaveInfo::FORMAT::PGE, 0));
    ff7save->loadFile(_saveFileNamePGE);
}

void FF7Save_Test::test_pdaExport()
{
    QVERIFY(ff7save->exportFile(_saveFileNamePDA, FF7SaveInfo::FORMAT::PDA));
    ff7save->loadFile(_saveFileNamePDA);
}

void FF7Save_Test::test_setSlotPsxRawData()
{
    ff7save->setFormat(FF7SaveInfo::FORMAT::PSX);
    ff7save->newGame(0);
    QVERIFY(ff7save->setSlotPsxRawData(0, _slotData));
}

void FF7Save_Test::test_psxExport()
{
    QVERIFY(ff7save->exportFile(_saveFileNamePSX, FF7SaveInfo::FORMAT::PSX, 0));
    ff7save->loadFile(_saveFileNamePSX);
}


void FF7Save_Test::test_psxDesc()
{
    QCOMPARE(ff7save->psxDesc(0), QStringLiteral("ＦＦ７／ＳＡＶＥ１５／９９：２８"));
    QString desc = QStringLiteral("ＦＶＦＶＦＶＦＶＦＶＦＶＦＶＦＶ");
    ff7save->setPsxDesc(desc, 0);
    QCOMPARE(ff7save->psxDesc(0), desc);
}

void FF7Save_Test::test_atbMode()
{
    QCOMPARE(ff7save->atbMode(0), FF7Save::ATB_ACTIVE);
    ff7save->setAtbMode(0, FF7Save::ATB_WAIT);
    QCOMPARE(ff7save->atbMode(0), FF7Save::ATB_WAIT);
    ff7save->setAtbMode(0, FF7Save::ATB_RECOMMENED);
    QCOMPARE(ff7save->atbMode(0), FF7Save::ATB_RECOMMENED);
}

void FF7Save_Test::test_battleHelp()
{
    QCOMPARE(ff7save->battleHelp(0), false);
    ff7save->setBattleHelp(0, true);
    QCOMPARE(ff7save->battleHelp(0), true);
}

void FF7Save_Test::test_battleMessageSpeed()
{
    QCOMPARE(ff7save->battleMessageSpeed(0), 38);
    ff7save->setBattleMessageSpeed(0, 255);
    QCOMPARE(ff7save->battleMessageSpeed(0), 255);
}

void FF7Save_Test::test_battlePoints()
{
    QCOMPARE(ff7save->battlePoints(0), 0);
    ff7save->setBattlePoints(0, 255);
    QCOMPARE(ff7save->battlePoints(0), 255);
    ff7save->setBattlePoints(0, 8536);
    QCOMPARE(ff7save->battlePoints(0), 8536);
    ff7save->setBattlePoints(0, 0xFFFF);
    QCOMPARE(ff7save->battlePoints(0), 0xFFFF);
}

void FF7Save_Test::test_battleSpeed()
{
    QCOMPARE(ff7save->battleSpeed(0), 0);
    ff7save->setBattleSpeed(0, 255);
    QCOMPARE(ff7save->battleSpeed(0), 255);
}

void FF7Save_Test::test_battleTargets()
{
    QCOMPARE(ff7save->battleTargets(0), false);
    ff7save->setBattleTargets(0, true);
    QCOMPARE(ff7save->battleTargets(0), true);
}

void FF7Save_Test::test_battles()
{
    QCOMPARE(ff7save->battles(0), 4732);
    ff7save->setBattles(0, -3);
    QCOMPARE(ff7save->battles(0), 0);
    ff7save->setBattles(0, 66666);
    QCOMPARE(ff7save->battles(0), 65535);
}

void FF7Save_Test::test_bikeHighScore()
{
    QCOMPARE(ff7save->bikeHighScore(0), 5700);
    ff7save->setBikeHighScore(0, 0xFFFF);
    QCOMPARE(ff7save->bikeHighScore(0), 0xFFFF);
}

void FF7Save_Test::test_bmProgress1()
{
    QList<bool> checkVar{false, false, false, true, true, true, true, false };
    for(int i=0; i < 8; i++)
        QCOMPARE(ff7save->bmProgress1(0, i), checkVar[i]);
    for(int i=0; i < 8; i++)
        ff7save->setBmProgress1(0, i, !checkVar[i]);
    for(int i=0; i < 8; i++)
        QCOMPARE(ff7save->bmProgress1(0, i), !checkVar[i]);
}

void FF7Save_Test::test_bmProgress2()
{
    QList<bool> checkVar{false, true, true, false, false, true, true, true };
    for(int i=0; i < 8; i++)
        QCOMPARE(ff7save->bmProgress2(0, i), checkVar[i]);
    for(int i=0; i < 8; i++)
        ff7save->setBmProgress2(0, i, !checkVar[i]);
    for(int i=0; i < 8; i++)
        QCOMPARE(ff7save->bmProgress2(0, i), !checkVar[i]);
}


void FF7Save_Test::test_bmProgress3()
{
    QList<bool> checkVar{true, true, false, false, false, false, false, false };
    for(int i=0; i < 8; i++)
        QCOMPARE(ff7save->bmProgress3(0, i), checkVar[i]);
    for(int i=0; i < 8; i++)
        ff7save->setBmProgress3(0, i, !checkVar[i]);
    for(int i=0; i < 8; i++)
        QCOMPARE(ff7save->bmProgress3(0, i), !checkVar[i]);
}

void FF7Save_Test::test_cameraMode()
{
    QCOMPARE(ff7save->cameraMode(0), FF7Save::CAMERA_AUTO);
    ff7save->setCameraMode(0, FF7Save::CAMERA_FIXED);
    QCOMPARE(ff7save->cameraMode(0), FF7Save::CAMERA_FIXED);
}

void FF7Save_Test::test_canFightNinjaInForest()
{
    QCOMPARE(ff7save->canFightNinjaInForest(0), false);
    ff7save->setCanFightNinjaInForest(0, true);
    QCOMPARE(ff7save->canFightNinjaInForest(0), true);
}

void FF7Save_Test::test_charAccessory()
{
    QCOMPARE(ff7save->charAccessory(0, 0), 18);
    ff7save->setCharAccessory(0, 0, 31);
    QCOMPARE(ff7save->charAccessory(0, 0), 31);
    ff7save->setCharAccessory(0, 0, 0xFF);
    QCOMPARE(ff7save->charAccessory(0, 0), 0xFF);
}

void FF7Save_Test::test_charArmor()
{
    QCOMPARE(ff7save->charArmor(0, 0), 27);
    ff7save->setCharArmor(0, 0, 24);
    QCOMPARE(ff7save->charArmor(0, 0), 24);
    ff7save->setCharArmor(0, 0, 0xFF);
    QCOMPARE(ff7save->charArmor(0, 0), 0xFF);
}

void FF7Save_Test::test_charBaseHp()
{
    QCOMPARE(ff7save->charBaseHp(0, 0), 9134);
    ff7save->setCharBaseHp(0, 0, 157);
    QCOMPARE(ff7save->charBaseHp(0, 0), 157);
    ff7save->setCharBaseHp(0, 0, 9134);
}

void FF7Save_Test::test_charBaseMp()
{
    QCOMPARE(ff7save->charBaseMp(0, 0), 877);
    ff7save->setCharBaseMp(0, 0, 157);
    QCOMPARE(ff7save->charBaseMp(0, 0), 157);
    ff7save->setCharBaseMp(0, 0, 877);
}

void FF7Save_Test::test_charCurrentExp()
{
    QCOMPARE(ff7save->charCurrentExp(0, 0), 14622721);
    ff7save->setCharCurrentExp(0, 0, 1000);
    QCOMPARE(ff7save->charCurrentExp(0, 0), 1000);
}

void FF7Save_Test::test_charCurrentHp()
{
    QCOMPARE(ff7save->charCurrentHp(0, 0), 9999);
    ff7save->setCharCurrentHp(0, 0, 1000);
    QCOMPARE(ff7save->charCurrentHp(0, 0), 1000);
}

void FF7Save_Test::test_charCurrentMp()
{
    QCOMPARE(ff7save->charCurrentMp(0, 0), 999);
    ff7save->setCharCurrentMp(0, 0, 100);
    QCOMPARE(ff7save->charCurrentMp(0, 0), 100);
}

void FF7Save_Test::test_charDex()
{
    QCOMPARE(ff7save->charDex(0, 0), 61);
    ff7save->setCharDex(0, 0, 255);
    QCOMPARE(ff7save->charDex(0, 0), 255);
}

void FF7Save_Test::test_charDexBonus()
{
    QCOMPARE(ff7save->charDexBonus(0, 0), 194);
    ff7save->setCharDexBonus(0, 0, 25);
    QCOMPARE(ff7save->charDexBonus(0, 0), 25);
}

void FF7Save_Test::test_charFlags()
{
    QCOMPARE(ff7save->charFlag(0, 0, 0), 0x00);
    ff7save->setCharFlag(0, 0, 0, 0xFF);
    QCOMPARE(ff7save->charFlag(0, 0, 0), 0xFF);

    QCOMPARE(ff7save->charFlag(0, 0, 1), 0xFE);
    ff7save->setCharFlag(0, 0, 1, 0xFF);
    QCOMPARE(ff7save->charFlag(0, 0, 1), 0xFF);

    QCOMPARE(ff7save->charFlag(0, 0, 2), 61);
    ff7save->setCharFlag(0, 0, 2, 0xFF);
    QCOMPARE(ff7save->charFlag(0, 0, 2), 0xFF);
}

void FF7Save_Test::test_charID()
{
    QCOMPARE(ff7save->charID(0, 0), 0);
    ff7save->setCharID(0, 0, 7);
    QCOMPARE(ff7save->charID(0, 0), 7);
    ff7save->setCharID(0, 0, 0);
}

void FF7Save_Test::test_charKills()
{
    QCOMPARE(ff7save->charKills(0, 0), 3125);
    ff7save->setCharKills(0, 0, 0);
    QCOMPARE(ff7save->charKills(0, 0), 0);
    ff7save->setCharKills(0, 0, 0xFFFF);
    QCOMPARE(ff7save->charKills(0, 0), 0xFFFF);
}

void FF7Save_Test::test_charLck()
{
    QCOMPARE(ff7save->charLck(0, 0), 29);
    ff7save->setCharLck(0, 0, 0xFF);
    QCOMPARE(ff7save->charLck(0, 0), 0xFF);
    ff7save->setCharLck(0, 0, 0);
    QCOMPARE(ff7save->charLck(0, 0), 0);
    ff7save->setCharLck(0, 0, 29);
}

void FF7Save_Test::test_charLckBonus()
{
    QCOMPARE(ff7save->charLckBonus(0, 0), 229);
    ff7save->setCharLckBonus(0, 0, 0xFF);
    QCOMPARE(ff7save->charLckBonus(0, 0), 0xFF);
    ff7save->setCharLckBonus(0, 0, 0);
    QCOMPARE(ff7save->charLckBonus(0, 0), 0);
    ff7save->setCharLckBonus(0, 0, 229);
}

void FF7Save_Test::test_charLevel()
{
    QCOMPARE(ff7save->charLevel(0, 0), 99);
    ff7save->setCharLevel(0, 0, 6);
    QCOMPARE(ff7save->charLevel(0, 0), 6);
    ff7save->setCharLevel(0, 0, 99);
}

void FF7Save_Test::test_charLimitBar()
{
    QCOMPARE(ff7save->charLimitBar(0, 0), 251);
    ff7save->setCharLimitBar(0, 0, 6);
    QCOMPARE(ff7save->charLimitBar(0, 0), 6);
    ff7save->setCharLimitBar(0, 0, 99);
}

void FF7Save_Test::test_charLimitLevel()
{
    QCOMPARE(ff7save->charLimitLevel(0, 0), 4);
    ff7save->setCharLimitLevel(0, 0, 2);
    QCOMPARE(ff7save->charLimitLevel(0, 0), 2);
    ff7save->setCharLimitLevel(0, 0, 4);
}

void FF7Save_Test::test_charMag()
{
    QCOMPARE(ff7save->charMag(0, 0), 100);
    ff7save->setCharMag(0, 0, 0xFF);
    QCOMPARE(ff7save->charMag(0, 0), 0xFF);
    ff7save->setCharMag(0, 0, 0);
    QCOMPARE(ff7save->charMag(0, 0), 0);
    ff7save->setCharMag(0, 0, 100);
}

void FF7Save_Test::test_charMagBonus()
{
    QCOMPARE(ff7save->charMagBonus(0, 0), 104);
    ff7save->setCharMagBonus(0, 0, 0xFF);
    QCOMPARE(ff7save->charMagBonus(0, 0), 0xFF);
    ff7save->setCharMagBonus(0, 0, 0);
    QCOMPARE(ff7save->charMagBonus(0, 0), 0);
    ff7save->setCharMagBonus(0, 0, 104);
}

void FF7Save_Test::test_charMateria()
{
    QCOMPARE(ff7save->charMateriaId(0, 0, 0), 73);
    QCOMPARE(ff7save->charMateriaAp(0, 0, 0), 0);
    QCOMPARE(ff7save->charMateriaId(0, 0, 1), 27);
    QCOMPARE(ff7save->charMateriaAp(0, 0, 1), 0xFFFFFF);
    ff7save->setCharMateria(0, 0, 0, 15, 127);
    QCOMPARE(ff7save->charMateriaId(0, 0, 0), 15);
    QCOMPARE(ff7save->charMateriaAp(0, 0, 0), 127);
}

void FF7Save_Test::test_charMaxHp()
{
    QCOMPARE(ff7save->charMaxHp(0, 0), 9999);
    ff7save->setCharMaxHp(0, 0, 777);
    QCOMPARE(ff7save->charMaxHp(0, 0), 777);
}

void FF7Save_Test::test_charMaxMp()
{
    QCOMPARE(ff7save->charMaxMp(0, 0), 999);
    ff7save->setCharMaxMp(0, 0, 135);
    QCOMPARE(ff7save->charMaxMp(0, 0), 135);
}

void FF7Save_Test::test_charName()
{
    QStringList checkVal{QStringLiteral("Cloud"), QStringLiteral("Barret"), QStringLiteral("Tifa"), QStringLiteral("Aeris"), QStringLiteral("Nanaki") , QStringLiteral("Yuffie"), QStringLiteral("Cait Sith"), QStringLiteral("Vincent"), QStringLiteral("Cid")};
    QStringList FlipVal{QStringLiteral("BigHair"), QStringLiteral("GunArm"), QStringLiteral("KarateKid"), QStringLiteral("EarthGirl"), QStringLiteral("WolfMan") , QStringLiteral("SneakyLady"), QStringLiteral("Stuffie"), QStringLiteral("BlaBlaBlaBla"), QStringLiteral("Dragoon")};

    for (int i=0; i< 9; i++)
        QCOMPARE(ff7save->charName(0, i), checkVal.at(i));
    for (int i=0; i< 9; i++)
        ff7save->setCharName(0, i, FlipVal.at(i));
    for (int i=0; i< 9; i++)
        QCOMPARE(ff7save->charName(0, i), FlipVal.at(i));
}

void FF7Save_Test::test_charNextExp()
{
    QCOMPARE(ff7save->charNextExp(0, 0), 0);
    ff7save->setCharNextExp(0, 0, 1000);
    QCOMPARE(ff7save->charNextExp(0, 0), 1000);
}

void FF7Save_Test::test_charSpi()
{
    QCOMPARE(ff7save->charSpi(0, 0), 98);
    ff7save->setCharSpi(0, 0, 0xFF);
    QCOMPARE(ff7save->charSpi(0, 0), 0xFF);
    ff7save->setCharSpi(0, 0, 0);
    QCOMPARE(ff7save->charSpi(0, 0), 0);
    ff7save->setCharSpi(0, 0, 98);
}

void FF7Save_Test::test_charSpiBonus()
{
    QCOMPARE(ff7save->charSpiBonus(0, 0), 24);
    ff7save->setCharSpiBonus(0, 0, 0xFF);
    QCOMPARE(ff7save->charSpiBonus(0, 0), 0xFF);
    ff7save->setCharSpiBonus(0, 0, 0);
    QCOMPARE(ff7save->charSpiBonus(0, 0), 0);
    ff7save->setCharSpiBonus(0, 0, 24);
}

void FF7Save_Test::test_charStr()
{
    QCOMPARE(ff7save->charStr(0, 0), 100);
    ff7save->setCharStr(0, 0, 0xFF);
    QCOMPARE(ff7save->charStr(0, 0), 0xFF);
    ff7save->setCharStr(0, 0, 0);
    QCOMPARE(ff7save->charStr(0, 0), 0);
    ff7save->setCharStr(0, 0, 100);
}

void FF7Save_Test::test_charStrBonus()
{
    QCOMPARE(ff7save->charStrBonus(0, 0), 155);
    ff7save->setCharStrBonus(0, 0, 0xFF);
    QCOMPARE(ff7save->charStrBonus(0, 0), 0xFF);
    ff7save->setCharStrBonus(0, 0, 0);
    QCOMPARE(ff7save->charStrBonus(0, 0), 0);
    ff7save->setCharStrBonus(0, 0, 155);
}

void FF7Save_Test::test_charTimeLimitUsed()
{
    QCOMPARE(ff7save->charTimesLimitUsed(0, 0, 1), 20);
    QCOMPARE(ff7save->charTimesLimitUsed(0, 0, 2), 14);
    QCOMPARE(ff7save->charTimesLimitUsed(0, 0, 3), 45);
    //Invalid Limit Test
    QCOMPARE(ff7save->charTimesLimitUsed(0, 0, 4), 0);
}

void FF7Save_Test::test_charUnknown()
{
    QCOMPARE(ff7save->charUnknown(0, 0, 0), 0);
    QCOMPARE(ff7save->charUnknown(0, 0, 1), 0);
    QCOMPARE(ff7save->charUnknown(0, 0, 2), 0);
    QCOMPARE(ff7save->charUnknown(0, 0, 3), 0);
    ff7save->setCharUnknown(0, 0, 0, 0xFF);
    ff7save->setCharUnknown(0, 0, 1, 0xFF);
    ff7save->setCharUnknown(0, 0, 2, 0xFF);
    ff7save->setCharUnknown(0, 0, 3, 0xFF);
    QCOMPARE(ff7save->charUnknown(0, 0, 0), 0xFF);
    QCOMPARE(ff7save->charUnknown(0, 0, 1), 0xFF);
    QCOMPARE(ff7save->charUnknown(0, 0, 2), 0xFF);
    QCOMPARE(ff7save->charUnknown(0, 0, 3), 0xFF);
}

void FF7Save_Test::test_charVit()
{
    QCOMPARE(ff7save->charVit(0, 0), 93);
    ff7save->setCharVit(0, 0, 0xFF);
    QCOMPARE(ff7save->charVit(0, 0), 0xFF);
    ff7save->setCharVit(0, 0, 0);
    QCOMPARE(ff7save->charVit(0, 0), 0);
    ff7save->setCharVit(0, 0, 93);
}

void FF7Save_Test::test_charVitBonus()
{
    QCOMPARE(ff7save->charVitBonus(0, 0), 135);
    ff7save->setCharVitBonus(0, 0, 0xFF);
    QCOMPARE(ff7save->charVitBonus(0, 0), 0xFF);
    ff7save->setCharVitBonus(0, 0, 0);
    QCOMPARE(ff7save->charVitBonus(0, 0), 0);
    ff7save->setCharVitBonus(0, 0, 135);
}

void FF7Save_Test::test_charWeapon()
{
    QCOMPARE(ff7save->charWeapon(0, 0), 15);
}

void FF7Save_Test::test_chocoAccel()
{
    QList<int> checkVal{62, 65, 65, 65, 60 , 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoAccel(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoAccel(0, i, checkVal.at(i) + 10);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoAccel(0, i), checkVal.at(i) + 10);
}

void FF7Save_Test::test_chocoCantMate()
{
    QList<bool> checkVal{false, false, false, false, false , false};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoCantMate(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoCantMate(0, i, !checkVal.at(i));
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoCantMate(0, i), !checkVal.at(i));
}

void FF7Save_Test::test_chocoCoop()
{
    QList<int> checkVal{100, 100, 100, 100, 100 , 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoCoop(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoCoop(0, i, checkVal.at(i) + 10);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoCoop(0, i), checkVal.at(i) + 10);
}

void FF7Save_Test::test_chocoIntelligence()
{
    QList<int> checkVal{100, 100, 100, 100, 100 , 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoIntelligence(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoIntelligence(0, i, checkVal.at(i) + 10);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoIntelligence(0, i), checkVal.at(i) + 10);
}

void FF7Save_Test::test_chocoMaxSpeed()
{
    QList<int> checkVal{3887, 3113, 3160, 3136, 2500 , 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoMaxSpeed(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoMaxSpeed(0, i, checkVal.at(i) + 10);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoMaxSpeed(0, i), checkVal.at(i) + 10);
}

void FF7Save_Test::test_chocoMaxSprintSpeed()
{
    QList<int> checkVal{5297, 3878, 3878, 3952, 3000 , 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoMaxSprintSpeed(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoMaxSprintSpeed(0, i, checkVal.at(i) + 10);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoMaxSprintSpeed(0, i), checkVal.at(i) + 10);
}

void FF7Save_Test::test_chocoName()
{
    QStringList checkVal{QStringLiteral("Spike"), QStringLiteral("Annie"), QStringLiteral("Randal"), QStringLiteral("Liz"), QStringLiteral("Tk-421") , QString()};
    QStringList FlipVal{QStringLiteral("B598"), QStringLiteral("T5M84n"), QStringLiteral("B:VJ%$"), QStringLiteral("V)$Jkj"), QStringLiteral("Choco") , QStringLiteral("CJNQ>N")};

    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoName(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoName(0, i, FlipVal.at(i));
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoName(0, i), FlipVal.at(i));
}

void FF7Save_Test::test_chocoPCount()
{
    QList<int> checkVal{0, 0, 0, 0, 0 , 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoPCount(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoPCount(0, i, checkVal.at(i) + 10);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoPCount(0, i), checkVal.at(i) + 10);
}

void FF7Save_Test::test_chocoPersonality()
{
    QList<int> checkVal{1, 0, 0, 0, 0 , 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoPersonality(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoPersonality(0, i, checkVal.at(i) + 10);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoPersonality(0, i), checkVal.at(i) + 10);
}

void FF7Save_Test::test_chocoRacesWon()
{
//    for (int i=0; i< 6; i++)
//        qWarning() << ff7save->chocoRaceswon(0, i);
    QList<int> checkVal{54, 9, 9, 7, 2 , 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoRaceswon(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoRaceswon(0, i, checkVal.at(i) + 10);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoRaceswon(0, i), checkVal.at(i) + 10);
}

void FF7Save_Test::test_chocoSex()
{
//    for (int i=0; i< 6; i++)
//        qWarning() << ff7save->chocoSex(0, i);
    QList<bool> checkVal{false, true, false, true, true , false};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoSex(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoSex(0, i, !checkVal.at(i));
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoSex(0, i), !checkVal.at(i));
}

void FF7Save_Test::test_chocoSpeed()
{
    QList<int> checkVal{3887, 3113, 3160, 3136, 2500 , 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoSpeed(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoSpeed(0, i, checkVal.at(i) + 10);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoSpeed(0, i), checkVal.at(i) + 10);
}

void FF7Save_Test::test_chocoSprintSpeed()
{
    QList<int> checkVal{5297, 3878, 3878, 3952, 3000 , 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoSprintSpeed(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoSprintSpeed(0, i, checkVal.at(i) + 10);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoSprintSpeed(0, i), checkVal.at(i) + 10);
}

void FF7Save_Test::test_chocoStamina()
{
//    for (int i=0; i< 6; i++)
//        qWarning() << ff7save->chocoStamina(0, i);
    QList<int> checkVal{9999, 9999, 9999, 9999, 9999, 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoStamina(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoStamina(0, i, 500);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoStamina(0, i), 500);
}

void FF7Save_Test::test_chocoType()
{
//    for (int i=0; i< 6; i++)
//        qWarning() << ff7save->chocoType(0, i);
    QList<int> checkVal{4, 2, 1, 3, 4, 0};
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoType(0, i), checkVal.at(i));
    for (int i=0; i< 6; i++)
        ff7save->setChocoType(0, i, 3);
    for (int i=0; i< 6; i++)
        QCOMPARE(ff7save->chocoType(0, i), 3);
}

void FF7Save_Test::test_chocoPens()
{
    QList<qint8> checkVal{8, 0, 0, 0};
    QCOMPARE(ff7save->chocoboPens(0), checkVal);

    QList<qint8> flipVal{4, 4, 4, 4};
    for (int i=0; i< 4; i++)
        ff7save->setChocoboPen(0, i, 4);
    QCOMPARE(ff7save->chocoboPens(0), flipVal);
}

void FF7Save_Test::test_chocoRatings()
{
    QList<quint8> checkVal{2, 2, 3, 2, 2, 0};
    QList<quint8> flipVal{4, 4, 4, 4, 4, 4};
    QCOMPARE(ff7save->chocoboRatings(0), checkVal);
    for (int i=0; i< 6; i++)
        ff7save->setChocoboRating(0, i, 4);
    QCOMPARE(ff7save->chocoboRatings(0), flipVal);
}

void FF7Save_Test::test_churchProgress()
{
    QCOMPARE(ff7save->churchProgress(0), 1);
    ff7save->setChurchProgress(0, 6);
    QCOMPARE(ff7save->churchProgress(0), 6);
}

void FF7Save_Test::test_clearSlot()
{
    ff7save->newGame(1);
    QCOMPARE(ff7save->isSlotEmpty(1), false);
    ff7save->clearSlot(1);
    QCOMPARE(ff7save->isSlotEmpty(1), true);
}

void FF7Save_Test::test_condorFunds()
{
    QCOMPARE(ff7save->condorFunds(0), 31000);
    ff7save->setCondorFunds(0, 0);
    QCOMPARE(ff7save->condorFunds(0), 0);
}

void FF7Save_Test::test_condorLoses()
{
    QCOMPARE(ff7save->condorLosses(0), 2);
    ff7save->setCondorLosses(0, 5);
    QCOMPARE(ff7save->condorLosses(0), 5);
}

void FF7Save_Test::test_condorWins()
{
    QCOMPARE(ff7save->condorWins(0), 1);
    ff7save->setCondorWins(0, 5);
    QCOMPARE(ff7save->condorWins(0), 5);
}

void FF7Save_Test::test_controlMode()
{
    QCOMPARE(ff7save->controlMode(0), false);
    ff7save->setControlMode(0, true);
    QCOMPARE(ff7save->controlMode(0), true);
}

void FF7Save_Test::test_controllerMapping()
{
    QByteArray defMapping = QByteArrayLiteral("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F");
    QCOMPARE(ff7save->controllerMapping(0), defMapping);

    QByteArray flipMapping = QByteArrayLiteral("\x0F\x0E\x0D\x0C\x0B\x0A\x09\x08\x07\x06\x05\x04\x03\x02\x01\x00");
    ff7save->setControllerMapping(0, flipMapping);
    QCOMPARE(ff7save->controllerMapping(0), flipMapping);
}

void FF7Save_Test::test_copyPasteSlot()
{
    ff7save->copySlot(0);
    QCOMPARE(ff7save->isBufferSlotPopulated(), true);
    ff7save->pasteSlot(1);
    QCOMPARE(ff7save->slotFF7Data(0), ff7save->slotFF7Data(1));
}

void FF7Save_Test::test_countdownCounter()
{
    QCOMPARE(ff7save->countdownTimer(0), 0);
    ff7save->setCountdownTimer(0, 0x122300);
    QCOMPARE(ff7save->countdownTimer(0), 0x122300);
}

void FF7Save_Test::test_craterSavePoint()
{
    QCOMPARE(ff7save->craterSavePointMapID(0), 758);
    QCOMPARE(ff7save->craterSavePointX(0), 548);
    QCOMPARE(ff7save->craterSavePointY(0), 464);
    QCOMPARE(ff7save->craterSavePointZ(0), 28);
    ff7save->setCraterSavePointMapID(0, 512);
    ff7save->setCraterSavePointX(0, 8);
    ff7save->setCraterSavePointY(0, 368);
    ff7save->setCraterSavePointZ(0, 50);
    QCOMPARE(ff7save->craterSavePointMapID(0), 512);
    QCOMPARE(ff7save->craterSavePointX(0), 8);
    QCOMPARE(ff7save->craterSavePointY(0), 368);
    QCOMPARE(ff7save->craterSavePointZ(0), 50);
}

void FF7Save_Test::test_cursorMode()
{
    QCOMPARE(ff7save->cursorMode(0), false);
    ff7save->setCursorMode(0, true);
    QCOMPARE(ff7save->cursorMode(0), true);
}

void FF7Save_Test::test_slotDescription()
{
    QCOMPARE(ff7save->descCurMP(0), 999);
    ff7save->setDescCurMP(0, 50);
    QCOMPARE(ff7save->descCurMP(0), 50);

    QCOMPARE(ff7save->descCurHP(0), 9999);
    ff7save->setDescCurHP(0, 50);
    QCOMPARE(ff7save->descCurHP(0), 50);

    QCOMPARE(ff7save->descMaxHP(0), 9999);
    ff7save->setDescMaxHP(0, 50);
    QCOMPARE(ff7save->descMaxHP(0), 50);

    QCOMPARE(ff7save->descMaxMP(0), 999);
    ff7save->setDescMaxMP(0, 50);
    QCOMPARE(ff7save->descMaxMP(0), 50);

    QCOMPARE(ff7save->descLevel(0), 99);
    ff7save->setDescLevel(0, 50);
    QCOMPARE(ff7save->descLevel(0), 50);

    QCOMPARE(ff7save->descGil(0), 26898072);
    ff7save->setDescGil(0, 50);
    QCOMPARE(ff7save->descGil(0), 50);

    QCOMPARE(ff7save->descLocation(0), QStringLiteral("Hallway"));
    ff7save->setDescLocation(0, QStringLiteral("Foo"));
    QCOMPARE(ff7save->descLocation(0), QStringLiteral("Foo"));

    QCOMPARE(ff7save->descName(0), QStringLiteral("Cloud"));
    ff7save->setDescName(0, QStringLiteral("SpikyHairGuy"));
    QCOMPARE(ff7save->descName(0), QStringLiteral("SpikyHairGuy"));

    QCOMPARE(ff7save->descTime(0), 649716);
    ff7save->setDescTime(0, 788);
    QCOMPARE(ff7save->descTime(0), 788);

    QCOMPARE(ff7save->descParty(0, 0), 0);
    ff7save->setDescParty(0, 0, 8);
    QCOMPARE(ff7save->descParty(0, 0), 8);

    QCOMPARE(ff7save->descParty(0, 1), 1);
    ff7save->setDescParty(0, 1, 0);
    QCOMPARE(ff7save->descParty(0, 1), 0);

    QCOMPARE(ff7save->descParty(0, 2), 8);
    ff7save->setDescParty(0, 2, 1);
    QCOMPARE(ff7save->descParty(0, 2), 1);
}

void FF7Save_Test::test_dialogColors()
{
    QCOMPARE(ff7save->dialogColorLL(0), QStringLiteral("#ff000000"));
    ff7save->setDialogColorLL(0, QStringLiteral("#ffddccdd"));
    QCOMPARE(ff7save->dialogColorLL(0), QStringLiteral("#ffddccdd"));

    QCOMPARE(ff7save->dialogColorLR(0), QStringLiteral("#ff808080"));
    ff7save->setDialogColorLR(0, QStringLiteral("#ffcceeff"));
    QCOMPARE(ff7save->dialogColorLR(0), QStringLiteral("#ffcceeff"));

    QCOMPARE(ff7save->dialogColorUL(0), QStringLiteral("#ff000000"));
    ff7save->setDialogColorUL(0, QStringLiteral("#ffeeffdd"));
    QCOMPARE(ff7save->dialogColorUL(0), QStringLiteral("#ffeeffdd"));

    QCOMPARE(ff7save->dialogColorUR(0), QStringLiteral("#ff808080"));
    ff7save->setDialogColorUR(0, QStringLiteral("#ffffddcc"));
    QCOMPARE(ff7save->dialogColorUR(0), QStringLiteral("#ffffddcc"));
}

void FF7Save_Test::test_disc()
{
    QCOMPARE(ff7save->disc(0), 3);
    ff7save->setDisc(0, 1);
    QCOMPARE(ff7save->disc(0), 1);
    ff7save->setDisc(0, 3);
}

void FF7Save_Test::test_donProgress()
{
    QCOMPARE(ff7save->donProgress(0), 159);
    ff7save->setDonProgress(0, 0);
    QCOMPARE(ff7save->donProgress(0), 0);
}

void FF7Save_Test::test_exportCharacter()
{
    QCOMPARE(ff7save->exportCharacter(0, 1, _charFileName), true);
    QFile file (_charFileName);
    file.open(QFile::ReadOnly);
    QByteArray charData = file.readAll();
    ff7save->importCharacter(0, 1, charData);
    QCOMPARE(FF7Char::toByteArray(ff7save->character(0, 1)), charData);
}

void FF7Save_Test::test_fieldHelp()
{
    QCOMPARE(ff7save->fieldHelp(0), false);
    ff7save->setFieldHelp(0, true);
    QCOMPARE(ff7save->fieldHelp(0), true);
}

void FF7Save_Test::test_fileTypeCheck()
{
    QFile file(_saveFileNamePC);
    file.open(QFile::ReadOnly);
    QCOMPARE(ff7save->fileDataFormat(file), FF7SaveInfo::FORMAT::PC);
    file.close();

    file.setFileName(_saveFileNameDEX);
    file.open(QFile::ReadOnly);
    QCOMPARE(ff7save->fileDataFormat(file), FF7SaveInfo::FORMAT::DEX);
    file.close();

    file.setFileName(_saveFileNamePDA);
    file.open(QFile::ReadOnly);
    QCOMPARE(ff7save->fileDataFormat(file), FF7SaveInfo::FORMAT::PDA);
    file.close();

    file.setFileName(_saveFileNamePGE);
    file.open(QFile::ReadOnly);
    QCOMPARE(ff7save->fileDataFormat(file), FF7SaveInfo::FORMAT::PGE);
    file.close();

    file.setFileName(_saveFileNamePS3);
    file.open(QFile::ReadOnly);
    QCOMPARE(ff7save->fileDataFormat(file), FF7SaveInfo::FORMAT::PS3);
    file.close();

    file.setFileName(_saveFileNamePSP);
    file.open(QFile::ReadOnly);
    QCOMPARE(ff7save->fileDataFormat(file), FF7SaveInfo::FORMAT::PSP);
    file.close();

    file.setFileName(_saveFileNamePSX);
    file.open(QFile::ReadOnly);
    QCOMPARE(ff7save->fileDataFormat(file), FF7SaveInfo::FORMAT::PSX);
    file.close();

    file.setFileName(_saveFileNameSWITCH);
    file.open(QFile::ReadOnly);
    QCOMPARE(ff7save->fileDataFormat(file), FF7SaveInfo::FORMAT::SWITCH);
    file.close();

    file.setFileName(_saveFileNameVGS);
    file.open(QFile::ReadOnly);
    QCOMPARE(ff7save->fileDataFormat(file), FF7SaveInfo::FORMAT::VGS);
    file.close();

    file.setFileName(_saveFileNameVMC);
    file.open(QFile::ReadOnly);
    QCOMPARE(ff7save->fileDataFormat(file), FF7SaveInfo::FORMAT::VMC);
    file.close();
}

void FF7Save_Test::test_fileName()
{
    QCOMPARE(ff7save->fileName(), _saveFileNamePSX);
}

void FF7Save_Test::test_fixMetaData()
{
    QString path = QStringLiteral("%1/%2").arg(QCoreApplication::applicationDirPath(), _saveFileNamePC);
    QCOMPARE(ff7save->fixMetaData(path), true);
}

void FF7Save_Test::test_generatePSSignaure()
{
    QByteArray checkVal = QByteArrayLiteral("\x65\xCF\x0C\x76\xDE\x7F\xDB\x89\x52\x32\x55\x46\xFA\x78\xD5\x62\x95\xF4\x2C\xFC");
    ff7save->setFormat(FF7SaveInfo::FORMAT::PS3);
    QCOMPARE(ff7save->generatePsSaveSignature(ff7save->slotPsxRawData(0), FF7SaveInfo::signingKey(FF7SaveInfo::FORMAT::PS3)), checkVal);
    ff7save->setFormat(FF7SaveInfo::FORMAT::PSX);
}

void FF7Save_Test::test_fileHeader()
{
    QByteArray checkVal = QByteArrayLiteral("\x71\x73\x27\x06\x00\x00\x00\x00\x00");
    ff7save->setFormat(FF7SaveInfo::FORMAT::PC);
    QCOMPARE(ff7save->fileHeader(), checkVal);
    ff7save->setFormat(FF7SaveInfo::FORMAT::PSX);
}

void FF7Save_Test::test_gil()
{
    QCOMPARE(ff7save->gil(0), 26898072);
    ff7save->setGil(0, 600);
    QCOMPARE(ff7save->gil(0), 600);
}

void FF7Save_Test::test_gp()
{
    QCOMPARE(ff7save->gp(0), 3576);
    ff7save->setGp(0, 600);
    QCOMPARE(ff7save->gp(0), 600);
}

void FF7Save_Test::test_importSlot()
{
    QCOMPARE(ff7save->isSlotModified(3), false);
    ff7save->importSlot(3, _saveFileNameSWITCH, 0);
    ff7save->importSlot(0, _saveFileNamePSX, 0);
    QCOMPARE(ff7save->isSlotModified(3), true);
    QCOMPARE(ff7save->slotFF7Data(3), ff7save->slotFF7Data(0));
}

void FF7Save_Test::test_variousIS()
{
    QCOMPARE(ff7save->isFF7(0), true);
    QCOMPARE(ff7save->isJPN(0), false);
    QCOMPARE(ff7save->isPAL(0), false);
    QCOMPARE(ff7save->isNTSC(0), true);
    QCOMPARE(ff7save->isFF7(8), false);
    QCOMPARE(ff7save->isSlotEmpty(8), true);
    QCOMPARE(ff7save->isSlotEmpty(0), false);
    QCOMPARE(ff7save->isSlotModified(0), true);
}

void FF7Save_Test::test_items()
{
    QCOMPARE(FF7Item::itemId(ff7save->item(0, 0)), FF7Item::GuardSource);
    QCOMPARE(FF7Item::itemQty(ff7save->item(0, 0)), 1);
    ff7save->setItem(0, 19, FF7Item::itemEncode(FF7Item::ChocoFeather, 20));
    QCOMPARE(FF7Item::itemId(ff7save->item(0, 19)), FF7Item::ChocoFeather);
    QCOMPARE(FF7Item::itemQty(ff7save->item(0, 19)), 20);
}

void FF7Save_Test::test_itemMask1()
{
    QList<bool> checkVal{true, true, true, true, true, true, true, false};
    for (int i=0; i< 8; i++)
        QCOMPARE(ff7save->itemMask1(0, i), checkVal.at(i));
    for (int i=0; i< 8; i++)
        ff7save->setItemMask1(0, i, !checkVal.at(i));
    for (int i=0; i< 8; i++)
        QCOMPARE(ff7save->itemMask1(0, i), !checkVal.at(i));
}

void FF7Save_Test::test_keyitems()
{
    QByteArray checkVar = QByteArrayLiteral("\x24\x39\x00\x39\x00\x1F\x04\x00");
    QCOMPARE(ff7save->keyItems(0), checkVar);
    QCOMPARE(ff7save->keyItem(0, FF7Save::KEYITEMS::LUNARHARP), true);
    QCOMPARE(ff7save->keyItem(0, FF7Save::KEYITEMS::HUGEMATERIA_COREL), false);
    ff7save->setKeyItem(0, FF7Save::KEYITEMS::HUGEMATERIA_COREL, true);
    QCOMPARE(ff7save->keyItem(0, FF7Save::KEYITEMS::HUGEMATERIA_COREL), true);
}

void FF7Save_Test::test_killedEmeraldWeapon()
{
    QCOMPARE(ff7save->killedEmeraldWeapon(0), true);
    ff7save->setKilledEmeraldWeapon(0, false);
    QCOMPARE(ff7save->killedEmeraldWeapon(0), false);
}

void FF7Save_Test::test_lengthChecks()
{
    const int coreSize = 4340;
    const int zero = 0;
    const int psxSlotSize = 8192;
    const int psxSlotHeader = 512;
    const int psxSlotFooter = 3340;
    const int pcFileHeader = 9;
    const int pdaFileHeader = 54;
    const int ps3FileHeader = 132;
    const int dexFileHeader = 12096;
    const int pcFileSize = 65109;
    const int pdaFileSize = 8246;
    const int ps3FileSize = 8324;
    const int vmcFileSize = 131072;
    const int vgsFileSize = 131136;
    const int dexFileSize = 134976;
    const int oneSlot = 1;
    const int fifteenSlots = 15;

    //Type is PSX
    QCOMPARE(ff7save->lenCoreSave(), coreSize);
    QCOMPARE(ff7save->lenFileHeader(), zero);
    QCOMPARE(ff7save->lenSlotHeader(), psxSlotHeader);
    QCOMPARE(ff7save->lenSlotFooter(), psxSlotFooter);
    QCOMPARE(ff7save->lenSlot(), psxSlotSize);
    QCOMPARE(ff7save->lenFile(), psxSlotSize);
    QCOMPARE(ff7save->numberOfSlots(), oneSlot);
    ff7save->setFormat(FF7SaveInfo::FORMAT::PC);
    QCOMPARE(ff7save->lenCoreSave(), coreSize);
    QCOMPARE(ff7save->lenFileHeader(), pcFileHeader);
    QCOMPARE(ff7save->lenSlotHeader(), zero);
    QCOMPARE(ff7save->lenSlotFooter(), zero);
    QCOMPARE(ff7save->lenSlot(), coreSize);
    QCOMPARE(ff7save->lenFile(), pcFileSize);
    QCOMPARE(ff7save->numberOfSlots(), fifteenSlots);
    ff7save->setFormat(FF7SaveInfo::FORMAT::DEX);
    QCOMPARE(ff7save->lenCoreSave(), coreSize);
    QCOMPARE(ff7save->lenFileHeader(), dexFileHeader);
    QCOMPARE(ff7save->lenSlotHeader(), psxSlotHeader);
    QCOMPARE(ff7save->lenSlotFooter(), psxSlotFooter);
    QCOMPARE(ff7save->lenSlot(), psxSlotSize);
    QCOMPARE(ff7save->lenFile(), dexFileSize);
    QCOMPARE(ff7save->numberOfSlots(), fifteenSlots);
    ff7save->setFormat(FF7SaveInfo::FORMAT::PDA);
    QCOMPARE(ff7save->lenCoreSave(), coreSize);
    QCOMPARE(ff7save->lenFileHeader(), pdaFileHeader);
    QCOMPARE(ff7save->lenSlotHeader(), psxSlotHeader);
    QCOMPARE(ff7save->lenSlotFooter(), psxSlotFooter);
    QCOMPARE(ff7save->lenSlot(), psxSlotSize);
    QCOMPARE(ff7save->lenFile(), pdaFileSize);
    QCOMPARE(ff7save->numberOfSlots(), oneSlot);
    ff7save->setFormat(FF7SaveInfo::FORMAT::PS3);
    QCOMPARE(ff7save->lenCoreSave(), coreSize);
    QCOMPARE(ff7save->lenFileHeader(), ps3FileHeader);
    QCOMPARE(ff7save->lenSlotHeader(), psxSlotHeader);
    QCOMPARE(ff7save->lenSlotFooter(), psxSlotFooter);
    QCOMPARE(ff7save->lenSlot(), psxSlotSize);
    QCOMPARE(ff7save->lenFile(), ps3FileSize);
    QCOMPARE(ff7save->numberOfSlots(), oneSlot);
    ff7save->setFormat(FF7SaveInfo::FORMAT::SWITCH);
    QCOMPARE(ff7save->lenCoreSave(), coreSize);
    QCOMPARE(ff7save->lenFileHeader(), pcFileHeader);
    QCOMPARE(ff7save->lenSlotHeader(), zero);
    QCOMPARE(ff7save->lenSlotFooter(), zero);
    QCOMPARE(ff7save->lenSlot(), coreSize);
    QCOMPARE(ff7save->lenFile(), pcFileSize);
    QCOMPARE(ff7save->numberOfSlots(), fifteenSlots);
    ff7save->setFormat(FF7SaveInfo::FORMAT::VGS);
    QCOMPARE(ff7save->lenCoreSave(), coreSize);
    QCOMPARE(ff7save->lenFileHeader(), 8256);
    QCOMPARE(ff7save->lenSlotHeader(), psxSlotHeader);
    QCOMPARE(ff7save->lenSlotFooter(), psxSlotFooter);
    QCOMPARE(ff7save->lenSlot(), psxSlotSize);
    QCOMPARE(ff7save->lenFile(), vgsFileSize);
    QCOMPARE(ff7save->numberOfSlots(), fifteenSlots);
    ff7save->setFormat(FF7SaveInfo::FORMAT::VMC);
    QCOMPARE(ff7save->lenCoreSave(), coreSize);
    QCOMPARE(ff7save->lenFileHeader(), psxSlotSize);
    QCOMPARE(ff7save->lenSlotHeader(), psxSlotHeader);
    QCOMPARE(ff7save->lenSlotFooter(), psxSlotFooter);
    QCOMPARE(ff7save->lenSlot(), psxSlotSize);
    QCOMPARE(ff7save->lenFile(), vmcFileSize);
    QCOMPARE(ff7save->numberOfSlots(), fifteenSlots);
    ff7save->setFormat(FF7SaveInfo::FORMAT::UNKNOWN);
    QCOMPARE(ff7save->lenCoreSave(), coreSize);
    QCOMPARE(ff7save->lenFileHeader(), zero);
    QCOMPARE(ff7save->lenSlotHeader(), zero);
    QCOMPARE(ff7save->lenSlotFooter(), zero);
    QCOMPARE(ff7save->lenSlot(), coreSize);
    QCOMPARE(ff7save->lenFile(), zero);
    QCOMPARE(ff7save->numberOfSlots(), zero);
    ff7save->setFormat(FF7SaveInfo::FORMAT::PSX);
}

void FF7Save_Test::test_locationInfo()
{
    QCOMPARE(ff7save->location(0), QStringLiteral("Hallway"));
    QCOMPARE(ff7save->mapId(0), 1);
    QCOMPARE(ff7save->locationId(0), 88);
    QCOMPARE(ff7save->locationX(0), -395);
    QCOMPARE(ff7save->locationY(0), 34);
    QCOMPARE(ff7save->locationT(0), 13);
    QCOMPARE(ff7save->locationD(0), 104);
    QString locString = QStringLiteral("New Place");
    ff7save->setLocation(0, locString);
    ff7save->setLocationId(0, 241);
    ff7save->setLocationX(0, 733);
    ff7save->setLocationY(0, -459);
    ff7save->setLocationT(0, 296);
    ff7save->setLocationD(0, 32);
    QCOMPARE(ff7save->location(0), locString);
    QCOMPARE(ff7save->locationId(0), 241);
    QCOMPARE(ff7save->locationX(0), 733);
    QCOMPARE(ff7save->locationY(0), -459);
    QCOMPARE(ff7save->locationT(0), 296);
    QCOMPARE(ff7save->locationD(0), 32);
    ff7save->setMapId(0, 3);
    QCOMPARE(ff7save->mapId(0), 3);
    ff7save->setMapId(0, 1);
}

void FF7Save_Test::test_love()
{
    QCOMPARE(ff7save->love(0, false, FF7Save::LOVER::LOVE_AERIS), 57);
    QCOMPARE(ff7save->love(0, false, FF7Save::LOVER::LOVE_BARRET), 21);
    QCOMPARE(ff7save->love(0, false, FF7Save::LOVER::LOVE_TIFA), 59);
    QCOMPARE(ff7save->love(0, false, FF7Save::LOVER::LOVE_YUFFIE), 34);
    QCOMPARE(ff7save->love(0, true, FF7Save::LOVER::LOVE_AERIS), 133);
    QCOMPARE(ff7save->love(0, true, FF7Save::LOVER::LOVE_BARRET), 106);
    QCOMPARE(ff7save->love(0, true, FF7Save::LOVER::LOVE_TIFA), 185);
    QCOMPARE(ff7save->love(0, true, FF7Save::LOVER::LOVE_YUFFIE), 104);
    ff7save->setLove(0, false, FF7Save::LOVER::LOVE_AERIS, 50);
    ff7save->setLove(0, false, FF7Save::LOVER::LOVE_BARRET, 50);
    ff7save->setLove(0, false, FF7Save::LOVER::LOVE_TIFA, 50);
    ff7save->setLove(0, false, FF7Save::LOVER::LOVE_YUFFIE, 50);
    ff7save->setLove(0, true, FF7Save::LOVER::LOVE_AERIS, 50);
    ff7save->setLove(0, true, FF7Save::LOVER::LOVE_BARRET, 50);
    ff7save->setLove(0, true, FF7Save::LOVER::LOVE_TIFA, 50);
    ff7save->setLove(0, true, FF7Save::LOVER::LOVE_YUFFIE, 50);
    QCOMPARE(ff7save->love(0, false, FF7Save::LOVER::LOVE_AERIS), 50);
    QCOMPARE(ff7save->love(0, false, FF7Save::LOVER::LOVE_BARRET), 50);
    QCOMPARE(ff7save->love(0, false, FF7Save::LOVER::LOVE_TIFA), 50);
    QCOMPARE(ff7save->love(0, false, FF7Save::LOVER::LOVE_YUFFIE), 50);
    QCOMPARE(ff7save->love(0, true, FF7Save::LOVER::LOVE_AERIS), 50);
    QCOMPARE(ff7save->love(0, true, FF7Save::LOVER::LOVE_BARRET), 50);
    QCOMPARE(ff7save->love(0, true, FF7Save::LOVER::LOVE_TIFA), 50);
    QCOMPARE(ff7save->love(0, true, FF7Save::LOVER::LOVE_YUFFIE), 50);
}

void FF7Save_Test::test_mainProgress()
{
    QCOMPARE(ff7save->mainProgress(0), 1997);
    ff7save->setMainProgress(0, 50);
    QCOMPARE(ff7save->mainProgress(0), 50);
    ff7save->setMainProgress(0, 1997);
}

void FF7Save_Test::test_magicOrder()
{
    QCOMPARE(ff7save->magicOrder(0), 0);
    for (int i= 1 ; i < 10 ; i ++) {
        ff7save->setMagicOrder(0, i);
        int check = (i < 6)? i : 0;
        QCOMPARE(ff7save->magicOrder(0), check);
    }
}

void FF7Save_Test::test_materiaCaves()
{
    QCOMPARE(ff7save->materiaCave(0, FF7Save::CAVE_HPMP), true);
    QCOMPARE(ff7save->materiaCave(0, FF7Save::CAVE_KOTR), true);
    QCOMPARE(ff7save->materiaCave(0, FF7Save::CAVE_MIME), true);
    QCOMPARE(ff7save->materiaCave(0, FF7Save::CAVE_QUADMAGIC), true);
    ff7save->setMateriaCave(0, FF7Save::CAVE_HPMP, false);
    ff7save->setMateriaCave(0, FF7Save::CAVE_KOTR, false);
    ff7save->setMateriaCave(0, FF7Save::CAVE_MIME, false);
    ff7save->setMateriaCave(0, FF7Save::CAVE_QUADMAGIC, false);
    QCOMPARE(ff7save->materiaCave(0, FF7Save::CAVE_HPMP), false);
    QCOMPARE(ff7save->materiaCave(0, FF7Save::CAVE_KOTR), false);
    QCOMPARE(ff7save->materiaCave(0, FF7Save::CAVE_MIME), false);
    QCOMPARE(ff7save->materiaCave(0, FF7Save::CAVE_QUADMAGIC), false);
}

void FF7Save_Test::test_menuLockVisible()
{
    for (int i=0; i < 10 ; i++) {
        QCOMPARE(ff7save->menuLocked(0, i), false);
        QCOMPARE(ff7save->menuVisible(0, i), true);
    }
    for (int i=0; i < 10 ; i++) {
        ff7save->setMenuLocked(0, i, true);
        ff7save->setMenuVisible(0, i, false);
    }
    for (int i=0; i < 10 ; i++) {
        QCOMPARE(ff7save->menuLocked(0, i), true);
        QCOMPARE(ff7save->menuVisible(0, i), false);
    }
}

void FF7Save_Test::test_messageSpeed()
{
    QCOMPARE(ff7save->messageSpeed(0), 0);
    ff7save->setMessageSpeed(0, 56);
    QCOMPARE(ff7save->messageSpeed(0), 56);
}

void FF7Save_Test::test_midgarTrainFlags()
{
    QList<bool> checkVal{true, true, true, true, false, false, false, false};
    for (int i=0; i< 8;i++)
        QCOMPARE(ff7save->midgarTrainFlags(0, i ), checkVal.at(i));
    for (int i=0; i< 8;i++)
        ff7save->setMidgarTrainFlags(0, i, !checkVal.at(i));
    for (int i=0; i< 8;i++)
        QCOMPARE(ff7save->midgarTrainFlags(0, i ), !checkVal.at(i));
}

void FF7Save_Test::test_options()
{
    QCOMPARE(ff7save->options(0), 1);
    ff7save->setOptions(0, 0);
    QCOMPARE(ff7save->soundMode(0), FF7Save::SOUND_MONO);
    ff7save->setOptions(0, 1);
}

void FF7Save_Test::test_party()
{
    QList<int> checkVal{0, 1, 8};
    for(int i=0; i<3; i++)
        QCOMPARE(ff7save->party(0,i), checkVal.at(i));

    QList<int> flipVal{8, 0, 1};
    for(int i=0; i<3; i++)
        ff7save->setParty(0,i, flipVal.at(i));
    for(int i=0; i<3; i++)
        QCOMPARE(ff7save->party(0,i), flipVal.at(i));

    for(int i=0; i<3; i++)
        ff7save->setParty(0,i, checkVal.at(i));
}

void FF7Save_Test::test_partyMateria()
{
    QCOMPARE(ff7save->partyMateriaId(0, 5), 72);
    QCOMPARE(ff7save->partyMateriaAp(0, 35), 171470);
    QCOMPARE(ff7save->partyMateriaId(0, 35), 25);
    QCOMPARE(ff7save->partyMateriaAp(0, 0), 0xFFFFFF);
    ff7save->setPartyMateria(0, 0, 15, 127);
    QCOMPARE(ff7save->partyMateriaId(0, 0), 15);
    QCOMPARE(ff7save->partyMateriaAp(0, 0), 127);
}

void FF7Save_Test::test_phsAllowedVisible()
{
    QList<bool> allowedCheck{true, false, false, true, false, false, false, false, false};
    QList<bool> visibleCheck{true, true, true, false, true, true, true, true, true};
    for (int i=0; i < 9 ; i++) {
        QCOMPARE(ff7save->phsAllowed(0, i), allowedCheck.at(i));
        QCOMPARE(ff7save->phsVisible(0, i), visibleCheck.at(i));
    }
    for (int i=0; i < 9 ; i++) {
        ff7save->setPhsAllowed(0, i, !allowedCheck.at(i));
        ff7save->setPhsVisible(0, i, !visibleCheck.at(i));
    }
    for (int i=0; i < 9 ; i++) {
        QCOMPARE(ff7save->phsAllowed(0, i), !allowedCheck.at(i));
        QCOMPARE(ff7save->phsVisible(0, i), !visibleCheck.at(i));
    }
}

void FF7Save_Test::test_playedPianoOnFlashBack()
{
    QCOMPARE(ff7save->playedPianoOnFlashback(0), false);
    ff7save->setPlayedPianoOnFlashback(0, true);
    QCOMPARE(ff7save->playedPianoOnFlashback(0), true);
}

void FF7Save_Test::test_region()
{
    ff7save->loadFile(_saveFileNamePSX);
    QCOMPARE(ff7save->region(0), QStringLiteral("BASCUS-94163FF7-S01"));
    ff7save->setRegion(0, QStringLiteral("PAL-E"));
    QCOMPARE(ff7save->region(0), QStringLiteral("BESCES-00867FF7-S01"));
    ff7save->setRegion(0, QStringLiteral("PAL-FR"));
    QCOMPARE(ff7save->region(0), QStringLiteral("BESCES-00868FF7-S01"));
    ff7save->setRegion(0, QStringLiteral("PAL-DE"));
    QCOMPARE(ff7save->region(0), QStringLiteral("BESCES-00869FF7-S01"));
    ff7save->setRegion(0, QStringLiteral("PAL-ES"));
    QCOMPARE(ff7save->region(0), QStringLiteral("BESCES-00900FF7-S01"));
    ff7save->setRegion(0, QStringLiteral("NTSC-J"));
    QCOMPARE(ff7save->region(0), QStringLiteral("BISLPS-00700FF7-S01"));
    ff7save->setRegion(0, QStringLiteral("NTSC-JI"));
    QCOMPARE(ff7save->region(0), QStringLiteral("BISLPS-01057FF7-S01"));
    ff7save->setRegion(0, QStringLiteral("NTSC-U"));
    QCOMPARE(ff7save->region(0), QStringLiteral("BASCUS-94163FF7-S01"));
}

void FF7Save_Test::test_runs()
{
    QCOMPARE(ff7save->runs(0), 504);
    ff7save->setRuns(0, 999);
    QCOMPARE(ff7save->runs(0), 999);
}

void FF7Save_Test::test_seenPandorasBox()
{
    QCOMPARE(ff7save->seenPandorasBox(0), true);
    ff7save->setSeenPandorasBox(0, false);
    QCOMPARE(ff7save->seenPandorasBox(0), false);
}

void FF7Save_Test::test_saveIcon()
{
    QString frame1 = QStringLiteral("00001D57DD3EBA42B75E535A382EF81DF339EE59EC71B31D8E39877D0831FF7FFF152176F3FFFFFFDF5D326366DADDFDDF8A66777756DDFD4F7168137B22D5FD554711813E22A2FDDF1511B35E7252F8AF32312B61B277FD8F376216617367F8CF67BB32B876BBFDBF76EBB3ECB7CBF87FB71B3111E7D7FD7F5B383111EBD8FDBFAAB71131EBDCFDAFDDB818B3CEDEFDDFDDBAEDCCCCDEFDFFFFBFEF5CECEEFF");
    QCOMPARE(ff7save->slotIcon(0).at(0).toHex().toUpper(), frame1);
}

void FF7Save_Test::test_snowboardScore_Time()
{
    QList<int> checkScore{24, 0, 0};
    QList<int> flipScore{38, 42, 78};
    QList<QString> checkTime{QStringLiteral("02362790"), QStringLiteral("00000000"), QStringLiteral("00000000")};
    QList<QString> flipTime{QStringLiteral("09265290"), QStringLiteral("03030303"), QStringLiteral("50505050")};
    for(int i=0; i<3; i++) {
        QCOMPARE(ff7save->snowboardScore(0, i), checkScore.at(i));
        QCOMPARE(ff7save->snowboardTime(0, i), checkTime.at(i));
    }
    for(int i=0; i<3; i++) {
        ff7save->setSnowboardScore(0, i, flipScore.at(i));
        ff7save->setSnowboardTime(0, i , flipTime.at(i));
    }
    for(int i=0; i<3; i++) {
        QCOMPARE(ff7save->snowboardScore(0, i), flipScore.at(i));
        QCOMPARE(ff7save->snowboardTime(0, i), flipTime.at(i));
    }
}

void FF7Save_Test::test_soundMode()
{
    QCOMPARE(ff7save->soundMode(0), 1);
    ff7save->setSoundMode(0, 0);
    QCOMPARE(ff7save->soundMode(0), 0);
}

void FF7Save_Test::test_speedScore()
{
    QList<quint16> checkVar{0, 900, 810, 0};
    QList<quint16> flipVar{0, 8, 90, 10};
    for(int i=0; i<4; i++)
        QCOMPARE(ff7save->speedScore(0,i), checkVar.at(i));
    for(int i=0; i<4; i++)
        ff7save->setSpeedScore(0,i, flipVar.at(i));
    for(int i=0; i<4; i++)
        QCOMPARE(ff7save->speedScore(0,i), flipVar.at(i));
}

void FF7Save_Test::test_stableMask_Owned_Occupied()
{
    QCOMPARE(ff7save->stablesOwned(0), 6);
    QCOMPARE(ff7save->stablesOccupied(0), 5);
    QCOMPARE(ff7save->stableMask(0), 31);
    ff7save->setStablesOwned(0, 4);
    ff7save->setStablesOccupied(0, 3);
    ff7save->setStableMask(0, 15);
    QCOMPARE(ff7save->stablesOwned(0), 4);
    QCOMPARE(ff7save->stablesOccupied(0), 3);
    QCOMPARE(ff7save->stableMask(0), 15);
}

void FF7Save_Test::test_startBombingMissing()
{
    QCOMPARE(ff7save->startBombingMission(0), false);
    ff7save->setStartBombingMission(0, true);
    QCOMPARE(ff7save->startBombingMission(0), true);
    ff7save->setStartBombingMission(0, false);
}

void FF7Save_Test::test_steps()
{
    QCOMPARE(ff7save->steps(0), 65529);
    ff7save->setSteps(0, 14);
    QCOMPARE(ff7save->steps(0), 14);
}

void FF7Save_Test::test_stolenMateria()
{
    QCOMPARE(ff7save->stolenMateriaId(0, 0), 68);
    QCOMPARE(ff7save->stolenMateriaAp(0, 0), 10350);
    QCOMPARE(ff7save->stolenMateriaId(0, 5), 59);
    QCOMPARE(ff7save->stolenMateriaAp(0, 5), 680);
    ff7save->setStolenMateria(0, 0, 15, 127);
    QCOMPARE(ff7save->stolenMateriaId(0, 0), 15);
    QCOMPARE(ff7save->stolenMateriaAp(0, 0), 127);
}

void FF7Save_Test::test_subMiniGameVictory()
{
    QCOMPARE(ff7save->subMiniGameVictory(0), false);
    ff7save->setSubMiniGameVictory(0, true);
    QCOMPARE(ff7save->subMiniGameVictory(0), true);
}

void FF7Save_Test::test_time()
{
    QCOMPARE(ff7save->time(0), 649716);
    ff7save->setTime(0, 123456);
    QCOMPARE(ff7save->time(0), 123456);
}

void FF7Save_Test::test_turtleParadiseFlyersSeen()
{
    QList<bool> checkVar{true, true, true, true, true, true, true};
    QCOMPARE(ff7save->turtleParadiseFlyersSeen(0), 255);
    for(int i=0;i<7;i++)
        QCOMPARE(ff7save->turtleParadiseFlyerSeen(0, i), checkVar.at(i));
}

void FF7Save_Test::test_Tut_Save_Sub()
{
    QCOMPARE(ff7save->tutSave(0), 58);
    ff7save->setTutSave(0, 5);
    QCOMPARE(ff7save->tutSave(0), 5);
    QCOMPARE(ff7save->tutSub(0), 47);
    ff7save->setTutSub(0, 4);
    QCOMPARE(ff7save->tutSub(0), 4);
}

void FF7Save_Test::test_uWeaponHp()
{
    QCOMPARE(ff7save->uWeaponHp(0), 6765824);
    ff7save->setUWeaponHp(0, 65538);
    QCOMPARE(ff7save->uWeaponHp(0), 65538);
}

void FF7Save_Test::test_unknown()
{
    QByteArray checkVar = QByteArrayLiteral("\x00\xFB\xDA\x00\x00\xFB\xDA\x00\x00\x00\x00\x00\x00");
    QByteArray flipVar = QByteArrayLiteral("\xFF\xFE\xDB\x33\x33\xFB\xDA\xFE\xFF\x43\x45\x76\xA1");
    QCOMPARE(ff7save->unknown(0, 4), checkVar);
    ff7save->setUnknown(0, 4, flipVar);
    QCOMPARE(ff7save->unknown(0, 4), flipVar);
    ff7save->setUnknown(0, 4, checkVar);
}

void FF7Save_Test::test_vincent_yuffie_unlocked()
{
    QCOMPARE(ff7save->vincentUnlocked(0), true);
    QCOMPARE(ff7save->yuffieUnlocked(0), true);
    ff7save->setVincentUnlocked(0, false);
    ff7save->setYuffieUnlocked(0, false);
    QCOMPARE(ff7save->vincentUnlocked(0), false);
    QCOMPARE(ff7save->yuffieUnlocked(0), false);
}

void FF7Save_Test::test_worldChocobo()
{
    QList<bool> checkVar{false, false, false, false, false, false, false};
    for(int i=0; i<7; i++)
        QCOMPARE(ff7save->worldChocobo(0, i), checkVar.at(i));
    for(int i=0; i<7; i++)
        ff7save->setWorldChocobo(0, i, !checkVar.at(i));
    for(int i=0; i<7; i++)
        QCOMPARE(ff7save->worldChocobo(0, i), !checkVar.at(i));
}

void FF7Save_Test::test_worldVehicle()
{
    QList<bool> checkVar{false, false, false, false, true, false, false};
    for(int i=0; i<7; i++)
        QCOMPARE(ff7save->worldVehicle(0, i), checkVar.at(i));
    for(int i=0; i<7; i++)
        ff7save->setWorldVehicle(0, i, !checkVar.at(i));
    for(int i=0; i<7; i++)
        QCOMPARE(ff7save->worldVehicle(0, i), !checkVar.at(i));
}

void FF7Save_Test::test_worldCoordsBH()
{
    QCOMPARE(ff7save->worldCoordsBhID(0), 3);
    QCOMPARE(ff7save->worldCoordsBhX(0), 171727);
    QCOMPARE(ff7save->worldCoordsBhY(0), 149607);
    QCOMPARE(ff7save->worldCoordsBhZ(0), 284);
    QCOMPARE(ff7save->worldCoordsBhAngle(0), 128);
    ff7save->setWorldCoordsBhID(0, 0);
    ff7save->setWorldCoordsBhX(0, 108);
    ff7save->setWorldCoordsBhY(0, 125);
    ff7save->setWorldCoordsBhZ(0, 133);
    ff7save->setWorldCoordsBhAngle(0, 12);
    QCOMPARE(ff7save->worldCoordsBhID(0), 0);
    QCOMPARE(ff7save->worldCoordsBhX(0), 108);
    QCOMPARE(ff7save->worldCoordsBhY(0), 125);
    QCOMPARE(ff7save->worldCoordsBhZ(0), 133);
    QCOMPARE(ff7save->worldCoordsBhAngle(0), 12);
}

void FF7Save_Test::test_worldCoordsDURW()
{
    QCOMPARE(ff7save->worldCoordsDurwID(0), 29);
    QCOMPARE(ff7save->worldCoordsDurwX(0), 117954);
    QCOMPARE(ff7save->worldCoordsDurwY(0), 157473);
    QCOMPARE(ff7save->worldCoordsDurwZ(0), 15933);
    QCOMPARE(ff7save->worldCoordsDurwAngle(0), 32);
    ff7save->setWorldCoordsDurwID(0, 0);
    ff7save->setWorldCoordsDurwX(0, 108);
    ff7save->setWorldCoordsDurwY(0, 125);
    ff7save->setWorldCoordsDurwZ(0, 133);
    ff7save->setWorldCoordsDurwAngle(0, 12);
    QCOMPARE(ff7save->worldCoordsDurwID(0), 0);
    QCOMPARE(ff7save->worldCoordsDurwX(0), 108);
    QCOMPARE(ff7save->worldCoordsDurwY(0), 125);
    QCOMPARE(ff7save->worldCoordsDurwZ(0), 133);
    QCOMPARE(ff7save->worldCoordsDurwAngle(0), 12);
}

void FF7Save_Test::test_worldCoordsLeader()
{
    QCOMPARE(ff7save->worldCoordsLeaderID(0), 0);
    QCOMPARE(ff7save->worldCoordsLeaderX(0), 108840);
    QCOMPARE(ff7save->worldCoordsLeaderY(0), 125942);
    QCOMPARE(ff7save->worldCoordsLeaderZ(0), 1331);
    QCOMPARE(ff7save->worldCoordsLeaderAngle(0), 128);
    ff7save->setWorldCoordsLeaderID(0, 3);
    ff7save->setWorldCoordsLeaderX(0, 108);
    ff7save->setWorldCoordsLeaderY(0, 125);
    ff7save->setWorldCoordsLeaderZ(0, 133);
    ff7save->setWorldCoordsLeaderAngle(0, 12);
    QCOMPARE(ff7save->worldCoordsLeaderID(0), 3);
    QCOMPARE(ff7save->worldCoordsLeaderX(0), 108);
    QCOMPARE(ff7save->worldCoordsLeaderY(0), 125);
    QCOMPARE(ff7save->worldCoordsLeaderZ(0), 133);
    QCOMPARE(ff7save->worldCoordsLeaderAngle(0), 12);
}

void FF7Save_Test::test_worldCoordsSub()
{
    QCOMPARE(ff7save->worldCoordsSubID(0), 13);
    QCOMPARE(ff7save->worldCoordsSubX(0), 133073);
    QCOMPARE(ff7save->worldCoordsSubY(0), 153467);
    QCOMPARE(ff7save->worldCoordsSubZ(0), 12096);
    QCOMPARE(ff7save->worldCoordsSubAngle(0), 245);
    ff7save->setWorldCoordsSubID(0, 0);
    ff7save->setWorldCoordsSubX(0, 108);
    ff7save->setWorldCoordsSubY(0, 125);
    ff7save->setWorldCoordsSubZ(0, 133);
    ff7save->setWorldCoordsSubAngle(0, 12);
    QCOMPARE(ff7save->worldCoordsSubID(0), 0);
    QCOMPARE(ff7save->worldCoordsSubX(0), 108);
    QCOMPARE(ff7save->worldCoordsSubY(0), 125);
    QCOMPARE(ff7save->worldCoordsSubZ(0), 133);
    QCOMPARE(ff7save->worldCoordsSubAngle(0), 12);
}

void FF7Save_Test::test_worldCoordsTc()
{
    QCOMPARE(ff7save->worldCoordsTcID(0), 19);
    QCOMPARE(ff7save->worldCoordsTcX(0), 239123);
    QCOMPARE(ff7save->worldCoordsTcY(0), 137128);
    QCOMPARE(ff7save->worldCoordsTcZ(0), 230);
    QCOMPARE(ff7save->worldCoordsTcAngle(0), 69);
    ff7save->setWorldCoordsTcID(0, 0);
    ff7save->setWorldCoordsTcX(0, 108);
    ff7save->setWorldCoordsTcY(0, 125);
    ff7save->setWorldCoordsTcZ(0, 133);
    ff7save->setWorldCoordsTcAngle(0, 12);
    QCOMPARE(ff7save->worldCoordsTcID(0), 0);
    QCOMPARE(ff7save->worldCoordsTcX(0), 108);
    QCOMPARE(ff7save->worldCoordsTcY(0), 125);
    QCOMPARE(ff7save->worldCoordsTcZ(0), 133);
    QCOMPARE(ff7save->worldCoordsTcAngle(0), 12);
}

void FF7Save_Test::test_worldCoordsWChoco()
{
    QCOMPARE(ff7save->worldCoordsWchocoID(0), 4);
    QCOMPARE(ff7save->worldCoordsWchocoX(0), 229402);
    QCOMPARE(ff7save->worldCoordsWchocoY(0), 148148);
    QCOMPARE(ff7save->worldCoordsWchocoZ(0), 253);
    QCOMPARE(ff7save->worldCoordsWchocoAngle(0), 247);
    ff7save->setWorldCoordsWchocoID(0, 0);
    ff7save->setWorldCoordsWchocoX(0, 108);
    ff7save->setWorldCoordsWchocoY(0, 125);
    ff7save->setWorldCoordsWchocoZ(0, 133);
    ff7save->setWorldCoordsWchocoAngle(0, 12);
    QCOMPARE(ff7save->worldCoordsWchocoID(0), 0);
    QCOMPARE(ff7save->worldCoordsWchocoX(0), 108);
    QCOMPARE(ff7save->worldCoordsWchocoY(0), 125);
    QCOMPARE(ff7save->worldCoordsWchocoZ(0), 133);
    QCOMPARE(ff7save->worldCoordsWchocoAngle(0), 12);
}

void FF7Save_Test::test_battleSpecialWins()
{
    QCOMPARE(ff7save->specialBattleWins(0), 16);
    ff7save->setSpecialBattleWins(0, 0xFF);
    QCOMPARE(ff7save->specialBattleWins(0), 0xFF);
    ff7save->setSpecialBattleWins(0, 0);
    QCOMPARE(ff7save->specialBattleWins(0), 0);
}

void FF7Save_Test::test_nonff7()
{
    QFile file("n7.mc");
    QVERIFY(file.open(QIODevice::WriteOnly));
    file.write(_fileData);
    file.close();
    ff7save = new FF7Save();
    QVERIFY(ff7save->loadFile("n7.mc"));
    QCOMPARE(ff7save->slotPsxRawData(0), _non7slotData);
    QCOMPARE(ff7save->region(0), _n7region);
    QCOMPARE(ff7save->format(), FF7SaveInfo::FORMAT::PGE);
}

void FF7Save_Test::test_non7Export()
{
    QVERIFY(ff7save->exportFile(_saveFileNameVMC, FF7SaveInfo::FORMAT::VMC, 0));
}

void FF7Save_Test::test_editN7()
{
    auto data = _non7slotData;
    data.replace(0x100, 1, QByteArray::fromRawData("\x13", 1));
    ff7save->setSlotPsxRawData(0, data);
    QVERIFY(ff7save->exportFile(_saveFileNameVMC, FF7SaveInfo::FORMAT::VMC, 0));
}

QTEST_MAIN(FF7Save_Test)

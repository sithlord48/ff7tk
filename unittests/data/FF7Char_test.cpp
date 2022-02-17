/****************************************************************************/
//    copyright 2021 - 2022  Chris Rizzitello <sithlord48@gmail.com>        //
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

#include <QtTest>

#include "FF7Char_test.h"

void FF7Char_Test::initTestCase()
{
    FF7CHARCloud.id = FF7Char::Cloud;
    FF7CHARCloud.level = 0x63;
    FF7CHARCloud.strength = 0x64;
    FF7CHARCloud.vitality = 0x5D;
    FF7CHARCloud.magic = 0x64;
    FF7CHARCloud.spirit = 0x62;
    FF7CHARCloud.dexterity = 0x3D;
    FF7CHARCloud.luck = 0x1D;
    FF7CHARCloud.strength_bonus = 0x9B;
    FF7CHARCloud.vitality_bonus = 0x87;
    FF7CHARCloud.magic_bonus = 0x68;
    FF7CHARCloud.spirit_bonus = 0x18;
    FF7CHARCloud.dexterity_bonus = 0xC2;
    FF7CHARCloud.luck_bonus = 0xE5;
    FF7CHARCloud.limitlevel = 4;
    FF7CHARCloud.limitbar = 0xFB;
    FF7CHARCloud.name[0] = 0x23;
    FF7CHARCloud.name[1] = 0x4C;
    FF7CHARCloud.name[2] = 0x4F;
    FF7CHARCloud.name[3] = 0x55;
    FF7CHARCloud.name[4] = 0x44;
    FF7CHARCloud.name[5] = 0xFF;
    FF7CHARCloud.name[6] = 0xFF;
    FF7CHARCloud.name[7] = 0x00;
    FF7CHARCloud.name[8] = 0x00;
    FF7CHARCloud.name[9] = 0xFF;
    FF7CHARCloud.name[10] = 0xFF;
    FF7CHARCloud.name[11] = 0xFF;
    FF7CHARCloud.weapon = 0x0F;
    FF7CHARCloud.armor = 0x1B;
    FF7CHARCloud.accessory = 0x12;
    FF7CHARCloud.statusFlag = 0x00;
    FF7CHARCloud.rowFlag = 0xFE;
    FF7CHARCloud.tnlFlag = 0x3D;
    FF7CHARCloud.limits = 0x02DB;
    FF7CHARCloud.kills = 0x0C35;
    FF7CHARCloud.timesused1 = 0x0014;
    FF7CHARCloud.timesused2 = 0x000E;
    FF7CHARCloud.timesused3 = 0x002D;
    FF7CHARCloud.curHP = 0x270F;
    FF7CHARCloud.baseHP = 0x23AE;
    FF7CHARCloud.curMP = 0x03E7;
    FF7CHARCloud.baseMP = 0x036D;
    FF7CHARCloud.z_4[0]= 0x00;
    FF7CHARCloud.z_4[1]= 0x00;
    FF7CHARCloud.z_4[2]= 0x00;
    FF7CHARCloud.z_4[3]= 0x00;
    FF7CHARCloud.maxHP = 0x270F;
    FF7CHARCloud.maxMP = 0x03E7;
    FF7CHARCloud.exp = 0x00DF2001;
    FF7CHARCloud.materias[0].id = 0x49;
    FF7CHARCloud.materias[0].ap[0] = 0x00;
    FF7CHARCloud.materias[0].ap[1] = 0x00;
    FF7CHARCloud.materias[0].ap[2] = 0x00;
    FF7CHARCloud.materias[1].id = 0x1B;
    FF7CHARCloud.materias[1].ap[0] = 0xFF;
    FF7CHARCloud.materias[1].ap[1] = 0xFF;
    FF7CHARCloud.materias[1].ap[2] = 0xFF;
    FF7CHARCloud.materias[2].id = 0x49;
    FF7CHARCloud.materias[2].ap[0] = 0x90;
    FF7CHARCloud.materias[2].ap[1] = 0x01;
    FF7CHARCloud.materias[2].ap[2] = 0x00;
    FF7CHARCloud.materias[3].id = 0x1C;
    FF7CHARCloud.materias[3].ap[0] = 0xFF;
    FF7CHARCloud.materias[3].ap[1] = 0xFF;
    FF7CHARCloud.materias[3].ap[2] = 0xFF;
    FF7CHARCloud.materias[4].id = 0xFF;
    FF7CHARCloud.materias[4].ap[0] = 0xFF;
    FF7CHARCloud.materias[4].ap[1] = 0xFF;
    FF7CHARCloud.materias[4].ap[2] = 0xFF;
    FF7CHARCloud.materias[5].id = 0x30;
    FF7CHARCloud.materias[5].ap[0] = 0x82;
    FF7CHARCloud.materias[5].ap[1] = 0x14;
    FF7CHARCloud.materias[5].ap[2] = 0x00;
    FF7CHARCloud.materias[6].id = 0xFF;
    FF7CHARCloud.materias[6].ap[0] = 0xFF;
    FF7CHARCloud.materias[6].ap[1] = 0xFF;
    FF7CHARCloud.materias[6].ap[2] = 0xFF;
    FF7CHARCloud.materias[7].id = 0x5A;
    FF7CHARCloud.materias[7].ap[0] = 0x26;
    FF7CHARCloud.materias[7].ap[1] = 0x02;
    FF7CHARCloud.materias[7].ap[2] = 0x00;
    FF7CHARCloud.materias[8].id = 0x15;
    FF7CHARCloud.materias[8].ap[0] = 0xFF;
    FF7CHARCloud.materias[8].ap[1] = 0xFF;
    FF7CHARCloud.materias[8].ap[2] = 0xFF;
    FF7CHARCloud.materias[9].id = 0x08;
    FF7CHARCloud.materias[9].ap[0] = 0xFF;
    FF7CHARCloud.materias[9].ap[1] = 0xFF;
    FF7CHARCloud.materias[9].ap[2] = 0xFF;
    FF7CHARCloud.materias[10].id = 0x01;
    FF7CHARCloud.materias[10].ap[0] = 0xFF;
    FF7CHARCloud.materias[10].ap[1] = 0xFF;
    FF7CHARCloud.materias[10].ap[2] = 0xFF;
    FF7CHARCloud.materias[11].id = 0x0B;
    FF7CHARCloud.materias[11].ap[0] = 0xFF;
    FF7CHARCloud.materias[11].ap[1] = 0xFF;
    FF7CHARCloud.materias[11].ap[2] = 0xFF;
    FF7CHARCloud.materias[12].id = 0x00;
    FF7CHARCloud.materias[12].ap[0] = 0xFF;
    FF7CHARCloud.materias[12].ap[1] = 0xFF;
    FF7CHARCloud.materias[12].ap[2] = 0xFF;
    FF7CHARCloud.materias[13].id = 0xFF;
    FF7CHARCloud.materias[13].ap[0] = 0xFF;
    FF7CHARCloud.materias[13].ap[1] = 0xFF;
    FF7CHARCloud.materias[13].ap[2] = 0xFF;
    FF7CHARCloud.materias[14].id = 0xFF;
    FF7CHARCloud.materias[14].ap[0] = 0xFF;
    FF7CHARCloud.materias[14].ap[1] = 0xFF;
    FF7CHARCloud.materias[14].ap[2] = 0xFF;
    FF7CHARCloud.materias[15].id = 0xFF;
    FF7CHARCloud.materias[15].ap[0] = 0xFF;
    FF7CHARCloud.materias[15].ap[1] = 0xFF;
    FF7CHARCloud.materias[15].ap[2] = 0xFF;
    FF7CHARCloud.expNext = 0;
}

void FF7Char_Test::test_fromByteArray()
{
    _charData = FF7Char::fromByteArray(_cloudData);
    QCOMPARE(_charData.id, FF7CHARCloud.id);
    QCOMPARE(_charData.strength, FF7CHARCloud.strength);
    QCOMPARE(_charData.vitality, FF7CHARCloud.vitality);
    QCOMPARE(_charData.magic, FF7CHARCloud.magic);
    QCOMPARE(_charData.spirit, FF7CHARCloud.spirit);
    QCOMPARE(_charData.dexterity, FF7CHARCloud.dexterity);
    QCOMPARE(_charData.luck, FF7CHARCloud.luck);
    QCOMPARE(_charData.strength_bonus, FF7CHARCloud.strength_bonus);
    QCOMPARE(_charData.vitality_bonus, FF7CHARCloud.vitality_bonus);
    QCOMPARE(_charData.magic_bonus, FF7CHARCloud.magic_bonus);
    QCOMPARE(_charData.spirit_bonus, FF7CHARCloud.spirit_bonus);
    QCOMPARE(_charData.dexterity_bonus, FF7CHARCloud.dexterity_bonus);
    QCOMPARE(_charData.luck_bonus, FF7CHARCloud.luck_bonus);
    QCOMPARE(_charData.limitlevel, FF7CHARCloud.limitlevel);
    QCOMPARE(_charData.limitbar, FF7CHARCloud.limitbar);
    for (int n =0 ; n < 12; n++) {
        QCOMPARE(_charData.name[n], FF7CHARCloud.name[n]);
    }
    QCOMPARE(_charData.weapon, FF7CHARCloud.weapon);
    QCOMPARE(_charData.armor, FF7CHARCloud.armor);
    QCOMPARE(_charData.accessory, FF7CHARCloud.accessory);
    QCOMPARE(_charData.statusFlag, FF7CHARCloud.statusFlag);
    QCOMPARE(_charData.rowFlag, FF7CHARCloud.rowFlag);
    QCOMPARE(_charData.tnlFlag, FF7CHARCloud.tnlFlag);
    QCOMPARE(_charData.limits, FF7CHARCloud.limits);
    QCOMPARE(_charData.kills, FF7CHARCloud.kills);
    QCOMPARE(_charData.timesused1, FF7CHARCloud.timesused1);
    QCOMPARE(_charData.timesused2, FF7CHARCloud.timesused2);
    QCOMPARE(_charData.timesused3, FF7CHARCloud.timesused3);
    QCOMPARE(_charData.curHP, FF7CHARCloud.curHP);
    QCOMPARE(_charData.baseHP, FF7CHARCloud.baseHP);
    QCOMPARE(_charData.curMP, FF7CHARCloud.curMP);
    QCOMPARE(_charData.baseMP, FF7CHARCloud.baseMP);
    for (int z =0 ; z < 4; z++) {
        QCOMPARE(_charData.z_4[z], FF7CHARCloud.z_4[z]);
    }
    QCOMPARE(_charData.maxHP, FF7CHARCloud.maxHP);
    QCOMPARE(_charData.maxMP, FF7CHARCloud.maxMP);
    QCOMPARE(_charData.exp, FF7CHARCloud.exp);
    QCOMPARE(_charData.expNext, FF7CHARCloud.expNext);
    for (int i =0 ; i < 16; i++) {
        QCOMPARE(_charData.materias[i].id, FF7CHARCloud.materias[i].id);
        for (int j =0 ; j < 3; j++) {
            QCOMPARE(_charData.materias[i].ap[j], FF7CHARCloud.materias[i].ap[j]);
        }
    }
}
void FF7Char_Test::test_toByteArray()
{
    QCOMPARE(FF7Char::toByteArray(_charData), _cloudData);
}

QTEST_MAIN(FF7Char_Test)

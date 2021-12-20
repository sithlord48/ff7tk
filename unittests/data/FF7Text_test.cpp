/****************************************************************************/
//    copyright 2021 - 2022 Chris Rizzitello <sithlord48@gmail.com>         //
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

#include "FF7Text_test.h"

void FF7Text_Test::test_toPCENG()
{
    QCOMPARE(FF7Text::toPC(range0x), range0xE);
    QCOMPARE(FF7Text::toPC(range1x), range1xE);
    QCOMPARE(FF7Text::toPC(range2x), range2xE);
    QCOMPARE(FF7Text::toPC(range3x), range3xE);
    QCOMPARE(FF7Text::toPC(range4x), range4xE);
    QCOMPARE(FF7Text::toPC(range5x), range5xE);
    QCOMPARE(FF7Text::toPC(range6x), range6xE);
    QCOMPARE(FF7Text::toPC(range7x), range7xE);
    QCOMPARE(FF7Text::toPC(range8x), range8xE);
    QCOMPARE(FF7Text::toPC(range9x), range9xE);
    QCOMPARE(FF7Text::toPC(rangeAx), rangeAxE);
    QCOMPARE(FF7Text::toPC(rangeBx), rangeBxE);
    QCOMPARE(FF7Text::toPC(rangeCx), rangeCxE);
    QCOMPARE(FF7Text::toPC(rangeDx), rangeDxE);
    QCOMPARE(FF7Text::toPC(rangeEx), rangeExE);
    QCOMPARE(FF7Text::toPC(rangeFx), rangeFxE);
}

void FF7Text_Test::test_toFF7ENG()
{
    QCOMPARE(FF7Text::toFF7(range0xE), range0x);
    QCOMPARE(FF7Text::toFF7(range1xE), range1x);
    QCOMPARE(FF7Text::toFF7(range2xE), range2x);
    QCOMPARE(FF7Text::toFF7(range3xE), range3x);
    QCOMPARE(FF7Text::toFF7(range4xE), range4x);
    //All Space Characters will evaluate to 00
    QByteArray temp = range5x;
    temp.replace('\x5F', '\x00');
    QCOMPARE(FF7Text::toFF7(range5xE), temp);
    QCOMPARE(FF7Text::toFF7(range6xE), range6x);
    QCOMPARE(FF7Text::toFF7(range7xE), range7x);
    QCOMPARE(FF7Text::toFF7(range8xE), range8x);
    QCOMPARE(FF7Text::toFF7(range9xE), range9x);
    //All Space Characters will evaluate to 00
    temp = rangeAx;
    temp.replace('\xAA', '\x00');
    QCOMPARE(FF7Text::toFF7(rangeAxE), temp);
    QCOMPARE(FF7Text::toFF7(rangeBxE), rangeBx);
    QEXPECT_FAIL("", "Expected Failure", Continue);
    QCOMPARE(FF7Text::toFF7(rangeCxE),rangeCx);
    //All Space Characters will evaluate to 00
    //0xD2 and 0xD3 are duplicates of 0x84 and 0x85
    temp = QByteArray::fromRawData("\x00\xD1\x84\x85\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    QCOMPARE(FF7Text::toFF7(rangeDxE), temp);
    temp = QByteArray::fromRawData("\x00\xE1\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 16);
    QCOMPARE(FF7Text::toFF7(rangeExE), temp);
    temp = QByteArray::fromRawData("\x00\x00\x00\x00\x00\x00\x00\x00\x00", 9);
    QCOMPARE(FF7Text::toFF7(rangeFxE), temp);
}
void FF7Text_Test::test_setJapanese()
{
    QSignalSpy(FF7Text::instance(), &FF7Text::languageChanged);
    FF7Text::setJapanese(true);
}

void FF7Text_Test::test_toPCJPN()
{
    QCOMPARE(FF7Text::toPC(range0x), range0xJ);
    QCOMPARE(FF7Text::toPC(range1x), range1xJ);
    QCOMPARE(FF7Text::toPC(range2x), range2xJ);
    QCOMPARE(FF7Text::toPC(range3x), range3xJ);
    QCOMPARE(FF7Text::toPC(range4x), range4xJ);
    QCOMPARE(FF7Text::toPC(range5x), range5xJ);
    QCOMPARE(FF7Text::toPC(range6x), range6xJ);
    QCOMPARE(FF7Text::toPC(range7x), range7xJ);
    QCOMPARE(FF7Text::toPC(range8x), range8xJ);
    QCOMPARE(FF7Text::toPC(range9x), range9xJ);
    QCOMPARE(FF7Text::toPC(rangeAx), rangeAxJ);
    QCOMPARE(FF7Text::toPC(rangeBx), rangeBxJ);
    QCOMPARE(FF7Text::toPC(rangeCx), rangeCxJ);
    QCOMPARE(FF7Text::toPC(rangeDx), rangeDxJ);
    QCOMPARE(FF7Text::toPC(rangeEx), rangeExJ);
    QCOMPARE(FF7Text::toPC(rangeFx), rangeFxJ);
    QCOMPARE(FF7Text::toPC(rangeFA0x), rangeFA0xJ);
    QCOMPARE(FF7Text::toPC(rangeFA1x), rangeFA1xJ);
    QCOMPARE(FF7Text::toPC(rangeFA2x), rangeFA2xJ);
    QCOMPARE(FF7Text::toPC(rangeFA3x), rangeFA3xJ);
    QCOMPARE(FF7Text::toPC(rangeFA4x), rangeFA4xJ);
    QCOMPARE(FF7Text::toPC(rangeFA5x), rangeFA5xJ);
    QCOMPARE(FF7Text::toPC(rangeFA6x), rangeFA6xJ);
    QCOMPARE(FF7Text::toPC(rangeFA7x), rangeFA7xJ);
    QCOMPARE(FF7Text::toPC(rangeFA8x), rangeFA8xJ);
    QCOMPARE(FF7Text::toPC(rangeFA9x), rangeFA9xJ);
    QCOMPARE(FF7Text::toPC(rangeFAAx), rangeFAAxJ);
    QCOMPARE(FF7Text::toPC(rangeFABx), rangeFABxJ);
    QCOMPARE(FF7Text::toPC(rangeFACx), rangeFACxJ);
    QCOMPARE(FF7Text::toPC(rangeFADx), rangeFADxJ);
    QCOMPARE(FF7Text::toPC(rangeFB0x), rangeFB0xJ);
    QCOMPARE(FF7Text::toPC(rangeFB1x), rangeFB1xJ);
    QCOMPARE(FF7Text::toPC(rangeFB2x), rangeFB2xJ);
    QCOMPARE(FF7Text::toPC(rangeFB3x), rangeFB3xJ);
    QCOMPARE(FF7Text::toPC(rangeFB4x), rangeFB4xJ);
    QCOMPARE(FF7Text::toPC(rangeFB5x), rangeFB5xJ);
    QCOMPARE(FF7Text::toPC(rangeFB6x), rangeFB6xJ);
    QCOMPARE(FF7Text::toPC(rangeFB7x), rangeFB7xJ);
    QCOMPARE(FF7Text::toPC(rangeFB8x), rangeFB8xJ);
    QCOMPARE(FF7Text::toPC(rangeFB9x), rangeFB9xJ);
    QCOMPARE(FF7Text::toPC(rangeFBAx), rangeFBAxJ);
    QCOMPARE(FF7Text::toPC(rangeFBBx), rangeFBBxJ);
    QCOMPARE(FF7Text::toPC(rangeFBCx), rangeFBCxJ);
    QCOMPARE(FF7Text::toPC(rangeFBDx), rangeFBDxJ);
    QCOMPARE(FF7Text::toPC(rangeFBEx), rangeFBExJ);
    QCOMPARE(FF7Text::toPC(rangeFC0x), rangeFC0xJ);
    QCOMPARE(FF7Text::toPC(rangeFC1x), rangeFC1xJ);
    QCOMPARE(FF7Text::toPC(rangeFC2x), rangeFC2xJ);
    QCOMPARE(FF7Text::toPC(rangeFC3x), rangeFC3xJ);
    QCOMPARE(FF7Text::toPC(rangeFC4x), rangeFC4xJ);
    QCOMPARE(FF7Text::toPC(rangeFC5x), rangeFC5xJ);
    QCOMPARE(FF7Text::toPC(rangeFC6x), rangeFC6xJ);
    QCOMPARE(FF7Text::toPC(rangeFC7x), rangeFC7xJ);
    QCOMPARE(FF7Text::toPC(rangeFC8x), rangeFC8xJ);
    QCOMPARE(FF7Text::toPC(rangeFC9x), rangeFC9xJ);
    QCOMPARE(FF7Text::toPC(rangeFCAx), rangeFCAxJ);
    QCOMPARE(FF7Text::toPC(rangeFCBx), rangeFCBxJ);
    QCOMPARE(FF7Text::toPC(rangeFCCx), rangeFCCxJ);
    QCOMPARE(FF7Text::toPC(rangeFCDx), rangeFCDxJ);
    QCOMPARE(FF7Text::toPC(rangeFD0x), rangeFD0xJ);
    QCOMPARE(FF7Text::toPC(rangeFD1x), rangeFD1xJ);
    QCOMPARE(FF7Text::toPC(rangeFD2x), rangeFD2xJ);
    QCOMPARE(FF7Text::toPC(rangeFD3x), rangeFD3xJ);
    QCOMPARE(FF7Text::toPC(rangeFD4x), rangeFD4xJ);
    QCOMPARE(FF7Text::toPC(rangeFD5x), rangeFD5xJ);
    QCOMPARE(FF7Text::toPC(rangeFD6x), rangeFD6xJ);
    QCOMPARE(FF7Text::toPC(rangeFD7x), rangeFD7xJ);
    QCOMPARE(FF7Text::toPC(rangeFD8x), rangeFD8xJ);
    QCOMPARE(FF7Text::toPC(rangeFD9x), rangeFD9xJ);
    QCOMPARE(FF7Text::toPC(rangeFDAx), rangeFDAxJ);
    QCOMPARE(FF7Text::toPC(rangeFDBx), rangeFDBxJ);
    QCOMPARE(FF7Text::toPC(rangeFDCx), rangeFDCxJ);
    QCOMPARE(FF7Text::toPC(rangeFDDx), rangeFDDxJ);
    QCOMPARE(FF7Text::toPC(rangeFE0x), rangeFE0xJ);
    QCOMPARE(FF7Text::toPC(rangeFE1x), rangeFE1xJ);
    QCOMPARE(FF7Text::toPC(rangeFE2x), rangeFE2xJ);
    QCOMPARE(FF7Text::toPC(rangeFE3x), rangeFE3xJ);
    QCOMPARE(FF7Text::toPC(rangeFE4x), rangeFE4xJ);
    QCOMPARE(FF7Text::toPC(rangeFE5x), rangeFE5xJ);
    QCOMPARE(FF7Text::toPC(rangeFE6x), rangeFE6xJ);
    QCOMPARE(FF7Text::toPC(rangeFE7x), rangeFE7xJ);
    QCOMPARE(FF7Text::toPC(rangeFE8x), rangeFE8xJ);
    QCOMPARE(FF7Text::toPC(rangeFE9x), rangeFE9xJ);
    QCOMPARE(FF7Text::toPC(rangeFEAx), rangeFEAxJ);
    QCOMPARE(FF7Text::toPC(rangeFEBx), rangeFEBxJ);
    QCOMPARE(FF7Text::toPC(rangeFECx), rangeFECxJ);
    QCOMPARE(FF7Text::toPC(rangeFEDx), rangeFEDxJ);
}

void FF7Text_Test::test_toFF7JPN()
{
    QCOMPARE(FF7Text::toFF7(range0xJ), range0x);
    QCOMPARE(FF7Text::toFF7(range1xJ), range1x);
    QCOMPARE(FF7Text::toFF7(range2xJ), range2x);
    QCOMPARE(FF7Text::toFF7(range3xJ), range3x);
    QCOMPARE(FF7Text::toFF7(range4xJ), range4x);
    QCOMPARE(FF7Text::toFF7(range5xJ), range5x);
    QCOMPARE(FF7Text::toFF7(range6xJ), range6x);
    QCOMPARE(FF7Text::toFF7(range7xJ), range7x);
    QCOMPARE(FF7Text::toFF7(range8xJ), range8x);
    QCOMPARE(FF7Text::toFF7(range9xJ), range9x);
    QCOMPARE(FF7Text::toFF7(rangeAxJ), rangeAx);
    QCOMPARE(FF7Text::toFF7(rangeBxJ), rangeBx);
    QCOMPARE(FF7Text::toFF7(rangeCxJ), rangeCx);
    QCOMPARE(FF7Text::toFF7(rangeDxJ), rangeDx);
    QEXPECT_FAIL("", "Chars Defined elsewhere", Continue);
    QCOMPARE(FF7Text::toFF7(rangeExJ), rangeEx);
    QByteArray temp = QByteArray::fromRawData("\x00\xEA\x00\xEA\x00\xEA\x00\xEA\x00\xEA\x00\xEA\x00\xEA\x00\xEA\x00\xEA", 18);
    QCOMPARE(FF7Text::toFF7(rangeFxJ), temp);
    QCOMPARE(FF7Text::toFF7(rangeFA0xJ), rangeFA0x);
    QCOMPARE(FF7Text::toFF7(rangeFA1xJ), rangeFA1x);
    QCOMPARE(FF7Text::toFF7(rangeFA2xJ), rangeFA2x);
    QCOMPARE(FF7Text::toFF7(rangeFA3xJ), rangeFA3x);
    QCOMPARE(FF7Text::toFF7(rangeFA4xJ), rangeFA4x);
    QCOMPARE(FF7Text::toFF7(rangeFA5xJ), rangeFA5x);
    QCOMPARE(FF7Text::toFF7(rangeFA6xJ), rangeFA6x);
    QCOMPARE(FF7Text::toFF7(rangeFA7xJ), rangeFA7x);
    QCOMPARE(FF7Text::toFF7(rangeFA8xJ), rangeFA8x);
    QCOMPARE(FF7Text::toFF7(rangeFA9xJ), rangeFA9x);
    QCOMPARE(FF7Text::toFF7(rangeFAAxJ), rangeFAAx);
    QCOMPARE(FF7Text::toFF7(rangeFABxJ), rangeFABx);
    QCOMPARE(FF7Text::toFF7(rangeFACxJ), rangeFACx);
    QCOMPARE(FF7Text::toFF7(rangeFADxJ),rangeFADx);
    QCOMPARE(FF7Text::toFF7(rangeFB0xJ), rangeFB0x);
    QCOMPARE(FF7Text::toFF7(rangeFB1xJ), rangeFB1x);
    QCOMPARE(FF7Text::toFF7(rangeFB2xJ), rangeFB2x);
    QCOMPARE(FF7Text::toFF7(rangeFB3xJ), rangeFB3x);
    QCOMPARE(FF7Text::toFF7(rangeFB4xJ), rangeFB4x);
    QCOMPARE(FF7Text::toFF7(rangeFB5xJ), rangeFB5x);
    QCOMPARE(FF7Text::toFF7(rangeFB6xJ), rangeFB6x);
    QCOMPARE(FF7Text::toFF7(rangeFB7xJ), rangeFB7x);
    QCOMPARE(FF7Text::toFF7(rangeFB8xJ), rangeFB8x);
    QCOMPARE(FF7Text::toFF7(rangeFB9xJ), rangeFB9x);
    QCOMPARE(FF7Text::toFF7(rangeFBAxJ), rangeFBAx);
    QCOMPARE(FF7Text::toFF7(rangeFBBxJ), rangeFBBx);
    QCOMPARE(FF7Text::toFF7(rangeFBCxJ), rangeFBCx);
    QCOMPARE(FF7Text::toFF7(rangeFBDxJ), rangeFBDx);
    QCOMPARE(FF7Text::toFF7(rangeFBExJ), rangeFBEx);
    QCOMPARE(FF7Text::toFF7(rangeFC0xJ), rangeFC0x);
    QCOMPARE(FF7Text::toFF7(rangeFC1xJ), rangeFC1x);
    QCOMPARE(FF7Text::toFF7(rangeFC2xJ), rangeFC2x);
    QCOMPARE(FF7Text::toFF7(rangeFC3xJ), rangeFC3x);
    QCOMPARE(FF7Text::toFF7(rangeFC4xJ), rangeFC4x);
    QCOMPARE(FF7Text::toFF7(rangeFC5xJ), rangeFC5x);
    QCOMPARE(FF7Text::toFF7(rangeFC6xJ), rangeFC6x);
    QCOMPARE(FF7Text::toFF7(rangeFC7xJ), rangeFC7x);
    QCOMPARE(FF7Text::toFF7(rangeFC8xJ), rangeFC8x);
    QCOMPARE(FF7Text::toFF7(rangeFC9xJ), rangeFC9x);
    QCOMPARE(FF7Text::toFF7(rangeFCAxJ), rangeFCAx);
    QCOMPARE(FF7Text::toFF7(rangeFCBxJ), rangeFCBx);
    QCOMPARE(FF7Text::toFF7(rangeFCCxJ), rangeFCCx);
    QCOMPARE(FF7Text::toFF7(rangeFCDxJ), rangeFCDx);
    QCOMPARE(FF7Text::toFF7(rangeFD0xJ), rangeFD0x);
    QCOMPARE(FF7Text::toFF7(rangeFD1xJ), rangeFD1x);
    QCOMPARE(FF7Text::toFF7(rangeFD2xJ), rangeFD2x);
    QCOMPARE(FF7Text::toFF7(rangeFD3xJ), rangeFD3x);
    QCOMPARE(FF7Text::toFF7(rangeFD4xJ), rangeFD4x);
    QCOMPARE(FF7Text::toFF7(rangeFD5xJ), rangeFD5x);
    QCOMPARE(FF7Text::toFF7(rangeFD6xJ), rangeFD6x);
    QCOMPARE(FF7Text::toFF7(rangeFD7xJ), rangeFD7x);
    QCOMPARE(FF7Text::toFF7(rangeFD8xJ), rangeFD8x);
    QCOMPARE(FF7Text::toFF7(rangeFD9xJ), rangeFD9x);
    QCOMPARE(FF7Text::toFF7(rangeFDAxJ), rangeFDAx);
    QCOMPARE(FF7Text::toFF7(rangeFDBxJ), rangeFDBx);
    QCOMPARE(FF7Text::toFF7(rangeFDCxJ), rangeFDCx);
    QCOMPARE(FF7Text::toFF7(rangeFDDxJ), rangeFDDx);
    QCOMPARE(FF7Text::toFF7(rangeFE0xJ), rangeFE0x);
    QCOMPARE(FF7Text::toFF7(rangeFE1xJ), rangeFE1x);
    QCOMPARE(FF7Text::toFF7(rangeFE2xJ), rangeFE2x);
    QCOMPARE(FF7Text::toFF7(rangeFE3xJ), rangeFE3x);
    QCOMPARE(FF7Text::toFF7(rangeFE4xJ), rangeFE4x);
    QCOMPARE(FF7Text::toFF7(rangeFE5xJ), rangeFE5x);
    QCOMPARE(FF7Text::toFF7(rangeFE6xJ), rangeFE6x);
    QCOMPARE(FF7Text::toFF7(rangeFE7xJ), rangeFE7x);
    QCOMPARE(FF7Text::toFF7(rangeFE8xJ), rangeFE8x);
    QCOMPARE(FF7Text::toFF7(rangeFE9xJ), rangeFE9x);
    QCOMPARE(FF7Text::toFF7(rangeFEAxJ), rangeFEAx);
    QCOMPARE(FF7Text::toFF7(rangeFEBxJ), rangeFEBx);
    QCOMPARE(FF7Text::toFF7(rangeFECxJ), rangeFECx);
    QCOMPARE(FF7Text::toFF7(rangeFEDxJ), rangeFEDx);
}

QTEST_MAIN(FF7Text_Test)

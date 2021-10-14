/****************************************************************************/
//    copyright 2021  Chris Rizzitello <sithlord48@gmail.com>               //
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

#include "PsColor_test.h"

void PsColor_Tests::test_toPsColor()
{
    QColor color("grey");
    QCOMPARE( PsColor::toPsColor(color.rgb()), 49680);
}

void PsColor_Tests::test_fromPsColor()
{
    QCOMPARE( PsColor::fromPsColor(0xFF00, false), 4278241023);
}

QTEST_MAIN(PsColor_Tests)

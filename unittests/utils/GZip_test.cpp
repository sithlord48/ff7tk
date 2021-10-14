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

#include "GZip_test.h"

void GZip_Tests::test_compress()
{
    const QByteArray inData = QByteArrayLiteral("\x00\x01\x02\0x02\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04");
    GZIP gzip;
    QByteArray outData = gzip.compress(inData);
    QCOMPARE(gzip.decompress(outData, inData.size()), inData);
}

QTEST_MAIN(GZip_Tests)

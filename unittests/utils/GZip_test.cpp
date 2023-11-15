//    SPDX-FileCopyrightText: 2021 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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

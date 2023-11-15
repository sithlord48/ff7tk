//    SPDX-FileCopyrightText: 2021 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <QtTest>

#include "GZipps_test.h"

void GZipps_Tests::test_compress()
{
    const QByteArray headerData = QByteArrayLiteral("\x00\x01\x02\x03");
    const QByteArray inData = QByteArrayLiteral("\x00\x01\x02\0x02\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04");
    GZIPPS gzipps;
    QByteArray outData = gzipps.compress(inData, headerData);
    QCOMPARE(gzipps.decompress(outData), inData);
}

QTEST_MAIN(GZipps_Tests)

//    SPDX-FileCopyrightText: 2021 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <QtTest>

#include "Lzs_test.h"

void Lzs_Tests::test_compress()
{
    const QByteArray inData = QByteArrayLiteral("\x00\x01\x02\0x02\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04");
    LZS lzs;
    QByteArray outData = lzs.compress(inData);
    QCOMPARE(lzs.decompress(outData, inData.size()), inData);
}

QTEST_MAIN(Lzs_Tests)

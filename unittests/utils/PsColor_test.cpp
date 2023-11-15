//    SPDX-FileCopyrightText: 2021 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

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

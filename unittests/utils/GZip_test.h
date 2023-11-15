//    SPDX-FileCopyrightText: 2021 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <QObject>

#include "../../src/utils/GZIP.h"

class GZip_Tests : public QObject
{
    Q_OBJECT
private slots:
    void test_compress();
};

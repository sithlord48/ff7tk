//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#include <AkaoIO.h>

AkaoIO::AkaoIO(QIODevice *device)
    : IO(device)
{
}

AkaoIO::~AkaoIO()
{
}

bool AkaoIO::read(Akao &akao) const
{
    Q_UNUSED(akao)
    // TODO
    return false;
}

bool AkaoIO::write(const Akao &akao) const
{
    Q_UNUSED(akao)
    // TODO
    return false;
}

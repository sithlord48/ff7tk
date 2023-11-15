//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <IO>
#include <Akao>

class AkaoIO : public IO
{
public:
    explicit AkaoIO(QIODevice *device);
    virtual ~AkaoIO() override;
    bool read(Akao &akao) const;
    bool write(const Akao &akao) const;
};

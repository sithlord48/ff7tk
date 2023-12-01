# SPDX-FileCopyrightText: Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: MIT
find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Qml
    Quick
)

set(libName ff7tkQuickDataTypes)
set(${libName}_MAKEQMLMODULE TRUE)

set(${libName}_URI "ff7tkQuick.DataTypes")

set(${libName}_HEADERS
    ff7tkQuickDataTypes.h
)

set(${libName}_PublicLIBLINKS
    Qt::Qml
    Qt::Quick
    ff7tk::ff7tk
    ff7tk::ff7tkData
)

MAKE_LIBRARY(${libName} ff7tk/ff7tkQuickDataTypes)

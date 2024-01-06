# SPDX-FileCopyrightText: Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: MIT

project(ff7tkQmlGallery VERSION 0.1.1 LANGUAGES CXX DESCRIPTION "Demo App for ff7tk using QML")

find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
        Quick
        QuickControls2
)
set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src ${CMAKE_BINARY_DIR}/imports CACHE STRING "" FORCE)

find_library(ff7tk ${CMAKE_BINARY_DIR}/src/core)
find_library(ff7tkData ${CMAKE_BINARY_DIR}/src/data)
find_library(ff7tkFormats ${CMAKE_BINARY_DIR}/src/formats)
find_library(ff7tkQuickControls ${CMAKE_BINARY_DIR}/src/quick/data)
find_library(ff7tkQuickDataTypes ${CMAKE_BINARY_DIR}/src/widgets/common)

set(${PROJECT_NAME}_SRC
        main.cpp
        qml.qrc
)

set(${PROJECT_NAME}_DEPENDS
    ff7tk::ff7tkQuickDataTypes
    ff7tk::ff7tkQuickControls
)

set(${PROJECT_NAME}_LIBLINKS
    ${${PROJECT_NAME}_DEPENDS}
    Qt::Quick
    Qt::QuickControls2
    ff7tk::ff7tk
)

MAKE_DEMO()

 
 
project( ff7tkQmlGallery )
#version number

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(REQUIRED_QT_VERSION "5.10.0")
cmake_minimum_required( VERSION 3.8.11 )
option(OPENSSL "Build With OpenSSL")

set ( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
        Quick
        QuickControls2
    )

if (OPENSSL)
    find_package ( OpenSSL REQUIRED )
    include_directories ( ${OPENSSL_INCLUDE_DIR} )
endif()

set ( ff7tkData
    ../data/FF7Text.cpp
    ../data/FF7Item.cpp
    )

set ( ff7tkIcons
    ../icons/items.qrc
    )

add_executable ( ff7tkQmlGallery
    main.cpp
    qml.qrc
    ${ff7tkData}
    ${ff7tkIcons}
    )

target_link_libraries ( ff7tkQmlGallery
    Qt5::Quick
    ${OPENSSL_LIBRARIES}
    )

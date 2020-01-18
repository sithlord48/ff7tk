project( ff7tkQmlGallery )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release )
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(REQUIRED_QT_VERSION "5.10.0")
cmake_minimum_required( VERSION 3.8 )
add_definitions ( -Wall )

if(WIN32)
    if(CMAKE_COMPILER_IS_GNUCC)
        #Prevent ms padding on packed structures on gcc compiler
        add_definitions(-mno-ms-bitfields)
    endif()
elseif(APPLE)
    add_definitions(-stdlib=libc++)
endif()

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
        Quick
        QuickControls2
    )

set ( ff7tkData
        ../src/data/FF7Text.cpp
        ../src/data/FF7Item.cpp
    )

set ( ff7tkIcons
        ../src/icons/items.qrc
    )

add_executable ( ff7tkQmlGallery
        main.cpp
        qml.qrc
        ${ff7tkData}
        ${ff7tkIcons}
    )

target_link_libraries ( ff7tkQmlGallery
        Qt5::Quick
    )

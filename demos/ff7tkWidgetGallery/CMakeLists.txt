project(ff7tkWidgetGallery VERSION 0.1.1 DESCRIPTION "Demo App for ff7tk with widgets")

set(WIDGETS ON CACHE BOOL BOOL FORCE)
set(FORMATS ON CACHE BOOL BOOL FORCE)

find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
        Widgets
        Quick
)

find_library(ff7tk ${CMAKE_BINARY_DIR}/src/data)
find_library(ff7tkFormats ${CMAKE_BINARY_DIR}/src/formats)
find_library(ff7tkUtils ${CMAKE_BINARY_DIR}/src/utils)
find_library(ff7tkWidgets ${CMAKE_BINARY_DIR}/src/widgets)

set(${PROJECT_NAME}_SRC
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

set(${PROJECT_NAME}_DEPENDS
    ff7tk::ff7tk
    ff7tk::ff7tkFormats
    ff7tk::ff7tkUtils
    ff7tk::ff7tkWidgets
)

set(${PROJECT_NAME}_LIBLINKS
    Qt::Widgets
    ${${PROJECT_NAME}_DEPENDS}
)

MAKE_DEMO()
project(ff7tkQmlGallery VERSION 0.1.1 LANGUAGES CXX DESCRIPTION "Demo App for ff7tk using QML")

find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
        Quick
        QuickControls2
)

set(${PROJECT_NAME}_SRC
        main.cpp
        qml.qrc
)

set(${PROJECT_NAME}_DEPENDS
    ff7tk::ff7tk
)

set(${PROJECT_NAME}_LIBLINKS
    ${${PROJECT_NAME}_DEPENDS}
    Qt::Quick
    Qt::QuickControls2
)

MAKE_DEMO()
project(ff7tkQmlGallery)

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
        Quick
        QuickControls2
    )

set ( ff7tkQmlGallery_SRCS
        main.cpp
        qml.qrc
    )

if (NOT APPLE)
    add_executable ( ff7tkQmlGallery ${ff7tkQmlGallery_SRCS})
    install(TARGETS ff7tkQmlGallery RUNTIME DESTINATION bin)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.desktop" DESTINATION share/applications/)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.png" DESTINATION share/pixmaps)

else()
    set(MACOSX_BUNDLE_DISPLAY_NAME "ff7tkQmlGallery")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ff7tk.QmlGallery")
    set(MACOSX_BUNDLE_BUNDLE_NAME "ff7tkQmlGallery")
    set(MACOSX_BUNDLE_DISPLAY_NAME "ff7tkQmlGallery")
    set(MACOSX_BUNDLE_INFO_STRING "ff7tk - QmlGallery")
    set(MACOSX_BUNDLE_COPYRIGHT "2012-2020 ff7tk Authors")
    add_executable(ff7tkQmlGallery MACOSX_BUNDLE ${ff7tkQmlGallery_SRCS})
    install(TARGETS ff7tkQmlGallery BUNDLE DESTINATION bin)
endif()

target_link_libraries ( ff7tkQmlGallery
        Qt5::Quick
        Qt5::QuickControls2
        ff7tk
    )

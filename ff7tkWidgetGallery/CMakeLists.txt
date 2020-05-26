project(ff7tkWidgetGallery)

set(CMAKE_AUTOUIC ON)

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
        Widgets
        Quick
    )

set ( ff7tkWidgetGallery_SRCS
        main.cpp
        mainwindow.cpp
    )

if (NOT APPLE)
    add_executable ( ff7tkWidgetGallery ${ff7tkWidgetGallery_SRCS})
    install(TARGETS ff7tkWidgetGallery RUNTIME DESTINATION bin)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.desktop" DESTINATION share/applications/)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetGallery.png" DESTINATION share/pixmaps)

else()
    set(MACOSX_BUNDLE_DISPLAY_NAME "ff7tkWidgetGallery")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.ff7tk.WidgetGallery")
    set(MACOSX_BUNDLE_BUNDLE_NAME "ff7tkWidgetGallery")
    set(MACOSX_BUNDLE_DISPLAY_NAME "ff7tkWidgetGallery")
    set(MACOSX_BUNDLE_INFO_STRING "ff7tk - WidgetGallery")
    set(MACOSX_BUNDLE_COPYRIGHT "2012-2020 ff7tk Authors")
    add_executable(ff7tkWidgetGallery MACOSX_BUNDLE ${ff7tkWidgetGallery_SRCS})
    install(TARGETS ff7tkWidgetGallery BUNDLE DESTINATION bin)
endif()

target_link_libraries ( ff7tkWidgetGallery
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Quick
        ff7tk
    )

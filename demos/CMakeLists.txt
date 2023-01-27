set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

#ff7tk Demo Applications
option(WIDGET_GALLERY "Build the widget based gallery" ON)
option(QML_GALLERY "Build the qml based gallery" ON)

if(WIDGET_GALLERY)
    add_subdirectory(ff7tkWidgetGallery)
endif()

if(QML_GALLERY)
    add_subdirectory(ff7tkQmlGallery)
endif()


find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Widgets
    Gui
)

find_library(ff7tk ${CMAKE_CURRENT_BINARY_DIR}/src/data)

set ( ff7tkWidgets_SRC
    AchievementEditor.cpp
    CharEditor.cpp
    ChocoboEditor.cpp
    ChocoboLabel.cpp
    ChocoboManager.cpp
    DialogPreview.cpp
    DoubleCheckBox.cpp
    ItemList.cpp
    ItemPreview.cpp
    ItemSelector.cpp
    LocationViewer.cpp
    MateriaEditor.cpp
    MenuListWidget.cpp
    MetadataCreator.cpp
    OptionsWidget.cpp
    PhsListWidget.cpp
    SlotPreview.cpp
    SlotSelect.cpp
)

set (ff7tkWidgets_HEADERS
    AchievementEditor.h
    ChocoboLabel.h
    DoubleCheckBox.h
    ItemSelector.h
    MenuListWidget.h
    PhsListWidget.h
    CharEditor.h
    ChocoboManager.h
    ItemList.h
    LocationViewer.h
    MetadataCreator.h
    SlotPreview.h
    ChocoboEditor.h
    DialogPreview.h
    ItemPreview.h
    MateriaEditor.h
    OptionsWidget.h
    SlotSelect.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkwidgets_export.h
)

add_library (ff7tkWidgets
  SHARED
    ${ff7tkWidgets_SRC}
    ${ff7tkWidgets_HEADERS}
)
add_library(ff7tk::ff7tkWidgets ALIAS ff7tkWidgets)

if (APPLE)
    set_target_properties(ff7tkWidgets PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
    if(${BUILD_FRAMEWORKS})
        target_include_directories(ff7tkWidgets PUBLIC $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:ff7tkWidgets>/Headers>)
    endif()
endif()

if(UNIX)
    set_target_properties(ff7tkWidgets PROPERTIES INSTALL_RPATH ${INSTALL_RPATH_STRING})
endif()

set_target_properties(ff7tkWidgets PROPERTIES
    FRAMEWORK ${BUILD_FRAMEWORKS}
    FRAMEWORK_VERSION ${PROJECT_VERSION_MAJOR}
    MACOSX_FRAMEWORK_IDENTIFIER com.sithlord48.ff7tkWidgets
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    PUBLIC_HEADER "${ff7tkWidgets_HEADERS}"
)

target_include_directories(ff7tkWidgets
  PUBLIC
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
     $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
     $<INSTALL_INTERFACE:include/ff7tk/widgets>
)

target_link_libraries (ff7tkWidgets
  PUBLIC
    Qt::Core
    Qt::Widgets
    Qt::Gui
    ff7tk::ff7tk
)

INSTALL_LIBRARY(ff7tkWidgets ff7tk/widgets)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets Gui)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED NO_MODULE COMPONENTS
    Core
    Widgets
    Gui
)

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
)

add_library (ff7tkWidgets SHARED ${ff7tkWidgets_SRC} ff7tkwidgets_export.h)
add_library(ff7tk::ff7tkWidgets ALIAS ff7tkWidgets)

target_include_directories(ff7tkWidgets
  PRIVATE
    ${PROJECT_BINARY_DIR}/src/data
  PUBLIC
     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
     $<INSTALL_INTERFACE:include/ff7tk/widgets>
  INTERFACE
    $<INSTALL_INTERFACE:include/ff7tk/widgets>
)

target_link_libraries (ff7tkWidgets
  PUBLIC
    Qt::Core
    Qt::Widgets
    Qt::Gui
    ff7tk::ff7tk
)

set_target_properties(
    ff7tkWidgets PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    PUBLIC_HEADER "${ff7tkWidgets_HEADERS}"
)

generate_export_header(ff7tkWidgets BASE_NAME ff7tkwidgets)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkWidgetsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ff7tkWidgetsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkWidgetsConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
)

include(GNUInstallDirs)

install(TARGETS ff7tkWidgets
    EXPORT ff7tkTargets
    COMPONENT ff7tkWidgets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/widgets
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/ff7tkwidgets_export.h
    COMPONENT ff7tkWidgets
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/widgets
)

install(
    EXPORT ff7tkTargets
    NAMESPACE ff7tk::
    COMPONENT ff7tkWidgets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
)

install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/ff7tkWidgetsConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/ff7tkWidgetsConfigVersion.cmake
    COMPONENT ff7tkWidgets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
)
export(EXPORT ff7tkTargets FILE ${CMAKE_CURRENT_BINARY_DIR}/ff7tkTargets.cmake)

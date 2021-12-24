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

generate_export_header(ff7tkWidgets BASE_NAME ff7tkwidgets)

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

install(TARGETS ff7tkWidgets
    EXPORT ff7tkTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT ff7tk_runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT ff7tk_runtime
        NAMELINK_COMPONENT ff7tk_development
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT ff7tk_runtime
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT ff7tk_development
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/widgets
        COMPONENT ff7tk_development
)

install(
    EXPORT ff7tkTargets
    NAMESPACE ff7tk::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
    COMPONENT ff7tk_development
)

install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/ff7tkWidgetsConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/ff7tkWidgetsConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
    COMPONENT ff7tk_development
)
export(EXPORT ff7tkTargets FILE ${CMAKE_CURRENT_BINARY_DIR}/ff7tkTargets.cmake)
set_property(GLOBAL APPEND PROPERTY ff7tk_targets ff7tkWidgets)


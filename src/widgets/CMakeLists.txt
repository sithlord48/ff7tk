find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
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
add_library (ff7tkWidgets SHARED ${ff7tkWidgets_SRC} ff7tkwidgets_export.h)
add_library(ff7tk::ff7tkWidgets ALIAS ff7tkWidgets)
target_include_directories(ff7tkWidgets PRIVATE ${PROJECT_BINARY_DIR}/src/data)

target_link_libraries (ff7tkWidgets PUBLIC
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
    )
target_link_libraries(ff7tkWidgets PRIVATE ff7tk::ff7tk)

set_property(TARGET ff7tkWidgets PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ff7tkWidgets PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(ff7tkWidgets BASE_NAME ff7tkwidgets)
include(GNUInstallDirs)

install(TARGETS ff7tkWidgets
    EXPORT ff7tkWidgetsConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install (
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
    FILES_MATCHING PATTERN "*.h"
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ff7tkwidgets_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk/widgets)

install(EXPORT ff7tkWidgetsConfig NAMESPACE ff7tk:: DESTINATION share/ff7tk/cmake)
export(TARGETS ff7tkWidgets FILE ff7tkWidgets.cmake)

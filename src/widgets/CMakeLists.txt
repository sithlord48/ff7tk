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

set( ff7tkWidgets_PublicLIBLINKS
       Qt::Core
       Qt::Widgets
       Qt::Gui
       ff7tk::ff7tk
)

MAKE_LIBRARY(ff7tkWidgets ff7tk/widgets)

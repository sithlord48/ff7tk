project( ff7tkWidgetGallery )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set ( CMAKE_BUILD_TYPE Release )
cmake_minimum_required( VERSION 3.8 )
set(REQUIRED_QT_VERSION "5.10.0")
add_definitions ( -Wall )

if(WIN32)
    if(CMAKE_COMPILER_IS_GNUCC)
        #Prevent ms padding on packed structures on gcc compiler
        add_definitions(-mno-ms-bitfields)
    endif()
elseif(APPLE)
    add_definitions(-stdlib=libc++)
endif()

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
        Widgets
        Gui
        Xml
    )

find_package( ZLIB REQUIRED )

set ( ff7tkWidgetGallery_SRCS
        main.cpp
        mainwindow.cpp
    )
#ADD ALL FF7TK ITEMS HERE IN DEMO
set ( ff7tkData
        ../src/data/FF7Achievements.cpp
        ../src/data/FF7Char.cpp
        ../src/data/FF7FieldItemList.cpp
        ../src/data/FF7Item.cpp
        ../src/data/FF7Location.cpp
        ../src/data/FF7Materia.cpp
        ../src/data/FF7Save.cpp #CAN USE OPENSSL TO SIGN PS3 SAVES.
        ../src/data/FF7Text.cpp
        ../src/data/SaveIcon.cpp
    )

set ( ff7tkFormats
        ../src/formats/Archive.cpp
        ../src/formats/IsoArchive.cpp
        ../src/formats/Lgp_p.cpp
        ../src/formats/Lgp.cpp
    )

set ( ff7tkIcons
        ../src/icons/achievements.qrc
        ../src/icons/characters.qrc
        ../src/icons/chocobo.qrc
        ../src/icons/common.qrc
        ../src/icons/items.qrc
        ../src/icons/locations.qrc
        ../src/icons/materia.qrc
        ../src/icons/psxButtons.qrc
    )

set ( ff7tkUtils
        ../src/utils/GZIP.cpp #NEEDS ZLIB
        ../src/utils/GZIPPS.cpp
        ../src/utils/LZS.cpp
        ../src/utils/PsColor.cpp
        ../src/utils/QLockedFile.cpp
    )

set ( ff7tkWidgets
        ../src/widgets/AchievementEditor.cpp
        ../src/widgets/CharEditor.cpp
        ../src/widgets/CharManager.cpp
        ../src/widgets/ChocoboEditor.cpp
        ../src/widgets/ChocoboLabel.cpp
        ../src/widgets/ChocoboManager.cpp
        ../src/widgets/DialogPreview.cpp
        ../src/widgets/DoubleCheckBox.cpp
        ../src/widgets/ItemList.cpp
        ../src/widgets/ItemPreview.cpp
        ../src/widgets/ItemSelector.cpp
        ../src/widgets/LocationViewer.cpp
        ../src/widgets/MateriaEditor.cpp
        ../src/widgets/MenuListWidget.cpp
        ../src/widgets/MetadataCreator.cpp
        ../src/widgets/OptionsWidget.cpp
        ../src/widgets/PhsListWidget.cpp
        ../src/widgets/SlotPreview.cpp
        ../src/widgets/SlotSelect.cpp
    )

add_executable ( ff7tkWidgetGallery
        ${ff7tkWidgetGallery_SRCS}
        ${ff7tkData}
        ${ff7tkFormats}
        ${ff7tkIcons}
        ${ff7tkUtils}
        ${ff7tkWidgets}
    )

target_link_libraries ( ff7tkWidgetGallery
        Qt5::Core
        Qt5::Gui
        Qt5::Xml
        Qt5::Widgets
        ${ZLIB_LIBRARIES}
        ${OPENSSL_LIBRARIES}
    )

 
project( ff7tkWidgetGallery )
#version number

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

cmake_minimum_required( VERSION 3.8.11 )
option(OPENSSL "Build With OpenSSL")

set ( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
set(REQUIRED_QT_VERSION "5.10.0")

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
        Widgets
        Gui
        Xml
    )

if (OPENSSL)
    find_package ( OpenSSL REQUIRED )
endif()

find_package( ZLIB REQUIRED )

set ( ff7tkWidgetGallery_SRCS
	main.cpp
	mainwindow.cpp
	)

set ( ff7tkData
    ../data/FF7Achievements.cpp
    ../data/FF7Char.cpp
    ../data/FF7FieldItemList.cpp
    ../data/FF7Item.cpp
    ../data/FF7Location.cpp
    ../data/FF7Materia.cpp
    ../data/FF7Save.cpp #CAN USE OPENSSL TO SIGN PS3 SAVES.
    ../data/FF7Text.cpp
    ../data/SaveIcon.cpp
	)

set ( ff7tkFormats
    ../formats/Archive.cpp
    ../formats/IsoArchive.cpp
    ../formats/Lgp_p.cpp
    ../formats/Lgp.cpp
    )

set ( ff7tkIcons
    ../icons/achievements.qrc
    ../icons/characters.qrc
    ../icons/chocobo.qrc
    ../icons/common.qrc
    ../icons/items.qrc
    ../icons/locations.qrc
    ../icons/materia.qrc
    ../icons/psxButtons.qrc
    )

set ( ff7tkUtils
    ../utils/GZIP.cpp #NEEDS ZLIB
    ../utils/GZIPPS.cpp 
    ../utils/LZS.cpp
    ../utils/PsColor.cpp
    ../utils/QLockedFile.cpp
    )

set ( ff7tkWidgets
    ../widgets/AchievementEditor.cpp
    ../widgets/CharEditor.cpp
    ../widgets/CharManager.cpp
    ../widgets/ChocoboEditor.cpp
    ../widgets/ChocoboLabel.cpp
    ../widgets/ChocoboManager.cpp
    ../widgets/DialogPreview.cpp
    ../widgets/DoubleCheckBox.cpp
    ../widgets/ItemList.cpp
    ../widgets/ItemPreview.cpp
    ../widgets/ItemSelector.cpp
    ../widgets/LocationViewer.cpp
    ../widgets/MateriaEditor.cpp
    ../widgets/MenuListWidget.cpp
    ../widgets/MetadataCreator.cpp
    ../widgets/OptionsWidget.cpp
    ../widgets/PhsListWidget.cpp
    ../widgets/SlotPreview.cpp
    ../widgets/SlotSelect.cpp
    )
add_executable ( ff7tkWidgetGallery ${ff7tkWidgetGallery_SRCS} ${ff7tkData} ${ff7tkFormats} ${ff7tkIcons} ${ff7tkUtils} ${ff7tkWidgets})

target_link_libraries ( ff7tkWidgetGallery  Qt5::Core Qt5::Gui Qt5::Xml Qt5::Widgets  ${ZLIB_LIBRARIES} ${OPENSSL_LIBRARIES} )

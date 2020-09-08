cmake_policy(SET CMP0074 NEW)
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
        Quick
    )

find_package( ZLIB REQUIRED )

set ( ff7tkData
        data/crypto/aes.c
        data/FF7Achievements.cpp
        data/FF7Char.cpp
        data/FF7FieldItemList.cpp
        data/FF7Item.cpp
        data/FF7Location.cpp
        data/FF7Materia.cpp
        data/FF7Save.cpp
        data/FF7SaveInfo.cpp
        data/FF7Text.cpp
        data/SaveIcon.cpp
    )

set ( ff7tkFormats
        formats/Archive.cpp
        formats/IsoArchive.cpp
        formats/Lgp_p.cpp
        formats/Lgp.cpp
    )

set ( ff7tkIcons
        icons/achievements.qrc
        icons/characters.qrc
        icons/chocobo.qrc
        icons/common.qrc
        icons/items.qrc
        icons/locations.qrc
        icons/materia.qrc
        icons/psxButtons.qrc
    )

set ( ff7tkUtils
        utils/GZIP.cpp #NEEDS ZLIB
        utils/GZIPPS.cpp
        utils/LZS.cpp
        utils/PsColor.cpp
        utils/QLockedFile.cpp
    )

set ( ff7tkWidgets
        widgets/AchievementEditor.cpp
        widgets/CharEditor.cpp
        widgets/CharManager.cpp
        widgets/ChocoboEditor.cpp
        widgets/ChocoboLabel.cpp
        widgets/ChocoboManager.cpp
        widgets/DialogPreview.cpp
        widgets/DoubleCheckBox.cpp
        widgets/ItemList.cpp
        widgets/ItemPreview.cpp
        widgets/ItemSelector.cpp
        widgets/LocationViewer.cpp
        widgets/MateriaEditor.cpp
        widgets/MenuListWidget.cpp
        widgets/MetadataCreator.cpp
        widgets/OptionsWidget.cpp
        widgets/PhsListWidget.cpp
        widgets/SlotPreview.cpp
        widgets/SlotSelect.cpp
    )


add_library (ff7tk SHARED
        about.h
        ${ff7tkData}
        ${ff7tkFormats}
        ${ff7tkIcons}
        ${ff7tkUtils}
        ${ff7tkWidgets}
    )

add_library (ff7tk::ff7tk ALIAS ff7tk)

target_link_libraries (ff7tk
        Qt5::Core
        Qt5::Gui
        Qt5::Xml
        Qt5::Widgets
        Qt5::Quick
        ZLIB::ZLIB
    )

set_property(TARGET ff7tk PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ff7tk PROPERTY SOVERSION 0)

include(GNUInstallDirs)

install(TARGETS ff7tk
    EXPORT ff7tkConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install ( FILES about.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk)

install (
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
    FILES_MATCHING PATTERN "*.h"
)

install (
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/formats
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
    FILES_MATCHING PATTERN "*.h"
)

install (
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/utils
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
    FILES_MATCHING PATTERN "*.h"
)

install (
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/widgets
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT ff7tkConfig NAMESPACE ff7tk:: DESTINATION share/ff7tk/cmake)
export(TARGETS ff7tk FILE ff7tk.cmake)

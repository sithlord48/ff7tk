
find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Quick
    Xml
)

set ( ff7tkData_SRC
        crypto/aes.c
        FF7Achievements.cpp
        FF7Char.cpp
        FF7FieldItemList.cpp
        FF7Item.cpp
        FF7Location.cpp
        FF7Materia.cpp
        FF7Save.cpp
        FF7SaveInfo.cpp
        FF7Text.cpp
        SaveIcon.cpp
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

configure_file(about.h.in ${CMAKE_CURRENT_SOURCE_DIR}/about.h @ONLY)

if(WIN32)
    if(CMAKE_COMPILER_IS_GNUCC)
        #Prevent ms padding on packed structures on gcc compiler
        add_definitions(-mno-ms-bitfields)
    endif()
elseif(APPLE)
    add_definitions(-stdlib=libc++)
endif()

add_library (ff7tk SHARED
        about.h
        ff7tk_export.h
        ${ff7tkIcons}
        ${ff7tkData_SRC}
)

add_library (ff7tk::ff7tk ALIAS ff7tk)

generate_export_header(ff7tk)

target_link_libraries (ff7tk PUBLIC
        Qt5::Core
        Qt5::Quick
        Qt5::Xml
)

set_property(TARGET ff7tk PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ff7tk PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})

include(GNUInstallDirs)

install(TARGETS ff7tk
    EXPORT ff7tkConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install ( FILES about.h ${CMAKE_CURRENT_BINARY_DIR}/ff7tk_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk)

install (
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT ff7tkConfig NAMESPACE ff7tk:: DESTINATION share/ff7tk/cmake)
export(TARGETS ff7tk FILE ff7tk.cmake)

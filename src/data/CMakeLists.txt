
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

set (ff7tkData_HEADERS
    ff7tkAbout.h            FF7FieldItemList.h  FF7Materia.h   FF7Save_Types.h  Type_FF7CHAR.h
    FF7Achievements.h  FF7Item.h           FF7Save.h      FF7Text.h        Type_FF7CHOCOBO.h
    FF7Char.h          FF7Location.h       FF7SaveInfo.h  SaveIcon.h       Type_materia.h
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
set ( ff7tk_TRS
    ../../lang/ff7tk_en.ts
    ../../lang/ff7tk_es.ts
    ../../lang/ff7tk_fr.ts
    ../../lang/ff7tk_de.ts
    ../../lang/ff7tk_ja.ts
    ../../lang/ff7tk_re.ts
    )

find_package(Qt5LinguistTools)
qt5_create_translation(TRS ${CMAKE_SOURCE_DIR} ${ff7tk_TRS})

configure_file(ff7tkAbout.h.in ${CMAKE_CURRENT_SOURCE_DIR}/ff7tkAbout.h @ONLY)

if(WIN32)
    if(CMAKE_COMPILER_IS_GNUCC)
        #Prevent ms padding on packed structures on gcc compiler
        add_definitions(-mno-ms-bitfields)
    endif()
elseif(APPLE)
    add_definitions(-stdlib=libc++)
endif()

add_library (ff7tk SHARED
        ${TRS}
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

set_target_properties(
    ff7tk PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${ff7tkData_HEADERS}"
)

target_include_directories(ff7tk PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include/ff7tk>
)

include(GNUInstallDirs)

install(TARGETS ff7tk
    EXPORT ff7tkConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
)

install(FILES ${TRS} DESTINATION share/ff7tk/lang)

install (FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tk_export.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
)

install(EXPORT ff7tkConfig NAMESPACE ff7tk:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk)
export(TARGETS ff7tk FILE ff7tk.cmake)

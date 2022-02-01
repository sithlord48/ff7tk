find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Quick
    Xml
    Svg
)

if(${QT_DEFAULT_MAJOR_VERSION} MATCHES "6")
    find_package(Qt6 COMPONENTS Core5Compat REQUIRED)
endif()

configure_file(ff7tkAbout.h.in ${CMAKE_CURRENT_BINARY_DIR}/ff7tkAbout.h @ONLY)


set ( ff7tk_SRC
        crypto/aes.c
        FF7Achievements.cpp  FF7Char.cpp     FF7FieldItemList.cpp
        FF7Item.cpp          FF7Location.cpp FF7Materia.cpp
        FF7Save.cpp          FF7SaveInfo.cpp FF7Text.cpp
        SaveIcon.cpp
)

set (ff7tk_HEADERS
    FF7FieldItemList.h  FF7Materia.h   FF7Save_Types.h  Type_FF7CHAR.h
    FF7Achievements.h  FF7Item.h           FF7Save.h      FF7Text.h        Type_FF7CHOCOBO.h
    FF7Char.h          FF7Location.h       FF7SaveInfo.h  SaveIcon.h       Type_materia.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tk_export.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkAbout.h
)

set ( ff7tk_RESOURCES
        ${CMAKE_SOURCE_DIR}/src/icons/achievements.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/characters.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/chocobo.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/common.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/items.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/locations.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/materia.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/psxButtons.qrc
)

set (ff7tk_PublicLIBLINKS
      Qt::Core
      Qt::Quick
      Qt::Xml
      Qt::Svg
)

if(${QT_DEFAULT_MAJOR_VERSION} EQUAL "6")
    set(ff7tk_PrivateLIBLINKS Qt6::Core5Compat)
endif()

MAKE_LIBRARY(ff7tk ff7tk)

if(WIN32 AND CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(ff7tk PRIVATE -mno-ms-bitfields)
elseif(APPLE)
     target_compile_options(ff7tk PRIVATE -stdlib=libc++)
endif()

find_package(Qt6 REQUIRED NO_MODULE COMPONENTS
    Core
    Core5Compat
    Svg
    Quick
    Xml
)

add_subdirectory(crypto)

set ( ff7tkData_SRC
        FF7Achievements.cpp  FF7Char.cpp     FF7FieldItemList.cpp
        FF7Item.cpp          FF7Location.cpp FF7Materia.cpp
        FF7Save.cpp          FF7SaveInfo.cpp FF7Text.cpp
        SaveIcon.cpp         FF7ItemModel.cpp
)

set (ff7tkData_HEADERS
    FF7FieldItemList.h  FF7Materia.h   FF7Save_Types.h  Type_FF7CHAR.h
    FF7Achievements.h  FF7Item.h           FF7Save.h      FF7Text.h        Type_FF7CHOCOBO.h
    FF7Char.h          FF7Location.h       FF7SaveInfo.h  SaveIcon.h       Type_materia.h
    FF7ItemModel.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkdata_export.h
)

set ( ff7tkData_RESOURCES
        ${CMAKE_SOURCE_DIR}/src/icons/achievements.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/characters.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/chocobo.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/common.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/items.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/locations.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/materia.qrc
        ${CMAKE_SOURCE_DIR}/src/icons/psxButtons.qrc
)

set (ff7tkData_PublicLIBLINKS
      Qt::Core
      Qt::Quick
      Qt::Xml
      Qt::Svg
      Qt::Core5Compat
)

set (ff7tkData_PrivateLIBLINKS
    CRYPTO
)

MAKE_LIBRARY(ff7tkData ff7tk/data)

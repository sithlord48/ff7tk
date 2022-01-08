find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Quick
    Xml
)

if(APPLE)
    find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
        Svg
    )
endif()

if(${QT_DEFAULT_MAJOR_VERSION} MATCHES "6")
    find_package(Qt6 COMPONENTS Core5Compat REQUIRED)
endif()

configure_file(ff7tkAbout.h.in ${CMAKE_CURRENT_BINARY_DIR}/ff7tkAbout.h @ONLY)

set ( ff7tkData_SRC
        crypto/aes.c
        FF7Achievements.cpp  FF7Char.cpp     FF7FieldItemList.cpp
        FF7Item.cpp          FF7Location.cpp FF7Materia.cpp
        FF7Save.cpp          FF7SaveInfo.cpp FF7Text.cpp
        SaveIcon.cpp
    )

set (ff7tkData_HEADERS
    FF7FieldItemList.h  FF7Materia.h   FF7Save_Types.h  Type_FF7CHAR.h
    FF7Achievements.h  FF7Item.h           FF7Save.h      FF7Text.h        Type_FF7CHOCOBO.h
    FF7Char.h          FF7Location.h       FF7SaveInfo.h  SaveIcon.h       Type_materia.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tk_export.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkAbout.h

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

add_library (ff7tk SHARED
        ${ff7tkIcons}
        ${ff7tkData_SRC}
        ${ff7tkData_HEADERS}
)
add_library (ff7tk::ff7tk ALIAS ff7tk)

if(WIN32 AND CMAKE_COMPILER_IS_GNUCC)
    #Prevent ms padding on packed structures on gcc compiler
    add_compile_options(-mno-ms-bitfields)
elseif(APPLE)
     target_link_libraries(ff7tk PUBLIC Qt::Svg)
     target_compile_options(ff7tk PRIVATE -stdlib=libc++)
     set_target_properties(ff7tk PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
     if(${BUILD_FRAMEWORKS})
         target_include_directories(ff7tk PUBLIC $<BUILD_INTERFACE:$<TARGET_BUNDLE_CONTENT_DIR:ff7tk>/Headers>)
     endif()
endif()

if(UNIX)
    set_target_properties(ff7tk PROPERTIES INSTALL_RPATH ${INSTALL_RPATH_STRING})
endif()

set_target_properties(ff7tk PROPERTIES
    FRAMEWORK ${BUILD_FRAMEWORKS}
    FRAMEWORK_VERSION ${PROJECT_VERSION_MAJOR}
    MACOSX_FRAMEWORK_IDENTIFIER com.sithlord48.ff7tk
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${ff7tkData_HEADERS}"
)

target_include_directories(ff7tk PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include/ff7tk>
)

generate_export_header(ff7tk)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ff7tkConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
)

target_link_libraries (ff7tk PUBLIC
        Qt::Core
        Qt::Quick
        Qt::Xml
)

if(${QT_DEFAULT_MAJOR_VERSION} EQUAL "6")
    target_link_libraries(ff7tk PRIVATE Qt6::Core5Compat)
endif()

install(TARGETS ff7tk
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
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ff7tk
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
      ${CMAKE_CURRENT_BINARY_DIR}/ff7tkConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/ff7tkConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ff7tk
    COMPONENT ff7tk_development
)

export(EXPORT ff7tkTargets FILE ${CMAKE_CURRENT_BINARY_DIR}/ff7tkTargets.cmake)

set_property(GLOBAL APPEND PROPERTY ff7tk_targets ff7tk)

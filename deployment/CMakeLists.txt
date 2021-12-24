include (CPackIFW)

##Cpack Deployment Info
#Generate list of built Targets
get_property( TARGETS GLOBAL PROPERTY ff7tk_targets)
set(TARGET_FILES "")
foreach (_target ${TARGETS})
    list(APPEND TARGET_FILES "${CMAKE_BINARY_DIR}/target-temp/${_target}.cmake")
    file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/target-temp/${_target}.cmake CONTENT $<TARGET_FILE:${_target}>)
endforeach()

if(TARGET ff7tkUtils)
    message (STATUS: "BUILDING UTILS")
    if(EXISTS ${ZLIB_ROOT}/bin/zlib.dll)
        set(ZLIB_TARGET "${ZLIB_ROOT}/bin/zlib.dll")
    elseif(EXISTS ${ZLIB_ROOT}/bin/libzlib.dll)
        set(ZLIB_TARGET "${ZLIB_ROOT}/bin/libzlib.dll")
    endif()
    message(STATUS "ZLIB_TARGET: ${ZLIB_TARGET}")
endif()

#Generic Info
set(CPACK_PACKAGE_CONTACT "sithlord48@gmail.com")
set(CPACK_STRIP_FILES TRUE)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.TXT")
set(CPACK_PACKAGE_NAME "ff7tk")
set(CPACK_PACKAGE_VENDOR "sithlord48")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/sithlord48/ff7tk")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${CMAKE_PROJECT_DESCRIPTION})
if (NOT CPACK_PACKAGE_VERSION )
    set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
endif()
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Qt${QT_DEFAULT_MAJOR_VERSION})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.TXT")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/preBuildCPack.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/preBuildCPack.cmake @ONLY)
set(CPACK_PRE_BUILD_SCRIPTS ${CMAKE_CURRENT_BINARY_DIR}/preBuildCPack.cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cpackOptions.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/cpackOptions.cmake @ONLY)
set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/cpackOptions.cmake)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)

#components
cpack_add_component(ff7tk_runtime
    DISPLAY_NAME "ff7tk Libraries"
    DESCRIPTION "Libraries needed to run applications built with ff7tk"
    REQUIRED
)

cpack_add_component(ff7tk_development
    DISPLAY_NAME "ff7tk Development Files"
    DESCRIPTION "Files needed to develop applications using ff7tk"
    DEPENDS ff7tk_runtime
    DISABLED
)

cpack_add_component_group(ff7tk_demos
    DISPLAY_NAME "ff7tk Demos"
    DESCRIPTION "Demo applicaions using ff7tk"
)

cpack_add_component(ff7tkWidgetGallery
    DISPLAY_NAME "DemoApp: Widget Gallery"
    DESCRIPTION "A Demo Application using ff7tk's widgets"
    DEPENDS ff7tk_runtime
    GROUP ff7tk_demos
)

cpack_add_component(ff7tkQmlGallery
    DISPLAY_NAME "DemoApp: Qml Gallery"
    DESCRIPTION "A Demo Application using ff7tk's Qml Components"
    DEPENDS ff7tk_runtime
    GROUP ff7tk_demos
)

#IFW
set(CPACK_IFW_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
set(CPACK_IFW_PACKAGE_TITLE "${CPACK_PACKAGE_NAME} Installer")
set(CPACK_IFW_PACKAGE_PUBLISHER ${CPACK_PACKAGE_CONTACT})
set(CPACK_IFW_PACKAGE_WIZARD_SHOW_PAGE_LIST OFF)

set(CPACK_IFW_PACKAGE_MAINTENANCE_TOOL_NAME ff7tk-install-tool)
set(CPACK_IFW_PACKAGE_MAINTENANCE_TOOL_INI_FILE ff7tk-install-tool.ini)
if(WIN32)
    set(CPACK_IFW_PACKAGE_ICON ${CMAKE_CURRENT_SOURCE_DIR}/ff7tk_installer.ico)
elseif(APPLE)
    set(CPACK_IFW_PACKAGE_ICON ${CMAKE_CURRENT_SOURCE_DIR}/ff7tk_installer.icns)
endif()

set(CPACK_IFW_PACKAGE_WINDOW_ICON ${CMAKE_CURRENT_SOURCE_DIR}/ff7tk_installer.png)

cpack_ifw_configure_component(ff7tk_runtime
    ESSENTIAL FORCED_INSTALLATION
    DISPLAY_NAME "ff7tk Runtime Libs"
    DESCRIPTION "Files run applications built with ff7tk"
    SORTING_PRIORITY 4
    LICENSES "LGPL3+" ${CPACK_RESOURCE_FILE_LICENSE}
)

cpack_ifw_configure_component(ff7tk_development
    DISPLAY_NAME "ff7tk Dev Files"
    DESCRIPTION "Files needed to build applications with ff7tk"
    DEFAULT FALSE
    SORTING_PRIORITY 3
    LICENSES "LGPL3+" ${CPACK_RESOURCE_FILE_LICENSE}
)

cpack_ifw_configure_component(ff7tkWidgetGallery
    DISPLAY_NAME "DemoApp: Widget Gallery"
    DESCRIPTION "A Demo Application using ff7tk's widgets"
    DEFAULT FALSE
    SORTING_PRIORITY 2
    LICENSES "LGPL3+" ${CPACK_RESOURCE_FILE_LICENSE}
)

cpack_ifw_configure_component(ff7tkQmlGallery
    DISPLAY_NAME "DemoApp: Qml Gallery"
    DESCRIPTION "A Demo Application using ff7tk's Qml Components"
    DEFAULT FALSE
    SORTING_PRIORITY 1
    LICENSES "LGPL3+" ${CPACK_RESOURCE_FILE_LICENSE}
)

#Set Name And Generator Based on the system
if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(CPACK_GENERATOR "ZIP")
    set(OS_STRING "macos_${CMAKE_SYSTEM_PROCESSOR}")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(CPACK_GENERATOR "7Z")
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(OS_STRING "win64")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(OS_STRING "win32")
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(CPACK_GENERATOR "TGZ")
    set(OS_STRING ${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR})
    if(EXISTS "/usr/bin/dpkg")
        list(APPEND CPACK_GENERATOR "DEB")
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
        set(CPACK_DEBIAN_PACKAGE_PROVIDES ${CPACK_PACKAGE_NAME})
        set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
    endif()
    if(EXISTS "/usr/bin/rpmbuild")
        list(APPEND CPACK_GENERATOR "RPM")
        set(CPACK_RPM_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Qt${QT_DEFAULT_MAJOR_VERSION}-${CMAKE_SYSTEM_PROCESSOR}.rpm")
    endif()
else()
    set(OS_STRING ${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR})
endif()

if (CPACK_IFW_FRAMEWORK_VERSION)
    list(APPEND CPACK_GENERATOR "IFW")
    list(APPEND CPACK_PACKAGE_EXECUTABLES "ff7tk-install-tool;Modify ff7tk Install")
endif()

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Qt${QT_DEFAULT_MAJOR_VERSION}-${OS_STRING}")

#Source Package
set(CPACK_SOURCE_IGNORE_FILES "build" .directory .git* )
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-src")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
if(UNIX AND NOT APPLE)
    install(
        DIRECTORY ${RUNTIME_DEPENDS_PATH}/
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT ff7tk_runtime_depends
        FILES_MATCHING PATTERN "*.*"
    )
elseif(WIN32)
    install(
        DIRECTORY ${RUNTIME_DEPENDS_PATH}/
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT ff7tk_runtime_depends
        FILES_MATCHING PATTERN "*.*"
    )
    cpack_add_component(ff7tk_runtime_depends
            HIDDEN
            REQUIRED
        )
endif()

include(CPackIFW)
cpack_ifw_configure_component(ff7tk_runtime_depends
    VIRTUAL FORCED_INSTALLATION
)

include(CPack)

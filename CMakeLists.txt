# SPDX-FileCopyrightText: 2019 - 2023 Chris Rizzitello <sithlord48@gmail.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0074 NEW)

#Set The Current Version Number to use as fallback if GIT Fails.
set(FF7TK_VERSION_MAJOR 1)
set(FF7TK_VERSION_MINOR 3)
set(FF7TK_VERSION_PATCH 0)
set(FF7TK_VERSION_TWEAK 0)
# Get the version from git if it's a git repository
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
  find_package(Git)
  if(GIT_FOUND)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} describe --long --match v* --always
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE GITREV
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
      string(FIND ${GITREV} "v" isRev)
      if(NOT ifRev EQUAL -1)
        string(REGEX MATCH [0-9]+ MAJOR ${GITREV})
        string(REGEX MATCH \\.[0-9]+ MINOR ${GITREV})
        string(REPLACE "." "" MINOR "${MINOR}")
        string(REGEX MATCH [0-9]+\- PATCH ${GITREV})
        string(REPLACE "-" "" PATCH "${PATCH}")
        string(REGEX MATCH \-[0-9]+\- TWEAK ${GITREV})
        string(REPLACE "-" "" TWEAK "${TWEAK}")
        set(FF7TK_VERSION_MAJOR ${MAJOR})
        set(FF7TK_VERSION_MINOR ${MINOR})
        set(FF7TK_VERSION_PATCH ${PATCH})
        set(FF7TK_VERSION_TWEAK ${TWEAK})
      elseif(NOT ${GITREV} STREQUAL "")
        set(FF7TK_VERSION_TWEAK ${GITREV})
      endif()
  endif()
endif()

option(USE_ALL_CPU "Detect and use all cores to build" ON)
if(USE_ALL_CPU)
    cmake_host_system_information(RESULT N QUERY NUMBER_OF_LOGICAL_CORES)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif()
set(FF7TK_VERSION "${FF7TK_VERSION_MAJOR}.${FF7TK_VERSION_MINOR}.${FF7TK_VERSION_PATCH}.${FF7TK_VERSION_TWEAK}")
message(STATUS "Building FF7TK: ${FF7TK_VERSION} Using: ${CMAKE_BUILD_PARALLEL_LEVEL} Threads")

#SET UP THE PROJECT
project(ff7tk VERSION ${FF7TK_VERSION} DESCRIPTION "Work with Final Fantasy 7 game data" LANGUAGES CXX C)

#Prevent In-sourcebuild
if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "In source builds are not allowed; Set a build path")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Pick a faster linker based on compiler for linux
if (UNIX AND NOT APPLE)
    if(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
        string(REPLACE "." ";" VERSION_LIST ${CMAKE_CXX_COMPILER_VERSION})
        list(GET VERSION_LIST 0 CLANG_VERSION_MAJOR)
        find_program(LLD_PROGRAM_MATCH_VER lld-${CLANG_VERSION_MAJOR})
        find_program(LLD_PROGRAM lld)
        if (LLD_PROGRAM_MATCH_VER)
            message(STATUS "Set linker to LLD: ${LLD_PROGRAM_MATCH_VER}")
            add_link_options("-fuse-ld=lld-${CLANG_VERSION_MAJOR}")
        elseif(LLD_PROGRAM)
            message(STATUS "Set linker to LLD: ${LLD_PROGRAM}")
            add_link_options("-fuse-ld=lld")
        endif()
    elseif(${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
        find_program(GNU_GOLD_PROGRAM gold)
        if (GNU_GOLD_PROGRAM)
            message(STATUS "Set linker to GNU gold")
            add_link_options("-fuse-ld=gold;LINKER:--threads,--thread-count=${CMAKE_BUILD_PARALLEL_LEVEL}")
        endif(GNU_GOLD_PROGRAM)
    endif()
endif()


#Set Our Required Qt Version
set(REQUIRED_QT_VERSION 6.2.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

##Modules We Will use
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(GNUInstallDirs)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/ff7tkMacros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/sbom.cmake)

# Setup the SBOM to be generated during install.
sbom_generate(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/sbom-${PROJECT_NAME}-${PROJECT_VERSION}.spdx
        LICENSE  LGPL-3.0-or-later
        SUPPLIER sithlord48
        SUPPLIER_URL "http://github.com/sithlord48/ff7tk"
)
#Qt Info to get deploy app
find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core)
get_target_property(qmake_executable Qt6::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${qmake_executable}" DIRECTORY)
if(WIN32 OR APPLE)
    if(WIN32)
        set(deployqtapp windeployqt)
    elseif(APPLE)
        set(deployqtapp macdeployqt)
    endif()
    find_program(PLATFORMDEPLOYQT ${deployqtapp} HINTS "${_qt_bin_dir}")
endif()
sbom_add(PACKAGE Qt VERSION ${Qt6Core_VERSION})

option(FRAMEWORKS "Build Frameworks on MacOS (EXPERMENTAL)" OFF)
#Set the Rpath for our libs.
if(UNIX)
    if(NOT APPLE)
        set(INSTALL_RPATH_STRING "\${ORIGIN}:\$ORIGIN/../lib:/lib:/usr/lib:/usr/local/lib:\$HOME/.local/lib:\$HOME/.local/usr/lib")
    elseif(APPLE AND NOT FRAMEWORKS)
        set(INSTALL_RPATH_STRING "@loader_path/../Frameworks @loader_path @executable_path @executable_path/../Frameworks")
    endif()
endif()

define_property(GLOBAL PROPERTY ff7tk_targets BRIEF_DOCS "Defined Non-Test Targets" FULL_DOCS "Dynamicly Generated list of Targets Tests")
define_property(GLOBAL PROPERTY ff7tk_tests BRIEF_DOCS "Defined Tests" FULL_DOCS "Dynamicly Generated list of Defined Tests")

add_subdirectory(docs)

option(DEMOS "Build Demo Apps" OFF)
if(DEMOS)
    add_subdirectory(demos)
endif()

option(TRANSLATIONS "Build ff7tk Translation files" ON)
if(TRANSLATIONS)
  add_subdirectory(translations)
endif()

add_subdirectory(src)

option(TESTS "Skip UnitTests" ON)
if(TESTS)
    add_subdirectory(unittests)
endif()

#Always add packaging last
option(PACKAGE "Allow Packaging" ON)
if(PACKAGE)
    add_subdirectory(packaging)
endif()

install (FILES "${CMAKE_CURRENT_SOURCE_DIR}/COPYING.TXT" DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/${PROJECT_NAME} RENAME LICENSE COMPONENT ff7tk_libraries)

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/_template/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake")
endif()

option(SBOM_LINT "Verify Generated SBOM is NTIA Compliant" OFF)
if (NOT SBOM_LINT)
    set(NO_VERIFY "NO_VERIFY")
endif()

option(SBOM_GRAPH "Create a Graph of the SBOM" OFF)
if(SBOM_GRAPH)
    set(GRAPH "GRAPH ${CMAKE_CURRENT_BINARY_DIR}/sbom-${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-spdx.png")
endif()

sbom_finalize(
    ${NO_VERIFY}
    ${GRPAH}
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sbom-${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}.spdx DESTINATION share/ff7tk COMPONENT ff7tk_libraries)

if(SBOM_GRAPH)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sbom-${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-spdx.png DESTINATION share/ff7tk COMPONENT ff7tk_libraries)
endif()

option(REUSE_LINT "Verify project for reuse complance" OFF)
if(REUSE_LINT)
    reuse_lint()
endif()

cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0074 NEW)

#Version will be written by tag v1.2.2-4
project(ff7tk VERSION 0.81.0.0 DESCRIPTION "Work with Final Fantasy 7 game data")

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

set(CMAKE_BUILD_PARALLEL_LEVEL ON)

if(NOT QT_DEFAULT_MAJOR_VERSION)
    set(QT_DEFAULT_MAJOR_VERSION 5 CACHE STRING "" FORCE)
endif()

if (${QT_DEFAULT_MAJOR_VERSION} MATCHES "5")
    set(REQUIRED_QT_VERSION 5.15.2)
elseif (${QT_DEFAULT_MAJOR_VERSION} MATCHES "6")
    set(REQUIRED_QT_VERSION 6.2.0)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(GNUInstallDirs)

# Get the version from git if it's a git repository
IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
  FIND_PACKAGE(Git)
  IF(GIT_FOUND)
    EXECUTE_PROCESS(
      COMMAND ${GIT_EXECUTABLE} describe --long --match v*
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE GITREV
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
      string(REGEX MATCH [0-9]+ MAJOR ${GITREV})
      string(REGEX MATCH \\.[0-9]+ MINOR ${GITREV})
      string(REPLACE "." "" MINOR ${MINOR})
      string(REGEX MATCH [0-9]+\- PATCH ${GITREV})
      string(REPLACE "-" "" PATCH ${PATCH})
      string(REGEX MATCH \-[0-9]+\- TWEAK ${GITREV})
      string(REPLACE "-" "" TWEAK ${TWEAK})
      set(CMAKE_PROJECT_VERSION_MAJOR ${MAJOR})
      set(CMAKE_PROJECT_VERSION_MINOR ${MINOR})
      set(CMAKE_PROJECT_VERSION_PATCH ${PATCH})
      set(CMAKE_PROJECT_VERSION_TWEAK ${TWEAK})
      set(CMAKE_PROJECT_VERSION "${MAJOR}.${MINOR}.${PATCH}.${TWEAK}")
  ENDIF(GIT_FOUND)
  ELSE()
ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)

#SET FF7TK_VERSION Used for user facing strings and package version string
set(FF7TK_VERSION "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}")
if(NOT CMAKE_PROJECT_VERSION_MAJOR EQUAL 0)
    string(APPEND FF7TK_VERSION ".${CMAKE_PROJECT_VERSION_PATCH}")
endif()
if(NOT CMAKE_PROJECT_VERSION_TWEAK EQUAL 0)
    string(APPEND FF7TK_VERSION "-${CMAKE_PROJECT_VERSION_TWEAK}")
endif()
MESSAGE(STATUS "Building FF7TK: ${FF7TK_VERSION}")

#Qt Info to get deploy app
find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED COMPONENTS Core)
get_target_property(qmake_executable Qt${QT_DEFAULT_MAJOR_VERSION}::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${qmake_executable}" DIRECTORY)
if(WIN32 OR APPLE)
    if(WIN32)
        set(deployqtapp windeployqt)
    elseif(APPLE)
        set(deployqtapp macdeployqt)
    endif()
    find_program(PLATFORMDEPLOYQT ${deployqtapp} HINTS "${_qt_bin_dir}")
endif()

#Set the Rpath for our libs.
if(UNIX)
    if(NOT APPLE)
        set(INSTALL_RPATH_STRING "\${ORIGIN}:\$ORIGIN/../lib:/lib:/usr/lib:/usr/local/lib:\$HOME/.local/lib:\$HOME/.local/usr/lib")
    else()
        set(INSTALL_RPATH_STRING "@loader_path/../Frameworks @loader_path @executable_path @executable_path/../Frameworks")
    endif()

endif()

define_property(GLOBAL PROPERTY ff7tk_targets BRIEF_DOCS "Defined Non-Test Targets" FULL_DOCS "Dynamicly Generated list of Targets Tests")

add_subdirectory(docs)

option(BUILD_DEMOS "Build Demo Apps" OFF)
if(BUILD_DEMOS)
    add_subdirectory(demos)
endif()

add_subdirectory(lang)
add_subdirectory(packaging)
add_subdirectory(src)

option(ENABLE_TESTING "Build and run UnitTests" ON)
if(ENABLE_TESTING)
    add_subdirectory(unittests)
endif()

#pkgconfig
configure_file(ff7tk.pc.in ff7tk.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/ff7tk.pc DESTINATION share/pkgconfig COMPONENT ff7tk_development)

install (FILES ${CMAKE_SOURCE_DIR}/COPYING.TXT DESTINATION share/licenses/${CMAKE_PROJECT_NAME} RENAME LICENSE COMPONENT ff7tk_runtime)

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake)
endif()


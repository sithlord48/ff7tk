cmake_minimum_required(VERSION 3.21)
cmake_policy(SET CMP0074 NEW)

project(ff7tk VERSION 0.80.21 DESCRIPTION "Work with Final Fantasy 7 game data")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_DEFAULT_MAJOR_VERSION 5)

set(CMAKE_BUILD_PARALLEL_LEVEL ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(GNUInstallDirs)

# Get the version from git if it's a git repository
IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
  FIND_PACKAGE(Git)
  IF(GIT_FOUND)
    EXECUTE_PROCESS(
      COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE "GIT_VERSION"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    MESSAGE( STATUS "Git Commit: ${GIT_VERSION}" )
    add_definitions( -DGIT_VERSION="${GIT_VERSION}")
  ENDIF(GIT_FOUND)
  ELSE()
ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)

option(WIDGET_GALLERY "Build the widget based gallery" OFF)
option(QML_GALLERY "Build the qml based gallery" OFF)
option(DOCS "Build and Install Documents (Requires Doxygen)" OFF)

add_subdirectory(lang)
add_subdirectory(src)

if(WIDGET_GALLERY)
    add_subdirectory(ff7tkWidgetGallery)
endif()

if(QML_GALLERY)
    add_subdirectory(ff7tkQmlGallery)
endif()

if(DOCS)
    add_subdirectory(docs)
endif()

#pkgconfig

configure_file(ff7tk.pc.in ff7tk.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/ff7tk.pc DESTINATION share/pkgconfig)

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake)
endif()

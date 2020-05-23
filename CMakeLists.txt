project(ff7tk)
set(PROJECT_VERSION "0.80.16")
cmake_minimum_required(VERSION 3.8)

option(BuildWidgetGallery "Build the widget based gallery" OFF)
option(BuildQmlGallery "Build the qml based gallery" OFF)
option(BuildDocs "Build and Install Documents (Requires Doxygen)" OFF)

#optional Parts.
if(BuildWidgetGallery)
    add_subdirectory(ff7tkWidgetGallery)
endif()

if(BuildQmlGallery)
    add_subdirectory(ff7tkQmlGallery)
endif()

if (BuildDocs)
    add_subdirectory(docs)
endif()

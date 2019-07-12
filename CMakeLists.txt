project(ff7tk)
set(PROJECT_VERSION "0.80.10")
cmake_minimum_required(VERSION 3.8)

option(BuildWidgetGallery "Build the widget based gallery")
option(BuildQmlGallery "Build the qml based gallery")
option(EnableOpenSSL "Enable OpenSSL")
option(BuildDocs "Build and Install Documents (Requires Doxygen)")

if(EnableOpenSSL)
    find_package ( OpenSSL REQUIRED )
    add_definitions(-DEnableOpenSSL)
endif()

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

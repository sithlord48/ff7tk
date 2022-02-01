# Building ff7tk

To build ff7tk you will a minimum of: 
    - [cmake] 3.21+
    - [Qt] 5.15.2 or 6.2.0+
    - [zlib]


A Default Build of ff7tk will build: 
     - A Required Core Library (libff7tk.so, libff7tk.dylib, or ff7tk.dll)
     - Additional Libraries ff7tkWidgets, ff7tkUtils and ff7tkFormats.
     - Headers for the libraries so you can link to them
     - Required CMake parts to find it post install.
     - Translation files "ff7tk_<lang>.qm" for supported languages
     - Documentation if [doxygen] was found on your system
     - Unit Test that will be run as part of the build process.

## Configuration
ff7tk Supports Several Build options
Build Options:
         Option          |            Description                  |   Default Value    | Addtional Requirments |
:-----------------------:|:---------------------------------------:|:------------------:|:---------------------:|
QT_DEFAULT_MAJOR_VERSION | The Major Version of Qt to use          | 5                  | |
CMAKE_BUILD_TYPE         | Type of Build that is produced          | ReleaseWithDebInfo | |
DOCS                     | Build Documentation.                    | ON                 | [doxygen] |
BUILD_TESTING            | Build and run unit tests                | ON                 | |
BUILD_DEMOS              | Build The Demo Applications             | OFF                | |
WIDGET_GALLERY           | Build the Widget based gallery.         | ON                 | Depends on BUILD_DEMOS|
QML_GALLERY              | Build the QML based gallery.            | ON                 | Depends on BUILD_DEMOS|
FRAMEWORKS               | Build as Frameworks (EXPERMANTAL)       | OFF                | Mac Os Only |
FORMATS                  | Build ff7tkFormats                      | ON                 | |
UTILS                    | Build ff7tkUtils.                       | ON                 | [zlib] |
WIDGETS                  | Build ff7tkWidgets.                     | ON                 | |

Example cmake configuration.
`cmake -S. -Bbuild -DWIDGET_GALLERY=ON -DCMAKE_INSTALL_PREFIX=<INSTALLPREFIX>`

## Build
After Configuring you Should be able to run make to build all targets.

`cmake --build build`

## Install
 To test installation run `DESTDIR=<installDIR> cmake --install build` to install into `<installDir>/<CMAKE_INSTALL_PREFIX>` <br>
 Running `cmake --install build` will install to the `CMAKE_INSTALL_PREFIX`

## Making ff7tk packages
 ff7tk can generate several packages using cpack
 To generate packages build the `package` or `package_source` target
 example ` cmake --build build --target package package_source` would generate both package and package source packages.
 Installing the Qt Installer Framework will allow ff7tk to create a QtIFW installer.
 
# Using ff7tk in your project

After installing you can use in your cmake project by simply adding 
`find_project(ff7tk)` link with `ff7tk::ff7tk`

Additional Modules include

`ff7tkFormats` link with `ff7tk::ff7tkFormats`

`ff7tkUtils` link with `ff7tk::ff7tkUtils`

`ff7tkWidgets` link with `ff7tk::ff7tkWidgets`


For QMake you can use the pkgconfig provided by the system
`config +=link_pkgconfig`
`PKGCONFIG += ff7tk`

## ff7tk version info
 include the file ff7tkAbout.h and use the function(s) ff7tk_version(), ff7tk_revision() or ff7tk_qt_version()

## Translations
  In addition to ff7tk's language files your application should also ship the qt_base_<lang>.qm these are required to translate strings from inside Qt libraries.

## Deploying ff7tk with your app
 When using ff7tk your project needs to ship the libraries ff7tk needs to run its recommened to run windepoyqt / macdeployqt on the ff7tk libs being used when you pack your application to be sure to get all the libs needed are deployed.
 
### Item Depends
  - ff7tk
    -- QtCore, QtXml, QtQml, QtQuick, QtSvg, Svg Image plugin, Core5Compat (for Qt6 builds) 
  - ff7tkWidgets
    -- ff7tk, QtWidgets, QtGui
  - ff7tkFormats
    -- QtCore
  - ff7tkUtils
    -- ff7tkFormats, QtGui, ZLib


[Qt]:https://www.qt.io
[doxygen]:http://www.stack.nl/~dimitri/doxygen/
[cmake]:https://cmake.org/
[zlib]:https://zlib.net/

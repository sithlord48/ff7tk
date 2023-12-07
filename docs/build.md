<!--
    SPDX-FileCopyrightText: 2019 - 2023 Chris Rizzitello <sithlord48@gmail.com>
    SPDX-License-Identifier: CC0-1.0
-->

# Building ff7tk

To build ff7tk you will a minimum of: 
    - [cmake] 3.21+
    - [Qt] 6.2.0+
    - [zlib]


A Default Build of ff7tk will build: 
     - A Required Core Library (libff7tk.so, libff7tk.dylib, or ff7tk.dll)
     - All Additional Libraries ff7tkQtWidgets, ff7tkWidgets, ff7tkUtils and ff7tkFormats.
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
CMAKE_BUILD_TYPE         | Type of Build that is produced          | ReleaseWithDebInfo | |
DOCS                     | Build Documentation                     | ON                 | [doxygen] |
DEMOS                    | Build The Demo Applications             | OFF                | |
FORMATS                  | Build ff7tkFormats                      | ON                 | |
PACKAGE                  | Enable Package target                   | ON                 | |
FRAMEWORKS               | Build as Frameworks (EXPERMANTAL)       | OFF                | Mac Os Only |
TESTS                    | Build and run unit tests                | ON                 | |
UTILS                    | Build ff7tkUtils.                       | ON                 | [zlib] |
WIDGETS                  | Build ff7tkWidgets.                     | ON                 | |
SPLITPACKAGES            | Create Split Packages                   | OFF                | |
CLEAN_TRS                | Remove Obsolete Translation Entries     | OFF                | |
SBOM_LINT                | Check the generated SBom for NTIA compliance | OFF           | [ntia-conformance-checker] |
SBOM_GRAPH               | Generate Sbom graph                     | OFF                | [spsx-tools] |
REUSE_LINT               | Check the project for reuse compliance  | OFF                | [reuse] |

Enabling Demos will allow you to set this additional options all are enabled by default
       Demo              |            Description                  |
:-----------------------:|:---------------------------------------:|
WIDGET_GALLERY           | Build the Widget based gallery.         |
QML_GALLERY              | Build the QML based gallery.            |

Example cmake configuration.
`cmake -S. -Bbuild -DDEMOS=ON -DCMAKE_INSTALL_PREFIX=<INSTALLPREFIX>`

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

`ff7tkData` link with `ff7tk::ff7tkData`

`ff7tkFormats` link with `ff7tk::ff7tkFormats`

`ff7tkUtils` link with `ff7tk::ff7tkUtils`

`ff7tkQtWidgets` link with `ff7tk::ff7tkQtWidgets`

`ff7tkWidgets` link with `ff7tk::ff7tkWidgets`


## ff7tk version info
 ff7tk Versions are based on its git info. Failing this the project version is updated on every release.
 include the file ff7tkInfo.h and use the function.
  - ff7tkInfo::version() To get version info in to form of Major.minor.patch.tweak
   -- tweak is Number of commits since the last tag release
### ff7tk version compatibility
 ff7tk versions with the same major and minor version are compatible. Building your project with an incompatible version can lead to API issues for this reason its HIGHLY recommend any CI jobs use a Release or specific COMMIT HASH when pulling ff7tk.

## Translations
  In addition to ff7tk's language files your application should also load and/or ship the qt_base_<lang>.qm these are required to translate strings from inside Qt libraries.
  
You can use ff7tkInfo::translationList to get a QMap<QString, QTranslation*> of all the auto detected language files. This will look in several places in the application directory and around the system to attempt to find them.

## Deploying ff7tk with your app
 When using ff7tk your project needs to ship the libraries ff7tk needs to run its recommended to run windepoyqt / macdeployqt on the ff7tk libs being used when you pack your application to be sure to get all the libs needed are deployed.
 
### Item Depends
  - ff7tk
    -- QtCore
  - ff7tkData
    -- QtCore, QtXml, QtSvg, Svg Image plugin, Core5Compat
  - ff7tkQtWidgets
    -- QtWidgets, QtGui
  - ff7tkWidgets
    -- ff7tkData, ff7tkQtWidgets, QtWidgets, QtGui
  - ff7tkFormats
    -- QtCore, QtGui, ff7tkUtils
  - ff7tkUtils
    -- QtGui, ZLib

### Sbom Generation
 A Software Bill Of Materials will be generated and installed into share/ff7tk
 The SBOM is generated at install time and does not require any additional software on the build system
 Generating a graph or verifing the sbom is ntia compliant requires additonal software see the option table above.

[Qt]:https://www.qt.io
[doxygen]:http://www.stack.nl/~dimitri/doxygen/
[cmake]:https://cmake.org/
[zlib]:https://zlib.net/
[ntia-conformance-checker]:https://github.com/spdx/ntia-conformance-checker
[spdx-tools]:https://github.com/spdx/sbom-tools
[reuse]:https://github.com/fsfe/reuse-tool

# Building ff7tk

To build ff7tk you will a minimum of: 
    - [cmake] 3.21+
    - [Qt] 5.15.2 or 6.2.0+
    - [zlib]


Currently ff7tk will build: 
     - A Required Core Library (libff7tk.so, libff7tk.dylib, or ff7tk.dll)
     - Additional Libraries ff7tkWidgets, ff7tkUtils and ff7tkFormats.
     - Headers for the libraries so you can link to them
     - Required CMake parts to find it post install.
     - Translation files "ff7tk_<lang>.qm" for english(en), spanish(es), french(fr), german(de), japanese(ja) and reunion retranslation(re).


## Configuration
Build Options:
    Option     |            Description                  | Default Value | Addtional Requirments |
:-------------:|:---------------------------------------:|:-------------:|:---------------------:|
WIDGET_GALLERY | Build the Widget based gallery.         | OFF           | |
QML_GALLERY    | Build the QML based gallery.            | OFF           | |
DOCS           | Build Documentation.                    | OFF           | [doxygen] |
FORMATS        | Build ff7tkFormats                      | ON            | |
UTILS          | Build ff7tkUtils.                       | ON            | [zlib] |
WIDGETS        | Build ff7tkWidgets.                     | ON            | |
QT_DEFAULT_MAJOR_VERSION | The Major Version of Qt to use| 5             | |

Example workflow.

## Configure

`cmake -S. -Bbuild -DWIDGET_GALLERY=ON -DCMAKE_INSTALL_PREFIX=<INSTALLPREFIX>`

## Build
After Configuring you Should be able to run make to build all targets.

`cmake --build build`

## Install
 To test installation run `DESTDIR=<installDIR> cmake --install build` to install into `<installDir>/<CMAKE_INSTALL_PREFIX>` <br>
 Running `cmake --install build` will install to the `CMAKE_INSTALL_PREFIX`


# Using With your project

After installing you can use in your cmake project by simply adding 
`find_project(ff7tk)` link with `ff7tk::ff7tk`

Additional Modules include

`ff7tkFormats` link with `ff7tk::ff7tkFormats`

`ff7tkUtils` link with `ff7tk::ff7tkUtils`

`ff7tkWidgets` link with `ff7tk::ff7tkWidgets`

For QMake you can use the pkgconfig provided by the system
`config +=link_pkgconfig`
`PKGCONFIG += ff7tk`

## Translations
  In addition to ff7tk's language files your application should also ship the qt_base_<lang>.qm

# ff7tk version info
 include the file ff7tkAbout.h and use the function(s) ff7tk_version(), ff7tk_revision() or ff7tk_qt_version()

[Qt]:https://www.qt.io
[doxygen]:http://www.stack.nl/~dimitri/doxygen/
[cmake]:https://cmake.org/
[zlib]:https://zlib.net/

# Building ff7tk
To build ff7tk you wil need [cmake], [Qt] and [zlib]

Currently ff7tk will build:
     - A Library (libff7tk.so, libff7tk.dylib, or ff7tk.dll)
     - Headers for the library so you can link to it
     - Required CMake parts to find it post install.


## Configuration
By Default only the library will be built. Enable additional items show below by adding options.

Build Options:
Option | Description |
:-----:|:-----------:|
WIDGET_GALLERY |Build the Widget based gallery.
QML_GALLERY |Build the Qml based gallery.
DOCS |Build Documentation, [doxygen] is required.

Example cmake command.

`cmake -DWIDGET_GALLERY=ON -DCMAKE_INSTALL_PREFIX=<INSTALLPREFIX> CMakeLists.txt`

## Building
After Configuring you Should be able to run make to build all targets.

`make`

## Install
 running`make install` will install the built items into the provided <INSTALLPREFIX>

# Using With your project

After installing you can use in your cmake project by simply adding 
`find_project(ff7tk)`
and link with `ff7tk::ff7tk`

For QMake you can use the pkgconfig provided by the system
`config +=link_pkgconfig`
`PKGCONFIG += ff7tk`

# ff7tk version info
 include the file ff7tk/about.h and use the function ff7tk_version()

[Qt]:https://www.qt.io
[doxygen]:http://www.stack.nl/~dimitri/doxygen/
[cmake]:https://cmake.org/
[zlib]:https://zlib.net/

# Building ff7tk
ff7tk does not currently build a library to be linked to your project. Include the files needed from ff7tk in your project. The instruction here are for the Gallery applications and Documentation.

## Configuration
ff7tk can be configured with with either cmake or qmake.

### Configure with cmake
Currently the ff7tk cmake does not build anything by default. You must provide an option.Building the Widget Gallery with cmake will require [zlib] since it includes but does not use the GZIP object.

Build Options:
Option | Description |
:-----:|:-----------:|
BuildWidgetGallery |Build the Widget based gallery.
BuildQmlDGallery |Build the Qml based gallery.
EnableOpenSSL |Enable [OpenSSL] for ps3 Save Signing.
BuildDocs |Build Documentation, [doxygen] is required.

Example cmake command.

`cmake -DBuildWidgetGallery=ON -DEnableOpenSSL=ON CMakeLists.txt`

### Configure with qmake
Simply open the pro file in either the ff7tkWidgetGallery or ff7tkQmlGallery folders. The qmake build for ff7tkWidgetGallery does not require [zlib] since it does not include the GZIP object at this time.

Example qmake command.

`qmake "DEFINES+=EnableOpenSSL" ff7tkWidgetGallery.pro`

## Building
After Configuring you Should be able to run make to build all targets.

`make`

## Additional Dependencies

----

  Object  | Dependency | Notes
 :-------:|:----------:|:-----:
 #FF7Save | [OpenSSL]  | Optional, but you will be unable to attempt ps3 save signing.
 #GZIP    | [zlib]     | Required.

[Qt]:https://www.qt.io
[doxygen]:http://www.stack.nl/~dimitri/doxygen/
[cmake]:https://cmake.org/
[extra-cmake-modules]:https://cgit.kde.org/extra-cmake-modules.git/tree
[OpenSSL]:https://www.openssl.org/
[OpenSSL Binaries]:https://wiki.openssl.org/index.php/Binaries
[zlib]:https://zlib.net/

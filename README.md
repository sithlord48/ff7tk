ff7tk
[![Linux Status](https://github.com/sithlord48/ff7tk/actions/workflows/build.yml/badge.svg)](https://github.com/sithlord48/ff7tk/actions/workflows/build.yml) [![Codacy Badge](https://app.codacy.com/project/badge/Grade/2f18d1606058447a9cc5fdc3753373de)](https://app.codacy.com/gh/sithlord48/ff7tk/dashboard)
===
ff7tk is a Toolkit that makes programing Final Fantasy VII tools easier.

This project is under [LGPL-3.0]+.

ff7tk is written by:

 - Chris Rizzitello <sithlord48@gmail.com>

 with Contributions from: 

 - Jérôme Arzel <myst6re@gmail.com>
 - Vegeta_Ss4 <vegeta.ss4.dev@gmail.com>

 Using Icons from:

 - Action Icons from [Tango Desktop Project]
 - Item Icons from[Team Avalanche GUI]
 - Char Images from [Aavock UI Overhaul]
## Using the Installers
### ff7tk installer
You can use the `ff7tk <version>-installer` to install ff7tk, when using them its recommended to install to one of following paths.
 - Windows:
   - `C:\Program Files\ff7tk`
   - `C:\Program Files\ff7tk-<VERSION#>`
 - Mac OS
   - `~/Applications/ff7tk`
   - `~/Applications/ff7tk-<VERSION#>`
   - `/Applications/ff7tk`
   - `/Applications/ff7tk-<VERSION#>`
 - Linux
   - `/opt/ff7tk`
   - `/opt/ff7tk-VERSION`
   - `~/.local/opt/ff7tk`
   - `~/.local/opt/ff7tk-<VERSION#>`

### Adding ff7tk to the path
  Depending on your os and how you install you may want to also add the install path explicitly to your "PATH"

  - Windows
    - [Windows_Add to_path]
    - Developers may also want to add `<ff7tk_install_path>/lib/cmake/ff7tk` to the path so cmake can easily find ff7tk.

  - Linux / Mac os
    - [Linux_Add_to_path]
    - Make a new file /etc/ld.so.d/ff7tk that contains the path to the ff7tk libs, then run `ldconfig`

## Building with ff7tk
 - [Building]
 - [Documentation]

## Projects using parts or all of ff7tk
 - [Black Chocobo]
 - [Makou Reactor]

## Getting Involved
 - ff7tk's [Web] page
 - Report [Bugs].
 - Support us by making a [Donation].
 - [Contribute] to ff7tk.

[Aavock UI Overhaul]:https://forums.qhimm.com/index.php?topic=20331
[Tango Desktop Project]:http://tango.freedesktop.org/Tango_Desktop_Project
[Team Avalanche GUI]:https://forums.qhimm.com/index.php?topic=18397
[Bugs]:https://github.com/sithlord48/ff7tk/issues
[Web]:https://github.com/sithlord48/ff7tk
[LGPL-3.0]:https://www.gnu.org/licenses/lgpl.html
[Donation]:http://sourceforge.net/p/blackchocobo/donate/
[Black Chocobo]:https://github.com/sithlord48/blackchocobo
[Makou Reactor]:https://github.com/myst6re/makoureactor
[Documentation]:https://sithlord48.github.io/ff7tk/
[Building]:http://sithlord48.github.io/ff7tk/md_docs_build.html
[Contribute]:http://sithlord48.github.io/ff7tk/md_docs_CONTRIBUTING.html
[Releases]:https://github.com/sithlord48/ff7tk/releases
[Windows_Add to_path]:https://docs.microsoft.com/en-us/previous-versions/office/developer/sharepoint-2010/ee537574(v=office.14)
[Linux_Add_to_path]:https://stackabuse.com/how-to-permanently-set-path-in-linux/

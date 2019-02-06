# Brief
This project is the open source openD developer's framework. The purpose of this project is to provide a framework which defines a unified API for DECT and Ultra Low Energy (ULE) DECT fixed and portable part devices designed to support various hardware platforms.

The idea of the openD framework is to make the DECT and ULE technology available to enable a fast and easy development of DECT and ULE devices. The framework provides sample codes, tutorials and documentation.

# Table of Contents

- [OpenD Community](#opendcommunity)
- [Quick Start Guide](#quickstartguide)
  - [Introduction](#quickstartguide_intro)
  - [Demonstration Applications](#demonstrationapplications)
  - [Hardware Platforms](#hardware_platforms)
  - [Build Instructions](#buildinstructions)
      - [Build System](#buildinstructions_sys)
      - [Toolchains](#buildinstructions_tool)
      - [Build Applications](#buildinstructions_app)
  - [IDE Integration](#ideintegration)
  - [Debugging](#debugging)
  - [UDP](#udp)
- [Further Information](#furtherinformation)
- [License](#license)
- [Acknowledgments](#acknowledgments)

<a name="opendcommunity"/>

# OpenD Community

The openD community is the place where you can find all information around DECT ULE and the openD framework. It is the place where developers come together to discuss DECT ULE and openD related topics and to exchange information and know-how. You will also find much more:

- News and events about openD and DECT ULE
- General information regarding the openD project
- Information about manufacturers and supported hardware
- Forums
- Blogs
- Live chat

<a name="quickstartguide"/>

# Quick Start Guide

<a name="quickstartguide_intro"/>

## Introduction

The background of the quick start guide is to provide a fast and easy introduction into the principles of the openD framework project. Users should get familiar with the purpose and concepts of the demonstration applications and should be able to setup a hardware configuration with a fixed part (FP) and a portable part (PP). One could also name the fixed part as a base and a portable part as a handset. Also, a user should be able to setup and configure his development environment and be able to build different configurations of this project.

<a name="demonstrationapplications"/>

## Demonstration Applications

In general, the purpose of the demonstration applications is to provide an overview of the key features of the openD framework - especially, this includes the utilization of HAN FUN profiles and services as well as voice calls and audio links. This chapter lists all available demonstration applications including a short descriptions containing the important services and principles. Please also refer to section [Hardware Platforms](#hardware_platforms) for a description which describes the hardware platforms and its related demonstration application features.

**Basic call**

  This example is a voice call from the PP to the FP or vise versa. It demonstrates the openD framework opens up a voice call including the management services as device registration, initiating the call and picking up the phone. This framework provides examples for both, the FP and the PP as initiator of the call.

  1. Run the UDP_Client_Legacy and LEGACY_FP_SERVER demo applications on the Raspberry PI 3 and the LEGACY_PP demo application on the Nucleo hardware.

  2. Open the registration window with the client demo application.<br/>
  The terminal input to open the registration window is the key "w".

  3. Press the blue button on the Nucleo hardware to send a registration request.<br/>
  Wait until the successful registration confirmation terminal output on the client demo application.

  4. Setup a call with the handset id shown in the successful registration confirmation output on the client demo application.<br/>
  The terminal input to setup a call with the handset id h is "r h". To setup a call with the Nucleo hardware press the blue button.<br/>
  Wait until the successful call setup confirmation terminal output on the client demo application.

  5. Release a call with the call id shown in the successful call setup confirmation output on the client demo application.<br/>
  The terminal input to release a call with the call id <c> is "t <c>". To release a call with the Nucleo hardware press the blue button.<br/>
  Wait until the successful call release confirmation terminal output on the client demo application.

  **Note:** It is also possible to use a C38H hardware as handset.<br/>
  **Note:** You can write a shell script to pipe the sound of the dspg hardware.<br/>
  Example for shell script:

  ```sh
  #!/bin/bash
  pulseaudio -k
  pactl load-module module-loopback source="nameOfSource" sink="nameOfSink"
  pactl load-module module-loopback source="nameOfSource" sink="nameOfSink"
  ```

**Internal call**

  The internal call example shows how to handle voice calls from one PP to another PP using a central FP. The FP acts as a central "server" between the to PPs and forwards the call.

  1. Run the UDP_Client_Legacy and LEGACY_FP_SERVER demo applications on the Raspberry PI 3 and the LEGACY_PP_INTERCOM demo application on the two Nucleo hardwares.

  2. Open the registration window with the client demo application.<br/>
  The terminal input to open the registration window is the key "w".

  3. Press the blue button on the first Nucleo hardware to send a registration request with the first handset.<br/>
  Wait until the successful registration confirmation terminal output on the client demo application.

  4. Open the registration window with the client demo application.<br/>
  The terminal input to open the registration window is the key "w".

  5. Press the blue button on the second Nucleo hardware to send a registration request with the second handset.<br/>
  Wait until the successful registration confirmation terminal output on the client demo application.

  6. Press the blue button on the first Nucleo hardware to send a setup intercom call request.

  7. Press the blue button on the second Nucleo hardware to answer the setup intercom call request.

  8. To release a call press the blue button on the first or second Nucleo hardware.

  **Note:** It is also possible to use a C38H hardware as handset.<br/>
  **Note:** You can write a shell script to pipe the sound of the dspg hardware.<br/>
  Example for shell script:

  ```sh
  #!/bin/bash
  pulseaudio -k
  pactl load-module module-loopback source="nameOfSource" sink="nameOfSink"
  pactl load-module module-loopback source="nameOfSource" sink="nameOfSink"
  ```

**Simple light with the HAN FUN 'Simple Switch' profile**

  This example utilizes the 'Simple Switch' profile from the HAN FUN specification. THe PP implements this profile provides the possibility to switch a light on the hardware platforms.

  1. Run the UDP_Client_Hanfun and HANFUN_SimpleSwitch_FP demo applications on the Raspberry PI 3 and the HANFUN_SimpleLight_PP demo application on the Nucleo hardware.

  2. Open the registration window with the client demo application.<br/>
  The terminal input to open the registration window and register a device x is "r 1 x".

  3. Press the blue button on the Nucleo hardware to send a registration request.

  4. List the registered devices to check if the portable part has been registered successfully with the client demo application.<br/>
  The terminal input to list the registered devices is "lr".

  5. Close the registration window with the client demo application.<br/>
  The terminal input to close the registration window is "r 0".

  6. Send a toggle command to device x/unit pair u with the client demo application.<br/>
  The terminal input to toggle the specific led on a device d with unit pair u is "tog d u".


**Simple switch with the HAN FUN 'On/Off' profile**

  The simple switch sample application implements a HAN FUN 'On/Off' profile on the PP side. The FP can use the profile to perform toggle operations on the hardware platforms.

  1. Run the UDP_Client_Hanfun and HANFUN_SimpleSwitch_FP demo applications on the Raspberry PI 3 and the HANFUN_SimpleLight_PP demo application on the Nucleo hardware.

  2. Open the registration window with the client demo application.<br/>
  The terminal input to open the registration window and register a device x is "r 1 x".

  3. Press the blue button on the Nucleo hardware to send a registration request.

  4. List the registered devices to check if the portable part has been registered successfully with the client demo application.<br/>
  The terminal input to list the registered devices is "lr".

  5. Send an on command to device x/unit pair u with the client demo application.<br/>
  The terminal input to turn on the specific led on a device d with unit pair u is "on d u".

  6. Send an off command to device x/unit pair u with the client demo application.<br/>
  The terminal input to turn off the specific led on a device d with unit pair u is "off d u".

  7. Deregister the device with the client demo application.<br/>
  The terminal input to deregister a device x is "d x".

**Device management example on the PP to mute audio**

  This example demonstrates how to mute the volume on the PP for an active audio connection with the openD framework. The implementation uses the device management services.

  1. Run the UDP_Client_Legacy and LEGACY_FP_SERVER demo applications on the Raspberry PI 3 and the LEGACY_PP demo application on the Nucleo hardware.

  2. Open the registration window with the client demo application.<br/>
  The terminal input to open the registration window is the key "w".

  3. Press the blue button on the Nucleo hardware to send a registration request.<br/>
  Wait until the successful registration confirmation terminal output on the client demo application.

  4. Setup a call with the handset id shown in the successful registration confirmation output on the client demo application.<br/>
  The terminal input to setup a call with the handset id h is "r h". To setup a call with the Nucleo hardware press the blue button.<br/>
  Wait until the successful call setup confirmation terminal output on the client demo application.

  5. Mute the audio on the client demo application.<br/>
  The terminal input to mute the audio is "z".<br/>
  Wait until the successful mute audio confirmation terminal output on the client demo application.

  6. Un-mute the audio on the client demo application.<br/>
  The terminal input to un-mute the audio is "u".<br/>
  Wait until the successful un-mute audio confirmation terminal output on the client demo application.

**Device management example on the PP to change the volume for audio**

  This is an example which shows how to use the device management services of the openD framework to change the volume of an active audio connection.

  1. Run the UDP_Client_Legacy and LEGACY_FP_SERVER demo applications on the Raspberry PI 3 and the LEGACY_PP demo application on the Nucleo hardware.

  2. Open the registration window with the client demo application.<br/>
  The terminal input to open the registration window is the key "w".

  3. Press the blue button on the Nucleo hardware to send a registration request.<br/>
  Wait until the successful registration confirmation terminal output on the client demo application.

  4. Setup a call with the handset id shown in the successful registration confirmation output on the client demo application.<br/>
  The terminal input to setup a call with the handset id h is "r h". To setup a call with the Nucleo hardware press the blue button.<br/>
  Wait until the successful call setup confirmation terminal output on the client demo application.

  5. Volume up the audio on the client demo application.<br/>
  The terminal input to mute the audio is "i".<br/>
  Wait until the successful volume up the audio confirmation terminal output on the client demo application.

  6. Volume down the audio on the client demo application.<br/>
  The terminal input to mute the audio is "o".<br/>
  Wait until the successful volume down the audio confirmation terminal output on the client demo application.

<a name="hardware_platforms"/>

## Hardware Platforms

This project supports different hardware platforms. This section provides an overview of the applicable platforms with respect to the openD device type.

| **openD Device** | **Hardware Platform** |
|:-:|:-:|
| FP | Raspberry PI 3 |
| PP | Nucleo-L476RG  |

To use the openD framework and its features, other hardware pieces are necessary. The project supports the following shields. Both, the Raspberry PI and the Nucleo-L476RG support the shields.

| **Shield** | **Manufacturer** | **Reference** |
|:-:|:-:|:-:|
| Dialog Shield | Dialog Semiconductor | [Link](https://www.dialog-semiconductor.com/opend) |
| DSPG Shield | DSP Group | [Link](https://www.dspg.com/) |

Please refer to the following images of the supported hardwares:

| **Manufacturer** | **Fixed Part** | **Portable Part** |
|:-:|:-:|:-:|
|Dialog Semiconductor|![Fixed Part - Dialog Semiconductor](/doc/pics/Dialog_FP.png)|![Portable Part - Dialog Semiconductor](/doc/pics/Dialog_PP.png)|
|DSPG|![Fixed Part - DSPG](/doc/pics/DSPG_FP.png)|![Portable Part - DSPG](/doc/pics/DSPG_PP.png)|

<a name="buildinstructions"/>

## Build Instructions

<a name="buildinstructions_sys"/>

### Build System

This project uses CMake as build system. A user is able to build the firmware with a terminal or with an IDE on Windows, Linux and OSX. The project requires a **CMake version >= v3.6**. Example installations are:

* Windows
  * [CMake Download](https://cmake.org/download/) from the official homepage.
* Linux
  * `sudo apt-get install cmake`
* OSX
  * Homebrew: `brew install cmake`

<a name="buildinstructions_tool"/>

### Toolchains

This project uses two different toolchains to build the firmware. The GNU Arm Embedded Toolchain (arm-none-eabi) builds the firmware for the Nucleo-L476RG board with ARM Cortex M4. The GNU Arm Linux Toolchain (arm-linux) builds the firmware for the Raspberry Pi.

* GNU Arm Embedded Toolchain
  * Windows / Linux / OSX
     * Please install the gcc-arm-none-eabi toolchain, version **7-2018-q2-update**. E.g. a download is available [here](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads).
     * For windows, the tool *Make* is also required. E.g., the MSYS2 includes it [MSYS2](http://www.msys2.org/).
       **Note:** Add both path to the environment `Path` variable.
       For example, add `C:\msys64\mingw64\bin` and `C:\Program Files (x86)\GNU Tools ARM Embedded\7 2018-q2-update\bin`.

* GNU Arm Linux Toolchain
  * Windows
     * Please install the gcc-arm-linux-gnueabihf toolchain, version **raspberry-gcc6.3.0-r3.exe**. E.g. a download is available [here](http://gnutoolchains.com/raspberry/).
     * Make is also required, you can download and install [MSYS2](http://www.msys2.org/).
       **Note:** Add both path to the environment `Path` variable.
       For example, add `C:\msys64\mingw64\bin` and `C:\SysGCC\Raspberry\bin`.
  * Linux
     * Please install the gcc-arm-linux-gnueabihf toolchain, version **linaro-1.13.1+bzr2650 - Linaro GCC 2014.03 4.8.3**. E.g. a download is available [here](https://github.com/raspberrypi/tools/tree/master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64 ).
  * OSX
     * E.g. a download is available [here](https://github.com/asymptotik/crosstool-arm-osx).


<a name="buildinstructions_app"/>

### Build Applications

**Generic Build Example**

In general, the procedure to build a version of this project with CMake is as follows:

1. Start a terminal in the home directory of the project.
2. Add a new directory for the CMake build system: `mkdir build`.
3. Go into the new directory: `cd build`.
4. Configure CMake: `cmake -DCMAKE_BUILD_TYPE=Release -DTOOLCHAIN_PREFIX=/usr -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/arm-linux-gnueabihf.cmake -DBOARD=DialogMmiRpi -DAPPLICATION=HANFUN_SimpleSwitch_FP ..`
5. Build the application: `make`

**DSPG Sources**

Please note, that if you want to build an application for a target for DSPG, you have to perform the additional steps:

1. Download the DSPG software package here [Software](https://www.dspg.com/wpdm-package/cmbs-host-sw-package).
      - The package contains a directory called `cmbs`. Please copy the complete folder into the directory `src/opend/dspg/`.
      - The package contains a directory called `CmndLib`. Please copy the complete folder into the directory `src/opend/dspg/pp_hanfun/iwu`.
2. Apply patch: patch/appcallCFile.patch
3. Apply patch: patch/appmsgparserCFile.patch
4. Apply patch: patch/appmsgparserHeader.patch
5. Apply patch: patch/appsrvCFile.patch


**Build Parameters**

According to step 4, the project provides several options to define which demonstration application CMake will configure and build. The following tables describe the different possibilities:

| **CMAKE_BUILD_TYPE** | **Description** |
|-|-|
| Release | CMake builds a release version of the application |
| Debug   | CMake builds a debug version of the application |


| **TOOLCHAIN_PREFIX** | **Description** |
|-|-|
| path_to_your_toolchain | This is the path of the toolchain prefix. Please note that this is just an example and it varies depending on the operating system and your installation directory. When you have installed the toolchain according to [Toolchains](#buildinstructions_tool), it should be `/usr` for Linux and `C:/SysGCC/Raspberry` or `C:/Program Files/GNU Tools ARM Embedded/7 2018-q2-update` for windows. |


| **CMAKE_TOOLCHAIN_FILE** | **Description** |
|-|-|
| cmake/toolchains/arm-linux-gnueabihf.cmake | Use this path if you want to build an application for the RaspberryPI |
| cmake/toolchains/toolchain-cortex-M4.cmake | Use this path if you want to build an application for the Nucleo |

| **BOARD** | **Description** |
|-|-|
| DialogMmiRpi | Board option for the Dialog Semiconductor fixed part |
| DialogMmiNucleo | Board option for the Dialog Semiconductor portable part |
| DspgDectRpi | Board option for the DSPG fixed part |
| DspgDectNucleo | Board option for the DSPG portable part |
| None | Board option for the UDP client |

| **APPLICATION** | **Description** |
|-|-|
| HANFUN_SimpleSwitch_FP | Application option to build the HAN FUN Simple Switch for the fixed part |
| HANFUN_SimpleLight_PP | Application option to build the HAN FUN Simple Light for the portable part |
| UDP_Client_Hanfun | Application option to build the HAN FUN UDP client |
| LEGACY_PP | Application option to build the legacy demo for the portable part |
| LEGACY_FP | Application option to build the legacy demo for the fixed part |
| LEGACY_FP_SERVER | Application option to build the legacy demo for the fixed part server |
| LEGACY_PP_INTERCOM | Application option to build the legacy demo for the portable part with intercom call |
| UDP_Client_Legacy | Application option to build the legacy UDP client |

**Examples**

Build the application HAN FUN Simple Switch for the fixed part, one for Dialog Semiconductor and one for DSPG:

```sh
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DTOOLCHAIN_PREFIX=/usr -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/arm-linux-gnueabihf.cmake -DBOARD=DialogMmiRpi -DAPPLICATION=HANFUN_SimpleSwitch_FP ..
make
```

```sh
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DTOOLCHAIN_PREFIX=/usr -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/arm-linux-gnueabihf.cmake -DBOARD=DspgDectRpi -DAPPLICATION=HANFUN_SimpleSwitch_FP ..
make
```

<a name="ideintegration"/>

## IDE Integration

This project supports VS Code as IDE [VSCode](https://code.visualstudio.com/). The application is available for Windows, Linux and OS. Furthermore, the following extensions are recommended:

**Installation**

* GNU/Linux, Windows and OSX - (**latest tested version: v1.30.2**)
    * [VSCode Download](https://code.visualstudio.com/Download)
* VSCode extensions
    * Open VSCode and search `(Crtl+Shift+x)` the following extensions:
        * C/C++
        * CMake
        * CMake Tools
        * Native Debug

**Settings**

There are a few additional settings required under the Windows platform.
Start VSCode and open `(Crtl+Shift+p)` the command palette. Search `Preferences: Open Settings (JSON)` to open the `settings.json` file .

Add MinGW Makefiles as preferred generator:

```cmake
"cmake.preferredGenerators": [
        "MinGW Makefiles",
        "Ninja",
        "Unix Makefiles"
    ]
```

Add the CMake path:

`"cmake.cmakePath": "path/to/cmake.exe"`

**Configuration for CMake**

The provided user options allow you to choose between application, target board and other options.

The options can be given to CMake as additional parameters during configuration.
1. As command line parameters: `cmake -DBOARD="DialogMmiRpi" ..`
2. With CMake GT GUI: `cmake-gui`
3. In the `settings.json` file of VSCode under .vscode: `"BOARD":"DialogMmiRpi",`

Available options are:

- `CMAKE_TOOLCHAIN_FILE` - Toolchain file definition.
    You can choose between: cmake/toolchains/arm-linux-gnueabihf.cmake, cmake/toolchains/toolchain-cortex-M4.cmake
    For example: `"CMAKE_TOOLCHAIN_FILE":"cmake/toolchains/arm-linux-gnueabihf.cmake"`

- `TOOLCHAIN_PREFIX` - Toolchain prefix definition.
    For example: `"TOOLCHAIN_PREFIX":"C:/Program Files/GNU Tools ARM Embedded/7 2018-q2-update"`
    **Note:** Must be path to your toolchain prefix.

- `APPLICATION` - Determines the application.
    You can choose between: HANFUN_SimpleSwitch_FP, HANFUN_SimpleLight_PP, UDP_Client
    For example: `"APPLICATION":"HANFUN_SimpleSwitch_FP"`

- `Board` - Determines the target board.
    You can choose between: DialogMmiRpi, DialogMmiNucleo, DspgDectNucleo, DspgDectRpi
    For example: `"BOARD":"DialogMmiRpi"`

- `BUILD_DOC` - Doxygen build.
    You can choose between: ON, OFF. Please note that you have to install Doxygen on your system to use this option.
    For example: `"BUILD_DOC":"ON"`

- `OPENOCD_BIN` - Path to openocd.
  **Note:** The VSCode debug configuration assumes that OpenOCD is installed on `C:/openocd`. Otherwise, the CMake variable `OPENOCD_BIN` must be adjusted accordingly.

**Usage**

1. Clone the repository and open the directory of the repository in VSCode.
2. `CMake Tools` will start the initialization process automatically.
3. In the `settings.json` file under the `.vscode` folder you can choose CMake configuration options.
    [Setup and Configuration](#setupandconfiguration) chapter for detailed information.
4. Choose a build type (`Debug` or `Release`) with a click on the blue status bar of CMake Tools. If VSCode asks for the a kit, please select *Do not use a kit*.
5. After the CMake configuration process a `Build` button will be available on the blue status bar.
6. Click this `Build` button to perform a build process of the firmware.
7. In the `launch.json` file under the `.vscode` folder you can choose debug configuration options.
    [Description of how to connect and flash](#flash) chapter for detailed information.
8. With the `F5` key you can start a debug session.

<a name="debugging"/>

## Debugging

The hardware platforms support debugging. The project utilizes [GDB](https://www.gnu.org/software/gdb/) and [OpenOCD](http://openocd.org/about/).

**Handset / Portable part**

The Nucleo-L476RG board communicates with the portable part via UART, so debugging via USB of the Nucleo-L476RG board is possible.
The Nucleo-L476RG board provides a built-in ST-LINK / V2-1 debugger with USB listing capability.
Alternatively, the ST-LINK/V2 for the for the STM8 and STM32 microcontroller families can be used.
You can read [ST-LINK/V2](https://www.st.com/en/development-tools/st-link-v2.html) for detailed confirmation.

**Base / Fixed part**

The Raspberry PI communicates with the fix part via serial connection, so debugging via USB of the Raspberry PI is possible.
The Raspberry PI provide an USB interface, but to use it for debugging you have to install the gdbserver.
You can read [Description of how to connect and flash](#flash) for detailed information how to install gdbserver.

**Installation**

* GNU Debugger (gdb)
    * Supplied by the toolchain.
* Open On-Chip Debugger (OpenOCD) - **Version 0.10.0**
    * Windows
        * [OpenOCD Download] (http://openocd.org/getting-openocd/)
    * Linux
        * Ubuntu/Linux Mint: `apt-get install openocd`
    * OSX
        * Homebrew: `brew install openocd`

<a name="flash"/>

**Flash**

* OpenOCD
    * OpenOCD must be started from the terminal with parameters. The interface and the target must be specified.
    * Example for the Nucleo-L476RG with STLinkV2-1: `openocd -f interface/stlink-v2-1.cfg -f target/stm32l4x.cfg` start the on board debugger.
* GDB
    * Example to start a debug session for the Nucleo-L476RG with the following steps:
      1. Run ARM-GNU GDB:
          * Windows Architecture: `arm-none-eabi-gdb.exe`
          * Linux Architecture: `arm-none-eabi-gdb`
      2. Choose binary to debug:
          * `file openD/build/src/platform/nucleol476/nucleoL476`
      3. Link GDB to OpenOCD:
          * `target extended-remote localhost:3333`
      4. Reset and halt of the target:
          * `monitor reset halt`
      5. Flash firmware to the flash memory of target:
          * `load`
      6. Add a break point at main entry:
          * `thbreak main`
      7. Run the debugger until breakpoint:
          * `continue`
      8. Finally run the program:
          * `continue`
* VSCode
    * Start VSCode and open `(Crtl+Shift+p)` the command palette.
      Execute the command `Debug: Open launch.json` and select as environment `C++ (GDB/LLDB)`.
      This will automatically generate a `launch.json`file under `.vscode`.
      In this file GDB and OpenOCD settings can be set. GDB and OpenOCD are then automatically started with the set settings when debugging.
    * Example for Nucleo-L476RG `launch.json` file:

        ```
          json
          {
          "version": "0.2.0",
          "configurations": [
              {
                  "name": "Debug-nucleoL476",
                  "type": "cppdbg",
                  "request": "launch",
                  "program": "C:/openD/build/src/platform/nucleol476/nucleoL476",
                  "args": [],
                  "stopAtEntry": true,
                  "cwd": "${workspaceRoot}",
                  "environment": [],
                  "externalConsole": false,
                  "debugServerArgs": "-f interface/stlink-v2-1.cfg -f target/stm32l4x.cfg",
                  "serverLaunchTimeout": 20000,
                  "filterStderr": true,
                  "filterStdout": false,
                  "serverStarted": "Info\\ :\\ [\\w\\d\\.]*:\\ hardware",
                  "setupCommands": [
                      { "text": "cd ${workspaceRoot}/build" },
                      { "text": "file \"C:/openD/build/src/platform/nucleol476/nucleoL476\"", "description": "load file", "ignoreFailures": false},
                      { "text": "target extended-remote localhost:3333", "description": "connect to target", "ignoreFailures": false },
                      { "text": "monitor reset halt", "description": "perform a reset and halt the target", "ignoreFailures": false },
                      { "text": "load", "description": "flash target", "ignoreFailures": false },
                      { "text": "set output-radix 16", "description": "set the default numeric base to 16", "ignoreFailures": false }
                  ],
                  "logging": {
                      "moduleLoad": true,
                      "trace": true,
                      "engineLogging": true,
                      "programOutput": true,
                      "exceptions": true
                  },
                  "MIMode": "gdb",
                  "MIDebuggerPath": "C:/Program Files/GNU Tools ARM Embedded/7 2018-q2-update/bin/arm-none-eabi-gdb.exe",
                  "debugServerPath": "C:/openocd/bin/openocd.exe"
              }
          ]
          }
        ```

    * Example for Raspberry PI `launch.json` file:
      **Note:** gdbserver must be installed (`apt-get install gdbserver`) on the Raspberry Pi and the VSCode extension `Remote VSCode`is required.

        ```
          json
          {
          "version": "0.2.0",
          "configurations": [
            {
              "name": "(gdb) Launch Remote Debugging of UDP_CLIENT",
              "type": "cppdbg",
              "request": "launch",
              "program": "${workspaceRoot}/build/UDP_CLIENT",
              "args": [],
              "stopAtEntry": true,
              "cwd": "${workspaceRoot}",
              "environment": [],
              "externalConsole": true,
              "MIMode": "gdb",
              "miDebuggerPath": "C:/SysGCC/raspberry/bin/arm-linux-gnueabihf-gdb-7.10.exe",
              "miDebuggerServerAddress": "10.10.112.20:1235",
              "setupCommands": [
                {
                  "description": "Enable pretty-printing for gdb",
                  "text": "-exec info registers -enable-pretty-printing",
                  "text": "handle SIG34 nostop noprint pass",
                  "ignoreFailures": true
                }
              ],
            }
          ]
          }
        ```

<a name="udp"/>

## UDP

The UDP communication between client and server application is specified by the Json protocol. Thus, it is possible to control the HANFUN server application via the HANFUN client application and to control the LEGACY server application via the LEGACY client application.

The protocol has the following structure:

| version | module | primitive | service | status | param1 | param2 | param3 |

1. version - 1.0.0<br/>
The version specifies the version of the UDP json protocol.

2. module - hanfun/legacy<br/>
The module specifies the module used. Supported are HANFUN and Legacy.

3. primitive - request/confirmation<br/>
The primitive field specifies the primitive used. Request and confirmation UDP messages can be sent.

4. service - Depending on used module<br/>
The service specifies the module specific service that should be executed.<br/>
Module hanfun - deviceManagementEntriesRegistration, deviceManagementRegisterDisable, deviceManagementRegisterEnable, IOnOffClientOn, IOnOffClientOff, IOnOffClientToggle<br/>
Module legacy - openRegistrationWindow, setupCall, releaseCall, mute, un-mute, volumeUp, volumeDown (mute, unmute, volumeUp, volumeDown are not supported by DSPG DHX91 handset hardware)

5. status - OK, ERR, INV<br/>
The status field is used to handle the confirmations.

6. param1<br/>
The param1 field is used to transmit a parameter with a request or confirmation.

7. param2<br/>
The param2 field is used to transmit a parameter with a request or confirmation.

7. param3<br/>
The param3 field is used to transmit a parameter with a request or confirmation.

**Example to send an UDP message with json protocol from Client to server:**

- Client and server application have to include the needed json library and the spezific UDP header.<br/>
  Then you can create a json library object.<br/>

  ```
  #include <sys/socket.h>
  #include "udp.h"
  #include <json/single_include/nlohmann/json.hpp>

  using json = nlohmann::json;
  
  json j;
  ```
  
- On the client side, the json object can be filled with the specific data to send a request over UDP.<br/>

  ```
  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "request";
  j["service"] = "setupCall";
  j["status"] = "OK";
  j["param1"] = "r";
  j["param2"] = "2";
  j["param3"] = "0";
  
  size_t len = strlen((j.dump()).c_str())+1;
  
  udp_send((j.dump()).c_str(), len);
  ```
 
  **Note:** The out of use parameters should be filled up with 0.
  
- On the server side, the received UDP message can be handled and parsed.<br/>

  ```
  char buffer[1024];
  
  udp_receive(buffer);
  
  j = json::parse(buffer);
 
  string version = j.at("version").get<std::string>();
  string module = j.at("module").get<std::string>();
  string primitive = j.at("primitive").get<std::string>();
  string service = j.at("service").get<std::string>();
  string status = j.at("status").get<std::string>();
  string key = j.at("param1").get<std::string>();
  string handsetId = j.at("param2").get<std::string>();
  string param3 = j.at("param3").get<std::string>();
  ```
 
- On the server side, the json object can be filled with the specific data to send a confirmation over UDP.<br/>
  

  ```
  j["version"] = "1.0.0";
  j["module"] = "legacy";
  j["primitive"] = "confirmation";
  j["service"] = "setupCall";
  j["status"] = "OK";
  j["param1"] = std::to_string( static_cast<int>( ((openD_callApiCfm_t*) appMessage.param)->param.setup.pmid[0]) );
  j["param2"] = "0";
  j["param3"] = "0";
  
  size_t len = strlen((j.dump()).c_str())+1;
  
  udp_send((j.dump()).c_str(), len);
  ```

<a name="furtherinformation"/>

# Further Information

For more information about the DECT ULE technology, please also visit the ULE Alliance:

[ULE Alliance](https://www.ulealliance.org/)

or the DECT Forum:

[DECT Forum](https://www.dect.org/)

<a name="license"/>

# License

This project can be licensed under Apache 2.0 or GPLv2. This project contains 3rd party software that might apply other licenses, this is stated in the appropriate file header.

```
     ___ _____ _   ___ _  _____ ___  ___  ___ ___
    / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
    \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
    |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
    embedded.connectivity.solutions.==============
```

<a name="acknowledgments"/>

# Acknowledgments

This project uses the JSON implementation v3.4.0 of Nields Lohmann, please refer to https://github.com/nlohmann/json.

The project uses the HAN FUN implementation v1.5.3 of the ULE Alliance, please refer to https://github.com/ULE-Alliance/hanfun.

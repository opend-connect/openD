# Build system

This project uses the CMake build system for all of its targets.

# Targets

## Requirements

- CMake version >= v3.6
- Further information will be provided during development

## Information

Currently, the project contains a specification with header files and a documentation only. The framework is under development and will include a documentation
about the target build system and sample code implementations in the future.

# Documentation

## Requirements

- CMake version >= v3.6
- Doxygen version >= 1.8.13
- Make

## Information

This project utilizes Doxygen as tool for specification and documentation. To build the Doxygen documentation on a GNU/Linux system follow the instructions below.

* In your terminal go to the root directory of the project and create the build directory.

      $ cd openD
      $ mkdir build
      $ cd build

* In this build directory run CMake with the definition `BUILD_DOC=true`. This will enable the documentation generation. After this you can build the Doxygen documentation.

      $ cmake -DBUILD_DOC=true ..
      $ make doc

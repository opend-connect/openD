# HAN-FUN

This project aims at providing an implementation of the [ULE Alliance](http://www.ulealliance.org/) HAN-FUN application specification.

## Overview

A HAN-FUN network is composed by a concentrator (base) and one or more nodes, in a star configuration,
all the nodes connect to the concentrator that serves a router between all the nodes in the network.

A HAN-FUN device, either concentrator or node, is composed of one or more units. Each unit implements
a profile, i.e. a predefined configuration of interfaces and any number of optional interfaces.

HAN-FUN interfaces have two roles, _Client_ and _Server_ and define what attributes are present in each
role. They also define the commands supported between each role.

In each device there is a special unit, unit 0, that provides core infrastructure services, for
example, the __Device Management__ service, the __Device Information__ service and the
__Attribute Reporting__ service.

In order to access the HAN-FUN network, a node must first register it self with the base to obtain
it's HAN-FUN address, by using the commands available in the Device Management service.

This address will then be used to send/receive packets from the network.

## Project Setup

This project is implemented in C++ and depends only on the standard C++ library for usage, however
the unit tests and example applications depend on third-party libraries.

The build system used is [CMake](http://www.cmake.org/).

* Dependencies

  * gcc (>= 4.6)
  * cmake (>= 2.8.11)

* Building:

      $ mkdir build/
      $ cd build/
      $ cmake ..
      $ make
      $ make doc # Build the documentation

The Doxygen generated API documentation can be found [here](http://ULE-Alliance.github.io/hanfun).

The project will follow [this](http://nvie.com/posts/a-successful-git-branching-model/) convention for development.
The following helper [scripts](https://github.com/nvie/gitflow) are available.

The versions of the project follow the [SemVer 2.0.0](http://semver.org/) specification.

## Testing

Currently the build of the unit tests is only supported when compiling using the code from the repository.

To build the unit tests present in the source code, issue the following commands
(on the root of the project):

    $ git submodule init
    $ git submodule update
    $ mkdir build
    $ cd build
    $ CMake -DHAN-FUN_BUILD_TESTS=ON ..
    $ make

The unit tests will be run at the end of the compilation if not cross-compiling.

To re-run the tests, issue:

    $ make check

## Examples

The folder _apps/_ contains two example applications, one for the concentrator (base) side and one
for the node side.

The _apps/example_XX.cpp_ files contain standalone applications that demo API usage.
Use __make example_XX__ to build each application or __make examples__ to build all of them.

The applications communicate over TCP/IP.
The support for this transport layer is based on the [libuv](https://github.com/joyent/libuv).
This is downloaded and build automatically when building the example applications is requested.

To build the example applications, issue the following commands (on the root of the project):

    $ mkdir build
    $ cd build
    $ cmake -DHF_BUILD_APPS=ON ..
    $ make

This will build the example applications for the base (_build/apps/base_) and for
the node (_build/apps/node_).

The *base* application demonstrates the registration of nodes in a HAN-FUN network and the binding
of nodes that have complementary interfaces.

The *node* application demonstrates, a simple switch or a simple light application.

For example to register a _simple switch_ and _simple light_ to the _base_ and bind the _switch_ to
the _light_ so that when the _switch toggles_ it toggles the _light_.

 * Open three terminals and start the applications;

       $ apps/base    (Base)
       $ apps/node 1  (Simple Switch)
       $ apps/node 2  (Simple Light)

 * Change the first node application to a simple switch;

       > ss

 * Change the second node application to a simple light;

       > sl

 * Start registration on the base and register the simple switch;

       > r 1 1 (on the base terminal)
       > r (on the switch terminal)
       > a (check device address, it should be 1)

 * Start registration on the base and register the simple light;

       > r 1 2 (on the base terminal)
       > r (on the light terminal)
       > a (check device address, it should be 2)

 * Bind the _switch_ to the _light_;

       > b 1 2 (on the base terminal)

 * Send a toggle command from the _switch_ to the _light_ :

       > toggle (on the switch terminal)

The last command should make the node application configured as a _light_ print that a
toggle command was received.

Please see the help in the applications for further features.

## Contributing

 1. Fork it!
 2. Create your feature branch: `git checkout -b my-new-feature`
 3. Commit your changes: `git commit -am 'Add some feature'`
 4. Push to the branch: `git push origin my-new-feature`
 5. Submit a pull request (PR).

## Author

 * Initial development by [Bithium S.A.](http://www.bithium.com)

## License

This library is released under dual-license, [GPLv2](http://www.gnu.org/licenses/gpl-2.0.html) and
[Apache 2.0](http://www.apache.org/licenses/LICENSE-2.0.txt).

Please see the file 'LICENSE' in the root folder for further information.


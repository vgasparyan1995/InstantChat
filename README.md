# InstantChat

Build steps:
```
cd test/googletest
mkdir build
cd build
cmake ..
make # at this point gtest libraries are created
cd ../../../
mkdir build
cd build
cmake ..
make
# at this point 3 executables are created:
# - client
# - server
# - chat_test (in test directory)
# Note that you can make each of them individually.
```
Dependencies:
- ncurses - Needs developer package installed. In CentOS/RHEL/Fedor 'ncurses-devel', in Debian/Ubuntu 'libncurses5-dev'.
- asio - This is a header-only library so nothing needed for it.

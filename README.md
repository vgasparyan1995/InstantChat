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


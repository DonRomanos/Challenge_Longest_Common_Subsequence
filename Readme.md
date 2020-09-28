[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

# Find Length of the Longest Common Subsequence of two Strings

This is a well known Problem from Dynamic Programming.

Given two strings, for example "AXYUIZ" and "CXYO" find the length of the largest common subsequence of both strings, e.g. in the example it is "XY" with a length of 2.

In order to practice this I recommend you to use a Test-Driven-Developement Approach, therefore no Tests are provided by default.

One you are sure you solved the Problems, enable the following CMake Option `BUILD_REFERENCE` which will build tests and a benchmark where you can verify your solution and compare against mine.

## Setup

Requirements:

* CMake
* Conan
* Python (for Conan)

Installing the Libraries using Conan (I recommend using a [conan profile](https://docs.conan.io/en/latest/reference/profiles.html) to specify your settings, e.g. run conan install .. -p gcc-9 ...)

```shell
mkdir build && cd build
conan install .. --build missing
conan build ..
```

Now you can start writing your tests in implementation_tests.hpp

### Disabling some of the Dependencies

If you don't have the dependencies or dont want to build with them for some reason you can disable them with these CMake Options, simply set them to 'OFF'.

```cmake
BUILD_REFERENCE
BUILD_BENCHMARK
```

### Alternative without Conan

Requirements:

* CMake

You can build the library without Conan if you manually install the gtest and google benchmark libraries.

Just tell Cmake where to find them by setting following CMake Variables

```cmake
gtest_DIR
benchmark_ROOT_DIR
```

Alternatively you can set the `CMAKE_MODULE_PATH` to the location where your `Findgtest.cmake` and `Findbenchmark.cmake` files are, if you have them.

Then you can use a command line like this

```cmake
cmake .. -G "Unix Makefiles" -D CMAKE_C_COMPILER=gcc-9 -D CMAKE_CXX_COMPILER=g++-9 -DCMAKE_BUILD_TYPE=DEBUG -D CMAKE_MODULE_PATH=$PWD
```

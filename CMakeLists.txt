cmake_minimum_required(VERSION 3.13)

project(longest_common_sequence)

option(BUILD_REFERENCE "Will build a reference implementation as a library, 
                        which will also be tested and benchmarked. Enable once you have your solution." OFF)
option(BUILD_BENCHMARK "This will enable the performance tests using google benchmark" ON)

add_library(${PROJECT_NAME} INTERFACE)
add_library(Challenge::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_sources(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/implementation.hpp
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_compile_options(${PROJECT_NAME} INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Werror -pedantic-errors -Wextra -Wconversion -Wsign-conversion -Wno-gnu-zero-variadic-macro-arguments>
    $<$<CXX_COMPILER_ID:MSVC>:
        /WX /W4>
)

######################################################################
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

find_package(gtest REQUIRED)

add_executable(${PROJECT_NAME}_Tests)

target_sources(${PROJECT_NAME}_Tests PRIVATE 
    src/implementation_tests.cpp
)

target_link_libraries(${PROJECT_NAME}_Tests PRIVATE
    Challenge::${PROJECT_NAME}
    gtest::gtest
    $<$<TARGET_EXISTS:Challenge::${PROJECT_NAME}_Reference>:Challenge::${PROJECT_NAME}_Reference>)

target_compile_options(${PROJECT_NAME}_Tests PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Wno-gnu-zero-variadic-macro-arguments>
)

include(GoogleTest)
enable_testing()
gtest_discover_tests(${PROJECT_NAME}_Tests)

######################################################################
if(BUILD_REFERENCE)
    target_sources(${PROJECT_NAME}_Tests PRIVATE 
    src/reference/tests.cpp
)    
endif()

######################################################################
if( BUILD_BENCHMARK AND BUILD_REFERENCE)
    find_package(benchmark REQUIRED)
    # Requires PThreads on Linux
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)

    add_executable(${PROJECT_NAME}_Benchmark)

    target_sources(${PROJECT_NAME}_Benchmark PRIVATE 
        src/reference/benchmark.cpp)

    target_link_libraries(${PROJECT_NAME}_Benchmark PRIVATE
        Challenge::${PROJECT_NAME}
        benchmark::benchmark
        Threads::Threads
        $<$<TARGET_EXISTS:Challenge::${PROJECT_NAME}_Reference>:Challenge::${PROJECT_NAME}_Reference>)

    add_custom_target(NAME ${PROJECT_NAME}_Benchmark
        COMMAND ${PROJECT_NAME}_Benchmark
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

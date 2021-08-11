project(fouing CXX)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/conan.cmake)

conan_cmake_run(REQUIRES boost/1.76.0
        gtest/1.11.0
        spdlog/1.8.5
        tl-expected/1.0.0
        BUILD missing
        BASIC_SETUP CMAKE_TARGETS)

option(UNIT_TEST "activate unit testing" ON)

add_subdirectory(fouine)

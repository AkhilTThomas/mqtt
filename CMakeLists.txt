cmake_minimum_required(VERSION 3.10)
project(mqtt-cpp)

set(CONAN_BUILD_INFO_FILE conanbuildinfo.cmake)

include(${CONAN_BUILD_INFO_FILE})
conan_basic_setup(TARGETS)

add_subdirectory(src)
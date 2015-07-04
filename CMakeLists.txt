cmake_minimum_required(VERSION 3.2)
project(mathproject)

# Boost libraries
find_package(Boost REQUIRED)

# Gtkmm
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

# Flex/Bison
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(MP_INTERPRETER_SOURCE_FILES interpreter/main.cpp)
add_executable(interpreter ${MP_INTERPRETER_SOURCE_FILES})
cmake_minimum_required(VERSION 3.2)
project(mathproject)

# Boost libraries
find_package(Boost REQUIRED)

# Gtkmm
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES main.cpp)
add_executable(mathproject ${SOURCE_FILES})
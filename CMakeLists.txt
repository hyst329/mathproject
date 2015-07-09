cmake_minimum_required(VERSION 3.2)
project(mathproject)

# Boost libraries
# find_package(Boost REQUIRED)

# Gtkmm
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

# Flex/Bison
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(MPParser interpreter/grammar/mp.y ${PROJECT_SOURCE_DIR}/interpreter/grammar/mpparser.cpp)
FLEX_TARGET(MPScanner interpreter/grammar/mp.l ${PROJECT_SOURCE_DIR}/interpreter/grammar/mplexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(MPScanner MPParser)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(MP_KERNEL_SOURCE_FILES kernel/placeholder.cpp kernel/Type.cpp kernel/Type.h kernel/Matrix.cpp kernel/Matrix.h
    kernel/Function.cpp kernel/Function.h kernel/AST.cpp kernel/AST.h)
add_library(kernel STATIC ${MP_KERNEL_SOURCE_FILES})

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

set(MP_INTERPRETER_SOURCE_FILES interpreter/main.cpp)
add_executable(interpreter ${MP_INTERPRETER_SOURCE_FILES} ${BISON_MPParser_OUTPUTS} ${FLEX_MPScanner_OUTPUTS})
add_dependencies(interpreter kernel)

set(MP_IDE_SOURCE_FILES ide/main.cpp)
add_executable(ide MP_IDE_SOURCE_FILES)
target_link_libraries(ide ${GTKMM_LIBRARIES})


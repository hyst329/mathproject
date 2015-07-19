cmake_minimum_required(VERSION 3.2)
project(mathproject)

# Boost libraries
find_package(Boost 1.58 COMPONENTS program_options REQUIRED)

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
    kernel/UserFunction.cpp kernel/UserFunction.h kernel/AST.cpp kernel/AST.h)
add_library(kernel STATIC ${MP_KERNEL_SOURCE_FILES} kernel/Array.cpp kernel/Array.h kernel/Error.cpp kernel/Error.h kernel/BuiltinFunctions.h kernel/BuiltinFunctions.cpp kernel/NullType.cpp kernel/NullType.h)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

set(MP_INTERPRETER_SOURCE_FILES interpreter/main.cpp)
add_executable(interpreter ${MP_INTERPRETER_SOURCE_FILES} ${BISON_MPParser_OUTPUTS} ${FLEX_MPScanner_OUTPUTS})
add_dependencies(interpreter kernel)
target_link_libraries(interpreter kernel ${Boost_LIBRARIES})

set(MP_IDE_SOURCE_FILES ide/main.cpp)
add_executable(ide ${MP_IDE_SOURCE_FILES})
target_link_libraries(ide ${GTKMM_LIBRARIES})

add_custom_command(TARGET ide POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/ide/userInterface.glade
                   ${PROJECT_BINARY_DIR}/userInterface.glade)
#file(COPY ide/userInterface.glade DESTINATION ${PROJECT_BINARY_DIR})
add_custom_command(TARGET interpreter POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/library/library.txt
                   ${PROJECT_BINARY_DIR}/library/library.txt)
#file(COPY library/library.txt DESTINATION ${PROJECT_BINARY_DIR}/library)

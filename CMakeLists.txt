cmake_minimum_required (VERSION 2.8)

add_definitions('-g')
add_definitions('-Wall')
add_definitions('-std=c++11')
add_definitions('-fno-rtti')

find_package(LLVM REQUIRED CONFIG)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

add_subdirectory(FunctionArgumentInstantiation)


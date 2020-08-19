cmake_minimum_required(VERSION 3.4.3)

find_package(LLVM REQUIRED CONFIG)
project(ByePass)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

SET(CMAKE_CXX_FLAGS "-Wall -fno-rtti")

add_library( LLVMBye MODULE
	Bye.cpp
)
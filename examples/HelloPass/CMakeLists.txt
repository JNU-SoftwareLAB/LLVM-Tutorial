cmake_minimum_required(VERSION 3.4.3)

find_package(LLVM REQUIRED CONFIG)
project(HelloPass)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

SET(CMAKE_CXX_FLAGS "-Wall -fno-rtti")

add_library( LLVMHello MODULE
	Hello.cpp	
)
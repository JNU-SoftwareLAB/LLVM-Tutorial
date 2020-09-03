cmake_minimum_required(VERSION 3.4.3)

SET(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)
project(PointerCheck)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${LLVM_INCLUDE_DIRS}")
add_definitions(${LLVM_DEFINITIONS})

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS ${PROJECT_SOURCE_DIR} \tINCLUDE PATH)
message(STATUS ${CMAKE_CURRENT_BINARY_DIR} \tlibDir PATH)


SET(CMAKE_CXX_FLAGS "-Wall -fno-rtti -O0")

add_executable(testCase test.cpp Analysis.cpp)

add_library(LLVMPointerCheck MODULE
	PointerAnalysis.cpp
	Analysis.cpp
)
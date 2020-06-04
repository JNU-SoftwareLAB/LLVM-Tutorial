cmake_minimum_required(VERSION 3.4.3)

find_package(LLVM REQUIRED CONFIG)
project(HelloWorld)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

set(LLVM_LINK_COMPONENTS
  Core # maybe over version 10, this is LLVMCore
  BitWriter
  Support
  )

add_llvm_executable(Hello
  HelloWorld.cpp
  )

# add_compile_options(Hello
# 					public
# 					-fno-rtti)

# message("${CMAKE_CXX_FLAGS}")

# get_target_property(MAIN_CFLAGS Hello COMPILE_FLAGS)
# message("-- Target Compiler flags are: ${MAIN_CFLAGS}")

set_target_properties(Hello PROPERTIES COMPILE_FLAGS "")
get_target_property(MAIN_CFLAGS Hello COMPILE_FLAGS)
message("-- Target Compiler flags are: ${MAIN_CFLAGS}")
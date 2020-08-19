  cmake_minimum_required(VERSION 3.4.3)

  find_package(LLVM REQUIRED CONFIG)
  project(JIT)
  
  message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
  message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
  
  include_directories(${LLVM_INCLUDE_DIRS})
  add_definitions(${LLVM_DEFINITIONS})
  list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
  include(AddLLVM)
  
  set(LLVM_LINK_COMPONENTS
    Core
    OrcJIT
    Support
    nativecodegen
	)
  
  add_llvm_executable(JIT
  	HowToUseJIT.cpp
	)

	set_target_properties(JIT PROPERTIES COMPILE_FLAGS "")
	list(APPEND COMPILE_FLAGS "-O1")
	# message(INFO "${COMPILE_FLAGS}")
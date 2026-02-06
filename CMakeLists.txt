cmake_minimum_required(VERSION 3.30)
project(ance)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(VCPKG_TARGET_TRIPLET x64-windows)

find_package(antlr4-generator CONFIG REQUIRED)
find_package(antlr4-runtime CONFIG REQUIRED)
message(STATUS "Found antlr4 includes at: ${ANTLR4_INCLUDE_DIR}")
find_library(ANTLR4_LIB antlr4-runtime)
message(STATUS "Found antlr4 lib at: ${ANTLR4_LIB}")
include_directories(SYSTEM ${ANTLR4_INCLUDE_DIR})

find_package(LLVM CONFIG REQUIRED)
message(STATUS "Found llvm package ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

find_package(LLD CONFIG REQUIRED)
message(STATUS "Found LLDConfig.cmake in ${LLD_CMAKE_DIR}")
include_directories(SYSTEM ${LLD_INCLUDE_DIRS})

find_package(Boost REQUIRED COMPONENTS locale regex)
message(STATUS "Found boost includes at: ${Boost_INCLUDE_DIRS}")

find_package(ICU REQUIRED COMPONENTS data i18n io tu uc)

include_directories(src)
add_subdirectory(src)
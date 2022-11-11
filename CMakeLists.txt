cmake_minimum_required(VERSION 3.22)
project(ance)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_GENERATOR_PLATFORM x64)

include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)

set(VCPKG_TARGET_TRIPLET x64-windows)
set(CMAKE_TOOLCHAIN_FILE C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_path(ANTLR4_INCLUDE_DIR antlr4-runtime.h HINTS C:/dev/vcpkg/installed/x64-windows/include/antlr4-runtime/)
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

include_directories(src)
add_subdirectory(src)
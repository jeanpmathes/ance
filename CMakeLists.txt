cmake_minimum_required(VERSION 3.30)
project(ance LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(VCPKG_TARGET_TRIPLET x64-windows)

find_package(antlr4-generator CONFIG REQUIRED)
find_package(antlr4-runtime CONFIG REQUIRED)
message(STATUS "Found ANTLR4 (${ANTLR4_INCLUDE_DIR})")

find_package(LLVM CONFIG REQUIRED)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

find_package(LLD CONFIG REQUIRED)
message(STATUS "Found LLD (via LLVM ${LLVM_PACKAGE_VERSION})")

find_package(Boost REQUIRED COMPONENTS locale regex)
message(STATUS "Found Boost ${Boost_VERSION}")

find_package(ICU REQUIRED COMPONENTS data i18n io tu uc)
message(STATUS "Found ICU ${ICU_VERSION}")

add_subdirectory(src)

cmake_minimum_required(VERSION 3.30)
project(ance
        VERSION 0.1.0
        DESCRIPTION "A compiler for the ance programming language"
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

add_library(ance_build_options INTERFACE)
add_library(ance::build_options ALIAS ance_build_options)

target_compile_features(ance_build_options INTERFACE cxx_std_23)
target_compile_options(ance_build_options INTERFACE /EHsc)

set(VCPKG_TARGET_TRIPLET x64-windows)

set(ignored "${CMAKE_TOOLCHAIN_FILE} ${CMAKE_C_COMPILER}")

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

if (BUILD_TESTING)
    find_package(Catch2 3 CONFIG REQUIRED)
    message(STATUS "Found Catch2 ${Catch2_VERSION}")
endif ()

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(tst)
endif ()

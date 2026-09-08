add_library(ance_compiler STATIC)
add_library(ance::compiler ALIAS ance_compiler)

add_executable(ance main.cpp)

add_subdirectory(ance)
add_subdirectory(grammar)

configure_file(
        "${PROJECT_SOURCE_DIR}/src/ance/Version.h.in"
        "${PROJECT_BINARY_DIR}/src/ance/Version.h"
)
include_directories(${PROJECT_BINARY_DIR}/src)

set_target_properties(ance_compiler PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

set(ERROR_OPTIONS -Werror -Wall -Wextra
        -Wno-c++98-compat-pedantic
        -Wno-exit-time-destructors
        -Wno-unsafe-buffer-usage
        -Wno-padded
        -Wno-ctad-maybe-unsupported
        -Wno-switch-enum
        -Wno-switch-default)

target_compile_options(ance_compiler PRIVATE
        -Wno-reserved-macro-identifier
        -Wno-unused-macros
        ${ERROR_OPTIONS})

foreach(file IN LISTS ANCE_ANTLR_GENERATED_FILES)
    if(file MATCHES "\\.cpp$")
        set_source_files_properties(${file}
                PROPERTIES
                COMPILE_FLAGS "-Wno-everything"
        )
    endif()
endforeach()

target_include_directories(ance_compiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ance_compiler SYSTEM PRIVATE
        ${ANTLR4_INCLUDE_DIR}
        ${LLVM_INCLUDE_DIRS}
        ${LLD_INCLUDE_DIRS})

target_compile_definitions(ance_compiler PRIVATE ${LLVM_DEFINITIONS})

set(LLD_AVAILABLE_LIBS lldCommon lldCOFF lldELF lldMachO lldMinGW lldWasm)

target_link_libraries(ance_compiler
        PUBLIC ance::build_options
        PRIVATE
        antlr4_shared
        ${LLVM_AVAILABLE_LIBS}
        ${LLD_AVAILABLE_LIBS}
        Boost::boost Boost::locale Boost::regex
        ICU ICU::data ICU::i18n ICU::io ICU::tu ICU::uc)

target_link_libraries(ance PRIVATE ance::compiler ance::build_options)

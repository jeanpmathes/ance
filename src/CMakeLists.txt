add_executable(ance)

add_subdirectory(ance)
add_subdirectory(grammar)

target_sources(ance PRIVATE main.cpp)

configure_file(
        "${PROJECT_SOURCE_DIR}/src/ance/Version.h.in"
        "${PROJECT_BINARY_DIR}/src/ance/Version.h"
)
include_directories(${PROJECT_BINARY_DIR}/src)

target_compile_features(ance PRIVATE cxx_std_23)
set_target_properties(ance PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

set(ERROR_OPTIONS
    -Werror -Weverything
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-c++98-c++11-compat-pedantic
    -Wno-exit-time-destructors
    -Wno-global-constructors
    -Wno-unsafe-buffer-usage
    -Wno-ctad-maybe-unsupported
    -Wno-switch-default
    -Wno-switch-enum
    -Wno-padded)

target_compile_options(ance PRIVATE
        /EHsc
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

target_include_directories(ance PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ance SYSTEM PRIVATE
        ${ANTLR4_INCLUDE_DIR}
        ${LLVM_INCLUDE_DIRS}
        ${LLD_INCLUDE_DIRS})

target_compile_definitions(ance PRIVATE ${LLVM_DEFINITIONS})

set(LLD_AVAILABLE_LIBS lldCommon lldCOFF lldELF lldMachO lldMinGW lldWasm)

target_link_libraries(ance PRIVATE
        antlr4_shared
        ${LLVM_AVAILABLE_LIBS}
        ${LLD_AVAILABLE_LIBS}
        Boost::boost Boost::locale Boost::regex
        ICU ICU::data ICU::i18n ICU::io ICU::tu ICU::uc)

add_executable(ance)

add_subdirectory(ance)
add_subdirectory(grammar)

target_sources(ance PRIVATE main.cpp CoreDefinitions.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reserved-macro-identifier -Wno-unused-macros")

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

target_compile_options(ance PRIVATE /EHsc -MDd ${ERROR_OPTIONS})

foreach(file IN LISTS ANCE_ANTLR_GENERATED_FILES)
    if(file MATCHES "\\.cpp$")
        set_source_files_properties(${file}
                PROPERTIES
                COMPILE_FLAGS "-Wno-everything"
        )
    endif()
endforeach()

target_include_directories(ance PUBLIC .)

set(LLD_AVAILABLE_LIBS lldCommon lldCOFF lldELF lldMachO lldMinGW lldWasm)

add_dependencies(ance antlr4_shared)
target_link_libraries(ance PRIVATE antlr4_shared)

target_link_libraries(ance PRIVATE ${LLVM_AVAILABLE_LIBS} ${LLD_AVAILABLE_LIBS})
target_link_libraries(ance PRIVATE Boost::boost Boost::locale Boost::regex)
target_link_libraries(ance PRIVATE ICU ICU::data ICU::i18n ICU::io ICU::tu ICU::uc)

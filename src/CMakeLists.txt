add_executable(ance main.cpp)

add_subdirectory(lang)
add_subdirectory(compiler)
add_subdirectory(grammar)
add_subdirectory(validation)

target_include_directories(ance PUBLIC .)
target_include_directories(ance SYSTEM PRIVATE grammar)

set(LLD_AVAILABLE_LIBS lldCommon lldCOFF lldELF lldMachO lldMinGW lldWasm)

target_link_libraries(ance PRIVATE ${ANTLR4_LIB})
target_link_libraries(ance PRIVATE ${LLVM_AVAILABLE_LIBS} ${LLD_AVAILABLE_LIBS})
target_link_libraries(ance PRIVATE Boost::boost Boost::locale Boost::regex)
target_link_libraries(ance PRIVATE ICU ICU::data ICU::i18n ICU::io ICU::tu ICU::uc)

set(ERROR_OPTIONS
    -Werror -Weverything
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-c++98-c++11-compat-pedantic
    -Wno-exit-time-destructors
    -Wno-global-constructors
    -Wno-switch-enum)

target_compile_options(ance PRIVATE /EHa -MDd ${ERROR_OPTIONS})

set_source_files_properties(grammar/anceBaseVisitor.cpp
                            grammar/anceLexer.cpp
                            grammar/anceParser.cpp
                            grammar/anceVisitor.cpp
                            PROPERTIES
                            COMPILE_FLAGS -Wno-everything)

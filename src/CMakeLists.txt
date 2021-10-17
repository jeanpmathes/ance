add_executable(ance main.cpp)

add_subdirectory(ance)
add_subdirectory(compiler)
add_subdirectory(grammar)
add_subdirectory(management)
add_subdirectory(validation)

include_directories(.)

set(LLD_AVAILABLE_LIBS lldCOFF;lldCommon;lldCore;lldDriver;lldELF;lldMachO;lldMachO2;lldMinGW;lldReaderWriter;lldWasm;lldYAML)
target_link_libraries(ance PRIVATE ${ANTLR4_LIB} ${LLVM_AVAILABLE_LIBS} ${LLD_AVAILABLE_LIBS})

target_compile_options(ance PRIVATE /EHa /W4 -Wdocumentation -MDd)
set_source_files_properties(grammar/anceBaseVisitor.cpp
                            grammar/anceLexer.cpp
                            grammar/anceParser.cpp
                            grammar/anceVisitor.cpp
                            PROPERTIES COMPILE_FLAGS /W0)
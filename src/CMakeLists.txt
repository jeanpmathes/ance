add_executable(ance)

add_subdirectory(grammar)
add_subdirectory(ance)

target_sources(ance PRIVATE main.cxx)

target_include_directories(ance PUBLIC .)
target_include_directories(ance SYSTEM PRIVATE grammar)

set(LLD_AVAILABLE_LIBS lldCommon lldCOFF lldELF lldMachO lldMinGW lldWasm)

target_link_libraries(ance PRIVATE ${ANTLR4_LIB})
target_link_libraries(ance PRIVATE ${LLVM_AVAILABLE_LIBS} ${LLD_AVAILABLE_LIBS})
target_link_libraries(ance PRIVATE Boost::boost Boost::locale Boost::regex)
target_link_libraries(ance PRIVATE ICU ICU::data ICU::i18n ICU::io ICU::tu ICU::uc)

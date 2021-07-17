include_directories(grammar)
include_directories(elements)

add_subdirectory(grammar)
add_subdirectory(elements)

target_sources(ance PRIVATE File.cpp
               DataVisitor.cpp)
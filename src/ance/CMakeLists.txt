include_directories(.)

include_directories(construct)
include_directories(expression)
include_directories(scope)
include_directories(statement)
include_directories(type)

add_subdirectory(construct)
add_subdirectory(expression)
add_subdirectory(scope)
add_subdirectory(statement)
add_subdirectory(type)

target_sources(ance PRIVATE AccessModifier.cpp)
include_directories(.)

include_directories(assignable)
include_directories(construct)
include_directories(expression)
include_directories(scope)
include_directories(statement)
include_directories(type)
include_directories(utility)

add_subdirectory(assignable)
add_subdirectory(construct)
add_subdirectory(expression)
add_subdirectory(scope)
add_subdirectory(statement)
add_subdirectory(type)
add_subdirectory(utility)

target_sources(ance PRIVATE AccessModifier.cpp
               InternalStorage.cpp)
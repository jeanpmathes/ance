include_directories(.)

include_directories(constant)
include_directories(value)

add_subdirectory(constant)
add_subdirectory(value)

target_sources(ance PRIVATE
               Function.cpp
               GlobalVariable.cpp
               LocalVariable.cpp
               Parameter.cpp
               Variable.cpp)
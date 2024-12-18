add_subdirectory(construct)
add_subdirectory(expression)
add_subdirectory(scope)
add_subdirectory(statement)
add_subdirectory(type)
add_subdirectory(utility)

target_sources(ance PRIVATE AccessModifier.cpp
               Accessibility.cpp
               Assigner.cpp
               CMP.cpp
               BinaryOperator.cpp
               Located.cpp
               UnaryOperator.cpp
               Context.cpp)

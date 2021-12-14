add_subdirectory(constant)
add_subdirectory(value)

target_sources(ance PRIVATE
               Function.cpp
               CustomFunction.cpp
               ExternFunction.cpp
               GlobalVariable.cpp
               LocalVariable.cpp
               Parameter.cpp
               Variable.cpp
               VariableDefinition.cpp
               FunctionDefinition.cpp
               FunctionGroup.cpp)
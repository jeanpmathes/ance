add_subdirectory(constant)
add_subdirectory(value)

target_sources(ance PRIVATE
               BasicBlock.cpp
               BasicBlockDefinitionSimple.cpp
               BasicBlockDefinitionEmpty.cpp
               Function.cpp
               CustomFunction.cpp
               ExternFunction.cpp
               GlobalVariable.cpp
               LocalVariable.cpp
               Parameter.cpp
               Variable.cpp
               VariableDefinition.cpp
               FunctionDefinition.cpp
               FunctionGroup.cpp
               Signature.cpp)
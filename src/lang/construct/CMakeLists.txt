add_subdirectory(descriptions)
add_subdirectory(constant)

target_sources(ance PRIVATE
               Value.cpp
               Constant.cpp
               Entity.cpp
               BasicBlock.cpp
               BasicBlockDefinitionSimple.cpp
               BasicBlockDefinitionFinalizing.cpp
               BasicBlockDefinitionEmpty.cpp
               BasicBlockDefinitionReturning.cpp
               BasicBlockDefinitionBranching.cpp
               BasicBlockDefinitionMatching.cpp
               RuntimeFunction.cpp
               Function.cpp
               CustomFunction.cpp
               SpecialMemberFunction.cpp
               ImportedFunction.cpp
               PredefinedFunction.cpp
               StatementFunction.cpp
               InitializerFunction.cpp
               GlobalVariable.cpp
               LocalVariable.cpp
               Parameter.cpp
               Variable.cpp
               VariableDefinition.cpp
               FunctionDefinition.cpp
               FunctionGroup.cpp
               Callable.cpp
               Signature.cpp
               Member.cpp
               CodeBlock.cpp)

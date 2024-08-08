add_subdirectory(native)
add_subdirectory(cmp)

target_sources(ance PRIVATE AnceCompiler.cpp
               AnceLinker.cpp
               Application.cpp
               Builder.cpp
               SourceTree.cpp
               TargetDescriptor.cpp
               FileContext.cpp
               Packages.cpp
               Runtime.cpp
               SourceVisitor.cpp
               ControlFlowGraphPrinter.cpp
               UnitResult.cpp
               Project.cpp
               Execution.cpp
               Unit.cpp
               ProjectDescription.cpp
               OptLevel.cpp
               CodePrinter.cpp)

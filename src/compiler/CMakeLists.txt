include_directories(.)

target_sources(ance PRIVATE AnceCompiler.cpp
               AnceLinker.cpp
               Application.cpp
               CompileState.cpp
               Runtime.cpp
               Visitor.cpp)
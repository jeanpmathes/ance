include_directories(.)

target_sources(ance PRIVATE AnceCompiler.cpp
               Application.cpp
               CompileState.cpp
               Runtime.cpp
               Visitor.cpp)
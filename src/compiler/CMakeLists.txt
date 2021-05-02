include_directories(.)

target_sources(ance PRIVATE anceCompiler.cpp
               Application.cpp
               CompileState.cpp
               Runtime.cpp
               Visitor.cpp)
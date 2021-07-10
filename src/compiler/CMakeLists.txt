include_directories(.)

target_sources(ance PRIVATE AnceCompiler.cpp
               AnceLinker.cpp
               Application.cpp
               CompileContext.cpp
               Runtime.cpp
               Visitor.cpp)
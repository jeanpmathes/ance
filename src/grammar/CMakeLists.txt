add_compile_options(/EHsc /MDd /w)

target_sources(ance PRIVATE anceBaseVisitor.cpp
                            anceLexer.cpp
                            anceParser.cpp
                            anceVisitor.cpp)
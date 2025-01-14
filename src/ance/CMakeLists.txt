add_compile_options(/EHsc /MDd /WX /W4)

target_sources(ance PRIVATE
               FILE_SET ast TYPE CXX_MODULES
               BASE_DIRS
               ${CMAKE_CURRENT_SOURCE_DIR}/ast
               FILES
               ast/ast.ixx)

target_sources(ance PRIVATE
               FILE_SET utility TYPE CXX_MODULES
               BASE_DIRS
               ${CMAKE_CURRENT_SOURCE_DIR}/utility
               FILES
               utility/utility.ixx)

target_sources(ance PRIVATE
               FILE_SET runner TYPE CXX_MODULES
               BASE_DIRS
               ${CMAKE_CURRENT_SOURCE_DIR}/runner
               FILES
               runner/runner.ixx)
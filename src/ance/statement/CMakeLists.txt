include_directories(.)

target_sources(ance PRIVATE AssignmentStatement.cpp
               LocalVariableDefinition.cpp
               DeleteStatement.cpp
               ReturnStatement.cpp
               ExpressionStatement.cpp
               Statement.cpp)
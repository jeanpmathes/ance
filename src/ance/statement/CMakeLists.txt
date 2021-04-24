include_directories(.)

target_sources(ance PRIVATE AssignmentStatement.cpp
        LocalVariableDefinition.cpp
        PrintStatement.cpp
        ReturnStatement.cpp
        ExpressionStatement.cpp
        Statement.cpp)
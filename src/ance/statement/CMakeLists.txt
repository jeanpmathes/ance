include_directories(.)

target_sources(ance PRIVATE assignment_statement.cpp
                            local_variable_definition.cpp
                            print_statement.cpp
                            return_statement.cpp
                            expression_statement.cpp
                            Statement.cpp)
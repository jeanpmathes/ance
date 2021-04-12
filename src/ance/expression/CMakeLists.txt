include_directories(.)

target_sources(ance PRIVATE default_value_expression.cpp
                            Expression.cpp
                            BuildableExpression.cpp
                            BuildableConstantExpression.cpp
                            floating_point_expression.cpp
                            function_call.cpp
                            integer_expression.cpp
                            literal_expression.cpp
                            sizeof_expression.cpp
                            sizeof_type.cpp
                            variable_expression.cpp)
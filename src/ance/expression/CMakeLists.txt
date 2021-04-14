include_directories(.)

target_sources(ance PRIVATE default_value_expression.cpp
                            Expression.cpp
                            ConstantExpression.cpp
                            BuildableExpression.cpp
                            BuildableConstantExpression.cpp
                            function_call.cpp
                            constantliteral_expression.cpp
                            sizeof_expression.cpp
                            sizeof_type.cpp
                            variable_expression.cpp)
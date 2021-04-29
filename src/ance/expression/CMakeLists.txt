include_directories(.)

target_sources(ance PRIVATE DefaultValueExpression.cpp
               Expression.cpp
               ConstantExpression.cpp
               BuildableExpression.cpp
               BuildableConstantExpression.cpp
               FunctionCall.cpp
               ConstantLiteralExpression.cpp
               SizeofExprExpression.cpp
               SizeofTypeExpression.cpp
               VariableExpression.cpp)
include_directories(.)

target_sources(ance PRIVATE DefaultValueExpression.cpp
               Expression.cpp
               ConstantExpression.cpp
               BuildableExpression.cpp
               BuildableConstantExpression.cpp
               FunctionCall.cpp
               ConstantLiteral.cpp
               SizeofExpression.cpp
               SizeofType.cpp
               VariableAccess.cpp
               RoughCast.cpp
               Allocation.cpp)
include_directories(.)

target_sources(ance PRIVATE Constant.cpp
                            ExpressionValue.cpp
                            Function.cpp
                            GlobalVariable.cpp
                            LocalVariable.cpp
                            Parameter.cpp
                            Value.cpp
                            ValueWrapper.cpp
                            Variable.cpp)
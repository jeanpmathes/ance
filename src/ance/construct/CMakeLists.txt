include_directories(.)

target_sources(ance PRIVATE Constant.cpp
                            ExpressionBackedValue.cpp
                            ExpressionBackedConstant.cpp
                            Function.cpp
                            GlobalVariable.cpp
                            LocalVariable.cpp
                            Parameter.cpp
                            Value.cpp
                            WrappedNativeValue.cpp
                            WrappedNativeConstant.cpp
                            Variable.cpp)
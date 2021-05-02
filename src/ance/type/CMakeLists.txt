include_directories(.)

target_sources(ance PRIVATE
               ArrayType.cpp
               DoubleType.cpp
               HalfType.cpp
               IntegerType.cpp
               QuadType.cpp
               SingleType.cpp
               SizeType.cpp
               UnsignedIntegerPointerType.cpp
               Type.cpp
               VoidType.cpp
               PointerType.cpp
               FloatingPointType.cpp)
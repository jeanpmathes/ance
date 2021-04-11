set(PROJECT_NAME ance)

################################################################################
# Source groups
################################################################################
set(Grammar_Files
    "ance.g4"
)
source_group("Grammar Files" FILES ${Grammar_Files})

set(Header_Files
    "AccessModifier.h"
    "anceCompiler.h"
    "anceConstants.h"
    "Application.h"
    "CompileState.h"
    "ConstantExpression.h"
    "Expression.h"
    "Statement.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Header_Files__Construct_Files
    "Constant.h"
    "Function.h"
    "GlobalVariable.h"
    "Scope.h"
    "Value.h"
)
source_group("Header Files\\Construct Files" FILES ${Header_Files__Construct_Files})

set(Header_Files__Expression_Files
    "default_value_expression.h"
    "function_call.h"
    "integer_expression.h"
    "literal_expression.h"
    "variable_expression.h"
)
source_group("Header Files\\Expression Files" FILES ${Header_Files__Expression_Files})

set(Header_Files__Generated_Files
    "anceBaseVisitor.h"
    "anceLexer.h"
    "anceParser.h"
    "anceVisitor.h"
)
source_group("Header Files\\Generated Files" FILES ${Header_Files__Generated_Files})

set(Header_Files__Statement_Files
    "assignment_statement.h"
    "expression_statement.h"
    "print_statement.h"
    "return_statement.h"
)
source_group("Header Files\\Statement Files" FILES ${Header_Files__Statement_Files})

set(Header_Files__Type_Files
    "ArrayType.h"
    "IntegerType.h"
    "Type.h"
)
source_group("Header Files\\Type Files" FILES ${Header_Files__Type_Files})

set(Header_Files__Visitor_Files
    "Visitor.h"
)
source_group("Header Files\\Visitor Files" FILES ${Header_Files__Visitor_Files})

set(Source_Files
    "ance.cpp"
    "anceCompiler.cpp"
    "Application.cpp"
    "CompileState.cpp"
    "Statement.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(Source_Files__Construct_Files
    "Constant.cpp"
    "Function.cpp"
    "GlobalVariable.cpp"
    "Scope.cpp"
    "Value.cpp"
)
source_group("Source Files\\Construct Files" FILES ${Source_Files__Construct_Files})

set(Source_Files__Expression_Files
    "default_value_expression.cpp"
    "function_call.cpp"
    "integer_expression.cpp"
    "literal_expression.cpp"
    "variable_expression.cpp"
)
source_group("Source Files\\Expression Files" FILES ${Source_Files__Expression_Files})

set(Source_Files__Generated_Files
    "anceBaseVisitor.cpp"
    "anceLexer.cpp"
    "anceParser.cpp"
    "anceVisitor.cpp"
)
source_group("Source Files\\Generated Files" FILES ${Source_Files__Generated_Files})

set(Source_Files__Statement_Files
    "assignment_statement.cpp"
    "expression_statement.cpp"
    "print_statement.cpp"
    "return_statement.cpp"
)
source_group("Source Files\\Statement Files" FILES ${Source_Files__Statement_Files})

set(Source_Files__Type_Files
    "ArrayType.cpp"
    "IntegerType.cpp"
)
source_group("Source Files\\Type Files" FILES ${Source_Files__Type_Files})

set(Source_Files__Visitor_Files
    "Visitor.cpp"
)
source_group("Source Files\\Visitor Files" FILES ${Source_Files__Visitor_Files})

set(Test_Files
    "../ance_examples/first.ance"
    "../ance_examples/first.nc"
)
source_group("Test Files" FILES ${Test_Files})

set(ALL_FILES
    ${Grammar_Files}
    ${Header_Files}
    ${Header_Files__Construct_Files}
    ${Header_Files__Expression_Files}
    ${Header_Files__Generated_Files}
    ${Header_Files__Statement_Files}
    ${Header_Files__Type_Files}
    ${Header_Files__Visitor_Files}
    ${Source_Files}
    ${Source_Files__Construct_Files}
    ${Source_Files__Expression_Files}
    ${Source_Files__Generated_Files}
    ${Source_Files__Statement_Files}
    ${Source_Files__Type_Files}
    ${Source_Files__Visitor_Files}
    ${Test_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    use_props(${PROJECT_NAME} DebugDLL      "LLVM.cmake")
    use_props(${PROJECT_NAME} DebugStatic   "LLVM.cmake")
    use_props(${PROJECT_NAME} Debug         "LLVM.cmake")
    use_props(${PROJECT_NAME} ReleaseDLL    "LLVM.cmake")
    use_props(${PROJECT_NAME} ReleaseStatic "LLVM.cmake")
    use_props(${PROJECT_NAME} Release       "LLVM.cmake")
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    use_props(${PROJECT_NAME} DebugDLL      "LLVM.cmake")
    use_props(${PROJECT_NAME} DebugStatic   "LLVM.cmake")
    use_props(${PROJECT_NAME} Debug         "LLVM.cmake")
    use_props(${PROJECT_NAME} ReleaseDLL    "LLVM.cmake")
    use_props(${PROJECT_NAME} ReleaseStatic "LLVM.cmake")
    use_props(${PROJECT_NAME} Release       "LLVM.cmake")
endif()

set(ROOT_NAMESPACE ance)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASEDLL    "TRUE"
        INTERPROCEDURAL_OPTIMIZATION_RELEASESTATIC "TRUE"
        INTERPROCEDURAL_OPTIMIZATION_RELEASE       "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASEDLL    "TRUE"
        INTERPROCEDURAL_OPTIMIZATION_RELEASESTATIC "TRUE"
        INTERPROCEDURAL_OPTIMIZATION_RELEASE       "TRUE"
    )
endif()
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:ReleaseDLL>:"
            "NDEBUG"
        ">"
        "$<$<CONFIG:ReleaseStatic>:"
            "NDEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:DebugDLL>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:DebugStatic>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:ReleaseDLL>:"
            "NDEBUG"
        ">"
        "$<$<CONFIG:ReleaseStatic>:"
            "NDEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:ReleaseDLL>:
                /Oi;
                /Gy;
                /Ot
            >
            $<$<CONFIG:ReleaseStatic>:
                /Oi;
                /Gy;
                /Ot
            >
            $<$<CONFIG:Release>:
                /Oi;
                /Gy;
                /Ot
            >
            /permissive-;
            /MP;
            /std:c++17;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            -w;
            anceBaseVisitor.h;
            anceBaseVisitor.cpp;
            anceLexer.h;
            anceLexer.cpp;
            anceVisitor.h;
            anceVisitor.cpp;
            anceParser.h;
            anceParser.cpp;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:ReleaseDLL>:
                /Oi;
                /Gy;
                /Ot
            >
            $<$<CONFIG:ReleaseStatic>:
                /Oi;
                /Gy;
                /Ot
            >
            $<$<CONFIG:Release>:
                /Oi;
                /Gy;
                /Ot
            >
            /permissive-;
            /MP;
            /std:c++17;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            -w;
            anceBaseVisitor.h;
            anceBaseVisitor.cpp;
            anceLexer.h;
            anceLexer.cpp;
            anceVisitor.h;
            anceVisitor.cpp;
            anceParser.h;
            anceParser.cpp;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:DebugDLL>:
                /INCREMENTAL
            >
            $<$<CONFIG:DebugStatic>:
                /INCREMENTAL
            >
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:ReleaseDLL>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            $<$<CONFIG:ReleaseStatic>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:DebugDLL>:
                /INCREMENTAL
            >
            $<$<CONFIG:DebugStatic>:
                /INCREMENTAL
            >
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:ReleaseDLL>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            $<$<CONFIG:ReleaseStatic>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Pre build events
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    add_custom_command_if(
        TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMANDS
        COMMAND      $<CONFIG:DebugDLL> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
        COMMAND   $<CONFIG:DebugStatic> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
        COMMAND         $<CONFIG:Debug> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
        COMMAND    $<CONFIG:ReleaseDLL> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
        COMMAND $<CONFIG:ReleaseStatic> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
        COMMAND       $<CONFIG:Release> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    add_custom_command_if(
        TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMANDS
        COMMAND      $<CONFIG:DebugDLL> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
        COMMAND   $<CONFIG:DebugStatic> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
        COMMAND         $<CONFIG:Debug> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
        COMMAND    $<CONFIG:ReleaseDLL> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
        COMMAND $<CONFIG:ReleaseStatic> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
        COMMAND       $<CONFIG:Release> java -jar ./antlr/antlr.jar -no-listener -visitor -Dlanguage=Cpp ./ance.g4
    )
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$(LLVMlibs);"
        "antlr4-runtime;"
        "kernel32;"
        "user32;"
        "gdi32;"
        "winspool;"
        "comdlg32;"
        "advapi32;"
        "shell32;"
        "ole32;"
        "oleaut32;"
        "uuid;"
        "odbc32;"
        "odbccp32"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$(LLVMlibs);"
        "antlr4-runtime;"
        "kernel32;"
        "user32;"
        "gdi32;"
        "winspool;"
        "comdlg32;"
        "advapi32;"
        "shell32;"
        "ole32;"
        "oleaut32;"
        "uuid;"
        "odbc32;"
        "odbccp32"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")


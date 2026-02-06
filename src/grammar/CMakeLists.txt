set(ANTLR_JAR_PATH "${CMAKE_CURRENT_LIST_DIR}/antlr/antlr.jar")

if (EXISTS "${ANTLR_JAR_PATH}")
    set(ANTLR4_JAR_LOCATION "${ANTLR_JAR_PATH}")
    message(STATUS "ANTLR jar found at: ${ANTLR4_JAR_LOCATION}")
    message(STATUS "ANTLR code generation ENABLED")

    antlr4_generate(
            ance_grammar
            ${CMAKE_CURRENT_LIST_DIR}/ance.g4
            BOTH        # Generate lexer and parser.
            FALSE       # Do not generate listener.
            TRUE        # Do generate visitor.
            "grammar"
    )

    set(ANCE_ANTLR_GENERATED_FILES
            ${ANTLR4_SRC_FILES_ance_grammar}
            PARENT_SCOPE
    )

    add_custom_target(ance_grammar
            DEPENDS ${ANTLR4_SRC_FILES_ance_grammar}
    )

    add_dependencies(ance ance_grammar)

    target_include_directories(ance SYSTEM PRIVATE
            ${ANTLR4_INCLUDE_DIR_ance_grammar}
    )

    target_sources(ance PRIVATE
            ${ANTLR4_SRC_FILES_ance_grammar}
    )
else()
    message(FATAL_ERROR
            "ANTLR jar not found at: ${ANTLR_JAR_PATH}\n"
            "ANTLR code generation is REQUIRED but cannot proceed.\n"
            "Please place antlr.jar in the 'antlr/' directory or fix the path."
    )
endif()

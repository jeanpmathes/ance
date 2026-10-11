add_subdirectory(generator)

function(add_tree_generator NAME)
    set(DEF_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/${NAME}.cpp")
    target_sources(ance_generator PRIVATE "${DEF_SOURCE}")

    set(HEADER_OUT "${ANCE_GENERATED_INCLUDE_DIR}/ance/${NAME}/Node.h")
    set(SOURCE_OUT "${ANCE_GENERATED_INCLUDE_DIR}/ance/${NAME}/Node.generated.cpp")

    target_sources(ance_compiler PRIVATE "${SOURCE_OUT}" "${HEADER_OUT}")

    set_property(GLOBAL APPEND PROPERTY ANCE_GENERATOR_OUTPUTS "${HEADER_OUT}" "${SOURCE_OUT}")
endfunction()

add_subdirectory(tree)

get_property(ANCE_GENERATOR_OUTPUTS GLOBAL PROPERTY ANCE_GENERATOR_OUTPUTS)

add_custom_target(ance_generate
        COMMAND ance_generator "${ANCE_GENERATED_INCLUDE_DIR}"
        DEPENDS ance_generator
        BYPRODUCTS ${ANCE_GENERATOR_OUTPUTS}
        COMMENT "Running ance_generator"
        VERBATIM
)

add_dependencies(ance_compiler ance_generate)

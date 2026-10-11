add_executable(ance_generator
        main.cpp
        Definition.cpp
        DefinitionRegistry.cpp
        tree/Definition.cpp
        tree/Emitter.cpp
        tree/Model.cpp
        utility/Strings.cpp
)

set_target_properties(ance_generator PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_include_directories(ance_generator PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ance_generator PRIVATE ance::build_options)

set(ANCE_GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/generated_src" CACHE INTERNAL "Generated include directory")

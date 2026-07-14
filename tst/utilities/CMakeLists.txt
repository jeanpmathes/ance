add_library(ance_test_utilities STATIC SourceTest.cpp)

target_include_directories(ance_test_utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ance_test_utilities
        PUBLIC Catch2::Catch2 ance::compiler ance::build_options)

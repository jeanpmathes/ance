add_executable(ance_unit_tests)
target_link_libraries(ance_unit_tests PRIVATE
        ance_test_utilities
        Catch2::Catch2WithMain)

add_subdirectory(ance)

include(Catch)
catch_discover_tests(ance_unit_tests
        DISCOVERY_MODE PRE_TEST
        DL_PATHS ${ANCE_TEST_DL_PATHS})

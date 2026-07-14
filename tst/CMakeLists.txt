if (WIN32 AND DEFINED VCPKG_INSTALLED_DIR)
    set(ANCE_TEST_DL_PATHS
            "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/$<$<CONFIG:Debug>:debug/>bin")
endif ()

add_subdirectory(utilities)
add_subdirectory(language)
add_subdirectory(unit)

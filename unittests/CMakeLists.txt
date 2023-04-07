enable_testing()

find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Test
)

add_subdirectory(data)

if(WIDGETS)
    add_subdirectory(widgets)
endif()

if(UTILS)
    add_subdirectory(utils)
endif()

if(FORMATS)
    add_subdirectory(formats)
endif()

if(UNIX AND NOT APPLE)
    set(qPA_Platform "QT_QPA_PLATFORM=minimal")
endif()

get_property( FF7TK_TESTS GLOBAL PROPERTY ff7tk_tests)

add_custom_target (run_tests ALL DEPENDS ${FF7TK_TESTS})

add_custom_command(
    TARGET run_tests
    POST_BUILD
    COMMAND ${qPA_Platform} ${CMAKE_CTEST_COMMAND} --test-dir "${CMAKE_BINARY_DIR}/unittests" --output-on-failure
)

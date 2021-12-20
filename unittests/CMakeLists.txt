enable_testing()

define_property(GLOBAL PROPERTY ff7tk_tests BRIEF_DOCS "Defined Tests" FULL_DOCS "Dynamicly Generated list of Defined Tests")

# MAKE_TEST - Set up a unit test
# NAME - Name of the new Test
# FILE - cpp File for the Test
macro (MAKE_TEST NAME FILE)
    get_filename_component(curDir ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(DEP_LIB ff7tk)
    if( NOT ${curDir} MATCHES data)
        string(SUBSTRING ${curDir} 0 1 FIRST_LETTER)
        string(TOUPPER ${FIRST_LETTER} FIRST_LETTER)
        string(REGEX REPLACE "^.(.*)" "${FIRST_LETTER}\\1" curDir_UPPER "${curDir}")
        string(APPEND DEP_LIB "${curDir_UPPER}")
    endif()
    add_executable( ${NAME} ${FILE} )
    target_link_libraries( ${NAME} ${DEP_LIB} Qt::Test)
    add_test(NAME ${NAME} COMMAND $<TARGET_FILE:${NAME}> WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../src/${curDir}")
    set_tests_properties(${NAME} PROPERTIES DEPENDS ${DEP_LIB})
    set_property(GLOBAL APPEND PROPERTY ff7tk_tests ${NAME})
endmacro()

find_package(Qt6 REQUIRED NO_MODULE COMPONENTS
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

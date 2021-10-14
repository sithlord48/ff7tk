macro (MAKE_FF7TK_DATA_TEST NAME FILE)
    add_executable( ${NAME} ${FILE} )
    target_link_libraries( ${NAME} ff7tk Qt::Test)
    add_test(NAME ${NAME} COMMAND $<TARGET_FILE:${NAME}> WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../../src/data")
    set_tests_properties(${NAME} PROPERTIES DEPENDS ff7tk)
endmacro()

MAKE_FF7TK_DATA_TEST(FF7Text_Tests FF7Text_test.cpp)
MAKE_FF7TK_DATA_TEST(FF7Save_Tests FF7Save_test.cpp)

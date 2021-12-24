find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_STRIP_FROM_PATH ${CMAKE_SOURCE_DIR})
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE mainpage.md)

    doxygen_add_docs(
        doxygen
        ${CMAKE_SOURCE_DIR}/docs
        ${CMAKE_SOURCE_DIR}/src
        COMMENT "Generating Documentation"
        ALL
    )

    install (DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html" DESTINATION share/doc/ff7tk COMPONENT ff7tk_development)
else()
    message(STATUS:"Doxygen is required to build documents, Skipping")
endif()


option(FORMATS "Build the formats libary" ON)
option(UTILS "Build utility library (Requires zlib)" ON)
option(WIDGETS "Build the widget libary" ON)

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

enable_testing()

find_package(Qt${QT_DEFAULT_MAJOR_VERSION} REQUIRED NO_MODULE COMPONENTS
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

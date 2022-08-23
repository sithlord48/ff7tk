find_package(Qt6 REQUIRED NO_MODULE COMPONENTS
    Core
    Quick
)

configure_file(ff7tkInfo.h.in ${CMAKE_CURRENT_BINARY_DIR}/ff7tkInfo.h @ONLY)

set (ff7tk_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkInfo.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tk_export.h
)

set (ff7tk_PublicLIBLINKS
      Qt::Core
      Qt::Quick
)

MAKE_LIBRARY(ff7tk ff7tk)

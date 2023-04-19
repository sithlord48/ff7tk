find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
)


configure_file(ff7tkInfo.h.in ${CMAKE_CURRENT_BINARY_DIR}/ff7tkInfo.h @ONLY)

set (ff7tk_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkInfo.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tk_export.h
)

set (ff7tk_PublicLIBLINKS
      Qt::Core
)

MAKE_LIBRARY(ff7tk ff7tk)

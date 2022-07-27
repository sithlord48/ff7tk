find_package(Qt6 REQUIRED NO_MODULE COMPONENTS
    Core
    Widgets
    Gui
)

set(ff7tkQtWidgets_SRC
    ColorDisplay.cpp
    DialogPreview.cpp
    DoubleCheckBox.cpp
    HexLineEdit.cpp
    QTaskBarButton.cpp
)

if(APPLE)
    list(APPEND ff7tkQtWidgets_SRC QTaskBarButton.mm)
endif()

set(ff7tkQtWidgets_HEADERS
    ColorDisplay.h
    DialogPreview.h
    DoubleCheckBox.h
    HexLineEdit.h
    QTaskBarButton.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkqtwidgets_export.h
)

set(ff7tkQtWidgets_PublicLIBLINKS
    Qt::Core
    Qt::Widgets
    Qt::Gui
)

MAKE_LIBRARY(ff7tkQtWidgets ff7tk/widgets/common)


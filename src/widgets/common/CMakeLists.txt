find_package(Qt6 REQUIRED NO_MODULE COMPONENTS
    Core
    Widgets
    Gui
)

set(ff7tkQtWidgets_SRC
    ColorDisplay.cpp
    DialogPreview.cpp
    DoubleCheckBox.cpp
)

set(ff7tkQtWidgets_HEADERS
    ColorDisplay.h
    DialogPreview.h
    DoubleCheckBox.h
    ${CMAKE_CURRENT_BINARY_DIR}/ff7tkqtwidgets_export.h
)

set(ff7tkQtWidgets_PublicLIBLINKS
    Qt::Core
    Qt::Widgets
    Qt::Gui
)

MAKE_LIBRARY(ff7tkQtWidgets ff7tk/widgets/common)

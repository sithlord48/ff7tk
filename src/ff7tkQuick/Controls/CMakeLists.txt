#
find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    Qml
    Quick
    QuickControls2
)

set(libName ff7tkQuickControls)
set(${libName}_MAKEQMLMODULE TRUE)
set(${libName}_URI "ff7tkQuick.Controls")

set(${libName}_QMLFILES
    ItemPreview.qml
    MateriaEditor.qml
    MateriaSlotButton.qml
    Components/ComboBox.qml
)

set(${libName}_DEPENDS
    QtQuick
    QtQuickControls2
    ff7tkQuickDataTypes
)

set(${libName}_PublicLIBLINKS
    Qt::Quick
    Qt::QuickControls2
    ff7tk::ff7tkQuickDataTypes
)

MAKE_LIBRARY(${libName} ff7tk/ff7tkQuickControls)

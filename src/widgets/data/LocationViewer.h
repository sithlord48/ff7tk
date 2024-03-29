//    SPDX-FileCopyrightText: 2013 - 2023 Chris Rizzitello <sithlord48@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QEvent>
#include <QModelIndex>
#include <QWidget>
#include <ff7tkwidgets_export.h>

class QAction;
class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QListWidget;
class QPushButton;
class QSpinBox;
class QTableWidget;
class QToolButton;

/** \class LocationViewer
 *  \brief Set Saves Location or View Field Locations and Toggle the items picked up from them.
 *  \todo Support Progression within this widget
 **/
class FF7TKWIDGETS_EXPORT LocationViewer : public QWidget
{
    Q_OBJECT
public:
    enum filterMode {NAME, ITEM};
    explicit LocationViewer(QWidget *parent = nullptr);
    void setFilterString(QString filter = "", LocationViewer::filterMode mode = LocationViewer::NAME);
signals:
    void locationChanged(QString);
    void xChanged(int x);
    void yChanged(int y);
    void tChanged(int t);
    void dChanged(int d);
    void mapIdChanged(int mapId);
    void locIdChanged(int locId);
    void locationStringChanged(QString);
    void fieldItemConnectRequest(quint8 index, QList<quint16> offset, QList<quint8>bit);
    void fieldItemCheck(int index);
    void fieldItemChanged(int index, bool checked);

public slots:
    void setSelected(const QString &);
    void setRegion(const QString &region);
    void setX(int x);
    void setY(int y);
    void setT(int t);
    void setD(int d);
    void setMapId(int mapId);
    void setLocationId(int locId);
    void setLocationString(const QString &);
    void setHorizontalHeaderStyle(QString styleSheet);
    void setFieldItemChecked(int row, bool checked);
    void init_fieldItems(void);
    void setAdvancedMode(bool advancedMode);
    bool advancedMode(void);

private slots:
    void itemChanged(int currentRow, int currentColumn, int prevRow, int prevColumn);
    void sbMapIdChanged(int mapId);
    void sbLocIdChanged(int locId);
    void sbXChanged(int x);
    void sbYChanged(int y);
    void sbTChanged(int t);
    void sbDChanged(int d);
    void lineLocationNameChanged(const QString &);
    void setLocation(int mapId, int locId);
    void filterLocations(QString filter);
    void actionNameSearchToggled(bool checked);
    void actionItemSearchToggled(bool checked);
    void actionRegExpSearchToggled(bool checked);
    void actionCaseSensitiveToggled(bool checked);
    void fieldItemListItemChanged(QModelIndex index);
    void btnUpdateSaveLocationClicked();
protected:
    void resizeEvent(QResizeEvent *ev);
    void changeEvent(QEvent *e);
private:
    const int COL_ID = 0;
    const int COL_FNAME = 1;
    const int COL_NAME = 2;
    void init_display(void);
    void init_connections(void);
    void init_disconnect(void);
    void updateText();
    void updateItemText(int locID = -1, bool currentLoc = false);
    QString translate(QString text);
    void searchItem(QRegularExpression exp);
    void searchName(QRegularExpression exp);
    QString region;
    int currentStartingLocation = -1;
    bool regExpSearch;
    bool caseSensitive;
    bool _advancedMode;
    quint8 searchMode;
    QTableWidget *locationTable;
    QToolButton *btnSearchOptions;
    QAction *actionNameSearch;
    QAction *actionItemSearch;
    QAction *actionRegExpSearch;
    QAction *actionCaseSensitive;
    QWidget *CoordsWidget;
    QLabel *lblLocationPreview;
    QLineEdit *lineTableFilter;
    QLineEdit *lineLocationName;
    QSpinBox *sbMapID;
    QSpinBox *sbLocID;
    QSpinBox *sbX;
    QSpinBox *sbY;
    QSpinBox *sbT;
    QSpinBox *sbD;
    QListWidget *fieldItemList;
    QGroupBox *groupFieldItems;
    QPushButton *btnUpdateSaveLocation;

    inline static const QString _tooltip = QStringLiteral("<html><head/><body><p><img src=\":/locations/%1_%2\" width=\"%3\" height\"%4\" /></p></body></html>");
};

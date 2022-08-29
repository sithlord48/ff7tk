/****************************************************************************/
//    copyright 2013 - 2022  Chris Rizzitello <sithlord48@gmail.com>        //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include <LocationViewer.h>

#include <QAction>
#include <QCheckBox>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMenu>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollBar>
#include <QSpinBox>
#include <QTableWidget>
#include <QToolButton>
#include <QTranslator>
#include <QVBoxLayout>
#include <QDir>
#include <QCoreApplication>

#include <FF7Location>
#include <FF7FieldItemList>

LocationViewer::LocationViewer(QWidget *parent)
    : QWidget(parent)
    , region(QString())
    , regExpSearch(false)
    , caseSensitive(false)
    , _advancedMode(false)
    , locationTable(new QTableWidget)
    , btnSearchOptions(new QToolButton)
    , actionNameSearch(new QAction(btnSearchOptions))
    , actionItemSearch(new QAction(btnSearchOptions))
    , actionRegExpSearch(new QAction(btnSearchOptions))
    , actionCaseSensitive(new QAction(btnSearchOptions))
    , lblLocationPreview(new QLabel)
    , lineTableFilter(new QLineEdit)
    , lineLocationName(new QLineEdit)
    , sbMapID(new QSpinBox)
    , sbLocID(new QSpinBox)
    , sbX(new QSpinBox)
    , sbY(new QSpinBox)
    , sbT(new QSpinBox)
    , sbD(new QSpinBox)
    , fieldItemList(new QListWidget)
    , groupFieldItems(new QGroupBox)
    , btnUpdateSaveLocation(new QPushButton)
    , translator(new QTranslator(this))

{
    locationTable->setRowCount(FF7Location::size());
    locationTable->setColumnCount(3);

    langDir = QStringLiteral("%1/%2").arg(QCoreApplication::applicationDirPath(), QStringLiteral("lang"));
    QDir translationDir(langDir);
    QStringList nameFilter{QStringLiteral("ff7tk_*.qm")};
    if (translationDir.entryList(nameFilter, QDir::Files, QDir::Name).isEmpty()) {
        translationDir.setPath(QStringLiteral("%1/../share/ff7tk/lang").arg(QCoreApplication::applicationDirPath()));
        if (translationDir.entryList(nameFilter, QDir::Files, QDir::Name).isEmpty()) {
            translationDir.setPath(QStringLiteral("%1/%2").arg(QDir::homePath(), QStringLiteral(".local/share/ff7tk/lang")));
            if (translationDir.entryList(nameFilter, QDir::Files, QDir::Name).isEmpty()) {
                translationDir.setPath(QStringLiteral("/usr/local/share/ff7tk/lang"));
                if (translationDir.entryList(nameFilter, QDir::Files, QDir::Name).isEmpty()) {
                    translationDir.setPath(QStringLiteral("/usr/share/ff7tk/lang"));
                }
            }
        }
    }
    langDir = translationDir.absolutePath();
    updateText();
    init_display();
    init_connections();
    actionNameSearch->setChecked(true);
}

void LocationViewer::resizeEvent(QResizeEvent *ev)
{
    if (ev->type() == QResizeEvent::Resize) {
        QPixmap pix(QStringLiteral(":/locations/%1_%2").arg(QString::number(sbMapID->value()), QString::number(sbLocID->value())));
        if (pix.isNull()) {
            return;
        }
        lblLocationPreview->setPixmap(pix.scaled(lblLocationPreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void LocationViewer::changeEvent(QEvent *e)
{
    if (e->type() != QEvent::LanguageChange) {
        QWidget::changeEvent(e);
    }
    updateText();
}

void LocationViewer::updateText()
{
    QStringList hozHeaderLabels = {tr("Filename"), tr("Location Name"), tr("LocID")};
    locationTable->setHorizontalHeaderLabels(hozHeaderLabels);
    for (int i = 0; i < locationTable->rowCount(); i++) {
        QTableWidgetItem *newItem = new QTableWidgetItem(FF7Location::locationString(i), 0);
        newItem->setFlags(newItem->flags() &= ~Qt::ItemIsEditable);
        newItem->setTextAlignment(Qt::AlignLeft);
        newItem->setToolTip(_tooltip.arg(
                                FF7Location::mapID(i),
                                FF7Location::locationID(i),
                                QString::number(fontMetrics().height() * 12),
                                QString::number(fontMetrics().height() * 15)));
        locationTable->setItem(i, 1, newItem);
    }
    actionNameSearch->setText(tr("Filter Mode: Name / Location String"));
    actionItemSearch->setText(tr("Filter Mode: Items Found at Location"));
    actionRegExpSearch->setText(tr("Process Regular Expressions"));
    actionCaseSensitive->setText(tr("Case Sensitive"));
    sbMapID->setPrefix(tr("MapID: "));
    sbLocID->setPrefix(tr("LocID: "));
    sbX->setPrefix(tr("X: "));
    sbY->setPrefix(tr("Y: "));
    sbT->setPrefix(tr("T: "));
    sbD->setPrefix(tr("D: "));
    lineLocationName->setPlaceholderText(tr("Location Name"));
    btnUpdateSaveLocation->setText(tr("Set as current location"));
    groupFieldItems->setTitle(tr("Field Items"));

    if (locationTable->currentRow() > -1)
        lineLocationName->setText(translate(FF7Location::rawLocationString(locationTable->item(locationTable->currentRow(), 0)->text())));

    if (actionNameSearch->isChecked())
        lineTableFilter->setPlaceholderText(actionNameSearch->text());
    else if (actionItemSearch)
        lineTableFilter->setPlaceholderText(actionItemSearch->text());

    init_fieldItems();
}

void LocationViewer::init_display(void)
{
    int h = fontMetrics().height();
    lblLocationPreview->setMinimumSize(h * 12, h *15);
    lblLocationPreview->setBaseSize(h * 24, h * 30);
    lblLocationPreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    locationTable->verticalHeader()->setHidden(true);
    locationTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    locationTable->setSelectionMode(QAbstractItemView::SingleSelection);
    locationTable->setSortingEnabled(true);
    locationTable->setColumnWidth(0, fontMetrics().horizontalAdvance(QChar('W')) * 6);
    locationTable->setColumnWidth(1, fontMetrics().horizontalAdvance(QChar('W')) * 15);
    locationTable->setColumnWidth(2, fontMetrics().horizontalAdvance(QChar('W')) * 4);
    for (int i = 0; i < locationTable->rowCount(); i++) {
        QTableWidgetItem *newItem = new QTableWidgetItem(FF7Location::fileName(i), 0);
        newItem->setFlags(newItem->flags() &= ~Qt::ItemIsEditable);
        newItem->setToolTip(_tooltip.arg(
                                FF7Location::mapID(i),
                                FF7Location::locationID(i),
                                QString::number(fontMetrics().height() * 12),
                                QString::number(fontMetrics().height() * 15)));
        newItem->setTextAlignment(Qt::AlignLeft);
        locationTable->setItem(i, 0, newItem);

        //To assure proper numerical sorting of location IDs they should all contain the same number of characters.
        newItem = new QTableWidgetItem(QStringLiteral("%1").arg(FF7Location::locationID(i).toInt(), 3, 10, QChar('0')).toUpper());
        newItem->setFlags(newItem->flags() &= ~Qt::ItemIsEditable);
        newItem->setTextAlignment(Qt::AlignHCenter);
        locationTable->setItem(i, 2, newItem);
        locationTable->setRowHeight(i, (fontMetrics().height() + 2));
    }
    locationTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    locationTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    locationTable->adjustSize();
    locationTable->setFixedWidth(locationTable->columnWidth(0) + locationTable->columnWidth(1) + locationTable->columnWidth(2) + locationTable->verticalScrollBar()->widthMM() + fontMetrics().horizontalAdvance(QChar('W')));
    locationTable->setCurrentCell(-1, -1);
    locationTable->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    actionNameSearch->setCheckable(true);
    actionItemSearch->setCheckable(true);
    actionRegExpSearch->setCheckable(true);
    actionCaseSensitive->setCheckable(true);

    QMenu *newMenu = new QMenu;
    newMenu->addAction(actionNameSearch);
    newMenu->addAction(actionItemSearch);
    newMenu->addSeparator();
    newMenu->addAction(actionRegExpSearch);
    newMenu->addAction(actionCaseSensitive);

    btnSearchOptions->setLayoutDirection(Qt::RightToLeft);
    btnSearchOptions->setIcon(QIcon::fromTheme(QStringLiteral("edit-clear"), QPixmap(":/common/edit-clear")));
    btnSearchOptions->setPopupMode(QToolButton::MenuButtonPopup);
    btnSearchOptions->setMenu(newMenu);

    sbMapID->setMaximum(3);
    sbMapID->setWrapping(true);

    sbMapID->setAlignment(Qt::AlignCenter);

    sbLocID->setMaximum(786);
    sbLocID->setWrapping(true);
    sbLocID->setAlignment(Qt::AlignCenter);

    sbX->setMinimum(-32767);
    sbX->setMaximum(32767);
    sbX->setWrapping(true);
    sbX->setAlignment(Qt::AlignCenter);

    sbY->setMinimum(-32767);
    sbY->setMaximum(32767);
    sbY->setWrapping(true);
    sbY->setAlignment(Qt::AlignCenter);

    sbT->setMaximum(65565);
    sbT->setWrapping(true);
    sbT->setAlignment(Qt::AlignCenter);

    sbD->setMaximum(255);
    sbD->setWrapping(true);
    sbD->setAlignment(Qt::AlignCenter);

    btnUpdateSaveLocation->setVisible(false);
    connect(btnUpdateSaveLocation, &QPushButton::clicked, this, &LocationViewer::btnUpdateSaveLocationClicked);

    fieldItemList->setFixedHeight(0);
    fieldItemList->setUniformItemSizes(true);
    fieldItemList->setSelectionMode(QAbstractItemView::NoSelection);

    QVBoxLayout *fitemLayout = new QVBoxLayout();
    fitemLayout->setContentsMargins(0, 0, 0, 0);
    fitemLayout->setSpacing(0);
    fitemLayout->addWidget(fieldItemList);

    groupFieldItems->setLayout(fitemLayout);
    groupFieldItems->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    QHBoxLayout *nameIDs = new QHBoxLayout;
    nameIDs->addWidget(lineLocationName);
    nameIDs->addWidget(sbMapID);
    nameIDs->addWidget(sbLocID);

    QHBoxLayout *XYTD = new QHBoxLayout;
    XYTD->addWidget(sbX);
    XYTD->addWidget(sbY);
    XYTD->addWidget(sbT);
    XYTD->addWidget(sbD);

    QVBoxLayout *CoordsLayout = new QVBoxLayout;
    CoordsLayout->setContentsMargins(3, 3, 3, 3);
    CoordsLayout->addLayout(nameIDs);
    CoordsLayout->addLayout(XYTD);

    QHBoxLayout *FilterLayout = new QHBoxLayout;
    FilterLayout->setContentsMargins(0, 0, 0, 0);
    FilterLayout->addWidget(lineTableFilter, 8);
    FilterLayout->addWidget(btnSearchOptions, 2);

    QVBoxLayout *LeftSideLayout = new QVBoxLayout;
    LeftSideLayout->setSpacing(0);
    LeftSideLayout->addWidget(locationTable);
    LeftSideLayout->addLayout(FilterLayout);

    QVBoxLayout *RightSideLayout = new QVBoxLayout;
    RightSideLayout->addLayout(CoordsLayout);
    RightSideLayout->addWidget(btnUpdateSaveLocation);
    RightSideLayout->addWidget(lblLocationPreview);
    RightSideLayout->addWidget(groupFieldItems);
    setAdvancedMode(advancedMode());

    QHBoxLayout *FinalLayout = new QHBoxLayout;
    FinalLayout->setContentsMargins(3, 3, 3, 3);
    FinalLayout->addLayout(LeftSideLayout, 1);
    FinalLayout->addLayout(RightSideLayout, 9);
    setLayout(FinalLayout);
    adjustSize();
}
void LocationViewer::init_connections(void)
{
    connect(locationTable, &QTableWidget::currentCellChanged, this, &LocationViewer::itemChanged);
    connect(lineTableFilter, &QLineEdit::textChanged, this, &LocationViewer::filterLocations);
    connect(btnSearchOptions, &QCheckBox::clicked, lineTableFilter, &QLineEdit::clear);
    connect(actionNameSearch, &QAction::toggled, this, &LocationViewer::actionNameSearchToggled);
    connect(actionItemSearch, &QAction::toggled, this, &LocationViewer::actionItemSearchToggled);
    connect(actionRegExpSearch, &QAction::toggled, this, &LocationViewer::actionRegExpSearchToggled);
    connect(actionCaseSensitive, &QAction::toggled, this, &LocationViewer::actionCaseSensitiveToggled);
    connect(sbMapID, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbMapIdChanged);
    connect(sbLocID, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbLocIdChanged);
    connect(sbX, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbXChanged);
    connect(sbY, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbYChanged);
    connect(sbT, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbTChanged);
    connect(sbD, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbDChanged);
    connect(lineLocationName, &QLineEdit::textChanged, this, &LocationViewer::lineLocationNameChanged);
    connect(fieldItemList, &QListWidget::clicked, this, &LocationViewer::fieldItemListItemChanged);
}
void LocationViewer::init_disconnect(void)
{
    disconnect(locationTable, &QTableWidget::currentCellChanged, this, &LocationViewer::itemChanged);
    disconnect(lineTableFilter, &QLineEdit::textChanged, this, &LocationViewer::filterLocations);
    disconnect(btnSearchOptions, &QCheckBox::clicked, lineTableFilter, &QLineEdit::clear);
    disconnect(actionNameSearch, &QAction::toggled, this, &LocationViewer::actionNameSearchToggled);
    disconnect(actionItemSearch, &QAction::toggled, this, &LocationViewer::actionItemSearchToggled);
    disconnect(actionRegExpSearch, &QAction::toggled, this, &LocationViewer::actionRegExpSearchToggled);
    disconnect(actionCaseSensitive, &QAction::toggled, this, &LocationViewer::actionCaseSensitiveToggled);
    disconnect(sbMapID, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbMapIdChanged);
    disconnect(sbLocID, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbLocIdChanged);
    disconnect(sbX, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbXChanged);
    disconnect(sbY, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbYChanged);
    disconnect(sbT, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbTChanged);
    disconnect(sbD, QOverload<int>::of(&QSpinBox::valueChanged), this, &LocationViewer::sbDChanged);
    disconnect(lineLocationName, &QLineEdit::textChanged, this, &LocationViewer::lineLocationNameChanged);
    disconnect(fieldItemList, &QListWidget::clicked, this, &LocationViewer::fieldItemListItemChanged);
}

void LocationViewer::itemChanged(int currentRow, int currentColumn, int prevRow, int prevColumn)
{
    Q_UNUSED(currentColumn)
    Q_UNUSED(prevColumn)

    if (currentRow != prevRow) {
        int mapID = FF7Location::mapID(locationTable->item(currentRow, 0)->text()).toInt();
        int locID = FF7Location::locationID(locationTable->item(currentRow, 0)->text()).toInt();
        setLocation(mapID, locID);
    }
}

void LocationViewer::setSelected(const QString &locFilename)
{
    locationTable->setCurrentItem(locationTable->item(-1, -1));
    for (int i = 0; i < FF7Location::size(); i++) {
        if (locationTable->item(i, 0)->text() == locFilename) {
            locationTable->setCurrentItem(locationTable->item(i, 0));
            break;
        }
    }
}

void LocationViewer::sbMapIdChanged(int mapId)
{
    setLocation(mapId, sbLocID->value());
    QString fileName = FF7Location::fileName(mapId, sbLocID->value());
    if (fileName.isEmpty())
        Q_EMIT mapIdChanged(mapId);
    else
        Q_EMIT locationChanged(fileName);
}

void LocationViewer::sbLocIdChanged(int locId)
{
    setLocation(sbMapID->value(), locId);
    QString fileName = FF7Location::fileName(sbMapID->value(), locId);
    if (fileName.isEmpty())
        Q_EMIT locIdChanged(locId);
    else
        Q_EMIT locationChanged(fileName);
}

void LocationViewer::sbXChanged(int x)
{
    Q_EMIT xChanged(x);
}

void LocationViewer::sbYChanged(int y)
{
    Q_EMIT yChanged(y);
}

void LocationViewer::sbTChanged(int t)
{
    Q_EMIT tChanged(t);
}

void LocationViewer::sbDChanged(int d)
{
    Q_EMIT dChanged(d);
}

void LocationViewer::setLocation(int mapId, int locId)
{
    init_disconnect();
    QString fileName = FF7Location::fileName(mapId, locId);
    setSelected(fileName);
    btnUpdateSaveLocation->setVisible(locId != currentStartingLocation);

    if (fileName.isEmpty()) {
        lblLocationPreview->setPixmap(QString());
    } else {
        lblLocationPreview->setPixmap(QPixmap(QStringLiteral("://locations/%1_%2").arg(QString::number(mapId), QString::number(locId))).scaledToWidth(lblLocationPreview->width(), Qt::SmoothTransformation));
        QString oldStr = FF7Location::rawLocationString(fileName);
        QString newStr = translate(oldStr);
        sbMapID->setValue(FF7Location::mapID(fileName).toInt());
        sbLocID->setValue(FF7Location::locationID(fileName).toInt());
        sbX->setValue(FF7Location::x(fileName).toInt());
        sbY->setValue(FF7Location::y(fileName).toInt());
        sbT->setValue(FF7Location::t(fileName).toInt());
        sbD->setValue(FF7Location::d(fileName).toInt());
        lineLocationName->setText(newStr);
        init_fieldItems();
    }
    init_connections();
}

void LocationViewer::lineLocationNameChanged(const QString &locName)
{
    Q_EMIT locationStringChanged(locName);
}

void LocationViewer::setX(int x)
{
    init_disconnect(); sbX->setValue(x); init_connections();
}

void LocationViewer::setY(int y)
{
    init_disconnect(); sbY->setValue(y); init_connections();
}

void LocationViewer::setT(int t)
{
    init_disconnect(); sbT->setValue(t); init_connections();
}

void LocationViewer::setD(int d)
{
    init_disconnect(); sbD->setValue(d); init_connections();
}

void LocationViewer::setMapId(int mapId)
{
    sbMapID->setValue(mapId);
}

void LocationViewer::setLocationId(int locId)
{
    updateItemText(currentStartingLocation, false);

    currentStartingLocation = locId;
    updateItemText(currentStartingLocation, true);

    sbLocID->setValue(locId);
    btnUpdateSaveLocation->setVisible(false);
}

void LocationViewer::setLocationString(const QString &locString)
{
    init_disconnect();
    QString newStr = translate(locString);
    lineLocationName->setText(newStr);
    init_connections();
}

void LocationViewer::btnUpdateSaveLocationClicked()
{
    updateItemText(currentStartingLocation, false);

    currentStartingLocation = sbLocID->value();
    updateItemText(currentStartingLocation, true);

    btnUpdateSaveLocation->setVisible(false);
    Q_EMIT locationChanged(FF7Location::fileName(sbMapID->value(), sbLocID->value()));
}

void LocationViewer::updateItemText(int locID, bool currentLoc)
{
    if(locID == -1)
        return;
    QFont font = locationTable->font();
    font.setBold(currentLoc);
    font.setItalic(currentLoc);
    QString locString = QStringLiteral("%1").arg(locID, 3, 10, QChar('0'));
    int row = locationTable->findItems(locString, Qt::MatchExactly).at(0)->row();
    locationTable->item(row, 0)->setFont(font);
    locationTable->item(row, 1)->setFont(font);
    locationTable->item(row, 2)->setFont(font);
}

void LocationViewer::setHorizontalHeaderStyle(QString styleSheet)
{
    locationTable->horizontalHeader()->setStyleSheet(styleSheet);
}

void LocationViewer::setRegion(const QString &newRegion)
{
    region = newRegion; setLocation(sbMapID->value(), sbLocID->value());
}

QString LocationViewer::translate(QString text)
{
    QString lang;

    if (region.contains(QStringLiteral("BASCUS-94163")) || region.contains(QStringLiteral("BESCES-00867")))
        lang = QStringLiteral("ff7tk_en.qm");
    else if (region.contains(QStringLiteral("BESCES-00868")))
        lang = QStringLiteral("ff7tk_fr.qm");
    else if (region.contains(QStringLiteral("BESCES-00869")))
        lang = QStringLiteral("ff7tk_de.qm");
    else if (region.contains(QStringLiteral("BESCES-00900")))
        lang = QStringLiteral("ff7tk_es.qm");
    else if (region.contains(QStringLiteral("BISLPS-00700")) || region.contains(QStringLiteral("BISLPS-01057")))
        lang = QStringLiteral("ff7tk_ja.qm");

    if(lang.isNull())
        return text;

    if(!translator->filePath().contains(lang))
        std::ignore = translator->load(lang, langDir);
    QString newText = translator->translate("FF7Location", text.toLatin1());
    if (newText.isEmpty())
        return text;
    return newText;
}

void LocationViewer::filterLocations(QString filter)
{
    if (filter.isEmpty()) {
        for (int i = 0; i < locationTable->rowCount(); i++)
            locationTable->setRowHidden(i, false);
        return;
    }

    QRegularExpression exp(filter);
    exp.setPatternOptions(caseSensitive ? QRegularExpression::PatternOption::NoPatternOption : QRegularExpression::CaseInsensitiveOption );
    switch (searchMode) {
    case NAME: searchName(exp); break;
    case ITEM: searchItem(exp); break;
    }
}

void LocationViewer::actionNameSearchToggled(bool checked)
{
    if (checked) {
        actionItemSearchToggled(false);
        searchMode = NAME;
        lineTableFilter->setPlaceholderText(actionNameSearch->text());
        if (!lineTableFilter->text().isEmpty()) {
            filterLocations(lineTableFilter->text());
        }
    } else {
        actionNameSearch->setChecked(false);
    }
}

void LocationViewer::actionItemSearchToggled(bool checked)
{
    if (checked) {
        actionNameSearchToggled(false);
        searchMode = ITEM;
        lineTableFilter->setPlaceholderText(actionItemSearch->text());
        if (!lineTableFilter->text().isEmpty())
            filterLocations(lineTableFilter->text());
    } else {
        actionItemSearch->setChecked(false);
    }
}

void LocationViewer::actionRegExpSearchToggled(bool checked)
{
    regExpSearch = checked;
    if (lineTableFilter->text().isEmpty())
        filterLocations(lineTableFilter->text());
}

void LocationViewer::actionCaseSensitiveToggled(bool checked)
{
    caseSensitive = checked;
    if (!lineTableFilter->text().isEmpty())
        filterLocations(lineTableFilter->text());
}

void LocationViewer::init_fieldItems(void)
{
    groupFieldItems->setVisible(false);
    fieldItemList->clear();
    QString fieldFileName = FF7Location::fileName(sbMapID->value(), sbLocID->value()); //store our current field's FileName
    if (fieldFileName.isEmpty()) {
        fieldItemList->setFixedHeight(0);
        return;
    } else {
        for (int i = 0; i < FF7FieldItemList::size(); i++) {
            for (int j = 0; j < FF7FieldItemList::maps(i).count(); j++) {
                if (FF7FieldItemList::maps(i).at(j) == fieldFileName) {
                    QListWidgetItem *newItem = new QListWidgetItem(FF7FieldItemList::text(i));
                    newItem->setCheckState(Qt::Unchecked);
                    fieldItemList->addItem(newItem);
                    Q_EMIT fieldItemConnectRequest(quint8(fieldItemList->count()) - 1, FF7FieldItemList::offset(i), FF7FieldItemList::bit(i));
                    Q_EMIT fieldItemCheck(fieldItemList->count() - 1);
                }
            }
        }

        if (fieldItemList->count() > 0)
            groupFieldItems->setVisible(true);

        if (fieldItemList->count() <= 5) {
            fieldItemList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            fieldItemList->setFixedHeight(fieldItemList->sizeHintForRow(0)*fieldItemList->count() + fieldItemList->contentsMargins().top() + fieldItemList->contentsMargins().bottom());
        } else {
            fieldItemList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
            fieldItemList->setFixedHeight(fieldItemList->sizeHintForRow(0) * 5 + fieldItemList->contentsMargins().top() + fieldItemList->contentsMargins().bottom());
        }
        groupFieldItems->setFixedHeight(fieldItemList->contentsRect().height() + groupFieldItems->contentsMargins().bottom() + groupFieldItems->contentsMargins().top());
    }
}

void LocationViewer::fieldItemListItemChanged(QModelIndex index)
{
    bool checked;
    if (fieldItemList->item(index.row())->checkState() == Qt::Checked)
        checked = true;
    else
        checked = false;

    Q_EMIT fieldItemChanged(index.row(), checked);

}
void LocationViewer::setFieldItemChecked(int row, bool checked)
{
    init_disconnect();
    if (fieldItemList->count() > row) {
        if (checked)
            fieldItemList->item(row)->setCheckState(Qt::Checked);
        else
            fieldItemList->item(row)->setCheckState(Qt::Unchecked);
    }
    init_connections();
}
void LocationViewer::searchName(QRegularExpression exp)
{
    for (int i = 0; i < locationTable->rowCount(); i++) {
        bool hidden = true;
        if(regExpSearch) {
        for (int j = 0; j < locationTable->columnCount(); j++) {
                if (exp.match(locationTable->item(i, j)->text()).hasMatch()) {
                    hidden = false;
                    break;
                }
            }
        } else {
            Qt::CaseSensitivity caseSensitiveValue = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
            for (int j = 0; j < locationTable->columnCount(); j++) {
                if (locationTable->item(i, j)->text().contains(exp.pattern(), caseSensitiveValue)) {
                    hidden = false;
                    break;
                }
            }
        }
        locationTable->setRowHidden(i, hidden);
    }
}
void LocationViewer::searchItem(QRegularExpression exp)
{
    QStringList locationNames;
    if(regExpSearch) {
        for (const FieldItem &fieldItem : FF7FieldItemList::fieldItemList()) {
                if (exp.match(fieldItem.Text).hasMatch())
                    locationNames.append(fieldItem.Maps);
        }
    } else {
        Qt::CaseSensitivity caseSensitiveValue = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
        for (const FieldItem &fieldItem : FF7FieldItemList::fieldItemList()) {
            if (fieldItem.Text.contains(exp.pattern(), caseSensitiveValue))
                locationNames.append(fieldItem.Maps);
        }
    }

    for (int i = 0; i < locationTable->rowCount(); i++) {
        bool hidden = true;
        for (int j = 0; j < locationNames.count(); j++) {
            if (locationTable->item(i, 0)->text() == locationNames.at(j)) {
                hidden = false;
                break;
            }
        }
        locationTable->setRowHidden(i, hidden);
    }
}

void LocationViewer::setAdvancedMode(bool advancedMode)
{
    _advancedMode = advancedMode;
    sbMapID->setVisible(_advancedMode);
    sbLocID->setVisible(_advancedMode);
    sbX->setVisible(_advancedMode);
    sbY->setVisible(_advancedMode);
    sbT->setVisible(_advancedMode);
    sbD->setVisible(_advancedMode);
}

bool LocationViewer::advancedMode(void)
{
    return _advancedMode;
}

void LocationViewer::setFilterString(QString filter, filterMode mode)
{
    switch (mode) {
    case NAME:
        actionNameSearch->setChecked(true);
        break;
    case ITEM:
        actionItemSearch->setChecked(true);
        break;
    }
    lineTableFilter->setText(filter);
    for (int i = 0; i < locationTable->rowCount(); i++) {
        if (!locationTable->isRowHidden(i)) {
            locationTable->selectRow(i);
            return;
        }
    }
}

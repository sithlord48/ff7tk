//    SPDX-FileCopyrightText: 2009 - 2022 Arzel Jérôme <myst6re@gmail.com>
//    SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QWidget>

#include <ff7tkqtwidgets_export.h>

typedef QPoint Cell;

class FF7TKQTWIDGETS_EXPORT ImageGridWidget : public QWidget
{
    Q_OBJECT
public:
    enum SelectionMode {
        NoSelection,
        SingleSelection,
        MultiSelection
    };
    explicit ImageGridWidget(QWidget *parent = nullptr);
    inline const QPixmap &pixmap() const {
        return _pixmap;
    }
    void setPixmap(const QPixmap &pixmap);
    void setPixmap(const QPoint &point, const QPixmap &pixmap);
    inline QPoint pixmapPoint() const {
        return _pixmapPoint;
    }
    void setPixmapPoint(const QPoint &point);
    inline int cellSize() const {
        return _cellSize;
    }
    void setCellSize(int size);
    inline int groupedCellSize() const {
        return _groupedCellSize;
    }
    void setGroupedCellSize(int size);
    void setCustomLines(const QList<QLine> &lines);
    inline QSize gridSize() const {
        return _gridSize.isValid() ? _gridSize : (_cellSize == 0 ? QSize() : _pixmap.size() / _cellSize);
    }
    inline QSize gridSizePixel() const {
        return _gridSize.isValid() ? _gridSize * _cellSize : _pixmap.size();
    }
    void setGridSize(const QSize &gridSize);
    QPixmap cellPixmap(const Cell &cell) const;
    inline const QList<Cell> &selectedCells() const {
        return _selectedCells;
    }
    inline SelectionMode selectionMode() const {
        return _selectionMode;
    }
    void setSelectionMode(SelectionMode mode);
signals:
    void currentSelectionChanged(const QList<Cell> &cells);
    void highlighted(const Cell &cell);
    void clicked(const Cell &cell);
public slots:
    inline void setSelectedCell(const Cell &cell) {
        setSelectedCells(QList<Cell>() << cell);
    }
    void setSelectedCells(const QList<Cell> &cells);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual QSize minimumSizeHint() const override;
    virtual QSize sizeHint() const override;
private:
    QList<QLine> createGrid(const QSize &gridS, int cellSize);
    void drawSelection(QPainter &painter, QPoint selection);
    inline QPoint scaledPoint(const Cell &cell) const {
        return _scaledRatio * cell;
    }
    Cell getCell(const QPoint &pos) const;
    bool cellIsInRange(const Cell &cell) const;
    void updateGrid();
    void clearHover();

    QPixmap _pixmap;
    QList<QLine> _gridLines, _groupedGridLines, _customLines;
    Cell _hoverCell, _startMousePress;
    QList<Cell> _selectedCells;
    QPoint _pixmapPoint, _scaledPixmapPoint, _scaledGridPoint;
    QSize _scaledPixmapSize;
    QSize _gridSize;
    double _scaledRatio;
    SelectionMode _selectionMode;
    int _cellSize, _groupedCellSize;
};

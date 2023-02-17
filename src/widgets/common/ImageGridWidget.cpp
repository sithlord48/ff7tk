/****************************************************************************/
//    Copyright (C) 2009-2022 Arzel Jérôme <myst6re@gmail.com>              //
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
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include <ImageGridWidget.h>

#include <QPainter>
#include <QPen>
#include <QStyleOption>
#include <QMouseEvent>

ImageGridWidget::ImageGridWidget(QWidget *parent)
    : QWidget(parent)
    , _hoverCell(-1, -1)
    , _startMousePress(-1, -1)
    , _pixmapPoint(-1, -1)
    , _scaledRatio(0.0)
    , _selectionMode(SingleSelection)
    , _cellSize(0)
    , _groupedCellSize(0)
{
    setMouseTracking(_selectionMode != NoSelection);
}

void ImageGridWidget::setPixmap(const QPixmap &pixmap)
{
    _pixmap = pixmap;
    updateGrid();
    update();
}

void ImageGridWidget::setPixmap(const QPoint &point, const QPixmap &pixmap)
{
    _pixmapPoint = point;
    _pixmap = pixmap;
    updateGrid();
    update();
}

void ImageGridWidget::setPixmapPoint(const QPoint &point)
{
    _pixmapPoint = point;
    updateGrid();
    update();
}

void ImageGridWidget::setCellSize(int size)
{
    _cellSize = size;
    updateGrid();
    update();
}

void ImageGridWidget::setGroupedCellSize(int size)
{
    _groupedCellSize = size;
    updateGrid();
    update();
}

void  ImageGridWidget::setCustomLines(const QList<QLine> &lines)
{
    _customLines = lines;
    update();
}

void ImageGridWidget::setGridSize(const QSize &gridSize)
{
    _gridSize = gridSize;
    updateGrid();
    update();
}

QPixmap ImageGridWidget::cellPixmap(const Cell &point) const
{
    if (point == Cell(-1, -1))
        return QPixmap();
    return _pixmap.copy(QRect(point * _cellSize, QSize(_cellSize, _cellSize)));
}

void ImageGridWidget::setSelectionMode(SelectionMode selectionMode)
{
    _selectionMode = selectionMode;
    setMouseTracking(_selectionMode != NoSelection);
    clearHover();
}

void ImageGridWidget::setSelectedCells(const QList<Cell> &cells)
{
    if (_selectedCells != cells) {
        _selectedCells = cells;
        update();
        Q_EMIT currentSelectionChanged(cells);
    }
}

void ImageGridWidget::clearHover()
{
    Cell newCell(-1, -1);

    if (newCell != _hoverCell) {
        _hoverCell = newCell;
        update();
    }
}

Cell ImageGridWidget::getCell(const QPoint &pos) const
{
    if (_cellSize == 0 || _scaledRatio == 0.0)
        return Cell(-1, -1);

    QPointF cell = QPointF(pos - _scaledGridPoint) / (_scaledRatio * _cellSize);
    Cell ret(qFloor(cell.x()), qFloor(cell.y()));
    return cellIsInRange(ret) ? ret : Cell(-1, -1);
}

bool ImageGridWidget::cellIsInRange(const Cell &point) const
{
    return QRect(QPoint(0, 0), gridSize()).contains(point);
}

QList<QLine> ImageGridWidget::createGrid(const QSize &gridS, int cellSize)
{
    QList<QLine> ret;

    if (cellSize == 0)
        return ret;

    const int lineCountV = gridS.width() + 1,
        lineCountH = gridS.height() + 1;

    for (int i = 0; i < lineCountV; ++i)
        ret.append(QLine(scaledPoint(QPoint(i * cellSize, 0)), scaledPoint(QPoint(i, gridS.height()) * cellSize)));

    for (int i = 0; i < lineCountH; ++i)
        ret.append(QLine(scaledPoint(QPoint(0, i * cellSize)), scaledPoint(QPoint(gridS.width(), i) * cellSize)));

    return ret;
}

void ImageGridWidget::updateGrid()
{
    _gridLines.clear();
    _groupedGridLines.clear();

    if (_cellSize == 0)
        return;

    const QSize gridS = gridSize();

    _scaledRatio = gridS.width() == 0 ? 0.0 : (gridS * _cellSize).scaled(size(), Qt::KeepAspectRatio).width() / double(gridS.width() * _cellSize);

    _gridLines = createGrid(gridS, _cellSize);

    _scaledGridPoint = (QPoint(width(), height()) - scaledPoint(QPoint(gridS.width(), gridS.height()) * _cellSize)) / 2;
    _scaledPixmapPoint = _pixmapPoint == QPoint(-1, -1) ? _scaledGridPoint : scaledPoint(_pixmapPoint);

    if (_groupedCellSize != 0)
        _groupedGridLines = createGrid(gridS * _cellSize / _groupedCellSize, _groupedCellSize);
}

void ImageGridWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    if (isEnabled()) {
        // Background
        p.setBrush(Qt::black);
        p.drawRect(0, 0, width(), height());
        // Grid Background
        p.setBrush(palette().color(QPalette::Dark));
        p.drawRect(QRect(_scaledGridPoint, gridSizePixel() * _scaledRatio));
        // Pixmap
        p.drawPixmap(QRect(_scaledPixmapPoint, _pixmap.size() * _scaledRatio), _pixmap);
        // Grid
        p.setPen(Qt::gray);
        p.translate(_scaledGridPoint);
        p.drawLines(_gridLines);
        p.setPen(QPen(Qt::darkGray, 3, Qt::DashLine));
        p.drawLines(_groupedGridLines);
        p.drawLines(_customLines);

        QColor lightRed(0xff, 0x7f, 0x7f);

        p.setPen(hasFocus() ? Qt::red : lightRed);
        for (const Cell &cell: _selectedCells) {
            drawSelection(p, cell);
        }

        p.setPen(lightRed);
        drawSelection(p, _hoverCell);
    } else {
        QStyleOption opt;
        opt.initFrom(this);
        p.drawPixmap(QRect(_scaledPixmapPoint, _pixmap.size() * _scaledRatio), QWidget::style()->generatedIconPixmap(QIcon::Disabled, _pixmap, &opt));
    }

    QWidget::paintEvent(event);
}

void ImageGridWidget::drawSelection(QPainter &p, QPoint selection)
{
    if (selection == Cell(-1, -1)) {
        return;
    }

    selection *= _cellSize;
    p.drawLine(QLine(scaledPoint(selection), scaledPoint(selection + QPoint(0, _cellSize))));
    p.drawLine(QLine(scaledPoint(selection), scaledPoint(selection + QPoint(_cellSize, 0))));
    p.drawLine(QLine(scaledPoint(selection + QPoint(_cellSize, 0)), scaledPoint(selection + QPoint(_cellSize, _cellSize))));
    p.drawLine(QLine(scaledPoint(selection + QPoint(0, _cellSize)), scaledPoint(selection + QPoint(_cellSize, _cellSize))));
}

void ImageGridWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    if (_selectionMode == NoSelection) {
        return;
    }

    Cell newCell = getCell(event->pos());

    if (_selectionMode == MultiSelection && _startMousePress != Cell(-1, -1) && _startMousePress != newCell) {
        QPoint diff = newCell - _startMousePress;
        QList<Cell> selectedCells;
        for (int yp = 0; yp < std::max(std::abs(diff.y()), 1); ++yp) {
            for (int xp = 0; xp < std::max(std::abs(diff.x()), 1); ++xp) {
                int x = diff.x() >= 0 ? xp : -xp,
                    y = diff.y() >= 0 ? yp : -yp;
                selectedCells.append(_startMousePress + Cell(x, y));
            }
        }

        setSelectedCells(selectedCells);
    } else if (newCell != _hoverCell) {
        _hoverCell = newCell;
        update();

        Q_EMIT highlighted(_hoverCell);
    }
}

void ImageGridWidget::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);

    if (_selectionMode == NoSelection) {
        return;
    }

    clearHover();
}

void ImageGridWidget::mousePressEvent(QMouseEvent *event)
{
    Cell cell = getCell(event->pos());

    if (_selectionMode != NoSelection) {
        setSelectedCell(cell);
        setFocus();
        if (_selectionMode == MultiSelection) {
            _startMousePress = cell;
        }
    }

    Q_EMIT clicked(cell);

    QWidget::mousePressEvent(event);
}

void ImageGridWidget::mouseReleaseEvent(QMouseEvent *event)
{
    _startMousePress = Cell(-1, -1);

    QWidget::mouseReleaseEvent(event);
}

void ImageGridWidget::keyPressEvent(QKeyEvent *event)
{
    if (_selectedCells.isEmpty()) {
        QWidget::keyPressEvent(event);
        return;
    }

    Cell cell = _selectedCells.last();

    switch (event->key()) {
    case Qt::Key_Left:
        cell.setX(cell.x() - 1);
        break;
    case Qt::Key_Right:
        cell.setX(cell.x() + 1);
        break;
    case Qt::Key_Up:
        cell.setY(cell.y() - 1);
        break;
    case Qt::Key_Down:
        cell.setY(cell.y() + 1);
        break;
    }

    if (cellIsInRange(cell)) {
        setSelectedCell(cell);
    } else {
        QWidget::keyPressEvent(event);
    }
}

void ImageGridWidget::resizeEvent(QResizeEvent *event)
{
    updateGrid();
    QWidget::resizeEvent(event);
}

QSize ImageGridWidget::minimumSizeHint() const
{
    return gridSize() * 8;
}

QSize ImageGridWidget::sizeHint() const
{
    return minimumSizeHint();
}

/****************************************************************************/
//    copyright 2009 - 2022  Arzel Jérôme <myst6re@gmail.com>               //
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
#include <TextureFile.h>

TextureFile::TextureFile() :
    _currentColorTable(0)
{
}

TextureFile::TextureFile(const QImage &image) :
    _image(image), _currentColorTable(0)
{
    QList<QRgb> colorTable = _image.colorTable();
    if (!colorTable.empty()) {
        _colorTables.append(colorTable);
    }
}

TextureFile::TextureFile(const QImage &image, const QList< QList<QRgb> > &colorTables) :
    _image(image), _colorTables(colorTables), _currentColorTable(0)
{
}

bool TextureFile::isValid() const
{
    return !_image.isNull();
}

void TextureFile::clear()
{
    _image = QImage();
    _colorTables.clear();
    _currentColorTable = 0;
}

const QImage &TextureFile::image() const
{
    return _image;
}

QImage *TextureFile::imagePtr()
{
    return &_image;
}

bool TextureFile::isPaletted() const
{
    return !_colorTables.isEmpty();
}

const QList< QList<QRgb> > &TextureFile::colorTables() const
{
    return _colorTables;
}

qsizetype TextureFile::currentColorTable() const
{
    return _currentColorTable;
}

QList<QRgb> TextureFile::colorTable(qsizetype id) const
{
    return _colorTables.value(id);
}

void TextureFile::setCurrentColorTable(qsizetype id)
{
    if (id < _colorTables.size() && _currentColorTable != id) {
        _currentColorTable = id;
        _image.setColorTable(_colorTables.at(_currentColorTable));
    }
}

void TextureFile::setColorTable(qsizetype id, const QList<QRgb> &colorTable)
{
    if (id < _colorTables.size()) {
        _colorTables.replace(id, colorTable);
    }
}

qsizetype TextureFile::colorTableCount() const
{
    return _colorTables.size();
}

void TextureFile::debug() const
{
    QImage img(4 * 16, int(4 * 16 * colorTableCount()), QImage::Format_RGB32);

    int y = 0;
    for (const QList<QRgb> &colorTable : _colorTables) {
        int x = 0;
        for (const QRgb &color : colorTable) {
            img.setPixel(x*4+0, y*4+0, color);
            img.setPixel(x*4+0, y*4+1, color);
            img.setPixel(x*4+0, y*4+2, color);
            img.setPixel(x*4+0, y*4+3, color);

            img.setPixel(x*4+1, y*4+0, color);
            img.setPixel(x*4+1, y*4+1, color);
            img.setPixel(x*4+1, y*4+2, color);
            img.setPixel(x*4+1, y*4+3, color);

            img.setPixel(x*4+2, y*4+0, color);
            img.setPixel(x*4+2, y*4+1, color);
            img.setPixel(x*4+2, y*4+2, color);
            img.setPixel(x*4+2, y*4+3, color);

            img.setPixel(x*4+3, y*4+0, color);
            img.setPixel(x*4+3, y*4+1, color);
            img.setPixel(x*4+3, y*4+2, color);
            img.setPixel(x*4+3, y*4+3, color);

            if (x==15) {
                x = 0;
                ++y;
            } else {
                ++x;
            }
        }
        while (y % 16 != 0) {
            img.setPixel(x*4+0, y*4+0, Qt::black);
            img.setPixel(x*4+0, y*4+1, Qt::black);
            img.setPixel(x*4+0, y*4+2, Qt::black);
            img.setPixel(x*4+0, y*4+3, Qt::black);

            img.setPixel(x*4+1, y*4+0, Qt::black);
            img.setPixel(x*4+1, y*4+1, Qt::black);
            img.setPixel(x*4+1, y*4+2, Qt::black);
            img.setPixel(x*4+1, y*4+3, Qt::black);

            img.setPixel(x*4+2, y*4+0, Qt::black);
            img.setPixel(x*4+2, y*4+1, Qt::black);
            img.setPixel(x*4+2, y*4+2, Qt::black);
            img.setPixel(x*4+2, y*4+3, Qt::black);

            img.setPixel(x*4+3, y*4+0, Qt::black);
            img.setPixel(x*4+3, y*4+1, Qt::black);
            img.setPixel(x*4+3, y*4+2, Qt::black);
            img.setPixel(x*4+3, y*4+3, Qt::black);

            if (x==15) {
                x = 0;
                ++y;
            } else {
                ++x;
            }
        }
    }

    img.save("palettes.png");
}

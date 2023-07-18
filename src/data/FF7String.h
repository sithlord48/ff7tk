/****************************************************************************/
//    copyright 2009 - 2022  Arzel Jérôme <myst6re@gmail.com>               //
//              2023 Chris Rizzitello <sithlord48@gmail.com>                //
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
#pragma once

#include <QString>
#include <ff7tkdata_export>

/**
 * @brief The FF7String is a container class for FF7Text. Internally it stores the raw data and if the text is encoded in japanese.
 */
class FF7TKDATA_EXPORT FF7String
{
public:
    /**
     * @brief FF7String Constructs a FF7String with raw data
     * @param data String in FF7Text Format. Will initialize to the language that the FF7Text singleton is using when the string is created
     * @sa setJapanese
     */
    explicit FF7String(QByteArrayView data = QByteArrayView());

    /**
     * @brief FF7String Constructs a FF7String using a String
     * @param text - Input String
     * @param jp - True if input is japanese.
     */
    FF7String(const QString &text, bool jp = false);

    /**
     * @brief data Access the data stored in the FF7String
     * @return raw data stored
     */
    const QByteArray &data() const;

    /**
     * @brief text
     * @return The Decoded FF7Text
     */
    QString text() const;

    /**
     * @brief setText sets the Text of the FF7String
     * @param text - New Text of the string
     * @param jp - True if input is japanese
     */
    void setText(const QString &text, bool jp = false);

    /**
     * @brief contains Check the text for a regular expression
     * @param regExp The expression to check
     * @return True if there was a match
     */
    bool contains(const QRegularExpression &regExp) const;

    /**
     * @brief indexOf Check the text for the location of a regular expression
     * @param regExp -  The expression to check
     * @param from - Starting point of the search
     * @param size - Size of the area to search
     * @return the index
     */
    qsizetype indexOf(const QRegularExpression &regExp, qsizetype from, qsizetype &size) const;

    /**
     * @brief lastIndexOf Check the text for the last location of a regular expression
     * @param regExp -  The expression to check
     * @param from - Starting point of the search
     * @param size - Size of the area to search
     * @return the index
     */
    qsizetype lastIndexOf(const QRegularExpression &regExp, qsizetype &from, qsizetype &size) const;

    inline bool operator ==(const FF7String &t2) const {
        return data() == t2.data();
    }
    inline bool operator !=(const FF7String &t2) const {
        return data() != t2.data();
    }

    /**
     * @brief isJapanese check internal encoding of the text
     * @return True if encoded in japanese
     */
    inline bool isJapanese() const {return _jp;}

    /**
     * @brief setJapanese Sets the intenal encoding of the text.
     * @param inJapanese - Set to True when the internal string is in japanese.
     */
    void setJapanese(bool inJapanese);

private:
    QByteArray _data;
    bool _jp = false;
};

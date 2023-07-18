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

#include <FF7String.h>
#include <FF7Text>

FF7String::FF7String(QByteArrayView data)
{
	_jp = FF7Text::isJapanese();
	_data = data.toByteArray();
	qsizetype index = data.lastIndexOf('\xFF');
	_data = (index != -1 ? data.first(index) : data).toByteArray();
}

FF7String::FF7String(const QString &text, bool jp)
{
	setText(text, jp);
}

const QByteArray &FF7String::data() const
{
	return _data;
}

QString FF7String::text() const
{
	bool langFlip = false;
	if(_jp != FF7Text::isJapanese()) {
		langFlip = true;
		FF7Text::setJapanese(_jp);
	}
	QString tmp = FF7Text::toPC(_data);
	if(langFlip)
		FF7Text::setJapanese(!_jp);
	return tmp;
}

void FF7String::setText(const QString &string, bool jp)
{
	bool langFlip = false;
	_jp = jp;
	if(jp != FF7Text::isJapanese()) {
		langFlip = true;
		FF7Text::setJapanese(jp);
	}
	_data = FF7Text::toFF7(string);
	if(langFlip)
		FF7Text::setJapanese(!jp);
}

bool FF7String::contains(const QRegularExpression &regExp) const
{
	return text().contains(regExp);
}

qsizetype FF7String::indexOf(const QRegularExpression &regExp, qsizetype from, qsizetype &size) const
{
	QString t = text();
	qsizetype offset = from < 0 ? t.size() - from : from;
	QRegularExpressionMatch match = regExp.match(t, offset);
	if (match.hasMatch()) {
		size = match.capturedLength();
	}
	return match.capturedStart();
}

qsizetype FF7String::lastIndexOf(const QRegularExpression &regExp, qsizetype &from, qsizetype &size) const
{
	QString t = text();
	qsizetype offset = from < 0 ? t.size() - from : from;
	qsizetype lastCapturedStart = -1;
	QRegularExpressionMatchIterator it = regExp.globalMatch(t);
	while (it.hasNext()) {
		QRegularExpressionMatch match = it.next();
		if (match.capturedEnd() >= offset) {
			break;
		}
		qsizetype capturedStart = match.capturedStart();
		if (capturedStart > lastCapturedStart) {
			lastCapturedStart = capturedStart;
			from = capturedStart - t.size();
			size = match.capturedLength();
		}
	}

	return lastCapturedStart;
}

void FF7String::setJapanese(bool inJapanese)
{
	if(_jp == inJapanese)
		return;
	_jp = inJapanese;
}

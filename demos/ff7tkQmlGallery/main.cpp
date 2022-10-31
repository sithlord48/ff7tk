/****************************************************************************/
//    copyright 2018 - 2022 Chris Rizzitello <sithlord48@gmail.com>         //
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
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <FF7Text>
#include <FF7Item>
#include <FF7Materia>
#include <ff7tkInfo>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<FF7Text>("org.ff7tk", 1, 0, "FF7Text", [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject * {
        return FF7Text::qmlSingletonRegister(engine, jsEngine);
    });

    qmlRegisterSingletonType<FF7Item>("org.ff7tk", 1, 0, "FF7Item", [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject * {
        return FF7Item::qmlSingletonRegister(engine, jsEngine);
    });

    qmlRegisterSingletonType<ff7tkInfo>("org.ff7tk", 1, 0, "FF7Info", [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject * {
        return ff7tkInfo::qmlSingletonRegister(engine, jsEngine);
    });

    qmlRegisterSingletonType<FF7Materia>("org.ff7tk", 1, 0, "FF7Materia", [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject * {
        return FF7Materia::qmlSingletonRegister(engine, jsEngine);
    });

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}

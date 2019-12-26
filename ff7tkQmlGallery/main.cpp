#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../src/data/FF7Text.h"
#include "../src/data/FF7Item.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);



    qmlRegisterSingletonType<FF7TEXT>("org.ff7tk", 1, 0, "FF7Text", [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject * {
        return FF7TEXT::instance()->qmlSingletonRegister(engine, jsEngine);
    });

    qmlRegisterSingletonType<FF7Item>("org.ff7tk", 1, 0, "FF7Item", [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject * {
        return FF7Item::instance()->qmlSingletonRegister(engine, jsEngine);
    });

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../data/FF7Text.h"
#include "../data/FF7Item.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    qmlRegisterType<FF7TEXT>("FF7Text", 1, 0, "FF7Text");
    qmlRegisterType<FF7Item>("FF7Item", 1, 0, "FF7Item");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

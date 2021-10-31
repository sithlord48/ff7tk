#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <FF7Text.h>
#include <FF7Item.h>
#include <ff7tkAbout.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
#if (QT_VERSION_MAJOR < 6)
        QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif

        qmlRegisterSingletonType<FF7TEXT>("org.ff7tk", 1, 0, "FF7Text", [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject * {
        return FF7TEXT::instance()->qmlSingletonRegister(engine, jsEngine);
    });

    qmlRegisterSingletonType<FF7Item>("org.ff7tk", 1, 0, "FF7Item", [](QQmlEngine *engine, QJSEngine *jsEngine) -> QObject * {
        return FF7Item::instance()->qmlSingletonRegister(engine, jsEngine);
    });

    QString versionString = QStringLiteral("%1-%2").arg(ff7tk_version().append(ff7tk_revision()), ff7tk_qt_version());
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("ff7tkVersion", versionString);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include "appmanager.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    AppManager appManager;

    qmlRegisterSingletonType<AppManager>("AppManager", 1, 0, "AppManager",
        [&](QQmlEngine*, QJSEngine*) -> QObject* {
            return &appManager;
        }
    );

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("CuteSockets", "Main");

    return app.exec();
}

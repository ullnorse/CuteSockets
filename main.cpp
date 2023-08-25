#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include "app.h"

int main(int argc, char *argv[])
{
    QGuiApplication qtGuiApp(argc, argv);

    App app;
    app.init();

    return qtGuiApp.exec();
}

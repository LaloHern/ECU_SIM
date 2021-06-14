#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "gpiocontroller.h"
#include "mcp_can_rpi/mcp_can_rpi.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;

    GPIOController gpiosController;

    view.engine()->rootContext()->setContextProperty("gpiosController", &gpiosController);

    view.setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    view.show();

    return app.exec();
}

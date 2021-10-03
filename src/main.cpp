#include "mainwindow.h"
#include <QApplication>
#include "videoplayer.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDir>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow main_window;

    QCoreApplication::setApplicationName("Video Widget Example");
    QCoreApplication::setOrganizationName("QtProject");
    QGuiApplication::setApplicationDisplayName(QCoreApplication::applicationName());
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    main_window.show();

    return app.exec();
}

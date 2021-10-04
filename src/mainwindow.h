#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDir>
#include <QDebug>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "chart/chart.h"
#include "chart/chartview.h"
#include "video/videoplayer.h"
#include "plot/qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionVideo_toggled(bool arg1);

    void on_actionLog_toggled(bool arg1);

    void on_actionCurve_toggled(bool arg1);

    void on_actionOpen_triggered(bool checked);

    void on_actionSave_layout_triggered();

private:
    Ui::MainWindow *ui;

    VideoPlayer *player = nullptr;

    QDockWidget *video_dockWidget = nullptr;

    QByteArray fileRawData;
    Chart *chart=nullptr;

private:
    void video_dockWiget_Init(void);
    void video_dockWiget_Close(void);



};
#endif // MAINWINDOW_H

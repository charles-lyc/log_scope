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
#include <QTimerEvent>
#include "protocal/package.h"
#include "protocal/frame.h"

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

    void on_actionOpen_triggered();

    void on_actionSave_layout_triggered();

    void on_dialData_valueChanged(int value);

    void on_dialVideo_valueChanged(int value);
    void on_pushButtonLock_clicked();

    void on_pushButtonPlay_clicked();

private:
    Ui::MainWindow *ui;

    VideoPlayer *player = nullptr;

    QDockWidget *video_dockWidget = nullptr;

    QByteArray fileRawData;
    Chart *chart=nullptr;
    ChartView *chartView;

    int videoStart;
    int dataStart;
    int dataStartBase;

    int timerID;
    QLineSeries *timelineSeries;
    int tick = 0;

    QVector<Frame_t> frames;

private:
    void video_dockWiget_Init(void);
    void video_dockWiget_Close(void);
    void timerEvent(QTimerEvent * event);


};
#endif // MAINWINDOW_H

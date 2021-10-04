#include "mainwindow.h"
#include "ui_mainwindow.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings;
    this->restoreState(settings.value("DOCK_LOCATIONS").toByteArray());

//    connect(ui->menubar, SIGNAL(triggered(QAction*)), this, SLOT(handleAction(QAction*)), Qt::UniqueConnection);
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(on_actionOpen_triggered()), Qt::UniqueConnection);
    connect(ui->actionVideo,SIGNAL(toggled(bool)),this,SLOT(on_actionVideo_toggled(bool)), Qt::UniqueConnection);
    connect(ui->actionCurve,SIGNAL(toggled(bool)),this,SLOT(on_actionLog_toggled(bool)), Qt::UniqueConnection);
    connect(ui->actionLog,SIGNAL(toggled(bool)),this,SLOT(on_actionCurve_toggled(bool)), Qt::UniqueConnection);


    // 把MainWindow的中间窗口去除，这时整个MainWindow只有Dock组成
    QWidget* center = takeCentralWidget();
        if(center)
            delete center;


#if 0
    // test  https://www.qcustomplot.com/index.php/tutorials/basicplotting
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plotWidget->xAxis->setLabel("x");
    ui->plotWidget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->plotWidget->xAxis->setRange(-1, 1);
    ui->plotWidget->yAxis->setRange(0, 1);
    ui->plotWidget->replot();
#endif

    player = new VideoPlayer();
    ui->video_dockWidget->setWidget(player);
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(player);
    player->resize(availableGeometry.width() / 6, availableGeometry.height() / 4);
    player->show();

    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        p.ry() += QRandomGenerator::global()->bounded(20);
        *series << p;
    }
    chart = new Chart();
    chart->addSeries(series);
    chart->setTitle("Zoom in/out example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();
    ChartView *chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->curve_dockWidget->setWidget(chartView);


    QTableView *tableView = new QTableView;
    ui->sheet_dockWidget->setWidget(tableView);
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"ID", "User Name", "City", "Classify", "Score", "Sign"});
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i = 0; i < 10; i++) {
        /* 加载第一列(ID)数据 */
        model->setItem(i, 0, new QStandardItem(QString("100%1").arg(i)));
        /* 加载第二列(User Name)数据 */
        model->setItem(i, 1, new QStandardItem(QString("User%1").arg(i)));
        /* 加载第三列(City)数据 */
        model->setItem(i, 2, new QStandardItem("Shanghai"));
        /* 加载第四列(Classify)数据 */
        model->setItem(i, 3, new QStandardItem("Engineer"));
        /* 加载第五列(Score)数据 */
        model->setItem(i, 4, new QStandardItem("80"));
        /* 加载第六列(Sign)数据 */
        model->setItem(i, 5, new QStandardItem("Hello world!"));
    }
    tableView->setModel(model);
    tableView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

#if 0
void MainWindow::video_dockWiget_Init(void)
{
    if (video_dockWidget == nullptr)
    {
        video_dockWidget = new QDockWidget();

        this->addDockWidget(Qt::DockWidgetArea::AllDockWidgetAreas,
                            video_dockWidget);

        video_dockWidget->

//        video_dockWidget->setParent(this);
        video_dockWidget->setWidget(player);
//        video_dockWidget->show();
    }

    if (player == nullptr)
    {
        player = new VideoPlayer();
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(player);
        player->resize(availableGeometry.width() / 6, availableGeometry.height() / 4);
        player->show();
    }
}

void MainWindow::video_dockWiget_Close(void)
{
    if (video_dockWidget != nullptr)
    {
        video_dockWidget->close();
        delete video_dockWidget;
        video_dockWidget = nullptr;
    }

    if (player != nullptr)
    {
        player->close();
        delete player;
        player = nullptr;
    }
}

#endif

void MainWindow::on_actionVideo_toggled(bool arg1)
{
//    if (arg1)
//        video_dockWiget_Init();
//    else
//        video_dockWiget_Close();
}

void MainWindow::on_actionLog_toggled(bool arg1)
{

}

void MainWindow::on_actionCurve_toggled(bool arg1)
{

}

void MainWindow::on_actionSave_layout_triggered()
{
    QSettings settings;
    settings.setValue("DOCK_LOCATIONS",this->saveState());

}

void MainWindow::on_dialVideo_valueChanged(int value)
{
    ui->labelSpinVideo->setText("Video start time adjust:\n" + QString::number(value) + "ms\n" + "(" + QString::number(value / 60000) + "min)");

    player->setPosition(value);
}

void MainWindow::on_dialData_valueChanged(int value)
{
    ui->labelSpinData->setText("Video start time adjust:\n" + QString::number(value) + "ms\n" + "(" + QString::number(value / 60000) + "min)");

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                    this, tr("open image file"),
                    "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));

    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    fileRawData = file.readAll();
    file.close();
}

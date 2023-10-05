#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QRandomGenerator>                     // 用于产生随机数
#include <QVector>
#include <QProcess>
#include <_timer.h>
// #include "qcustomplot.h"

float CPUTimer::time = 0.0f;

// 构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗口图标
    this->setWindowIcon(QIcon(":/icons/images/ChartTitle.png"));
    // 设置窗口标题
    this->setWindowTitle("Chart");

    this->setCentralWidget(ui->splitter);

#if 0
    // 读取.qss文件，设置样式表
    QFile qssFile(":/qss/styleSheet.qss");
    if(qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = qssFile.readAll();
        qApp->setStyleSheet(styleSheet);                // 只有这种方法才能使得样式表生效
    }
    else
        qDebug() << "qss文件打开失败";
    qssFile.close();
#endif

//    ui->customwidget->addChartView(0, 1);
//    ui->customwidget->addChartView(1, 1);
//    ui->customwidget->addChartView(2, 2);
//    for(int i = 0; i < ui->customwidget->getChartView2DIndex().size(); ++i) {
//        qDebug() << "(" << ui->customwidget->getChartView2DIndex()[i].row << ", " << ui->customwidget->getChartView2DIndex()[i].col << ")";
//    }
//    ui->widget->removeChartView(3);
//    for(int i = 0; i < ui->widget->getChartView2DIndex().size(); ++i) {
//        qDebug() << "(" << ui->widget->getChartView2DIndex()[i].row << ", " << ui->widget->getChartView2DIndex()[i].col << ")";
//    }
//    ui->widget->removeChartView(1, 1);
//    for(int i = 0; i < ui->widget->getChartView2DIndex().size(); ++i) {
//        qDebug() << "(" << ui->widget->getChartView2DIndex()[i].row << ", " << ui->widget->getChartView2DIndex()[i].col << ")";
//    }
    // ui->customwidget->addChartView(4, 2, 2);

    // 添加自定义QChartView
    ui->customwidget->addChartView(0, 0);
    customChartView* chartView = ui->customwidget->getChartView();
    if(!chartView) {
        qDebug() << "error";
        exit(-1);
    }
    this->chart = new customChart;
    this->chart->setBackgroundBrush(Qt::lightGray);        // 设置图表背景颜色
    chartView->setChart(this->chart);                      // 为QChartView设置QChart
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->setDragMode(QGraphicsView::ScrollHandDrag);

    // this->chart->setTitle("匹配滤波");                      // 设置标题
    this->chart->setMargins(QMargins(0, 0, 0, 0));         // 设置图表的内边界
    this->chart->setBackgroundRoundness(20);               // 设置背景方框圆角半径

    this->chart->series[0]->setName("  series 0");
    this->chart->series[0]->setUseOpenGL(true);            // 使用OpenGL加速

    this->chart->axisX->setRange(0, 10);                           // 设置坐标轴范围
    this->chart->axisX->setLabelFormat("%.2f");                      // 设置标签格式
    this->chart->axisX->setTickCount(7);                           // 设置主刻度个数
    this->chart->axisX->setMinorTickCount(2);                      // 设置次刻度个数
    // this->chart->axisX->setTitleText("time/s");                    // 设置标题

    this->chart->axisY->setRange(0, 10);                           // 设置坐标轴范围
    this->chart->axisY->setLabelFormat("%.2f");                      // 设置标签格式
    this->chart->axisY->setTickCount(8);                           // 设置主刻度个数
    this->chart->axisY->setMinorTickCount(2);                      // 设置次刻度个数
    // this->chart->axisY->setTitleText("信号幅度/dB");                     // 设置标题

    QVector<QPointF> data;
    for(int i = 0; i < 6000; ++i) {
        //随机 0- 1.0 之间的 double 数 不包括1.0
        double number = QRandomGenerator::global()->bounded(0.5);
        data.append(QPointF(i, number));
    }
    this->chart->series[0]->replace(data);
    this->chart->axisX->setRange(0, 5999);
    this->chart->axisY->setRange(0, 1.0);
}

// 析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

// 槽函数
void MainWindow::on_pushButton_del_clicked()
{
    int row = ui->spinBox_row->text().toInt();
    int col = ui->spinBox_col->text().toInt();
    ui->customwidget->removeChartView(row, col);
}

// 槽函数
void MainWindow::on_pushButton_add_clicked()
{
    int row = ui->spinBox_row->text().toInt();
    // int rowSpan = ui->spinBox_rowSpan->text().toInt();
    int col = ui->spinBox_col->text().toInt();
    // int colSpan = ui->spinBox_colSpan->text().toInt();
    ui->customwidget->addChartView(row, col);
}


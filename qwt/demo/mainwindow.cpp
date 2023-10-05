#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPen>
#include <QtMath>

// 构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(QSize(800, 600));          // 设置窗口大小
    this->setWindowTitle(QString("Qwt测试程序").toUtf8());          // 设置窗口标题

    this->qwtInit();                        // 初始化qwt
    this->qwtDataInit();                    // qwt数据初始化
}

// 析构函数
MainWindow::~MainWindow()
{
    delete ui;
#if 0  // 会发生内存泄露，但在该析构函数被调用执行下面的代码时，程序会崩溃，具体原因尚未得知。应该研究一下Qt的内存泄露问题！
    if(this->canvas)
        delete this->canvas;
    if(this->grid)
        delete this->grid;
    if(this->magnifier)
        delete this->magnifier;
    if(this->legend)
        delete this->legend;
    if(this->panner)
        delete this->panner;
    if(this->zoomer)
        delete this->zoomer;
    for(int i = 0; i < this->curve.size(); ++i) {
        QwtPlotCurve* obj = this->curve.takeAt(i);
    }
#endif
}

// 初始化qwt
void MainWindow::qwtInit()
{
    /*--------------------画布--------------------*/
    // this->canvas = new QwtPlotCanvas();       // 创建画布
    this->canvas = new QwtPlotCanvas();
    this->canvas->setPalette(Qt::white);      // 设置画板
    this->canvas->setBorderRadius(10);        // 设置画布四个角的半径
    ui->plot->setCanvas(this->canvas);        // 绑定画布
    ui->plot->plotLayout()->setAlignCanvasToScales(true);
    /*--------------------画布--------------------*/

    /*--------------------qwtplot--------------------*/
    ui->plot->setTitle("qwt demo");         // 设置qwt标题
    ui->plot->setAxisTitle(QwtPlot::xBottom, QString("x轴").toUtf8());   // 设置qwt横轴名称
    ui->plot->setAxisScale(QwtPlot::xBottom, 0.0, 10.0, 1);              // 设置qwt横轴范围
    ui->plot->setAxisAutoScale(QwtPlot::xBottom, true);                  // 设置qwt横轴自适应
    ui->plot->setAxisTitle(QwtPlot::yLeft, QString("y轴").toUtf8());     // 设置qwt纵轴名称
    ui->plot->setAxisScale(QwtPlot::yLeft, 0.0, 10.0, 1);                // 设置qwt纵轴范围
    ui->plot->setAxisAutoScale(QwtPlot::yLeft, true);                    // 设置qwt纵轴自适应
    /*--------------------qwtplot--------------------*/

    /*--------------------网格--------------------*/
    this->grid = new QwtPlotGrid;           // 创建网格
    this->grid->setPen(Qt::black, 1, Qt::DashDotDotLine);
    this->grid->attach(ui->plot);
    /*--------------------网格--------------------*/

    /*--------------------图例--------------------*/
    this->legend = new QwtLegend;                                        // 创建图例
    this->legend->setDefaultItemMode(QwtLegendData::Checkable);          // 设置图例可点击
    ui->plot->insertLegend(this->legend);                                // 插入图例
    /*--------------------图例--------------------*/

#if 0
    // 有bug，当坐标轴的范围设置超过10时，生成的窗口会特别大
    this->zoomer = new QwtPlotZoomer(this->canvas);
    // this->zoomer->setRubberBandPen(QPen(Qt::blue));                      // 设置方框的颜色
    // this->zoomer->setMousePattern(QwtEventPattern::MouseSelect3, Qt::RightButton, Qt::ControlModifier);
#endif
    // 移动图形，默认为鼠标左键(可通过相应的函数更改)
    this->panner = new customQwtPlotPanner(this->canvas);

    // 使用鼠标滑轮对图形进行放大，上滑：放大；下滑：缩小
    this->magnifier = new customQwtPlotMagnifier(this->canvas);
}

// qwt数据初始化
void MainWindow::qwtDataInit()
{
    this->data.resize(2);                                                // 实现确定要添加多少条曲线

    for(int i = 0; i < this->data.size(); ++i) {
        this->curve.append(new QwtPlotCurve);                            // 向QVector中添加创建的曲线对象
    }

    this->curve[0]->setTitle("curve 0");                                 // 设置曲线名称
    this->curve[0]->setPen(Qt::blue, 2);                                 // 设置曲线颜色及线宽
    this->curve[1]->setTitle("curve 1");
    this->curve[1]->setPen(Qt::red, 2);

    for(double i = 0.1; i < 100.0; i += 0.1) {
        this->data[0].append(qLn(i));
        this->data[1].append(-qLn(i));
    }

    this->curve[0]->setSamples(this->data[0]);
    this->curve[1]->setSamples(this->data[1]);

    for(int i = 0; i < this->curve.size(); ++i) {
        this->curve[i]->attach(ui->plot);                                // 绑定曲线
    }
}


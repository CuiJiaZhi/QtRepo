#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "qwt_plot_canvas.h"        // 画布
#include "qwt_plot_curve.h"         // 曲线
#include "qwt_plot_grid.h"          // 网格
#include "qwt_plot_layout.h"        // 布局
#include "qwt_legend.h"             // 图例

#include "qwt_plot_zoomer.h"
//#include "qwt_plot_panner.h"        // 平移
//#include "qwt_plot_magnifier.h"     // 放大

#include "customqwtplotmagnifier.h"
#include "customqwtplotpanner.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void qwtInit();                // 初始化qwt
    void qwtDataInit();            // qwt数据初始化

private slots:

protected:

signals:

private:
    Ui::MainWindow *ui;

    QwtPlotCanvas* canvas;          // 画布
    QVector<QwtPlotCurve*> curve;   // 曲线
    QwtPlotGrid* grid;              // 网格
    QwtLegend* legend;              // 图例

    QwtPlotZoomer* zoomer;
    customQwtPlotPanner* panner;
    // QwtPlotPanner* panner;
    // QwtPlotMagnifier* magnifier;
    customQwtPlotMagnifier* magnifier;

    QVector<QVector<double>> data;  // 数据
};
#endif // MAINWINDOW_H

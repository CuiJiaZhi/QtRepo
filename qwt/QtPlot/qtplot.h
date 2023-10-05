#ifndef QTPLOT_H
#define QTPLOT_H

#include <QWidget>
#include "QtPlot_global.h"

#include "qwt_plot_curve.h"             // 曲线
#include "qwt_plot_grid.h"              // 网格

namespace Ui {
class QtPlot;
}

class QTPLOT_EXPORT QtPlot : public QWidget
{
    Q_OBJECT

public:
    explicit QtPlot(QWidget *parent = nullptr);
    ~QtPlot();

private:
    Ui::QtPlot *ui;

    QwtPlotCurve* curve;
    QwtPlotGrid* grid;
};

#endif // QTPLOT_H

#ifndef CUSTOMQWTPLOTPANNER_H
#define CUSTOMQWTPLOTPANNER_H

#include <QObject>
#include "qwt_plot_panner.h"

class QWT_EXPORT customQwtPlotPanner : public QwtPlotPanner
{
    Q_OBJECT

public:
    // 构造函数
    explicit customQwtPlotPanner(QWidget* canvas = nullptr);
    // 析构函数
    ~customQwtPlotPanner();

private slots:
    void do_UpdateGrid(int dx, int dy);                 // 自定义槽函数

private:
    class PrivateData;
    PrivateData* m_data;
};

#endif // CUSTOMQWTPLOTPANNER_H

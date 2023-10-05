#ifndef CUSTOMQWTPLOTPANNER_H
#define CUSTOMQWTPLOTPANNER_H

#include "qwt_plot_panner.h"

class customQwtPlotPanner : public QwtPlotPanner
{
    Q_OBJECT

public:
    // 构造函数
    explicit customQwtPlotPanner(QWidget* canvas = nullptr);
    // 析构函数
    virtual ~customQwtPlotPanner();

protected:
    // 重写鼠标按压事件
    virtual void widgetMousePressEvent(QMouseEvent* event) override;
    // 重写鼠标释放事件
    virtual void widgetMouseReleaseEvent(QMouseEvent* event) override;
    // 重写鼠标滑轮事件
    virtual void widgetMouseMoveEvent(QMouseEvent* event) override;
    // 重写窗口绘制事件
    virtual void paintEvent(QPaintEvent* event) override;

    virtual void moveCanvas(int dx, int dy) override;      // 平移坐标轴的函数

public slots:
#if 1
    void do_UpdateGrid(int dx, int dy);                 // 自定义槽函数
#endif

private:
#ifndef QT_NO_CURSOR
    void showCursor(bool on);
#endif

    class PrivateData;
    PrivateData* m_data;
};

#endif // CUSTOMQWTPLOTPANNER_H

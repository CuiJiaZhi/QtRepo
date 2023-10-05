#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QChartView>       // 视图类
#include <QChart>           // 图形项类
#include <QLineSeries>      // 序列类
#include <QValueAxis>       // 坐标轴
#include <QEvent>
#include <QMouseEvent>

QT_CHARTS_USE_NAMESPACE     // using namespace QT_CHARTS_NAMESPACE

// 自定义ChartView类
class customChartView : public QChartView
{
    Q_OBJECT
public:
    customChartView(QWidget *parent = nullptr);         // 构造函数
    ~customChartView();                                 // 析构函数
    void setCustomZoom(bool customZoom);                // 设置是否定义放大

protected:
    void mousePressEvent(QMouseEvent* event) override;           // 鼠标左键按下事件
    void mouseReleaseEvent(QMouseEvent* event) override;         // 鼠标左键释放事件
    void mouseMoveEvent(QMouseEvent* event) override;            // 鼠标移动事件
    void wheelEvent(QWheelEvent* event) override;                // 鼠标滚轮事件

private slots:

signals:
    void mouseMoved(QPointF point);                      // 自定义鼠标移动信号

private:
    QPointF pressPoint;                                  // 鼠标按下时的视图坐标
    QPointF releasePoint;                                // 鼠标释放时的视图坐标
    QPointF currentPoint;                                // 鼠标当前的视图坐标
    bool customZoom = false;                             // 是否自定义放大
    bool tracking = false;                               // 是否在鼠标按下时实时获取轨迹坐标，鼠标跟踪
};

#endif // CUSTOMCHARTVIEW_H

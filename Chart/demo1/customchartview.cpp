#include "customchartview.h"

// 构造函数
customChartView::customChartView(QWidget *parent)
    : QChartView(parent)
{
    this->setMouseTracking(true);                   // 实时产生mouseMoveEvent事件
    this->setDragMode(QGraphicsView::NoDrag);       // 设置鼠标拖动模式，不影响QChartView的自动放大功能
    this->setRubberBand(QChartView::NoRubberBand);  // 设置自动放大模式
}

// 析构函数
customChartView::~customChartView() {}

// 设置是否自动放大
void customChartView::setCustomZoom(bool automaticZoom)
{
    this->customZoom = automaticZoom;
}

// 鼠标按下事件
void customChartView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        this->pressPoint = event->pos();                  // 获取鼠标按下时的视图坐标
        this->tracking = true;
    }
    QChartView::mousePressEvent(event);                   // 父类继续处理事件
}

// 鼠标释放事件
void customChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        this->releasePoint = event->pos();             // 获取释放时的视图坐标
        if(this->customZoom &&
           this->dragMode() == QGraphicsView::RubberBandDrag) {     // 鼠标光标变成十字形
            QRectF rectf;
            rectf.setTopLeft(this->pressPoint);
            rectf.setBottomRight(this->releasePoint);
            this->chart()->zoomIn(rectf);              // 按照矩形放大
        }
        this->tracking = false;
    }
    QChartView::mouseReleaseEvent(event);              // 父类继续处理事件
}

// 鼠标移动事件
void customChartView::mouseMoveEvent(QMouseEvent *event)
{
    this->currentPoint = event->pos();                    // 获取鼠标当前的视图坐标
    emit mouseMoved(this->currentPoint);                  // 发射自定义信号
    if(this->tracking) {
        QPointF lastPoint = this->pressPoint;
        if((this->dragMode() == QGraphicsView::ScrollHandDrag) &&          // 鼠标光标变成手形
            (this->rubberBand() == QChartView::NoRubberBand)) {            // 不自动放大
            this->chart()->scroll((lastPoint.x() - this->currentPoint.x()) / 20.0,      // 除数用于调整灵敏度
                                  (this->currentPoint.y() - lastPoint.y()) / 20.0);     // 除数用于调整灵敏度
        }
    }

    QChartView::mouseMoveEvent(event);                   // 父类继续处理事件
}

// 鼠标滚轮事件
void customChartView::wheelEvent(QWheelEvent *event)
{
    QPoint numDegree = event->angleDelta() / 8; // event->angleDelta()获取滚轮的相对的滚动量，除以8表示角度，再除以15表示步数
    if(numDegree.isNull())
        return;
    QPoint numStep = numDegree / 15;            // 步数
    int stepY = numStep.y();                    // 垂直方向上滚轮的滚动步数
    if(stepY > 0) {                             // 大于0，向前滚动，放大
        this->chart()->zoom(1.1);               // 大于1，放大
    }
    else {
        this->chart()->zoom(0.9);               // 0~1，缩小
    }

    event->accept();
}

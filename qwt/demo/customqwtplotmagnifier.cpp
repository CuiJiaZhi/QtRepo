#include "customqwtplotmagnifier.h"

#include "qwt_plot.h"
#include "qwt_scale_map.h"

#include <QWheelEvent>

class customQwtPlotMagnifier::PrivateData
{
public:
    // 构造函数
    PrivateData()
        : wheelFactor(0.9),
        wheelModifiers(Qt::NoModifier)
    {
    }

    // 滑轮放缩系数
    double wheelFactor;
    //
    Qt::KeyboardModifiers wheelModifiers;
};

// 构造函数
customQwtPlotMagnifier::customQwtPlotMagnifier(QWidget* canvas)
    : QwtPlotMagnifier(canvas)
{
    this->m_data = new PrivateData();
}

// 析构函数
customQwtPlotMagnifier::~customQwtPlotMagnifier()
{
    delete this->m_data;
}

// 设置滑轮放缩系数
void customQwtPlotMagnifier::setWheelFactor(double wheelFactor)
{
    this->m_data->wheelFactor = wheelFactor;
}

// 获取滑轮放缩系数
double customQwtPlotMagnifier::wheelFactor() const
{
    return this->m_data->wheelFactor;
}

void customQwtPlotMagnifier::setWheelModifiers(Qt::KeyboardModifiers modifiers)
{
    this->m_data->wheelModifiers = modifiers;
}

Qt::KeyboardModifiers customQwtPlotMagnifier::wheelModifiers() const
{
    return this->m_data->wheelModifiers;
}

// 重写rescale()函数
void customQwtPlotMagnifier::rescale(double factor)
{
    QwtPlot* plt = this->plot();                // 获取QwtPlot指针对象
    if(plt == NULL)
        return;

    factor = qAbs(factor);                      // 缩放系数去绝对值
    if(factor == 1.0 || factor == 0.0)
        return;

    bool doReplot = false;

    const bool autoReplot = plt->autoReplot();
    plt->setAutoReplot(false);

    /*--------------------添加--------------------*/
    QPoint cursorPos = canvas()->mapFromGlobal(canvas()->cursor().pos());       // 获取当前鼠标的坐标
    /*--------------------添加--------------------*/

    // QwtAxis::AxisPositions表示Number of axis positions，即坐标轴的数量，4个
    // 0: YLeft; 1: YRight; 2: XBottom; 3: XTop
    for(int axisPos = 0; axisPos < QwtAxis::AxisPositions; axisPos++)
    {
        // typedef int QwtAxisId
        const QwtAxisId axisId(axisPos);

        if(isAxisEnabled(axisId)) {
            const QwtScaleMap scaleMap = plt->canvasMap(axisId);

            double v1 = scaleMap.s1();
            double v2 = scaleMap.s2();

            if(scaleMap.transformation()) {
                // the coordinate system of the paint device is always linear
                v1 = scaleMap.transform(v1);      // scaleMap.p1()
                v2 = scaleMap.transform(v2);      // scaleMap.p2()
            }

            /*--------------------添加--------------------*/
            const double posInAxis = (axisId / 2 ? cursorPos.x() : cursorPos.y());
            const double lenthInAxis = (axisId / 2 ? canvas()->rect().width() : canvas()->rect().height());
            double posRadio = posInAxis / lenthInAxis;              // 获取当前鼠标在X/Y轴的位置（百分比）
            // plot的Y轴方向与鼠标Y轴方向不同
            if(axisId / 2 == 0) {
                posRadio = 1 - posRadio;
            }
            double center = posRadio * (v2 - v1) + v1;              // 将百分比转化为v1到v2的点
            v1 = center - (center - v1) * factor;                   // 将鼠标中心分成两部分，分别进行缩放
            v2 = center + (v2 - center) * factor;
            /*--------------------添加--------------------*/

            if(scaleMap.transformation()) {
                v1 = scaleMap.invTransform(v1);
                v2 = scaleMap.invTransform(v2);
            }

            plt->setAxisScale(axisId, v1, v2);                      // 设置指定坐标轴的范围
            doReplot = true;
        }
    }

    plt->setAutoReplot(autoReplot);

    if(doReplot)
        plt->replot();
}

// 重写widgetWheelEvent()函数
void customQwtPlotMagnifier::widgetWheelEvent(QWheelEvent* event)
{
    if(event->modifiers() != this->m_data->wheelModifiers) {
        return;
    }

    if(this->m_data->wheelFactor != 0.0)
    {
#if QT_VERSION < 0x050000
        const int wheelDelta = wheelEvent->delta();
#else
        const QPoint delta = event->angleDelta();
        // 鼠标滑轮前滑，wheelDelta = 120; 鼠标滑轮后滑，wheelDelta = -120
        const int wheelDelta = (qAbs(delta.x()) > qAbs(delta.y())) ? delta.x() : delta.y();
#endif
        double factor = std::pow(this->m_data->wheelFactor, qAbs(wheelDelta / 120.0));

        if(wheelDelta < 0)                      // 鼠标滑轮前滑，放大; 鼠标滑轮后滑，缩小
            factor = 1 / factor;

        this->rescale(factor);
    }
}

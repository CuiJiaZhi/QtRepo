#ifndef CUSTOMQWTPLOTMAGNIFIER_H
#define CUSTOMQWTPLOTMAGNIFIER_H

#include "qwt_plot_magnifier.h"

// 自定义QwtPlotMagnifier类，实现使用QwtPlotMagnifier通过滚轮缩放时，缩放中心是鼠标停留的地方
class customQwtPlotMagnifier : public QwtPlotMagnifier
{
    Q_OBJECT

public:
    // 构造函数(显式)
    explicit customQwtPlotMagnifier(QWidget* canvas = nullptr);
    // 析构函数
    virtual ~customQwtPlotMagnifier();
    // 设置滑轮放缩系数
    void setWheelFactor(double wheelFactor);
    // 获取滑轮放缩系数
    double wheelFactor() const;

    void setWheelModifiers(Qt::KeyboardModifiers modifiers);
    Qt::KeyboardModifiers wheelModifiers() const;
protected:
    // 重写rescale()函数
    virtual void rescale(double factor) override;
    // 重写widgetWheelEvent()函数
    virtual void widgetWheelEvent(QWheelEvent* event) override;

private:
    class PrivateData;
    PrivateData* m_data;
};

#endif // CUSTOMQWTPLOTMAGNIFIER_H

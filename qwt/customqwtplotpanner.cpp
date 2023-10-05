#include "customqwtplotpanner.h"
#include "qwt_plot.h"
#include "qwt_scale_map.h"

#include <QMouseEvent>
#include <QDebug>

class customQwtPlotPanner::PrivateData
{
public:
    // 构造函数
    PrivateData() :
    #ifndef QT_NO_CURSOR
        cursor(NULL),
        restoreCursor(NULL),
        hasCursor(false)
    #endif
    {
    }
    // 析构函数
    ~PrivateData()
    {
    #ifndef QT_NO_CURSOR
        delete cursor;
        delete restoreCursor;
    #endif
    }

    // 成员变量
    QPoint initialPos;
    QPoint pos;

#ifndef QT_NO_CURSOR
    QCursor* cursor;
    QCursor* restoreCursor;
    bool hasCursor;
#endif
};

// 构造函数
customQwtPlotPanner::customQwtPlotPanner(QWidget* canvas)
    : QwtPlotPanner(canvas)
{
    this->m_data = new PrivateData();

    // qobject_cast<QwtPlotPanner*>(this)
    QObject::connect(this, SIGNAL(moved(int, int)), SLOT(do_UpdateGrid(int, int)));
}

// 析构函数
customQwtPlotPanner::~customQwtPlotPanner()
{
    delete this->m_data;
}

// 自定义槽函数
void customQwtPlotPanner::do_UpdateGrid(int dx, int dy)
{
    (void)(dx); (void)(dy);
    qDebug() << "1\n";
#if 0
    if(dx == 0 && dy == 0)
        return;

    QwtPlot* plot = this->plot();                                   // 获取QwtPlot指针对象
    if(plot == nullptr)
        return;

    const bool doAutoReplot = plot->autoReplot();                   // 获取当前的自动刷新设置
    plot->setAutoReplot( false );                                   // 设置不会自动刷新，以便在修改坐标轴范围时避免重绘

    // 遍历四个坐标轴
    for ( int axisPos = 0; axisPos < QwtAxis::AxisPositions; axisPos++ )
    {
        {
            const QwtAxisId axisId( axisPos );

            if ( !m_data->isAxisEnabled[axisId] )
                continue;

            const QwtScaleMap map = plot->canvasMap( axisId );      // 获取给定坐标轴的画布映射

            // 通过画布映射将坐标轴上的标尺刻度值（分别是上下界）转换为画布上的像素值
            // 调用plot->axisScaleDiv(axisId)获取给定坐标轴的坐标刻度范围，使用lowerBound()和upperBound()函数分别获取坐标轴的下界和上界
            // 调用map.transform()函数将这些坐标刻度值转换为画布上的像素值。map.transform()函数接受一个坐标值作为参数，并返回对应的像素值
            const double p1 = map.transform( plot->axisScaleDiv( axisId ).lowerBound() );
            const double p2 = map.transform( plot->axisScaleDiv( axisId ).upperBound() );

            // x轴：通过map.invTransform(p1 - dx)和map.invTransform(p2 - dx)分别将p1和p2减去dx后的像素值转换回对应的坐标值
            // y轴：通过map.invTransform(p1 - dy)和map.invTransform(p2 - dy)分别将p1和p2减去dy后的像素值转换回对应的坐标值
            double d1, d2;
            if ( QwtAxis::isXAxis( axisPos ) )
            {
                d1 = map.invTransform( p1 - dx );
                d2 = map.invTransform( p2 - dx );
            }
            else
            {
                d1 = map.invTransform( p1 - dy );
                d2 = map.invTransform( p2 - dy );
            }

            plot->setAxisScale( axisId, d1, d2 );
        }
    }

    plot->setAutoReplot( doAutoReplot );                            // 恢复先前的自动刷新设置
    plot->replot();                                                 // 调用replot()函数手动触发重新绘制
#endif
}

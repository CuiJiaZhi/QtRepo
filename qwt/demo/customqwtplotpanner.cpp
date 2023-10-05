#include "customqwtplotpanner.h"
#include "qwt_plot.h"
#include "qwt_scale_div.h"
#include "qwt_scale_map.h"
#include "qwt_painter.h"
#include "qwt_picker.h"

#include <QMouseEvent>
#include <QBitmap>
#include <QDebug>
#include <QPainter>

static QVector<QwtPicker*> qwtActivePickers(QWidget* w)
{
    QVector<QwtPicker*> pickers;

    QObjectList children = w->children();
    for(int i = 0; i < children.size(); i++)
    {
        QwtPicker* picker = qobject_cast<QwtPicker*>(children[i]);
        if(picker && picker->isEnabled())
            pickers += picker;
    }

    return pickers;
}

#if 0
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
        for(int axis = 0; axis < QwtAxis::AxisPositions; axis++)
            isAxisEnabled[axis] = true;
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
     QPoint lastPos;
     QPoint diffPos;

#ifndef QT_NO_CURSOR
    QCursor* cursor;
    QCursor* restoreCursor;
    bool hasCursor;
#endif

    bool isAxisEnabled[QwtAxis::AxisPositions];
};
#endif

class customQwtPlotPanner::PrivateData
{
public:
    // 构造函数
    PrivateData()
        : button(Qt::LeftButton)
        , buttonModifiers(Qt::NoModifier)
        , abortKey(Qt::Key_Escape)
        , abortKeyModifiers(Qt::NoModifier)
#ifndef QT_NO_CURSOR
        , cursor(nullptr)
        , restoreCursor(nullptr)
        , hasCursor(false)
#endif
        , isEnabled(false)
        , orientations(Qt::Vertical | Qt::Horizontal)
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

    Qt::MouseButton button;
    Qt::KeyboardModifiers buttonModifiers;

    int abortKey;
    Qt::KeyboardModifiers abortKeyModifiers;

    QPoint initialPos;
    QPoint pos;
    QPoint lastPos;
    QPoint diffPos;

    QPixmap pixmap;
    QBitmap contentsMask;

#ifndef QT_NO_CURSOR
    QCursor* cursor;
    QCursor* restoreCursor;
    bool hasCursor;
#endif
    bool isEnabled;
    Qt::Orientations orientations;
    bool isAxisEnabled[QwtAxis::AxisPositions];
};

// 构造函数
customQwtPlotPanner::customQwtPlotPanner(QWidget* canvas)
    : QwtPlotPanner(canvas)
{
    // 创建PrivateData对象
    this->m_data = new PrivateData();

#if 1
    // 连接信号与槽函数
    QObject::connect(this, SIGNAL(moved(int,int)), SLOT(do_UpdateGrid(int,int)));
    QObject::connect(this, SIGNAL(panned(int,int)), SLOT(moveCanvas(int,int)));
#endif
}

// 析构函数
customQwtPlotPanner::~customQwtPlotPanner()
{
    delete this->m_data;
}

// 重写鼠标按压事件
void customQwtPlotPanner::widgetMousePressEvent(QMouseEvent* event)
{
    if((event->button() != m_data->button) || (event->modifiers() != m_data->buttonModifiers)) {
        return;
    }

    QWidget* w = parentWidget();
    if(w == nullptr)
        return;

#ifndef QT_NO_CURSOR
    showCursor(true);
#endif

    this->m_data->initialPos = this->m_data->pos = event->pos();                   // 记录鼠标按下时刻的坐标

    setGeometry(parentWidget()->rect());

    QVector<QwtPicker*> pickers = qwtActivePickers(parentWidget());
    for(int i = 0; i < pickers.size(); i++)
        pickers[i]->setEnabled(false);

    this->m_data->pixmap = grab();
    this->m_data->contentsMask = contentsMask();

    for(int i = 0; i < pickers.size(); i++)
        pickers[i]->setEnabled(true);

    QWidget::show();
}

// 重写鼠标释放事件
void customQwtPlotPanner::widgetMouseReleaseEvent(QMouseEvent* event)
{
    if(isVisible())
    {
        QWidget::hide();
#if 1
#ifndef QT_NO_CURSOR
        showCursor(false);
#endif
        QPoint pos = event->pos();                                     // 记录鼠标释放时刻的坐标
        if(!isOrientationEnabled(Qt::Horizontal))
            pos.setX(this->m_data->initialPos.x());
        if(!isOrientationEnabled(Qt::Vertical))
            pos.setY(this->m_data->initialPos.y());

        this->m_data->pixmap = QPixmap();
        this->m_data->contentsMask = QBitmap();
        this->m_data->pos = pos;

        if(this->m_data->pos != this->m_data->initialPos)
        {
            emit panned(this->m_data->pos.x() - this->m_data->initialPos.x(),       // 在鼠标释放时，发射信号panned(int dx, int dy);
                        this->m_data->pos.y() - this->m_data->initialPos.y());
//            emit panned(this->m_data->diffPos.x(), this->m_data->diffPos.y());
        }
#endif
    }
}

// 重写鼠标移动函数
void customQwtPlotPanner::widgetMouseMoveEvent(QMouseEvent* event)
{
    // 检查窗口部件的可见性
    if (!QWidget::isVisible())
        return;

    QPoint pos = event->pos();                       // 获取鼠标当前的坐标

    if(!isOrientationEnabled(Qt::Horizontal))
        this->m_data->pos.setX(this->m_data->lastPos.x());
    if(!isOrientationEnabled(Qt::Vertical))
        this->m_data->pos.setY(this->m_data->lastPos.y());

    // 判断位置pos是否位于QWidget窗口部件的矩形区域内
    if(pos != this->m_data->pos && rect().contains(this->m_data->pos))
    {
        this->m_data->pos = pos;
        // 向窗口部件发送一个重绘事件，并将窗口部件标记为需要更新
        // 调用QWidget::update()函数会触发以下操作：
            // 发送重绘事件：函数会将一个QPaintEvent事件发送到窗口部件的事件队列中，这指示Qt引擎在适当的时候重新绘制该窗口部件。
            // 标记为需要更新：函数会将窗口部件标记为需要更新，在下一个事件循环中将其重新绘制，Qt引擎会在事件循环的某个时刻，根据需要刷新窗口的区域。
        QWidget::update();

        if(this->m_data->lastPos != QPoint(0, 0)) {
            this->m_data->diffPos = pos - this->m_data->lastPos;
            // 在鼠标移动过程中，发射信号moved(int dx, int dy);
            emit moved(this->m_data->diffPos.x(), this->m_data->diffPos.y());
        }
    }

    // 存储鼠标上一时刻的坐标
    this->m_data->lastPos = pos;
}

#if 1
// 自定义槽函数
void customQwtPlotPanner::do_UpdateGrid(int dx, int dy)
{
    if(dx == 0 && dy == 0)
        return;

    QwtPlot* plot = this->plot();                                   // 获取QwtPlot指针对象
    if(plot == nullptr)
        return;

    // 遍历四个坐标轴
    for(int axisPos = 0; axisPos < QwtAxis::AxisPositions; axisPos++)
    {
        const QwtAxisId axisId(axisPos);

        if(!this->m_data->isAxisEnabled[axisId])
            continue;

        const QwtScaleMap map = plot->canvasMap(axisId);               // 获取给定坐标轴的画布映射

        // 通过画布映射将坐标轴上的标尺刻度值（分别是上下界）转换为画布上的像素值
        // 调用plot->axisScaleDiv(axisId)获取给定坐标轴的坐标刻度范围，使用lowerBound()和upperBound()函数分别获取坐标轴的下界和上界
        // 调用map.transform()函数将这些坐标刻度值转换为画布上的像素值。map.transform()函数接受一个坐标值作为参数，并返回对应的像素值
        const double p1 = map.transform(plot->axisScaleDiv(axisId).lowerBound());
        const double p2 = map.transform(plot->axisScaleDiv(axisId).upperBound());

        // x轴：通过map.invTransform(p1 - dx)和map.invTransform(p2 - dx)分别将p1和p2减去dx后的像素值转换回对应的坐标值
        // y轴：通过map.invTransform(p1 - dy)和map.invTransform(p2 - dy)分别将p1和p2减去dy后的像素值转换回对应的坐标值
        double d1, d2;
        if(QwtAxis::isXAxis(axisPos)) {
            d1 = map.invTransform(p1 - dx);
            d2 = map.invTransform(p2 - dx);
        }
        else {
            d1 = map.invTransform(p1 - dy);
            d2 = map.invTransform(p2 - dy);
        }
        plot->setAxisScale(axisId, d1, d2);
    }

    plot->replot();                                                 // 调用replot()函数手动触发重新绘制
}
#endif

// 重写窗口绘制函数
void customQwtPlotPanner::paintEvent(QPaintEvent* event)
{
    int dx = this->m_data->pos.x() - this->m_data->initialPos.x();
    int dy = this->m_data->pos.y() - this->m_data->initialPos.y();

    QRectF r;
    r.setSize(this->m_data->pixmap.size() / QwtPainter::devicePixelRatio(&this->m_data->pixmap));
    r.moveCenter(QPointF(r.center().x() + dx, r.center().y() + dy));

    QPixmap pm = QwtPainter::backingStore(this, size());
    QwtPainter::fillPixmap(parentWidget(), pm);

    QPainter painter(&pm);

    if(!this->m_data->contentsMask.isNull()) {
        QPixmap masked = this->m_data->pixmap;
        masked.setMask(this->m_data->contentsMask);
        painter.drawPixmap(r.toRect(), masked);
    }
    else {
        painter.drawPixmap(r.toRect(), this->m_data->pixmap);
    }

    painter.end();

    if(!this->m_data->contentsMask.isNull())
        pm.setMask(this->m_data->contentsMask);

    painter.begin(this);
    painter.setClipRegion(event->region());
    painter.drawPixmap(0, 0, pm);
}

void customQwtPlotPanner::moveCanvas(int dx, int dy)
{
#if 1
    if(dx == 0 && dy == 0)
        return;

    QwtPlot* plot = this->plot();                                   // 获取QwtPlot指针对象
    if (plot == nullptr)
        return;

    const bool doAutoReplot = plot->autoReplot();                   // 获取当前的自动刷新设置
    plot->setAutoReplot(false);                                   // 设置不会自动刷新，以便在修改坐标轴范围时避免重绘

    // 遍历四个坐标轴
    for(int axisPos = 0; axisPos < QwtAxis::AxisPositions; axisPos++)
    {
        const QwtAxisId axisId(axisPos);

        if(!m_data->isAxisEnabled[axisId])
            continue;

        const QwtScaleMap map = plot->canvasMap(axisId);      // 获取给定坐标轴的画布映射

        // 通过画布映射将坐标轴上的标尺刻度值（分别是上下界）转换为画布上的像素值
        // 调用plot->axisScaleDiv(axisId)获取给定坐标轴的坐标刻度范围，使用lowerBound()和upperBound()函数分别获取坐标轴的下界和上界
        // 调用map.transform()函数将这些坐标刻度值转换为画布上的像素值。map.transform()函数接受一个坐标值作为参数，并返回对应的像素值
        const double p1 = map.transform(plot->axisScaleDiv(axisId).lowerBound());
        const double p2 = map.transform(plot->axisScaleDiv(axisId).upperBound());

        // x轴：通过map.invTransform(p1 - dx)和map.invTransform(p2 - dx)分别将p1和p2减去dx后的像素值转换回对应的坐标值
        // y轴：通过map.invTransform(p1 - dy)和map.invTransform(p2 - dy)分别将p1和p2减去dy后的像素值转换回对应的坐标值
        double d1, d2;
        if(QwtAxis::isXAxis(axisPos))
        {
            d1 = map.invTransform(p1 - dx);
            d2 = map.invTransform(p2 - dx);
        }
        else
        {
            d1 = map.invTransform(p1 - dy);
            d2 = map.invTransform(p2 - dy);
        }

        plot->setAxisScale(axisId, d1, d2);
    }

    plot->setAutoReplot(doAutoReplot);                            // 恢复先前的自动刷新设置
    plot->replot();                                               // 调用replot()函数手动触发重新绘制
#endif
}

#ifndef QT_NO_CURSOR
void customQwtPlotPanner::showCursor(bool on)
{
    if(on == this->m_data->hasCursor)
        return;

    QWidget* w = parentWidget();
    if(w == nullptr || this->m_data->cursor == nullptr)
        return;

    this->m_data->hasCursor = on;

    if(on) {
        if(w->testAttribute(Qt::WA_SetCursor)) {
            delete this->m_data->restoreCursor;
            this->m_data->restoreCursor = new QCursor(w->cursor());
        }
        w->setCursor(*this->m_data->cursor);
    }
    else {
        if(this->m_data->restoreCursor) {
            w->setCursor(*this->m_data->restoreCursor);
            delete this->m_data->restoreCursor;
            this->m_data->restoreCursor = nullptr;
        }
        else
            w->unsetCursor();
    }
}
#endif

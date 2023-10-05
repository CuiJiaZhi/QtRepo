#ifndef CUSTOMCHART_H
#define CUSTOMCHART_H

#include <QChart>           // 图形项类
#include <QGraphicsItem>
#include <QLineSeries>      // 序列类
#include <QSplineSeries>
#include <QValueAxis>       // 坐标轴
#include <QPen>             // 画笔
#include <QBrush>
#include <QVector>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE     // using namespace QT_CHARTS_NAMESPACE

class customChart : public QChart
{
    Q_OBJECT
public:
    customChart(QGraphicsItem* parent = nullptr);  // 构造函数
    ~customChart();             // 析构函数

    int seriesNum() const;      // 获取序列的个数
    void appendSeries();        // 添加序列
    void appendSeries(QString& name);   // 添加序列
    void clearSeries(int index);        // 清空序列
    void deleteSeries();                // 删除序列
    void deleteSeries(int index);       // 删除序列

    QValueAxis* axisX;          // 坐标轴横轴
    QValueAxis* axisY;          // 坐标轴纵轴
    QVector<QLineSeries*> series;    // 序列
    QPen pen;                   // 画笔
    QBrush brush;               // 画刷
};

#endif // CUSTOMCHART_H

#include "customchart.h"

// 构造函数
customChart::customChart(QGraphicsItem* parent)
    : QChart(parent)
{
    this->axisX = new QValueAxis;         // 坐标轴横轴
    this->addAxis(this->axisX, Qt::AlignBottom);        // 将坐标轴添加到图表中，并指定方向

    this->axisY = new QValueAxis;         // 坐标轴纵轴
    this->addAxis(this->axisY, Qt::AlignLeft);          // 将坐标轴添加到图表中，并指定方向

    this->series.append(new QLineSeries); // 序列
    this->addSeries(this->series[0]);                   // 将序列添加到图表中

    this->series[0]->attachAxis(this->axisX);           // 序列附加坐标轴
    this->series[0]->attachAxis(this->axisY);
}

// 析构函数
customChart::~customChart()
{
    delete this->axisX;                         // 删除指向QValueAxis的指针对象
    delete this->axisY;                         // 删除指向QValueAxis的指针对象
    for(int i = 0; i < this->series.size(); ++i) {
        delete this->series[i];                 // 删除QVector中的指针对象
    }
    this->series.clear();                       // 清空QVector
}

// 获取序列个数
int customChart::seriesNum() const {
    return this->series.size();
}

// 添加序列
void customChart::appendSeries()
{
    int idx = this->series.size();                        // 获取添加序列之前的序列个数
    this->series.append(new QLineSeries);
    this->addSeries(this->series[idx]);                   // 将序列添加到图表中
    this->series[idx]->attachAxis(this->axisX);           // 序列附加坐标轴
    this->series[idx]->attachAxis(this->axisY);
}

// 添加序列以及名称
void customChart::appendSeries(QString& name)
{
    int idx = this->series.size();                        // 获取添加序列之前的序列个数
    this->series.append(new QLineSeries);
    this->addSeries(this->series[idx]);                   // 将序列添加到图表中
    this->series[idx]->attachAxis(this->axisX);           // 序列附加坐标轴
    this->series[idx]->attachAxis(this->axisY);
    this->series[idx]->setName(name);                     // 设置序列名称
}

// 清空序列
void customChart::clearSeries(int index)
{
    if(index < this->series.size() && index >= 0) {
        if(this->series[index]->count())                      // 序列中的点数
            this->series[index]->clear();                     // 清空指定序列
    }
    else if(index == -1) {
        for(int i = 0; i < this->series.size(); ++i) {
            if(this->series[i]->count())                      // 序列中的点数
                this->series[i]->clear();                     // 清空全部序列
        }
    }
}

// 删除末尾序列
void customChart::deleteSeries()
{
    if(this->series.size() == 0)
        return;

    this->removeSeries(this->series[this->series.size() - 1]);       // 从chart中移除序列
    QLineSeries* obj = this->series.takeAt(this->series.size() - 1); // 获取指针对象，并将其从QVector中移除
    delete obj;                                                      // 释放从QVector中移除的对象，防止内存泄漏
}

// 删除指定序列
void customChart::deleteSeries(int index)
{
    (void)(index);
}

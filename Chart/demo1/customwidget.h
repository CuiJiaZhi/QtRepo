#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPoint>
#include "customchartview.h"

// 定义表示二维索引的结构体
typedef struct twoDimensionalIndex {
    int row;                // 行
    int col;                // 列
    twoDimensionalIndex() : row(0), col(0) {};
    twoDimensionalIndex(int row, int col) : row(row), col(col) {};
}twoDimIndex;

// 自定义类
class customWidget : public QWidget
{
    Q_OBJECT
public:
    explicit customWidget(QWidget *parent = nullptr);           // 构造函数
    ~customWidget();                                            // 析构函数

    void addChartView(int row, int col);                        // 向自定义QWidget中添加自定义QChartView
    // void addChartView(int row, int col, int rowSpan = 1, int colSpan = 1);
    void addChartView(int total, int row, int col);             // 向自定义QWidget中按照指定的方式添加total个自定义QChartView
    void removeChartView();                                     // 从自定义QWidget中解绑自定义QChartView
    void removeChartView(int index);                            // 从自定义QWidget中解绑自定义QChartView
    void removeChartView(int row, int col);                     // 从自定义QWidget中解绑自定义QChartView
    customChartView* getChartView() const;                      // 获取自定义QWidget中的最后一个自定义QChartView
    customChartView* getChartView(int row, int col) const;      // 按照二维索引获取自定义QWidget中的自定义QChartView
    customChartView* getChartView(int index) const;             // 按照索引获取自定义QWidget中的自定义QChartView

    QVector<twoDimIndex> getChartView2DIndex() const;           // 顺序返回自定义QChartView的二维索引

signals:

private:
    QVector<customChartView*> chartview;                        // 自定义QChartView
    QVector<twoDimIndex> chartView2DIndex;                      // 自定义QWidget中的自定义QChartView的二维索引
    QGridLayout* gridLayout;                                    // 网格布局管理器
};

#endif // CUSTOMWIDGET_H

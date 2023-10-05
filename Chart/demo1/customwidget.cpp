#include "customwidget.h"
#include <QDebug>

// 构造函数
customWidget::customWidget(QWidget *parent)
    : QWidget{parent}
{
    this->gridLayout = new QGridLayout(this);                    // 添加网格布局管理器
    //this->chartview.append(new customChartView(this));           // 在自定义的QWidget中添加自定义的QChartView
    //this->chartView2DIndex.append(twoDimIndex(0, 0));            // 添加自定义QWidget中的自定义QChartView的二维索引
    //this->gridLayout->addWidget(this->chartview[0]);             // 将自定义的QChartView添加到网格布局管理器中
}

// 析构函数
customWidget::~customWidget()
{
    if(this->chartview.size() > 0) {
        for(int i = 0; i < this->chartview.size(); ++i) {
            delete this->chartview[i];                          // 删除QVector中的指针对象
        }
    }
    if(this->gridLayout)
        delete this->gridLayout;
}

// 向自定义QWidget中添加自定义QChartView
void customWidget::addChartView(int row, int col)
{
    int index = this->chartview.size();
    this->chartview.append(new customChartView(this));
    this->chartView2DIndex.append(twoDimIndex(row, col));                 // 添加自定义QWidget中的自定义QChartView的二维索引
    this->gridLayout->addWidget(this->chartview[index], row, col);        // 将自定义的QChartView添加到网格布局管理器中

    this->gridLayout->setRowStretch(row, 1);                              // 设置行的伸展因子
    this->gridLayout->setColumnStretch(col, 1);                           // 设置列的伸展因子
}

// 向自定义QWidget中添加自定义QChartView
// void customWidget::addChartView(int row, int col, int rowSpan, int colSpan)
// {
//     int index = this->chartview.size();
//     this->chartview.append(new customChartView(this));
//     this->chartView2DIndex.append(twoDimIndex(row, col));                 // 添加自定义QWidget中的自定义QChartView的二维索引
//     this->gridLayout->addWidget(this->chartview[index], row, col, rowSpan, colSpan);        // 将自定义的QChartView添加到网格布局管理器中
//     this->gridLayout->setRowStretch(row, 1);                              // 设置行的伸展因子
//     this->gridLayout->setColumnStretch(col, 1);                           // 设置列的伸展因子
// }

// 向自定义QWidget中按照指定的方式添加total个自定义QChartView
void customWidget::addChartView(int total, int row, int col)
{
    if(total != row * col)
        return;
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
//            if(i == 0 && j == 0)
//                continue;
            int index = this->chartview.size();
            this->chartview.append(new customChartView(this));
            this->chartView2DIndex.append(twoDimIndex(i, j));                 // 添加自定义QWidget中的自定义QChartView的二维索引
            this->gridLayout->addWidget(this->chartview[index], i, j);        // 将自定义的QChartView添加到网格布局管理器中
        }
    }
}

// 从自定义QWidget中移除自定义QChartView
void customWidget::removeChartView()
{
    int size = this->chartview.size();
    if(size > 0) {
        this->gridLayout->removeWidget(this->chartview[size - 1]);        // 从自定义QWidget中解绑自定义QChartView
        this->chartview[size - 1]->setParent(nullptr);
        // customChartView* obj = this->chartview.takeAt(size - 1);          // 获取指针对象，并将其从QVector中移除
        // delete obj;                                                       // 删除指针对象
    }
    // this->chartView2DIndex.removeAt(size - 1);
    this->chartView2DIndex[size - 1] = twoDimIndex(-1, -1);
}

// 从自定义QWidget中移除自定义QChartView
void customWidget::removeChartView(int index)
{
    if(index < this->chartview.size()) {
        this->gridLayout->removeWidget(this->chartview[index]);           // 从自定义QWidget中解绑自定义QChartView
        this->chartview[index]->setParent(nullptr);
        // customChartView* obj = this->chartview.takeAt(index);             // 获取指针对象，并将其从QVector中移除
        // delete obj;                                                       // 删除指针对象
    }
    // this->chartView2DIndex.removeAt(index);
    this->chartView2DIndex[index] = twoDimIndex(-1, -1);
}

// 从自定义QWidget中移除自定义QChartView
void customWidget::removeChartView(int row, int col)
{
    int index = 0;
    int size = this->chartView2DIndex.size();
    for(int i = 0; i < size; ++i) {
        if((this->chartView2DIndex[i].row == row) && (this->chartView2DIndex[i].col == col)) {
            index = i;
            if(index < this->chartview.size()) {
                this->gridLayout->removeWidget(this->chartview[index]);           // 从自定义QWidget中解绑自定义QChartView
                this->chartview[index]->setParent(nullptr);
                // customChartView* obj = this->chartview.takeAt(index);             // 获取指针对象，并将其从QVector中移除
                // delete obj;                                                       // 删除指针对象
            }
            // this->chartView2DIndex.removeAt(index);
            this->chartView2DIndex[index] = twoDimIndex(-1, -1);
            return;
        }
    }
    qDebug() << "此二维索引不存在";
}

// 获取自定义QWidget中的最后一个自定义QChartView
customChartView* customWidget::getChartView() const
{
    int size = this->chartview.size();
    if(size > 0)
        return this->chartview[size - 1];
    return nullptr;
}

// 按照二维索引获取自定义QWidget中的自定义QChartView
customChartView* customWidget::getChartView(int row, int col) const
{
    int size = this->chartview.size();
    for(int i = 0; i < size; ++i) {
        if((this->chartView2DIndex[i].row == row) && (this->chartView2DIndex[i].col == col)) {
            return this->chartview[i];
        }
    }
    return nullptr;
}

// 按照索引获取自定义QWidget中的自定义QChartView
customChartView* customWidget::getChartView(int index) const
{
    if(index < this->chartview.size() && index >= 0)
        return this->chartview[index];
    return nullptr;
}

// 顺序返回自定义QChartView的索引
QVector<twoDimIndex> customWidget::getChartView2DIndex() const {
    return this->chartView2DIndex;
}


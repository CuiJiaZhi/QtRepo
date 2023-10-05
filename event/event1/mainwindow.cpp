#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QCursor>

// hello GitHub
// hello GitHub

// 构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(this, SIGNAL(moved(QPoint)), SLOT(do_moved(QPoint)));
}

// 析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

// 鼠标按压事件
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    // event->globalPos(): 返回当前鼠标位置相对于屏幕左上角的坐标
    // pos(): 返回窗口左上角相对于屏幕左上角的坐标
    // event->pos(): 返回当前鼠标位置相对于窗口左上角的坐标
    if(event->button() == Qt::LeftButton) {                     // 按下的是否为鼠标左键
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);                  // 设置鼠标形状
        QApplication::setOverrideCursor(cursor);                // 指针改变鼠标形状
        this->offset = event->globalPos() - pos();
    }
}

// 鼠标移动事件
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton) {                     // 是否为鼠标左键
        emit moved(event->globalPos() - this->offset);          // 发送信号moved(QPoint point)
    }
}

// 鼠标释放事件
void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    (void)(event);
    QApplication::restoreOverrideCursor();                      // 恢复鼠标指针形状
}

// 鼠标双击事件
void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {                     // 双击鼠标左键
        if(QWidget::windowState() != Qt::WindowFullScreen) {    // 当前窗口是否为全屏状态
            QWidget::setWindowState(Qt::WindowFullScreen);      // 将当前窗口设置为全屏状态
        }
        else {
            QWidget::setWindowState(Qt::WindowNoState);         // 将当前窗口恢复为之前的状态
        }
    }
}

// 槽函数
void MainWindow::do_moved(QPoint point)
{
    qDebug() << point;
}

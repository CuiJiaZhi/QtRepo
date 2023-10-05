#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 构造函数
    MainWindow(QWidget *parent = nullptr);
    // 析构函数
    ~MainWindow();

private slots:
    // 槽函数
    void do_moved(QPoint point);

protected:
    // 重写鼠标按压事件
    virtual void mousePressEvent(QMouseEvent* event) override;
    // 重写鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    // 重写鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    // 重写鼠标双击事件
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

signals:
    // 信号
    void moved(QPoint point);

private:
    Ui::MainWindow *ui;

    QPoint offset;
};
#endif // MAINWINDOW_H

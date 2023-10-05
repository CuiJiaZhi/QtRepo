#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customchartview.h"
#include "customwidget.h"
#include "customchart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_del_clicked();

    void on_pushButton_add_clicked();

private:
    Ui::MainWindow *ui;

    customChart* chart;
};
#endif // MAINWINDOW_H

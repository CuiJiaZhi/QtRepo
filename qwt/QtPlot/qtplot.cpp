#include "qtplot.h"
#include "ui_qtplot.h"

QtPlot::QtPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtPlot)
{
    ui->setupUi(this);
}

QtPlot::~QtPlot()
{
    delete ui;
}

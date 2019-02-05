#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qpainter.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter qp(this);
    d.setScale(150.0);
    //d.drawModel(&qp, t);
    c.test(&qp, &d);
    qp.end();
}

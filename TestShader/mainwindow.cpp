#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"

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
    cs->smooth(D, DS);
    p->paint(&qp, D, 50, 20);
    p->paint(&qp, DS, 50 + imageSize * p->mash, 20);
    qp.end();

}

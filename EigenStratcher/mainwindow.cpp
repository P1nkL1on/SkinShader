#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qpainter.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->runTests();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter qp(this);
    //d.drawModel(&qp, t);
//    c.test0();
//    c.test(&qp, &d);
    EsCalculatorHelp::testRandom3Model(&qp, &d);
    qp.end();
}

void MainWindow::runTests() const
{
    EsCalculatorTests esCTests;
    QTest::qExec(&esCTests);
}

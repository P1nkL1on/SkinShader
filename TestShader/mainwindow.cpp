#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"

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

void MainWindow::runTests() const
{
    PlaneVectorTests planeTests;
    QTest::qExec(&planeTests);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    if (everSaved)return;
    PlaneVector DS = PlaneVector(imageSize, imageSize);
    PlaneVector DS1 = PlaneVector(imageSize, imageSize);
    cs->smooth(D, DS, 1);
    cs->smooth(D, DS1, 2);

    PlaneVector Dsharp = PlaneVector(imageSize, imageSize);
    PlaneVector::summ(D, 1.5, DS1, -.5, Dsharp);

    QPainter qp(this);
    p->paint(&qp, D, 50, 20);
    p->paint(&qp, DS, 60 + imageSize * p->mash, 20);
    p->paint(&qp, DS1, 70 + imageSize * p->mash * 2, 20);
    p->paint(&qp, Dsharp, 50, 30 + imageSize * p->mash);
    qp.end();

//    everSaved = true;
//    const QImage orig = p->paint(D);//
//    const QImage blur = p->paint(DS);//

//    orig.save("image.png");
//    blur.save("imageBlured.png");

//    qDebug() << "done";
}

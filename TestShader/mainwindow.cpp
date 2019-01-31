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
    D = D.changeSize(400, 600, 2);
    PlaneVector DS = PlaneVector(D.width(), D.height());
    PlaneVector DS1 = PlaneVector(D.width(), D.height());
    cs->smooth(D, DS, 1);
//    cs->smooth(D, DS1, 2);

    PlaneVector Dsharp = PlaneVector(D.width(), D.height());
    PlaneVector::summ(D, 1.5, DS1, -.5, Dsharp);

    QPainter qp(this);
    p->paint(&qp, D, 50, 20);
    p->paint(&qp, DS, 60 + D.width() * p->mash, 20);
//    p->paint(&qp, DS1, 70 + imageSize * p->mash * 2, 20);
    p->paint(&qp, Dsharp, 60 + D.width() * p->mash * 2, 20);
    qp.end();

//    everSaved = true;
//    const QImage orig = p->paint(D);//
//    const QImage blur = p->paint(DS);//

//    orig.save("image.png");
//    blur.save("imageBlured.png");

//    qDebug() << "done";
}

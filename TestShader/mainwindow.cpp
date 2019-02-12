#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include "Shading/trianglespeller.h"

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

}

void MainWindow::on_pushButton_clicked()
{
    if (everSaved)return;
    PlaneVector D = PlaneVector("test.png");
    D = D.changeSize(200, 300, 2);
    PlaneVector res = PlaneVector(900, 900);

    PlaneVector DS = PlaneVector(D.width(), D.height());

    QPainter qp(this);
    p->paint(&qp, D, 50, 20);

    double r = 1;
    double offset = 0;
        cs->blurCross(D, DS, r + offset, r - offset, 1, 0, 2);
        p->paint(&qp, DS, 500, 20);

    TriangleSpeller::findAllPixelCoordinates(D, 40, 40, 180, 0, 30, 250);
    //TriangleSpeller::fillTexture(D, res, .2, .2, .9, .0, .15, .75, 510, 210, 210, 610, 10, 10);
    //p->paint(&qp, D, 20, 20);
    //p->paint(&qp, res, 620, 20);
    qp.end();

//    everSaved = true;
//    const QImage orig = p->paint(D);//
//    const QImage blur = p->paint(DS);//

//    orig.save("image.png");
//    blur.save("imageBlured.png");

    qDebug() << "done";
}

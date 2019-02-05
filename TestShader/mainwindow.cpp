#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include "trianglespeller.h"

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
    PlaneVector D = PlaneVector("rock.jpeg");
    D = D.changeSize(200, 300, 2);

    PlaneVector DS = PlaneVector(D.width(), D.height());

    QPainter qp(this);
    p->paint(&qp, D, 50, 20);

    for (int i = 0; i < 2; ++i){
        const double r = .7 + .7 * i;
        cs->blurCross(D, DS, r, 1.0, 1.0, 2);
        p->paint(&qp, DS, 60 + D.width() * p->mash * (i+1), 20);
    }
    qp.end();

//    everSaved = true;
//    const QImage orig = p->paint(D);//
//    const QImage blur = p->paint(DS);//

//    orig.save("image.png");
//    blur.save("imageBlured.png");

//    qDebug() << "done";
}

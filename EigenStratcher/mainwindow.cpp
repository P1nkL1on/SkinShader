#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qpainter.h>
#include <QFileDialog>
#include <QDebug>

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
    //EsCalculatorHelp::testRandom3Model(&qp, &d);
    processer->drawSelf(&qp);
    qp.end();
}

void MainWindow::runTests() const
{
    EsCalculatorTests esCTests;
    QTest::qExec(&esCTests);
}

void MainWindow::on_actionLoad_Texture_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "../../../", "Images (*.png *.xpm *.jpg)");
    if (fileName.isEmpty())
        return;
    const bool success = processer->loadTexture(fileName);
    qDebug() << (success? "Texture loaded successfully!" : ("Error in loading " + fileName));
    if (success)
        processer->scaleNormallyToMax(900);
}

void MainWindow::on_actionLoad_Model_triggered()
{
    processer->loadModel(model);
    qDebug() << "Model loaded successfully!";
}

void MainWindow::on_actionLoad_Stretched_Model_triggered()
{
    processer->loadStretchedModel(model2);
    qDebug() << "Stretched model loaded successfully!";
}

void MainWindow::on_actionSave_Stretched_Texture_triggered()
{
}

void MainWindow::on_actionStretch_Texture_triggered()
{
    processer->stretchTexture();
    repaint();
}

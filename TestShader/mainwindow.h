#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "planevectordrawer.h"
#include "crossshading.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    PlaneVectorDrawer *p = new PlaneVectorDrawer();
    const int imageSize = 300;
    PlaneVector D = PlaneVector::testPlaneVector(imageSize, imageSize);
    PlaneVector DS = PlaneVector(imageSize, imageSize);
    CrossShading *cs = new CrossShading();
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H

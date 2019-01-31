#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "planevectortests.h"
#include "crossshading.h"
#include "planevectordrawer.h"

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
    void runTests() const;

    PlaneVectorDrawer *p = new PlaneVectorDrawer();
    const int imageSize = 250;
    bool everSaved = false;
    PlaneVector D = PlaneVector("rock2.jpeg");
    //PlaneVector::testPlaneVector(imageSize, imageSize);
    CrossShading *cs = new CrossShading();
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H

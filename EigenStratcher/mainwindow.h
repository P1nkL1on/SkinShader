#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "escalculatortests.h"

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
    void runTests() const;
    Ui::MainWindow *ui;
    esModel t = esModel::createTestModel();
    esDrawer d = esDrawer();
    esCalculator c = esCalculator();
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H

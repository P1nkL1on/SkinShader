#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "StretchCalculator/escalculatortests.h"
#include "esprocesser.h"
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
    EsProcesser *processer = new EsProcesser();
protected:
    void paintEvent(QPaintEvent *e);
private slots:
    void on_actionLoad_Texture_triggered();
    void on_actionLoad_Model_triggered();
    void on_actionLoad_Stretched_Model_triggered();
    void on_actionSave_Stretched_Texture_triggered();
    void on_actionStretch_Texture_triggered();
};

#endif // MAINWINDOW_H

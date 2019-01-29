#ifndef PLANEVECTORTESTS_H
#define PLANEVECTORTESTS_H

#include <QTest>
#include "planevector.h"

class PlaneVectorTests : public QObject
{
    Q_OBJECT
public:

private:

private slots:
    void testInitiate();
    void testHeiWid();
    void testInOut();
    void testInOutError();
    void testGettingInt();
    void testNoneInter();
    void testNearestInter();
};

#endif // PLANEVECTORTESTS_H

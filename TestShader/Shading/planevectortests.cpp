#include "planevectortests.h"


void PlaneVectorTests::testInitiate()
{
    PlaneVector p = PlaneVector(10, 20);
    QVERIFY(p.getValue(0, 0) == 0.0);
}

void PlaneVectorTests::testHeiWid()
{
    PlaneVector p = PlaneVector(8, 6);
    QVERIFY(p.width() == 8);
    QVERIFY(p.height() == 6);
}

void PlaneVectorTests::testInOut()
{
    PlaneVector p = PlaneVector(5, 5);
    for (int i = 0; i < 5; ++i)
        p.setValue(i * i * .33, i, i);
    QVERIFY(p.getValue(0, 0) == 0.0);
    QVERIFY(p.getValue(4, 4) == 16 * .33);
    QVERIFY(p.getValue(0, 4) == 0.0);
    QVERIFY(p.getValue(2, 2) == 4 * .33);
}

void PlaneVectorTests::testInOutError()
{
    PlaneVector p = PlaneVector(5, 5);
    bool catchedError = false;
    try{
        double value = p.getValue(5, 0);
    }catch(...){
        catchedError = true;
    }
    QVERIFY(catchedError);
}

void PlaneVectorTests::testGettingInt()
{
    PlaneVector p = PlaneVector(2, 2);
    for (int i = 0; i < 4; ++i)
        p.setValue(i * 1.0, i % 2, i / 2);
    QVERIFY(p.getValue(0, 0) == 0.0);
    QVERIFY(p.getValue(1, 0) == 1.0);
    QVERIFY(p.getValue(0, 1) == 2.0);
    QVERIFY(p.getValue(1, 1) == 3.0);
}

void PlaneVectorTests::testNoneInter()
{
    PlaneVector p = PlaneVector(2, 2);
    for (int i = 0; i < 4; ++i)
        p.setValue(i * 1.0, i % 2, i / 2);
    QVERIFY(p.getValue(0.9, 0.5) == 0.0);
    QVERIFY(p.getValue(1.2, 0.2) == 1.0);
    QVERIFY(p.getValue(0.9999, 1.9999) == 2.0);
    QVERIFY(p.getValue(1.00001, 1.65) == 3.0);
}

void PlaneVectorTests::testNearestInter()
{
    PlaneVector p = PlaneVector(2, 2);
    for (int i = 0; i < 4; ++i)
        p.setValue(i * 1.0, i % 2, i / 2);
    QVERIFY(p.getValue(0.2, 0.3, 1) == 0.0);
    QVERIFY(p.getValue(0.7, 0.3, 1) == 1.0);
    QVERIFY(p.getValue(0.99, 0.99, 1) == 3.0);
}

void PlaneVectorTests::testBilinearInter()
{
    PlaneVector p = PlaneVector(2, 2);
    for (int i = 0; i < 4; ++i)
        p.setValue(i * 1.0, i % 2, i / 2);

    QVERIFY(p.getValue(0, 0.5, 2) == 1.0);
    QVERIFY(p.getValue(0.5, 0, 2) == .5);
    QVERIFY(p.getValue(1.0, 0.5, 2) == 2.0);
    QVERIFY(p.getValue(.5, 1.0, 2) == 2.5);
    QVERIFY(p.getValue(.5, .5, 2) == 1.5);
}

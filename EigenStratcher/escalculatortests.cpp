#include "escalculatortests.h"
using namespace std;
using namespace Eigen;
using namespace EigenFuncs;

bool esCalculatorTests::compareMatrices33D(const Mat33D &a, const Mat33D &b) const
{
    const Mat33D dif = a - b;
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c){
            const double difEl = a(r,c) - b(r,c);
            if (difEl > eps || difEl < -eps)
                return false;
        }
    return true;
}

bool esCalculatorTests::isMatrix33DinUV(const Mat33D &mat) const
{
    for (int c = 0; c < 3; ++c){
        if (mat(2, c) > eps || mat(2, c) < -eps)
            return false;
    }
    return true;
}

void esCalculatorTests::caluclateEdgeLength(const Mat33D &mat, double &edge1, double &edge2) const
{
    edge1 = (mat.col(1) - mat.col(0)).norm();
    edge2 = (mat.col(2) - mat.col(0)).norm();
}

bool esCalculatorTests::compareTriangleEdges(const Mat33D &a, const Mat33D &b) const
{
    double ae1, ae2, be1, be2;
    caluclateEdgeLength(a, ae1, ae2);
    caluclateEdgeLength(b, be1, be2);

    const double e1d = ae1 - be1,
                 e2d = ae2 - be2;
    if (e1d > eps || e1d < -eps)
        return false;
    if (e2d > eps || e2d < -eps)
        return false;
    return true;
}
void esCalculatorTests::testCompare0()
{
    Mat33D a;
    a << -1.2 , -.3 , 2.2 , 1 , 2 , .2 , 1.2 , .6 , 1.1;
    Mat33D b;
    b << -1.20000, -.3, 2.2000, (.5+.5), .2 * 10.0, .2, 1.2, .6, 1.1;

    QVERIFY(compareMatrices33D(a,b));
}

void esCalculatorTests::testCompare1()
{
    Mat33D a;
    a << 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, .5, .5, .5;
    Mat33D b = a;

    QVERIFY(compareMatrices33D(a,b));
}

void esCalculatorTests::testNonCompare0()
{
    Mat33D a;
    a << 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, .5, .5, .5;
    Mat33D b;
    b << 1.0, 2.0, 3.01, 3.0, 2.0, 1.0, .5, .5, .5;

    QVERIFY(!compareMatrices33D(a,b));
}

void esCalculatorTests::testQ_Simple()
{
    Mat33D a, b, Q;
    a << -1.2 , -.3 , 2.2 , 1 , 2 , .2 , 1.2 , .6 , 1.1;
    b << 1.0, 2.0, 3.01, 3.0, 2.0, 1.0, .5, .5, .5;

    esCalculator e;
    e.calculateQ(a, b, Q);

    QVERIFY(compareMatrices33D(Q * a, b));
}

void esCalculatorTests::testQ_GtoUV()
{
    Mat33D a, b, Q;
    a << 1, 2, 3, 4, 5, 6, -1, -2, 5;
    b << .5, .7, .2, .4, .9, .1, .0, .0, .0;

    esCalculator e;
    e.calculateQ(a, b, Q);

    QVERIFY(compareMatrices33D(Q * a, b));
}

void esCalculatorTests::testQ_GtoUVBorders()
{
    Mat33D a, b, Q;
    a << 1, 2, 3, 1, 4, 1, 2, 10, 2;
    b << 1.0, .0, .0, 1.0, 1.0, .0, .0, .0, .0;

    esCalculator e;
    e.calculateQ(a, b, Q);

    QVERIFY(compareMatrices33D(Q * a, b));
}

void esCalculatorTests::testQ_Same()
{
    Mat33D a, b, Q;
    b << 1.0, .0, .0, 1.0, 1.0, .0, .0, .0, .0;
    a = b;

    esCalculator e;
    e.calculateQ(a, b, Q);

    QVERIFY(compareMatrices33D(Q * a, b));
}

void esCalculatorTests::testQ_Parallel()
{
    Mat33D a, b, Q;
    a << 6.0, -.3, .2, 3.0, 6.0, .0, 2.0, 2.0, 2.0;
    b << 1.0, .0, .0, 1.0, 1.0, .0, .0, .0, .0;

    esCalculator e;
    e.calculateQ(a, b, Q);

    QVERIFY(compareMatrices33D(Q * a, b));
}

void esCalculatorTests::testQ_Ortogonal()
{
    Mat33D a, b, Q;
    a << .1, .1, .1, .1, 2.0, .1, .2, 1.0, 3.0;
    b << 1.0, .0, .0, 1.0, 1.0, .0, .0, .0, .0;

    esCalculator e;
    e.calculateQ(a, b, Q);
    QVERIFY(compareMatrices33D(Q * a, b));
}

void esCalculatorTests::testCentrate0()
{
    Mat33D a, aCentrated, aCentrAnalitic;
    a << -.1, .1, .0, .5, -.5, 1.2, 5, 8, 5;
    aCentrAnalitic << -.1, .1, .0, .1, -.9, .8, -1, 2, -1;

    esCalculator e;
    e.centrateMatrix(a, aCentrated);
    QVERIFY(compareMatrices33D(aCentrAnalitic, aCentrated));
}

void esCalculatorTests::testCentrate1()
{
    Mat33D a, aCentrated, aCentrAnalitic;
    a << -.1, .1, .0, .5, -1.5, 1, 20, 100, -120;
    aCentrAnalitic = a;

    esCalculator e;
    e.centrateMatrix(a, aCentrated);
    QVERIFY(compareMatrices33D(aCentrAnalitic, aCentrated));
}

Mat33D esCalculatorTests::calculateRGcenter(const Mat33D &g, const Mat33D &uv) const
{
    esCalculator e;
    Mat33D a, b, R, Q;

    // centrate triangles a0, and uv b0
    e.centrateMatrix(g, a);
    e.centrateMatrix(uv, b);

    // calculate Q, then closest R, which should lie down the a0 to b0 plane
    e.calculateQ(a, b, Q);
    e.calculateClosestR(Q, R);

    return R * a;
}


void esCalculatorTests::testRcenter_LiePlane()
{
    Mat33D g, uv;
    g << -1.2 , -.3 , 2.2 , 1 , 2 , .2 , 1.2 , .6 , 1.1;
    uv << 1.0, .1, .6, .9, .5, .2, .0, .0, .0;

    QVERIFY(isMatrix33DinUV(calculateRGcenter(g, uv)));
}

void esCalculatorTests::testRcenter_EqualSides()
{
    Mat33D g, uv;
    g << -1.2 , -.3 , 2.2 , 1 , 2 , .2 , 1.2 , .6 , 1.1;
    uv << 1.0, .1, .6, .9, .5, .2, .0, .0, .0;

    QVERIFY(compareTriangleEdges(calculateRGcenter(g, uv), g));
}

void esCalculatorTests::testRcenter_Complex0()
{
    Mat33D g, uv;
    g << .1, .1, .1, .1, 2.0, .1, .2, 1.0, 3.0;
    uv << 1.0, .0, .0, 1.0, 1.0, .0, .0, .0, .0;

    const Mat33D lied = calculateRGcenter(g, uv);

    QVERIFY(isMatrix33DinUV(lied));
    QVERIFY(compareTriangleEdges(lied, g));
}

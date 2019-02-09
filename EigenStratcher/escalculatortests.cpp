#include "escalculatortests.h"
using namespace std;
using namespace Eigen;

bool EsCalculatorTests::isEqualMatrices(const Matrix3d &a, const Matrix3d &b) const
{
    const Matrix3d dif = a - b;
    for (int c = 0; c < 3; ++c)
        if (abs(dif.col(c).norm()) > eps)
            return false;
    return true;
}

bool EsCalculatorTests::isTriangleStackLyingInUv(const Matrix3d &triangleStack) const
{
    return abs(triangleStack.row(2).norm()) <= eps;
}

void EsCalculatorTests::edgeLengths(const Matrix3d &triangleStack, double &edge1Length, double &edge2Length) const
{
    edge1Length = (triangleStack.col(1) - triangleStack.col(0)).norm();
    edge2Length = (triangleStack.col(2) - triangleStack.col(0)).norm();
}


bool EsCalculatorTests::isEqualTrianglesEdgeLengths(const Matrix3d &triangleStack1, const Matrix3d &triangleStack2) const
{
    double ae1, ae2, be1, be2;
    edgeLengths(triangleStack1, ae1, ae2);
    edgeLengths(triangleStack2, be1, be2);

    const double e1d = ae1 - be1,
                 e2d = ae2 - be2;

    return (abs(e1d) <= eps && abs(e2d) <= eps);
}
void EsCalculatorTests::testMatricesIsEqual0()
{
    Matrix3d a, b;
    a << -1.2, -.3 , 2.2, 1, 2, .2, 1.2, .6, 1.1;
    b << -1.20000, -.3, 2.2000, (.5+.5), .2 * 10.0, .2, 1.2, .6, 1.1;

    QVERIFY(isEqualMatrices(a,b));
}

void EsCalculatorTests::testMatricesIsEqual1()
{
    Matrix3d a, b;
    a << 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, .5, .5, .5;
    b = a;

    QVERIFY(isEqualMatrices(a,b));
}

void EsCalculatorTests::testMatricesIsNonEqual0()
{
    Matrix3d a, b;
    a << 1.0, 2.0, 3.0 , 3.0, 2.0, 1.0, .5, .5, .5;
    b << 1.0, 2.0, 3.01, 3.0, 2.0, 1.0, .5, .5, .5;

    QVERIFY(!isEqualMatrices(a,b));
}

void EsCalculatorTests::testTriangleIsInUV0()
{
    Matrix3d a;
    a <<
         .0, 1.0, 2.0,
         1.0, .0, 2.0,
         .0, .0, .0;

    QVERIFY(isTriangleStackLyingInUv(a));
}

void EsCalculatorTests::testTriangleIsInUV1()
{
    Matrix3d a;
    a <<
         1.0, 3.0, 2.0,
         1.0, .0, 2.0,
         1E-6, -5E-6, -.0;

    QVERIFY(isTriangleStackLyingInUv(a));
}

void EsCalculatorTests::testTriangleIsInsideUV0()
{
    Matrix3d a;
    a <<
         .0, 1.0, 2.0,
         1.0, .0, 2.0,
         -.0, .001, .0;

    QVERIFY(!isTriangleStackLyingInUv(a));
}

void EsCalculatorTests::testEdgeLength0()
{
    Matrix3d a;
    a <<
         .0, 1.0, 0,
         .0, .0, 3.0,
         .0, .0, 4.0;

    double e1length, e2length;
    edgeLengths(a, e1length, e2length);

    QVERIFY(abs(e1length - 1.0) <= eps);
    QVERIFY(abs(e2length - 5.0) <= eps);
}

void EsCalculatorTests::testEdgeLength1()
{
    const Matrix3d a = Matrix3d::Identity();
    double e1length, e2length;
    edgeLengths(a, e1length, e2length);

    const double rootTwo = sqrt(2.0);
    QVERIFY(abs(e1length - rootTwo) <= eps);
    QVERIFY(abs(e2length - rootTwo) <= eps);
}

void EsCalculatorTests::testEdgeLength2()
{
    const Matrix3d a = Matrix3d::Zero();
    double e1length, e2length;
    edgeLengths(a, e1length, e2length);

    QVERIFY(abs(e1length) <= eps);
    QVERIFY(abs(e2length) <= eps);
}

void EsCalculatorTests::testEdgeLengthsAreEqual0()
{
    Matrix3d a,b;
    a << .0, 3.0, 2.0, .0, 4.0, .4, .1, .1, .2;
    b << .0, 4.0, -2.0, .0, 3.0, -.4, .1, .1, .0;

    QVERIFY(isEqualTrianglesEdgeLengths(a, b));
}

void EsCalculatorTests::testEdgeLengthsAreEqual1()
{
    Matrix3d a,b;
    a << .0, 3.0, 2.0, .0, 4.0, .4, .1, .1, .2;
    b = a;

    QVERIFY(isEqualTrianglesEdgeLengths(a, b));
}

void EsCalculatorTests::testTransformBetweenAnyTriangles0()
{
    Matrix3d a, b;
    a << -1.2 , -.3 , 2.2 , 1 , 2 , .2 , 1.2 , .6 , 1.1;
    b << 1.0, 2.0, 3.01, 3.0, 2.0, 1.0, .5, .5, .5;

    Matrix3d Q =
        EsCalculator::transformBetweenTriangles(a, b);

    QVERIFY(isEqualMatrices(Q * a, b));
}

void EsCalculatorTests::testTransformBetweenTrianglesToUV()
{
    Matrix3d a, b;
    a << 1, 2, 3, 4, 5, 6, -1, -2, 5;
    b << .5, .7, .2, .4, .9, .1, .0, .0, .0;

    Matrix3d Q =
        EsCalculator::transformBetweenTriangles(a, b);

    QVERIFY(isEqualMatrices(Q * a, b));
    QVERIFY(isTriangleStackLyingInUv(Q));
}

void EsCalculatorTests::testTransformBetweenSameTrianglesIsIdentity()
{
    Matrix3d a;
    a << 1, 2, 3, 0, -1, -0, -1, -2, 5;

    QVERIFY(isEqualMatrices(EsCalculator::transformBetweenTriangles(a, a), Matrix3d::Identity()));
}

void EsCalculatorTests::testTransformBetweenTrianglesToUVCaseBorder()
{
    Matrix3d a, b;
    a << 1, 2, 3, 1, 4, 1, 2, 10, 2;
    b << 1.0, .0, .0, 1.0, 1.0, .0, .0, .0, .0;

    Matrix3d Q =
        EsCalculator::transformBetweenTriangles(a, b);

    QVERIFY(isEqualMatrices(Q * a, b));
}

void EsCalculatorTests::testTransformBetweenAnyTrianglesCaseSame()
{
    Matrix3d a, b;
    a << 1.0, .0, .0, 1.0, 1.0, .0, .0, .0, .0;
    b = a;

    Matrix3d Q =
        EsCalculator::transformBetweenTriangles(a, b);

    QVERIFY(isEqualMatrices(Q * a, b));
}

void EsCalculatorTests::testTransformBetweenAnyTrianglesCaseParallel()
{
    Matrix3d a, b;
    a << 6.0, -.3, .2, 3.0, 6.0, .0, 2.0, 2.0, 2.0;
    b << 1.0, .0, .0, 1.0, 1.0, .0, .0, .0, .0;

    Matrix3d Q =
        EsCalculator::transformBetweenTriangles(a, b);

    QVERIFY(isEqualMatrices(Q * a, b));
}

void EsCalculatorTests::testTransformBetweenAnyTrianglesCaseOrtogonal()
{
    Matrix3d a, b;
    a << .1, .1, .1, .1, 2.0, .1, .2, 1.0, 3.0;
    b << 1.0, .0, .0, 1.0, 1.0, .0, .0, .0, .0;

    Matrix3d Q =
        EsCalculator::transformBetweenTriangles(a, b);

    QVERIFY(isEqualMatrices(Q * a, b));
}

void EsCalculatorTests::testCentredTriange0()
{
    Matrix3d a, aCentrAnalitic;
    a << -.1, .1, .0, .5, -.5, 1.2, 5, 8, 5;
    aCentrAnalitic << -.1, .1, .0, .1, -.9, .8, -1, 2, -1;

    const Matrix3d aCentrated =
            EsCalculator::centredTriangleStack(a);

    QVERIFY(isEqualMatrices(aCentrAnalitic, aCentrated));
}

void EsCalculatorTests::testCentredTriange1()
{
    Matrix3d a;
    a << -.1, .1, .0, .5, -1.5, 1, 20, 100, -120;

    const Matrix3d aCentrated =
            EsCalculator::centredTriangleStack(a);

    QVERIFY(isEqualMatrices(aCentrated, a));
}

Matrix3d EsCalculatorTests::closestRotationMatrix(const Matrix3d &g, const Matrix3d &uv) const
{
    // centrate triangles a0, and uv b0
    const Matrix3d a = EsCalculator::centredTriangleStack(g);
    const Matrix3d b = EsCalculator::centredTriangleStack(uv);

    // calculate Q, then closest R, which should lie down the a0 to b0 plane
    const Matrix3d Q = EsCalculator::transformBetweenTriangles(a, b);
    return EsCalculator::closestRotationMatrix(Q);
}
Matrix3d EsCalculatorTests::closestApplyRotationMatrixToG(const Matrix3d &g, const Matrix3d &uv) const
{
    return closestRotationMatrix(g, uv) * EsCalculator::centredTriangleStack(g);
}


void EsCalculatorTests::testClosestRotationMatrixIsLyingToUV()
{
    Matrix3d g, uv;
    g << -1.2 , -.3 , 2.2 , 1 , 2 , .2 , 1.2 , .6 , 1.1;
    uv << 1.0, .1, .6, .9, .5, .2, .0, .0, .0;

    QVERIFY(isTriangleStackLyingInUv(closestApplyRotationMatrixToG(g, uv)));
}

void EsCalculatorTests::testClosestRotationMatrixDoNotChangeEdgeLength()
{
    Matrix3d g, uv;
    g << -1.2 , -.3 , 2.2 , 1 , 2 , .2 , 1.2 , .6 , 1.1;
    uv << 1.0, .1, .6, .9, .5, .2, .0, .0, .0;

    QVERIFY(isEqualTrianglesEdgeLengths(closestApplyRotationMatrixToG(g, uv), g));
}

void EsCalculatorTests::testClosestRotationAnyCase()
{
    Matrix3d g, uv;
    g << .1, .1, .1, .1, 2.0, .1, .2, 1.0, 3.0;
    uv << 1.0, .0, .0, 1.0, 1.0, .0, .0, .0, .0;

    const Matrix3d lied = closestApplyRotationMatrixToG(g, uv);

    QVERIFY(isTriangleStackLyingInUv(lied));
    QVERIFY(isEqualTrianglesEdgeLengths(lied, g));
}

void EsCalculatorTests::testClosestRotationMatrixNumerical0()
{
    Matrix3d g, uv;
    g << .0, 1, 2, 1, 0, 1, 2, 2, 2;
    uv << .0, .5, 1, .5, .0, .5, 0, 0, 0;

    QVERIFY(isEqualMatrices(Matrix3d::Identity(), closestRotationMatrix(g, uv)));
}

void EsCalculatorTests::testClosestRotationMatrixNumerical1()
{
    Matrix3d g, uv, Ranalitic;
    g << .0, 1, 2, 2, 2, 2, 1, 0, 1;
    uv << .0, .5, 1, .5, .0, .5, 0, 0, 0;

    Ranalitic << 1, 0, 0, 0, 0, 1, 0, -1, 0;

    QVERIFY(isEqualMatrices(Ranalitic, closestRotationMatrix(g, uv)));
}

#include "escalculatorhelp.h"

using namespace EsCalculator;
using namespace Eigen;
using namespace std;

void EsCalculatorHelp::testRandomTriangleWithPainting(QPainter *qp, EsDrawer *dr)
{
        dr->drawSystemG(qp, 5);

        const Matrix3d V_g0 = MatrixXd::Random(3,3);
        Matrix3d V_uv0 = //MatrixXd::Random(3,3);
                (Matrix3d::Identity() - MatrixXd::Random(3,3)) * .5;
        V_uv0(2,0) = V_uv0(2,1) = V_uv0(2,2) = 0.0;

        const Matrix3d V_g = centredTriangleStack(V_g0);
        const Matrix3d V_uv = centredTriangleStack(V_uv0);

        const Matrix3d Q = transformBetweenTriangles(V_g, V_uv);
        const Matrix3d R = closestRotationMatrix(Q);
        const Matrix3d V_gR = R * V_g;

        const Matrix2d e12 = edgeStack(V_uv);
        const Matrix2d e12_R = edgeStack(V_gR);

        const Matrix2d T = transformBetweenEdgePair(e12, e12_R);

//        traceMatrix(e12, "e12");
//        traceMatrix(e12_R, "e12 '");
//        traceMatrix(T, "T");
//        const Matrix2d tt = T * e12;
//        traceMatrix((tt), "T * e12");

        const Matrix2d S = stretchCompressAxes(Q, R, T);
        traceMatrix(S);

    //    dr->debugTriangle(qp, V_g);
        dr->debugTriangle(qp, V_uv0, QColor(200, 20, 250, 20));
        dr->debugTriangle(qp, V_uv, QColor(40, 40, 200, 100));
        dr->debugTriangle(qp, V_gR, QColor(0, 200, 0, 150));

    //    coutEdgeLengths("v_g", V_g);
    //    coutEdgeLengths("v_gR", V_gR);
    //    coutEdgeLengths("v_uv", V_uv);

    //    coutMatrix("v_gR", V_gR);
    //    coutMatrix("v_uv", V_uv);
        const double uNorm = S.col(0).norm(),
                     vNorm = S.col(1).norm();

        // haha!
        //cout << endl << uNorm * svd.singularValues()(0,0) << "  " << vNorm * svd.singularValues()(1,0)<< endl;

        const Vector2d zer = Vector2d::Zero();
        const Vector2d stretchAxis = S.col(0) * .2;
        const Vector2d compressAxis = S.col(1) * .2;

        dr->drawLine(qp, zer, stretchAxis, QColor(30, 30, 200), 2);
        dr->drawLine(qp, zer, compressAxis, Qt::red, 2);
}

void EsCalculatorHelp::testRandom2TriangleWithPainting(QPainter *qp, EsDrawer *dr)
{
    dr->drawSystemG(qp, 3);
    dr->drawSystemUV(qp);

    const Matrix3d triangleStack = MatrixXd::Random(3,3) + 2 * Matrix3d::Ones();
    const Matrix3d targetTriangleStack = triangleStack + .4 * MatrixXd::Random(3,3) + Matrix3d::Ones();
    Matrix3d triangleUvTriangleStack = MatrixXd::Random(3,3);
    triangleUvTriangleStack = (triangleUvTriangleStack + Matrix3d::Ones()) * .5;
    triangleUvTriangleStack(2,0) = triangleUvTriangleStack(2,1) = triangleUvTriangleStack(2,2) = 0.0;

    dr->debugTriangle(qp, triangleStack, Qt::darkRed);
    dr->debugTriangle(qp, targetTriangleStack, Qt::darkBlue);
    dr->debugTriangleUV(qp, triangleUvTriangleStack, Qt::darkYellow);

    const Matrix3d Vg0 = centredTriangleStack(triangleStack);
    const Matrix3d VgT = centredTriangleStack(targetTriangleStack);
    const Matrix3d Vuv = centredTriangleStack(triangleUvTriangleStack);

    dr->debugTriangle(qp, Vg0, Qt::red);
    dr->debugTriangle(qp, VgT, Qt::blue);
    dr->debugTriangleUV(qp, Vuv, Qt::yellow);

    // V_g0 -> V_g1
    // Q0 * V_g0 = V_uv, Q1 * V_g1 = V_uv
    // Q0 =V_uv * V_g0-1, etc
    const Matrix3d Q0 = transformBetweenTriangles(Vg0, Vuv);
    const Matrix3d QT = transformBetweenTriangles(VgT, Vuv);

    // R0 = R0(Q0)
    const Matrix3d R0 = closestRotationMatrix(Q0);
    const Matrix3d RT = closestRotationMatrix(QT);

    const Matrix2d e12 = edgeStack(R0 * Vg0);
    const Matrix2d e12_R = edgeStack(RT * VgT);

    dr->debugTriangleUV(qp, R0 * Vg0, Qt::red);
    dr->debugTriangleUV(qp, RT * VgT, Qt::blue);
    return;
    // T = ...
    const Matrix2d T = transformBetweenEdgePair(e12, e12_R);
    //
    const Matrix2d S = stretchCompressAxes(Q0, R0, T);
    //
}

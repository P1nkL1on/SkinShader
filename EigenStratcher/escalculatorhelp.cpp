#include "escalculatorhelp.h"

using namespace EsCalculator;
using namespace Eigen;
using namespace std;

void EsCalculatorHelp::testRandomTriangleWithPainting(QPainter *qp, EsDrawer *dr)
{
        dr->drawSystemG(qp, 5);

        const Matrix3d V_g0 = MatrixXd::Random(3,3);
        Matrix3d V_uv0 = MatrixXd::Random(3,3);
//                (Matrix3d::Identity() - MatrixXd::Random(3,3)) * .5;
        V_uv0(2,0) = V_uv0(2,1) = V_uv0(2,2) = 0.0;

        const Matrix3d V_g = centredTriangleStack(V_g0);
        const Matrix3d V_uv = centredTriangleStack(V_uv0);

        const Matrix3d Q = transformBetweenTriangles(V_g, V_uv);
        const Matrix3d R = closestRotationMatrix(Q);
        const Matrix3d V_gR = R * V_g;

        const Matrix2d e12 = edgeStack(V_uv);
        const Matrix2d e12_R = edgeStack(V_gR);

        const Matrix2d T = transformBetweenEdgePair(e12, e12_R);

        JacobiSVD<MatrixXd> svd(T, ComputeFullU | ComputeFullV);
//        cout << endl << svd.singularValues() << endl;

        Matrix2d S = leftTopBlock(Q * R.transpose()) * svd.matrixV();
//        traceMatrix("S = Q * R^t", Q * R.transpose());
//        traceMatrix("S = Q * R^t * V", S);


    //    dr->debugTriangle(qp, V_g);
        dr->debugTriangle(qp, V_uv, QColor(50, 80, 240, 150));
        dr->debugTriangle(qp, V_gR, QColor(200, 200, 0, 150));

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
        const Vector2d stretchAxis = S.col(0);
        const Vector2d compressAxis = S.col(1);

        dr->drawLine(qp, zer, stretchAxis, QColor(30, 30, 200), 3);
        dr->drawLine(qp, zer, compressAxis, Qt::red, 3);
}

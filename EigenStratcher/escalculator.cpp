#include "escalculator.h"
#include <Eigen/Dense>

using namespace EigenFuncs;
using namespace std;
using namespace Eigen;

void esCalculator::test(QPainter *qp, esDrawer *dr) const
{
    cout << "****************" << endl;
    //dr->drawTriangleG();
    const QVector<Vector3D> gc =
    {
        makeVector3D(2.3, 2.0, 1.7),
        makeVector3D(-.15, 1.0, 1.1),
        makeVector3D(1.6, -.7, 0.7)
    };
    const QVector<Vector2D> UVc =
    {
        makeVector2D(.0, .0),
        makeVector2D(.0, .5),
        makeVector2D(.75, .0)
    };

    const Mat33D matg =  MatrixXd::Random(3,3);
//            makeMat33DFrom3Vector3D(
//            gc[0], gc[1], gc[2]);
    const Mat23D matUV = MatrixXd::Random(2,3);
//            makeMat23DFrom3Vector2D(
//            UVc[0], UVc[1], UVc[2]);

    cout <<  "V_g = матрица мировых координат" << endl << (matg) << endl << endl << "V_uv = текстурные на плоскости" << endl << (matUV) << endl;
    cout << endl<< "Q= трансформа чтобы V_g --> V_uv" << endl;

    const auto Q = matUV * matg.inverse();

    cout << Q << endl << "^  Q = V_uv * V_g-1  формула для вычисления матрицы" << endl << endl;// << endl << "v  V_uv = Q * V_g" << endl;
    //cout << (Q * matg) << endl << endl;

    JacobiSVD<MatrixXd> svd(Q, ComputeFullU | ComputeFullV);
//    cout << "Its singular values are:" << endl << svd.singularValues()(0,0) << svd.singularValues()(1,0) << endl;
//    cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << svd.matrixU() << endl;
//    cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd.matrixV() << endl;

    Mat23D RI;
    RI << 1, 0, 0, 0, 1, 0;
    Mat23D R = svd.matrixU() * RI * svd.matrixV().transpose();
    cout << "R = транфсформа, переносящая V_g в плоскость V_uv, но только юниформом" << endl << R << endl << endl <<"R * V_g = "<< endl<< (R * matg) << endl;

    dr->drawSystemG(qp, 5);
    //dr->drawTriangleG(qp, gc[0], gc[1], gc[2]);
    dr->debugTriangle(qp, matg);
    dr->debugTriangle(qp, matUV);
    const Mat23D d2 = R * matg;
    dr->debugTriangle(qp, d2);

    cout << endl << endl << endl << matg << endl << endl << d2 << endl;
}

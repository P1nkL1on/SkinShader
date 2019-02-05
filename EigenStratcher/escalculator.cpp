#include "escalculator.h"
#include <Eigen/Dense>

using namespace EigenFuncs;
using namespace std;
using namespace Eigen;

void esCalculator::test(QPainter *qp, esDrawer *dr) const
{
    cout << "****************" << endl;
    //dr->drawTriangleG();
    const QVector<Vector3D> gc = {
        makeVector3D(1.3, 2.0, 1.7),
        makeVector3D(-.5, .0, -1.7),
        makeVector3D(.6, -.7, 0.7)
    };
    const QVector<Vector2D> UVc = {
        makeVector2D(.0, .0),
        makeVector2D(.0, .5),
        makeVector2D(.75, .0)
    };

    const Mat33D matg = makeMat33DFrom3Vector3D(
                        gc[0], gc[1], gc[2]);
    const Mat23D matUV = makeMat23DFrom3Vector2D(
                        UVc[0], UVc[1], UVc[2]);

    cout <<  "V_g = " << endl << (matg) << endl << endl << "V_uv = " << endl << (matUV) << endl;
    cout << endl<< "Q=" << endl;

    const auto Q = matUV * matg.inverse();

    cout << Q << endl << "^  Q = V_uv * V_g-1" << endl << endl << "v  V_uv = Q * V_g" << endl;
    cout << (Q * matg) << endl << endl;

    JacobiSVD<MatrixXd> svd(Q, ComputeThinU | ComputeThinV);
    cout << "Its singular values are:" << endl << svd.singularValues()(0,0) << svd.singularValues()(1,0) << endl;
//    cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << svd.matrixU() << endl;
//    cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd.matrixV() << endl;


}

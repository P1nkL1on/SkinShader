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

    Mat33D V_g =  MatrixXd::Random(3,3);
    //            makeMat33DFrom3Vector3D(
    //            gc[0], gc[1], gc[2]);
    const Mat23D V_uv = MatrixXd::Random(2,3);
    //            makeMat23DFrom3Vector2D(
    //            UVc[0], UVc[1], UVc[2]);

    V_g(2,0) = V_g(2,1) = V_g(2,2) = 1.5;

    cout <<  "V_g =" << endl << (V_g) << endl << endl << "V_uv =" << endl << (V_uv) << endl;
    cout << endl<< "Q=" << endl;

    const Mat23D Q = V_uv * V_g.inverse();

    cout << Q << endl << "^  Q = V_uv * V_g-1 " << endl << endl;// << endl << "v  V_uv = Q * V_g" << endl;
    //cout << (Q * matg) << endl << endl;

    JacobiSVD<MatrixXd> svd(Q, ComputeFullU | ComputeFullV);
    //    cout << "Its singular values are:" << endl << svd.singularValues()(0,0) << svd.singularValues()(1,0) << endl;
        cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << svd.matrixU() << endl;
        cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd.matrixV() << endl;

    Mat23D RI;
    RI << 1.0, .0, .0, .0, 1.0, .0;
    Mat23D RI0;
    RI0 << svd.singularValues()(0,0), 0, 0, 0, svd.singularValues()(1,0), 0;

    Mat23D R = svd.matrixU() * RI * svd.matrixV().transpose();
    const Mat23D VR_uv = R * V_g;
    cout << "RI = " <<endl << RI << endl << endl << "RI0 = " << endl << RI0 << endl << endl << "Q = U * RI0 * V^T " << endl << (svd.matrixU() * RI0 * svd.matrixV().transpose()) << endl<<endl;
    cout << "R = U * RI * V^T" << endl << R << endl << endl <<"R * V_g = VR_uv"<< endl<< VR_uv << endl <<endl << "Q * V_g = V_uv" << endl << "R * V_g = VR_uv" << endl;

    dr->drawSystemG(qp, 5);
    dr->debugTriangle(qp, V_g);
    //dr->debugTriangle(qp, V_uv);
    dr->debugTriangle(qp, VR_uv);

    Mat22D e12, e12R;
    calculateE1E2(V_uv, e12);
    cout << "'" ;
    calculateE1E2(VR_uv, e12R);

    Mat22D T = e12R * (e12.inverse());
    cout <<endl << "T = "  << endl << T << endl << endl << (T * e12) << endl;
}

void esCalculator::calculateE1E2(const Mat23D &orig, Mat22D &res) const
{
    res << orig(0,1) - orig(0,0), orig(0,2) - orig(0,0),
           orig(1,1) - orig(1,0), orig(1,2) - orig(1,0);
    cout << "e1e2 = " << endl << res << endl << endl;
}

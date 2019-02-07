#include "escalculator.h"
#include <Eigen/Dense>
#include <Eigen/QR>

using namespace EigenFuncs;
using namespace std;
using namespace Eigen;

void esCalculator::test0() const
{
    cout << endl << "**************" << endl;

    Matrix<double, 3,3> V_g30;
    V_g30 << -1.2 ,  -.3 ,  2.2 ,  1 ,  2 ,  .2 ,  1.2 ,  .6 ,  1.1;
    Matrix<double, 3,3> V_uv30;
    V_uv30 << .75,  .5,  .05,  .99,  .0,  .2,  .0,  .0,  .0;


    Matrix<double, 3,3> V_g3;
    Matrix<double, 3,3> V_uv3;
    const auto g3center = centrateMatrix(V_g30, V_g3);
    cout << "det " << V_g3.determinant() << endl;
    const auto uv3center = centrateMatrix(V_uv30, V_uv3);
//    V_g3 = V_g30;
//    V_uv3 = V_uv30;


    const Matrix<double, 3,3> Q3 = V_uv3 * V_g3.completeOrthogonalDecomposition().pseudoInverse();//.inverse();
    const Matrix<double, 3,3> prover = (Q3 * V_g3);

    cout << endl << "V_g = " << endl << V_g3 << endl;
    cout << endl << "V_uv = " << endl << V_uv3 << endl;
    cout << endl << "Q = " << endl << Q3 << endl;
    cout << endl << "Q * V_g " << endl << prover << endl;
    cout << endl << "delta (Q*V_g, V_uv) " << endl << (V_uv3 - prover) << endl;
}

void esCalculator::test(QPainter *qp, esDrawer *dr) const
{
//    cout << "****************" << endl;
//    //dr->drawTriangleG();
//    const QVector<Vector3D> gc =
//    {
//        makeVector3D(2.3, 2.0, 1.7),
//        makeVector3D(-.15, 1.0, 1.1),
//        makeVector3D(1.6, -.7, 0.7)
//    };
//    const QVector<Vector2D> UVc =
//    {
//        makeVector2D(.0, .0),
//        makeVector2D(.0, .5),
//        makeVector2D(.75, .0)
//    };

//    const Mat33D V_g =  MatrixXd::Random(3,3);
//    //            makeMat33DFrom3Vector3D(
//    //            gc[0], gc[1], gc[2]);
//    const Mat23D V_uv = MatrixXd::Random(2,3);
//    //            makeMat23DFrom3Vector2D(
//    //            UVc[0], UVc[1], UVc[2]);

//    //V_g(2,0) = V_g(2,1) = V_g(2,2) = 1.5;

//    cout <<  "V_g =" << endl << (V_g) << endl << endl << "V_uv =" << endl << (V_uv) << endl;
//    cout << endl<< "Q=" << endl;

//    const Mat23D Q = V_uv * V_g.inverse();

//    cout << Q << endl << "^  Q = V_uv * V_g-1 " << endl << endl;// << endl << "v  V_uv = Q * V_g" << endl;
//    //cout << (Q * matg) << endl << endl;

//    JacobiSVD<MatrixXd> svd(Q, ComputeFullU | ComputeFullV);
//    //    cout << "Its singular values are:" << endl << svd.singularValues()(0,0) << svd.singularValues()(1,0) << endl;
//        cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << svd.matrixU() << endl;
//        cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd.matrixV() << endl;

//    Mat23D RI;
//    RI << 1.0, .0, .0, .0, 1.0, .0;
//    Mat23D RI0;
//    RI0 << svd.singularValues()(0,0), 0, 0, 0, svd.singularValues()(1,0), 0;

//    Mat23D R = svd.matrixU() * RI * svd.matrixV().transpose();
//    const Mat23D VR_uv = R * V_g;
//    cout << "RI = " <<endl << RI << endl << endl << "RI0 = " << endl << RI0 << endl << endl << "Q = U * RI0 * V^T " << endl << (svd.matrixU() * RI0 * svd.matrixV().transpose()) << endl<<endl;
//    cout << "R = U * RI * V^T" << endl << R << endl << endl <<"R * V_g = VR_uv"<< endl<< VR_uv << endl <<endl << "Q * V_g = V_uv" << endl << "R * V_g = VR_uv" << endl;

    dr->drawSystemG(qp, 5);
//    //dr->debugTriangle(qp, V_g);
//    //dr->debugTriangle(qp, V_uv);
//    //dr->debugTriangle(qp, VR_uv);

//    Mat22D e12, e12R;
//    calculateE1E2(V_uv, e12);
//    cout << "'" ;
//    calculateE1E2(VR_uv, e12R);

//    Mat22D T = e12R * (e12.inverse());
//    cout <<endl << "T = "  << endl << T << endl << endl << (T * e12) << endl;


    cout << "****333333****" << endl;
    Mat33D V_g3 = MatrixXd::Random(3,3);
    Mat33D V_uv3 = MatrixXd::Random(3,3);
    V_uv3(2,0) = V_uv3(2,1) = V_uv3(2,2) = 0.0;



    Mat33D g3centered, uv3centered;
    const auto g3center = centrateMatrix(V_g3, g3centered);
    const auto uv3center = centrateMatrix(V_uv3, uv3centered);
    //dr->debugTriangle(qp, V_g3);

    //dr->debugTriangle(qp, V_uv3);

    const Mat33D Q3 = uv3centered * g3centered.completeOrthogonalDecomposition().pseudoInverse();
    const Mat33D prover = (Q3 * g3centered);

    cout << endl << "V_g = " << endl << g3centered << endl;
    cout << endl << "V_uv = " << endl << uv3centered << endl;
    cout << endl << "Q = " << endl << Q3 << endl;
    cout << endl << "Q * V_g " << endl << prover << endl;

    dr->debugTriangle(qp, g3centered);
    dr->debugTriangle(qp, uv3centered);
    dr->debugTriangle(qp, prover);

    cout << endl << "Q centered = " << endl << Q3 << endl;
    JacobiSVD<MatrixXd> svd3(Q3, ComputeFullU | ComputeFullV);
    cout << "Its singular values are:" << endl << svd3.singularValues() << endl;
//    cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << svd3.matrixU() << endl;
//    cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd3.matrixV() << endl;

    const double singNorm = 1.0;

    Mat33D RI3;
    RI3 << singNorm, .0, .0,
           .0, singNorm, .0,
           .0, .0, singNorm;

    Mat33D RI03;
    RI03 << svd3.singularValues()(0,0), .0, .0,
            .0, svd3.singularValues()(1,0), .0,
            .0, .0, svd3.singularValues()(2,0);

    cout << endl <<"I=" << endl << RI3 << endl;
    cout << endl <<"I sigma=" << endl << RI03 << endl;

    const Mat33D R3 = svd3.matrixU() * RI3 * svd3.matrixV().transpose();
    const Mat33D res = (R3 * g3centered);
    cout << endl <<"R3=" << endl << R3 << endl;
    cout << endl <<"res=" << endl << res << endl;
    cout << endl <<"target=" << endl << uv3centered << endl;

    dr->debugTriangle(qp, res);

//    const Mat33D Q3 = V_uv3 * V_g3.inverse();
//    JacobiSVD<MatrixXd> svd3(Q3, ComputeFullU | ComputeFullV);
//    cout << "Q3x3 = "<< Q3 << endl;
//    //cout << "Its singular values are:" << endl << svd3.singularValues() << endl;
//    //cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << svd3.matrixU() << endl;
//    //cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd3.matrixV() << endl;

//    const double singNorm = 1.0;//svd3.singularValues().norm();
//    Mat33D RI3;
//    RI3 << singNorm, .0, .0,
//           .0, singNorm, .0,
//           .0, .0, singNorm;
//    Mat33D RI03;
//    RI03 << svd3.singularValues()(0,0), .0, .0,
//            .0, svd3.singularValues()(1,0), .0,
//            .0, .0, svd3.singularValues()(2,0);
//    cout << "RI3" << endl << RI3 << endl;
//    cout << "RI03" << endl << RI03 << "  @@ "<< RI03.determinant()<<endl;
//    const Mat33D R3 = svd3.matrixU() /* * RI3*/ * svd3.matrixV().transpose();
//    const Mat33D VR_uv3 = R3 * V_g3;


//    cout << "Q3 = " << endl << (svd3.matrixU() * RI03 * svd3.matrixV().transpose()) << endl;
//    cout << "R3 = " << endl << R3 << endl;
//    cout << "orig UV" << endl << V_uv3 << endl;
//    cout << "orig" << endl << V_g3 << endl;
//    cout << "res" << endl << VR_uv3 << endl;

    cout << endl << "O:  ";
    for (int i = 1; i < 3; ++i)
        cout << (g3centered.col(i) - g3centered.col(0)).norm() <<", ";
    cout << endl << "R:  ";
    for (int i = 1; i < 3; ++i)
        cout << (res.col(i) - res.col(0)).norm() <<", ";
    cout << endl;

    //cout << endl << (svd3.matrixV().transpose() * svd3.matrixV()) << endl << endl << (svd3.matrixU().transpose() * svd3.matrixU()) << endl;
}

void esCalculator::calculateE1E2(const Mat23D &orig, Mat22D &res) const
{
    res << orig(0,1) - orig(0,0), orig(0,2) - orig(0,0),
           orig(1,1) - orig(1,0), orig(1,2) - orig(1,0);
    cout << "e1e2 = " << endl << res << endl << endl;
}

Matrix<double, 3, 1> esCalculator::centrateMatrix(const Mat33D &orig, Mat33D &res) const
{
    const Matrix<double, 3, 1> g3center = (orig.col(0) + orig.col(1) + orig.col(2)) / 3.0;
    res = orig;
    for (int i = 0; i < 3; ++i) // demension
        for (int j = 0; j < 3; ++j) // dot index
            res(i, j) -= g3center(i,0);

    cout << endl << "Matrix = " << endl << orig << endl;
    cout << endl << "Centered matrix = " << endl << res << endl;

    return g3center;
}

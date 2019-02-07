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
//    V_g30 << -1.2 ,  -.3 ,  2.2 ,  1 ,  2 ,  .2 ,  1.2 ,  .6 ,  1.1;
    Matrix<double, 3,3> V_uv30;
//    V_uv30 << .75,  .5,  .05,  .99,  .0,  .2,  .0,  .0,  .0;
    V_g30 <<  0.179551, 0.142379, -0.32193,
             -0.646687, 0.927702, -0.281014,
              0.195603, 0.63568, -0.831284;
    V_uv30 <<  0.10832, 0.265491, -0.373811,
               1.05258, -0.442457, -0.610126,
               0, 0, 0;

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
    dr->drawSystemG(qp, 5);

    const
    Mat33D V_g0 = MatrixXd::Random(3,3);
    Mat33D V_uv0 = MatrixXd::Random(3,3);

    V_uv0(2,0) = V_uv0(2,1) = V_uv0(2,2) = 0.0;

    Mat33D V_g, V_uv, Q, R, V_gR;

    centrateMatrix(V_g0, V_g);
    centrateMatrix(V_uv0, V_uv);

    calculateQ(V_g, V_uv, Q);
    calculateClosestR(Q, R);

    V_gR = R * V_g;

    dr->debugTriangle(qp, V_g);
    dr->debugTriangle(qp, V_uv);
    dr->debugTriangle(qp, V_gR);

    coutEdgeLengths("v_g", V_g);
    coutEdgeLengths("v_gR", V_gR);
    coutEdgeLengths("v_uv", V_uv);

    coutMatrix("v_gR", V_gR);
    coutMatrix("v_uv", V_uv);
}

void esCalculator::calculateE1E2(const Mat23D &orig, Mat22D &res) const
{
    res << orig(0,1) - orig(0,0), orig(0,2) - orig(0,0),
           orig(1,1) - orig(1,0), orig(1,2) - orig(1,0);
    //    coutMatrix("e1e2 =", res);
}

void esCalculator::coutMatrix(const string &name, const MatrixXd &doubleMatrix) const
{
    cout << endl << name << "= " << endl << doubleMatrix << endl;
}

void esCalculator::coutEdgeLengths(const string &name, const MatrixXd &mat) const
{
    double edge1 = (mat.col(1) - mat.col(0)).norm();
    double edge2 = (mat.col(2) - mat.col(0)).norm();
    cout << endl << name << ": {"<< edge1<<", " << edge2 << "}" << endl;
}

Matrix<double, 3,1> esCalculator::centrateMatrix(const Mat33D &orig, Mat33D &res) const
{
    const Matrix<double, 3, 1> g3center = (orig.col(0) + orig.col(1) + orig.col(2)) / 3.0;
    res = orig;
    for (int i = 0; i < 3; ++i) // demension
        for (int j = 0; j < 3; ++j) // dot index
            res(i, j) -= g3center(i,0);
//    coutMatrix("Incoming matrix =", orig);
//    coutMatrix("Centered matrix =", res);
    return g3center;
}

void esCalculator::calculateQ(const Mat33D &V_g, const Mat33D &V_uv, Mat33D &resQ) const
{
//    resQ = V_uv * V_g.inverse();
    resQ = V_uv * V_g.completeOrthogonalDecomposition().pseudoInverse();
}

void esCalculator::calculateClosestR(const Mat33D &Q, Mat33D &resR) const
{
    Mat33D I3;
    I3 << 1.0, 0, 0,
          0, 1.0, 0,
          0, 0, 1.0;
    JacobiSVD<MatrixXd> svd(Q, ComputeFullU | ComputeFullV);
//    Mat33D RI03;
//    RI03 << svd.singularValues()(0,0), .0, .0,
//            .0, svd.singularValues()(1,0), .0,
//            .0, .0, svd.singularValues()(2,0);

//    cout << "Its singular values are:" << endl << svd.singularValues() << endl;
//    cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << svd.matrixU() << endl;
//    cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd.matrixV() << endl;
//    coutMatrix("Q = U*sig*Vt", (svd.matrixU() * RI03 * svd.matrixV().transpose()));
    resR = svd.matrixU() * I3 * svd.matrixV().transpose();
}

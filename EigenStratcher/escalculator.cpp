#include "escalculator.h"
#include <Eigen/Dense>
#include <Eigen/QR>

using namespace EigenFuncs;
using namespace std;
using namespace Eigen;

//void EsCalculator::test0() const
//{
//    cout << endl << "**************" << endl;

//    Matrix<double, 3,3> V_g30;
////    V_g30 << -1.2 ,  -.3 ,  2.2 ,  1 ,  2 ,  .2 ,  1.2 ,  .6 ,  1.1;
//    Matrix<double, 3,3> V_uv30;
////    V_uv30 << .75,  .5,  .05,  .99,  .0,  .2,  .0,  .0,  .0;
//    V_g30 <<  0.179551, 0.142379, -0.32193,
//             -0.646687, 0.927702, -0.281014,
//              0.195603, 0.63568, -0.831284;
//    V_uv30 <<  0.10832, 0.265491, -0.373811,
//               1.05258, -0.442457, -0.610126,
//               0, 0, 0;

//    Matrix<double, 3,3> V_g3;
//    Matrix<double, 3,3> V_uv3;
//    const auto g3center = centredTriangleStack(V_g30, V_g3);
//    cout << "det " << V_g3.determinant() << endl;
//    const auto uv3center = centredTriangleStack(V_uv30, V_uv3);
////    V_g3 = V_g30;
////    V_uv3 = V_uv30;


//    const Matrix<double, 3,3> Q3 = V_uv3 * V_g3.completeOrthogonalDecomposition().pseudoInverse();//.inverse();
//    const Matrix<double, 3,3> prover = (Q3 * V_g3);

//    cout << endl << "V_g = " << endl << V_g3 << endl;
//    cout << endl << "V_uv = " << endl << V_uv3 << endl;
//    cout << endl << "Q = " << endl << Q3 << endl;
//    cout << endl << "Q * V_g " << endl << prover << endl;
//    cout << endl << "delta (Q*V_g, V_uv) " << endl << (V_uv3 - prover) << endl;
//}

//void EsCalculator::test(QPainter *qp, EsDrawer *dr) const
//{
//    dr->drawSystemG(qp, 5);

//    const
//    Mat33D V_g0 = MatrixXd::Random(3,3);
//    Mat33D V_uv0 = MatrixXd::Random(3,3);

//    V_uv0(2,0) = V_uv0(2,1) = V_uv0(2,2) = 0.0;

//    Mat33D V_g, V_uv, Q, R, V_gR;

//    centredTriangleStack(V_g0, V_g);
//    centredTriangleStack(V_uv0, V_uv);

//    transformBetweenTriangles(V_g, V_uv, Q);
//    calculateClosestR(Q, R);

//    V_gR = R * V_g;
//    Mat22D e_R, e;
//    calculateE1E2(V_uv, e);
//    calculateE1E2(V_gR, e_R);

//    traceMatrix("v_gR 3x3", V_gR);
//    traceMatrix("e1e2 __ R 2x2", e_R);

//    Mat22D T;
//    calculateT(e, e_R, T);

//    JacobiSVD<MatrixXd> svd(T, ComputeFullU | ComputeFullV);
//    cout << endl << svd.singularValues() << endl;

//    Mat22D S = removeLastRow(Q * R.transpose()) * svd.matrixV();
//    traceMatrix("S = Q * R^t", Q * R.transpose());
//    traceMatrix("S = Q * R^t * V", S);


////    dr->debugTriangle(qp, V_g);
//    dr->debugTriangle(qp, V_uv, QColor(50, 80, 240, 150));
//    dr->debugTriangle(qp, V_gR, QColor(200, 200, 0, 150));

////    coutEdgeLengths("v_g", V_g);
////    coutEdgeLengths("v_gR", V_gR);
////    coutEdgeLengths("v_uv", V_uv);

////    coutMatrix("v_gR", V_gR);
////    coutMatrix("v_uv", V_uv);
//    const double uNorm = S.col(0).norm(),
//                 vNorm = S.col(1).norm();

//    // haha!
//    //cout << endl << uNorm * svd.singularValues()(0,0) << "  " << vNorm * svd.singularValues()(1,0)<< endl;

//    dr->drawLine(qp, makeVector3D(0, 0, 0), makeVector3D(S(0,0) / uNorm, S(1,0) / uNorm, 0), QColor(30, 30, 200), 3);
//    dr->drawLine(qp, makeVector3D(0, 0, 0), makeVector3D(S(0,1) / vNorm, S(1,1) / vNorm, 0), Qt::red, 3);
//}

//Mat22D EsCalculator::removeLastRow(const Mat33D &mat) const
//{
//    Mat22D res;
//    res << mat(0,0), mat(0,1), mat(1,0), mat(1,1);
//    return res;
//}

void EsCalculator::traceMatrix(const Matrix3Xd &doubleMatrix, const string &name)
{
    cout << endl << name << "= " << endl << doubleMatrix << endl;
}
void EsCalculator::traceEdgeLengths(const Matrix3d &triangleStack, const string &name)
{
    double edgeLength1 = (triangleStack.col(1) - triangleStack.col(0)).norm();
    double edgeLength2 = (triangleStack.col(2) - triangleStack.col(0)).norm();
    cout << endl << name << ": {"<< edgeLength1<<", " << edgeLength2 << "}" << endl;
}

Vector3d EsCalculator::centredTriangleStack(const Matrix3d &originalTriangleStack, Matrix3d &resultCentredTriangleStack)
{
    const Vector3d centerColumnValue =
            1 / 3.0
            * (originalTriangleStack.col(0)
             + originalTriangleStack.col(1)
             + originalTriangleStack.col(2));

    resultCentredTriangleStack = originalTriangleStack;
    for (int colIndex = 0; colIndex < 3; ++colIndex)
        resultCentredTriangleStack.col(colIndex) -= centerColumnValue;

    return centerColumnValue;
}

Matrix3d EsCalculator::centredTriangleStack(const Matrix3d &originalTriangleStack)
{
    Matrix3d res;
    const Vector3d center = centredTriangleStack(originalTriangleStack, res);
    return res;
}

Matrix3d EsCalculator::transformBetweenTriangles(const Matrix3d &triangleStack, const Matrix3d &targetTriangleStack)
{
    // Q * V_g = V_uv
    // ret Q = V_uv * V_g^-1
    return targetTriangleStack * triangleStack.completeOrthogonalDecomposition().pseudoInverse();
}

Matrix3d EsCalculator::closestRotationMatrix(const Matrix3d &transformMatrix)
{
    // Q = U * sigm * V^t
    // T = U * I * V^t
    const Matrix3d I = Matrix3d::Identity();
    JacobiSVD<Matrix3d> svd(transformMatrix, ComputeFullU | ComputeFullV);

    return svd.matrixU() * I * svd.matrixV().transpose();
}

Matrix2d EsCalculator::transformBetweenEdgePair(const Matrix2d &originalEdgeStack, const Matrix2d &targetEdgeStack)
{
    // target edge stack    transf * edgeStack original
    // [e1', e2']           = T * [e1  e2]
    // T = [e1' e2'] * [e1 e2]^-1
    return targetEdgeStack * originalEdgeStack.completeOrthogonalDecomposition().pseudoInverse();
}

Matrix2d EsCalculator::leftTopBlock(const Matrix3d &triangleStack)
{
    // [x y] z
    // [x y] z
    //  x y  z
    return triangleStack.block<2,2>(0,0);
}

Matrix2d EsCalculator::edgeStack(const MatrixXd &orig)
{
    Matrix2d res;
    res << orig(0,1) - orig(0,0), orig(0,2) - orig(0,0),
           orig(1,1) - orig(1,0), orig(1,2) - orig(1,0);
    return res;
}

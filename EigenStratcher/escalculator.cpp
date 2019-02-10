#include "escalculator.h"
#include <Eigen/QR>
#include "iostream"

using namespace std;
using namespace Eigen;

void EsCalculator::traceMatrix(const Matrix3d &doubleMatrix, const string &name)
{
    cout << endl << name << "= " << endl << doubleMatrix << endl;
}
void EsCalculator::traceMatrix(const Matrix2d &doubleMatrix, const string &name)
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
    // (10)
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

Matrix2d EsCalculator::transformOfEdges(const Matrix3d &triangleStack, const Matrix3d &targetTriangleStack, const Matrix3d &triangleUvTriangleStack)
{
    // centrate
    const Matrix3d Vg0 = centredTriangleStack(triangleStack);
    const Matrix3d VgT = centredTriangleStack(targetTriangleStack);
    const Matrix3d Vuv = centredTriangleStack(triangleUvTriangleStack);

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
    // T = ...
    return transformBetweenEdgePair(e12, e12_R);
}

Matrix2d EsCalculator::stretchCompressAxesOld(const Matrix3d &transformBetweenWorldAndUvTriangles,
                                           const Matrix3d &closestRotationMatrixToIt,
                                           const Matrix2d &transformBetweeenEdges)
{
    // (13)
    // T --> svd
    // T = U1 * sig1 * V1
    // ret S = Q * R^t * V1
    const JacobiSVD<Matrix2d> svd(transformBetweeenEdges, ComputeFullU | ComputeFullV);
    return leftTopBlock(transformBetweenWorldAndUvTriangles * closestRotationMatrixToIt.transpose()) * svd.matrixV();
}

Matrix2d EsCalculator::stretchCompressAxes(const Matrix2d &transformBetweeenEdges, double &rs, double &rt)
{
    // new approximate, cause strange things happen with R0, Q0, R1, Q1
    const JacobiSVD<Matrix2d> svd(transformBetweeenEdges, ComputeFullU | ComputeFullV);
    rs = svd.singularValues()(0,0);
    rt = svd.singularValues()(1,0);
    return svd.matrixV();
}

Matrix2d EsCalculator::stretchCompressAxes(const Matrix3d &triangleStack,
                                           const Matrix3d &targetTriangleStack,
                                           const Matrix3d &triangleUvTriangleStack,
                                           double &rs, double &rt)
{
    return stretchCompressAxes(transformOfEdges(triangleStack, targetTriangleStack, triangleUvTriangleStack), rs, rt);
}


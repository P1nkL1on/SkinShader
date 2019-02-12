#ifndef ESCALCULATOR_H
#define ESCALCULATOR_H

#include "string"
#include "Eigen/Core"
#include <Eigen/Dense>
#include "QVector"

namespace EsCalculator
{
    Eigen::Vector3d centredTriangleStack(const Eigen::Matrix3d &originalTriangleStack, Eigen::Matrix3d &resultCentredTriangleStack);
    Eigen::Matrix3d centredTriangleStack(const Eigen::Matrix3d &originalTriangleStack);

    void traceMatrix(const Eigen::Matrix3d &doubleMatrix, const std::string &name = "matrix");
    void traceMatrix(const Eigen::Matrix2d &doubleMatrix, const std::string &name = "matrix");
    void traceEdgeLengths(const Eigen::Matrix3d &triangleStack, const std::string &name = "edge's lengths");

    // Q = Q(V_g1, V_g2);
    Eigen::Matrix3d transformBetweenTriangles(const Eigen::Matrix3d &triangleStack, const Eigen::Matrix3d &targetTriangleStack);
    // R = R(Q)
    Eigen::Matrix3d closestRotationMatrix(const Eigen::Matrix3d &transformMatrix);
    // T = T(e12, e12');
    Eigen::Matrix2d transformBetweenEdgePair(const Eigen::Matrix2d &originalEdgeStack, const Eigen::Matrix2d &targetEdgeStack);

    // S = S(Q, R, T)
    Eigen::Matrix2d stretchCompressAxesOld(const Eigen::Matrix3d &transformBetweenWorldAndUvTriangles,
                                        const Eigen::Matrix3d &closestRotationMatrixToIt,
                                        const Eigen::Matrix2d &transformBetweeenEdges);
    // S = S(T) -> rs, rt
    Eigen::Matrix2d stretchCompressAxes(const Eigen::Matrix2d &transformBetweeenEdges, double &rs, double &rt);

    // S = S(V_g, V_g', V_uv) -> rs, rt
    Eigen::Matrix2d stretchCompressAxes(const Eigen::Matrix3d &triangleStack,
                                        const Eigen::Matrix3d &targetTriangleStack,
                                        const Eigen::Matrix3d &triangleUvTriangleStack,
                                        double &rs, double &rt);
    // T = T(V_g, V_g', V_uv);
    Eigen::Matrix2d transformOfEdges(const Eigen::Matrix3d &triangleStack,
                                     const Eigen::Matrix3d &targetTriangleStack,
                                     const Eigen::Matrix3d &triangleUvTriangleStack);

    QVector<Eigen::Matrix2d> transformOfEdgesForEachVertex(
            const QVector<Eigen::Vector3d> &vertices,
            const QVector<Eigen::Vector3d> &changedVertices,
            const QVector<Eigen::Vector2d> &textureVertices,
            const QVector<int> &polygonIndices,
            const QVector<int> &texturePolygonIndices);

    Eigen::Matrix2d leftTopBlock(const Eigen::Matrix3d &triangleStack);
    Eigen::Matrix2d edgeStack (const Eigen::MatrixXd &orig);
}


#endif // ESCALCULATOR_H

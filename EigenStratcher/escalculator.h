#ifndef ESCALCULATOR_H
#define ESCALCULATOR_H

#include "string"
#include "Eigen/Core"
#include <Eigen/Dense>


namespace EsCalculator
{
    Eigen::Vector3d centredTriangleStack(const Eigen::Matrix3d &originalTriangleStack, Eigen::Matrix3d &resultCentredTriangleStack);
    Eigen::Matrix3d centredTriangleStack(const Eigen::Matrix3d &originalTriangleStack);

    void traceMatrix(const Eigen::Matrix3d &doubleMatrix, const std::string &name = "matrix");
    void traceMatrix(const Eigen::Matrix2d &doubleMatrix, const std::string &name = "matrix");
    void traceEdgeLengths(const Eigen::Matrix3d &triangleStack, const std::string &name = "edge's lengths");

    Eigen::Matrix3d transformBetweenTriangles(const Eigen::Matrix3d &triangleStack, const Eigen::Matrix3d &targetTriangleStack);
    Eigen::Matrix3d closestRotationMatrix(const Eigen::Matrix3d &transformMatrix);
    Eigen::Matrix2d transformBetweenEdgePair(const Eigen::Matrix2d &originalEdgeStack, const Eigen::Matrix2d &targetEdgeStack);

    Eigen::Matrix2d stretchCompressAxesOld(const Eigen::Matrix3d &transformBetweenWorldAndUvTriangles,
                                        const Eigen::Matrix3d &closestRotationMatrixToIt,
                                        const Eigen::Matrix2d &transformBetweeenEdges);
    Eigen::Matrix2d stretchCompressAxes(const Eigen::Matrix2d &transformBetweeenEdges, double &rs, double &rt);
    Eigen::Matrix2d stretchCompressAxes(const Eigen::Matrix3d &triangleStack,
                                        const Eigen::Matrix3d &targetTriangleStack,
                                        const Eigen::Matrix3d &triangleUvTriangleStack,
                                        double &rs, double &rt);
    Eigen::Matrix2d transformOfEdges(const Eigen::Matrix3d &triangleStack,
                                     const Eigen::Matrix3d &targetTriangleStack,
                                     const Eigen::Matrix3d &triangleUvTriangleStack);

    Eigen::Matrix2d leftTopBlock(const Eigen::Matrix3d &triangleStack);
    Eigen::Matrix2d edgeStack (const Eigen::MatrixXd &orig);
}


#endif // ESCALCULATOR_H

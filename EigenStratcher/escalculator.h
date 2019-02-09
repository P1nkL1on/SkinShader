#ifndef ESCALCULATOR_H
#define ESCALCULATOR_H

#include "esdrawer.h"
#include "string"

namespace EsCalculator
{
    Eigen::Vector3d centredTriangleStack(const Eigen::Matrix3d &originalTriangleStack, Eigen::Matrix3d &resultCentredTriangleStack);
    Eigen::Matrix3d centredTriangleStack(const Eigen::Matrix3d &originalTriangleStack);

    void traceMatrix(const Eigen::Matrix3Xd &doubleMatrix, const std::string &name = "matrix");
    void traceEdgeLengths(const Eigen::Matrix3d &triangleStack, const std::string &name = "edge's lengths");

    Eigen::Matrix3d transformBetweenTriangles(const Eigen::Matrix3d &triangleStack, const Eigen::Matrix3d &targetTriangleStack);
    Eigen::Matrix3d closestRotationMatrix(const Eigen::Matrix3d &transformMatrix);
    Eigen::Matrix2d transformBetweenEdgePair(const Eigen::Matrix2d &originalEdgeStack, const Eigen::Matrix2d &targetEdgeStack);

    Eigen::Matrix2d leftTopBlock(const Eigen::Matrix3d &triangleStack);
    Eigen::Matrix2d edgeStack (const Eigen::MatrixXd &orig);
}


#endif // ESCALCULATOR_H

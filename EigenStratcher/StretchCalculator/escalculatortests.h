#ifndef ESCALCULATORTESTS_H
#define ESCALCULATORTESTS_H

#include <QTest>
#include "escalculator.h"

class EsCalculatorTests : public QObject
{
    Q_OBJECT
public:

private:
    const double eps = 1E-5;
    bool isEqualMatrices(const Eigen::Matrix3d &a, const Eigen::Matrix3d &b) const;
    bool isTriangleStackLyingInUv(const Eigen::Matrix3d &triangleStack) const;
    bool isEqualTrianglesEdgeLengths(const Eigen::Matrix3d &triangleStack1, const Eigen::Matrix3d &triangleStack2) const;
    void edgeLengths(const Eigen::Matrix3d &triangleStack, double &edge1Length, double &edge2Length) const;

    Eigen::Matrix3d closestRotationMatrix(const Eigen::Matrix3d &g, const Eigen::Matrix3d &uv) const;
    Eigen::Matrix3d closestApplyRotationMatrixToG(const Eigen::Matrix3d &g, const Eigen::Matrix3d &uv) const;
private slots:
    void testMatricesIsEqual0();
    void testMatricesIsEqual1();
    void testMatricesIsNonEqual0();

    void testTriangleIsInUV0();
    void testTriangleIsInUV1();
    void testTriangleIsInsideUV0();

    void testEdgeLength0();
    void testEdgeLength1();
    void testEdgeLength2();

    void testEdgeLengthsAreEqual0();
    void testEdgeLengthsAreEqual1();

    void testTransformBetweenAnyTriangles0();
    void testTransformBetweenTrianglesToUV();
    void testTransformBetweenSameTrianglesIsIdentity();
    void testTransformBetweenTrianglesToUVCaseBorder();
    void testTransformBetweenAnyTrianglesCaseSame();
    void testTransformBetweenAnyTrianglesCaseParallel();
    void testTransformBetweenAnyTrianglesCaseOrtogonal();

    void testCentredTriange0();
    void testCentredTriange1();

    void testClosestRotationMatrixIsLyingToUV();
    void testClosestRotationMatrixDoNotChangeEdgeLength();
    void testClosestRotationAnyCase();
    void testClosestRotationMatrixNumerical0();
    void testClosestRotationMatrixNumerical1();
};

#endif // ESCALCULATORTESTS_H

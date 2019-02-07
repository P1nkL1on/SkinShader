#ifndef ESCALCULATORTESTS_H
#define ESCALCULATORTESTS_H

#include <QTest>
#include "escalculator.h"

class esCalculatorTests : public QObject
{
    Q_OBJECT
public:

private:
    const double eps = 1E-5;
    bool compareMatrices33D(const EigenFuncs::Mat33D &a, const EigenFuncs::Mat33D &b) const;
    bool isMatrix33DinUV(const EigenFuncs::Mat33D &mat) const;
    void caluclateEdgeLength(const EigenFuncs::Mat33D &mat, double &edge1, double &edge2) const;
    bool compareTriangleEdges(const EigenFuncs::Mat33D &a, const EigenFuncs::Mat33D &b) const;

    EigenFuncs::Mat33D calculateRGcenter(const EigenFuncs::Mat33D &g, const EigenFuncs::Mat33D &uv) const;
private slots:
    void testCompare0();
    void testCompare1();
    void testNonCompare0();

    void testQ_Simple();
    void testQ_GtoUV();
    void testQ_GtoUVBorders();
    void testQ_Same();
    void testQ_Parallel();
    void testQ_Ortogonal();

    void testCentrate0();
    void testCentrate1();

    void testRcenter_LiePlane();
    void testRcenter_EqualSides();
    void testRcenter_Complex0();
};

#endif // ESCALCULATORTESTS_H

#ifndef ESCALCULATORHELP_H
#define ESCALCULATORHELP_H

#include "escalculator.h"
#include "esdrawer.h"

namespace EsCalculatorHelp{

//  private:
//    EigenFuncs::Mat22D removeLastRow(const EigenFuncs::Mat33D &mat) const;
//    void test(QPainter *qp, esDrawer *dr) const;
//    void test0() const;
    Eigen::Vector2d makeVector2D(const double x, const double y);
    Eigen::Vector3d makeVector3D(const double x, const double y, const double z);
    Eigen::Matrix3d makeMatrixFromVectors3D(const Eigen::Vector3d &dot0, const Eigen::Vector3d &dot1, const Eigen::Vector3d &dot2);
    Eigen::Matrix3d makeMatrixFromVectors2D(const Eigen::Vector2d &dot0, const Eigen::Vector2d &dot1, const Eigen::Vector2d &dot2);
    void testRandomTriangleWithPainting(QPainter *qp, EsDrawer *dr);
    void testRandom2TriangleWithPainting(QPainter *qp, EsDrawer *dr);
    void testRandom3Model(QPainter *qp, EsDrawer *dr);
}

#endif // ESCALCULATORHELP_H

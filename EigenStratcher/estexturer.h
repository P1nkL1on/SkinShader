#ifndef ESTEXTURER_H
#define ESTEXTURER_H

#include "Shading/planevector.h"
#include "StretchCalculator/escalculator.h"
#include "StretchCalculator/esmodel.h"

namespace EsTexturer
{
PlaneVector applyInterpolatedTransforms(
        const PlaneVector &texture,
        const QVector<Eigen::Matrix2d> &eachUvVertexTransforms,
        const QVector<Eigen::Vector2d> &textureCoordinates,
        const QVector<int> &polygonIndexesTrianglulated);
bool isBarricentered (
        const double X, const double Y,
        const Eigen::Vector2d &dot1,
        const Eigen::Vector2d &dot2,
        const Eigen::Vector2d &dot3,
        double &m1, double &m2, double &m3);
double getPixelValueAfterStretching(
        const PlaneVector &texture,
        const int pixelX, const int pixelY,
        const double stretchRatio,
        const Eigen::Vector2d &direction);
}

#endif // ESTEXTURER_H

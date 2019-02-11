#ifndef CROSSSHADING_H
#define CROSSSHADING_H

#include "planevector.h"


class CrossShading
{
public:
    CrossShading();
    void smooth (const PlaneVector &v, PlaneVector &to, const int interpolation) const;
    void blurInDirection (
            const PlaneVector &originalImage,
            PlaneVector &resultImage,
            const double r, const double directionX, const double directionY,
            const int interpolationType) const;
    void blurCross(
            const PlaneVector &originalImage,
            PlaneVector &resultImage,
            const double rs, const double rt, const double directX, const double directY,
            const int interpolationType) const;

    double blurPixelInDirection(
            const PlaneVector &originalImage,
            const int x, const int y,
            const double r, const double directionX, const double directionY,
            const int interpolationType) const;

    void blurPixelsInTriangleInDirect(
            const PlaneVector &originalImage,
            PlaneVector &resImage,
            const float x0, const float y0,
            const float x1, const float y1,
            const float x2, const float y2,
            const double r,
            const double directionX, const double directionY,
            const int interpolationType) const;
    void blurPixelsInTriangleCross(
            const PlaneVector &originalImage,
            PlaneVector &resImage,
            const float x0, const float y0,
            const float x1, const float y1,
            const float x2, const float y2,
            const double rs, const double rt,
            const double directionX, const double directionY,
            const int interpolationType) const;
private:
    double getC(const int center, const double tan, const int number, const int max) const;
    double getInVec(const PlaneVector &v, const int x, const int y, const double xvec, const double yvec1, const double K, const int interPolation) const;
    double getGaussian(double delt, double x) const;
};

#endif // CROSSSHADING_H

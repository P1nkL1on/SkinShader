#ifndef CROSSSHADING_H
#define CROSSSHADING_H

#include "planevector.h"

class CrossShading
{
public:
    CrossShading();
    void smooth (const PlaneVector &v, PlaneVector &to) const;
private:
    int getC (const int center, const double tan, const int number, const int max) const;
    double getInVec(const PlaneVector &v, const int x, const int y, const double xvec, const double yvec1, const int K) const;
    double getGaussian(double delt, double x) const;
};

#endif // CROSSSHADING_H

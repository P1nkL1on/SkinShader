#ifndef ESCALCULATOR_H
#define ESCALCULATOR_H

#include "esdrawer.h"

class esCalculator
{
public:
    esCalculator() = default;
    void test(QPainter *qp, esDrawer *dr) const;
private:
    void calculateE1E2 (const EigenFuncs::Mat23D &orig, EigenFuncs::Mat22D &res) const;
};

#endif // ESCALCULATOR_H

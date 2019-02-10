#ifndef ESCALCULATORHELP_H
#define ESCALCULATORHELP_H

#include "escalculator.h"
#include "esdrawer.h"

namespace EsCalculatorHelp{

//  private:
//    EigenFuncs::Mat22D removeLastRow(const EigenFuncs::Mat33D &mat) const;
//    void test(QPainter *qp, esDrawer *dr) const;
//    void test0() const;

    void testRandomTriangleWithPainting(QPainter *qp, EsDrawer *dr);
    void testRandom2TriangleWithPainting(QPainter *qp, EsDrawer *dr);
}

#endif // ESCALCULATORHELP_H

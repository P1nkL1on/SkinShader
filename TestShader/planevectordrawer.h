#ifndef PLANEVECTORDRAWER_H
#define PLANEVECTORDRAWER_H

#include "planevector.h"
#include "qpainter.h"

class PlaneVectorDrawer
{
public:
    PlaneVectorDrawer();
    void paint(QPainter *qp, const PlaneVector &vec, const int x = 0, const int y = 0) const;
    int mash = 3;
private:

    double minGraduationValue = 0;
    double maxGraduationValue = 100;

    int minColor = 0;
    int maxColor = 255;

    QColor transformValueToColor(const double value) const;
};

#endif // PLANEVECTORDRAWER_H

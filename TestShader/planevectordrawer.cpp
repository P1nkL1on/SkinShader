#include "planevectordrawer.h"

PlaneVectorDrawer::PlaneVectorDrawer()
{

}

void PlaneVectorDrawer::paint(QPainter *qp, const PlaneVector &vec, const int x, const int y) const
{
    for (int i = 0; i < vec.width(); ++i)
        for (int j = 0; j < vec.height(); ++j){
            qp->setPen(QPen(transformValueToColor(vec.getValue(i, j)), mash));
            qp->drawPoint(x + i * mash, y + j * mash);
        }
}

QColor PlaneVectorDrawer::transformValueToColor(const double value) const
{
    int resInt = int(double(value - minGraduationValue) / (maxGraduationValue - minGraduationValue) * (maxColor - minColor) + minColor);
    if (resInt > maxColor) resInt = maxColor;
    if (resInt < minColor) resInt = minColor;
    return QColor(resInt, resInt, resInt);
}

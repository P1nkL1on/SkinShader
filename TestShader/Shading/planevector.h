#ifndef PLANEVECTOR_H
#define PLANEVECTOR_H

#include <iostream>
#include <vector>
#include "QImage"
#include "point.h"

class PlaneVector
{
public:
    PlaneVector(const int width, const int height);
    PlaneVector(const QImage &image);
    PlaneVector(const QString &imagePath);

    void setParamsFromQImage (const QImage &image);

    void setValue(const double value, const int x, const int y);
    void setValue(const double value, const int number);
    double getValue(const int x, const int y) const;
    double getValue(const float x, const float y, const int flagInterpolation) const;
    int width() const;
    int height() const;
    PlaneVector changeSize(const int wid, const int hei, const int flagInterpolation) const;

    double bilinearInterpolateCoordinate(const float x, const float y) const;
    static double bilinearInterpolate(
            const float x, const float y,
            const double a00, const double a10, const double a01, const double a11);

    static PlaneVector testPlaneVector(const int wid, const int hei);
    static void summ (const PlaneVector &a, const double ka,
                      const PlaneVector &b, const double kb, PlaneVector &res);

    // addition to point.h
    void setValue(const double value, const Point xy);
    double getValue(const Point xy) const;
    double getValue(const FPoint xy, const int flagInterpolation) const;
private:
    std::vector<double> m_values;
    int m_width;    // x
    int m_height;   // y
    void assertCoordinates (const int x, const int y) const;
};

#endif // PLANEVECTOR_H

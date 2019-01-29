#ifndef PLANEVECTOR_H
#define PLANEVECTOR_H

#include <iostream>
#include <vector>

class PlaneVector
{
public:
    PlaneVector(const int width, const int height);

    void setValue(const double value, const int x, const int y);
    double getValue(const int x, const int y) const;
    double getValue(const float x, const float y, const int flagInterpolation) const;
    int width() const;
    int height() const;
    static PlaneVector testPlaneVector(const int wid, const int hei);

private:
    std::vector<double> m_values;
    int m_width;    // x
    int m_height;   // y

    bool assertCoordinates (const int x, const int y) const;
    bool assertCoordinates (const float x, const float y) const;
};

#endif // PLANEVECTOR_H

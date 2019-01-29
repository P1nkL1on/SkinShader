#include "planevector.h"
#include <QtGlobal>
#include <math.h>

PlaneVector::PlaneVector(const int width, const int height)
{
    m_values = std::vector<double>(width * height);
    std::fill(m_values.begin(), m_values.end(), 0.0);
    m_width = width;
    m_height = height;
}

void PlaneVector::setValue(const double value, const int x, const int y)
{
    if (!assertCoordinates(x, y))
        return;
    m_values[y * width() + x] = value;
}

double PlaneVector::getValue(const int x, const int y) const
{
    if (!assertCoordinates(x, y))
        return 0.0;
    return m_values[y * width() + x];
}

double PlaneVector::getValue(const float x, const float y, const int flagInterpolation) const
{
    switch (flagInterpolation){

        default:
            return getValue((int)x, (int)y);
    }
}

int PlaneVector::width() const
{
    return m_width;
}

int PlaneVector::height() const
{
    return m_height;
}

bool PlaneVector::assertCoordinates(const int x, const int y) const
{
    return assertCoordinates((float)x, (float)y);
}

bool PlaneVector::assertCoordinates(const float x, const float y) const
{
    Q_ASSERT(x >= 0.0 && x < width());
    Q_ASSERT(y >= 0.0 && y < height());
    return true;
}


PlaneVector PlaneVector::testPlaneVector(const int wid, const int hei)
{
    PlaneVector res = PlaneVector(wid, hei);
    for (int x = 0; x < wid; ++x)
        for (int y = 0; y < hei; ++y){
            double distToCenter = sqrt((double)((wid / 2 - x) * (wid / 2 - x) + (hei / 2 - y)*(hei / 2 - y)));
            if (!(distToCenter >= hei / 3 || distToCenter <= hei / 4) || x == wid / 2 || y == hei / 2)
            {
                continue;
            }
            res.setValue(100.0, x, y);//(100.0 - ((((x + y) % 2)? ((x + y) / 2) : (100 - (x + y) / 2)) * .2), x, y);
        }
    return res;
}

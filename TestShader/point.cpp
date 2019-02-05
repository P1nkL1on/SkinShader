#include "point.h"

Point::Point(int X, int Y)
{
    m_x = X;
    m_y = Y;
}

int Point::x() const
{
    return m_x;
}

int Point::y() const
{
    return m_y;
}


FPoint::FPoint(float X, float Y)
{
    m_x = X;
    m_y = Y;
}

float FPoint::x() const
{
    return m_x;
}

float FPoint::y() const
{
    return m_y;
}

DPoint::DPoint(double X, double Y)
{
    m_x = X;
    m_y = Y;
}

double DPoint::x() const
{
    return m_x;
}

double DPoint::y() const
{
    return m_y;
}


#ifndef POINT_H
#define POINT_H


class Point
{
private:
    int m_x;
    int m_y;
public:
    Point(int X, int Y);
    int x() const;
    int y() const;
};

class FPoint
{
private:
    float m_x;
    float m_y;
public:
    FPoint(float X, float Y);
    float x() const;
    float y() const;
};

class DPoint
{
private:
    double m_x;
    double m_y;
public:
    DPoint(double X, double Y);
    double x() const;
    double y() const;
};

#endif // POINT_H

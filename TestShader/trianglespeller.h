#ifndef TRIANGLESPELLER_H
#define TRIANGLESPELLER_H
#include "planevector.h"

class TriangleSpeller
{
public:
    static void findAllPixelCoordinates(
            PlaneVector &v,
            const int x1, const int y1,
            const int x2, const int y2,
            const int x3, const int y3);
    static void swap(int &a, int &b);
    static void swapMax(int &a, int &b, int &c);

};

#endif // TRIANGLESPELLER_H

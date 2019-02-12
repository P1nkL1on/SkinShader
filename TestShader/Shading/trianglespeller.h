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
    static void ballicentrate(
            const int X, const int Y,
            const int x1, const int y1,
            const int x2, const int y2,
            const int x3, const int y3,
            float &m1,
            float &m2,
            float &m3);
    static void fillTexture(
            PlaneVector &texture,
            PlaneVector &drawTo,
            // texture coords
            const float xt0, const float yt0,
            const float xt1, const float yt1,
            const float xt2, const float yt2,
            // final screen coords
            const int x0, const int y0,
            const int x1, const int y1,
            const int x2, const int y2
            );
    static void ballicentrate(
            const float X, const float Y,
            const float x1, const float y1,
            const float x2, const float y2,
            const float x3, const float y3,
            float &m1,
            float &m2,
            float &m3);
};

#endif // TRIANGLESPELLER_H

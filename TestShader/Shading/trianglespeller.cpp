#include "trianglespeller.h"
#include "iostream"
#include "qdebug.h"

void TriangleSpeller::findAllPixelCoordinates(PlaneVector &v,
                                              const int x0, const int y0,
                                              const int x1, const int y1,
                                              const int x2, const int y2)
{
    float a,b,c;
    int X0 = x0, Y0 = y0, X1 = x1, Y1 = y1, X2 = x2, Y2 = y2;
    if (Y0 == Y1 && Y0 == Y2) return;
    if (Y0 > Y1){ std::swap(Y0, Y1); std::swap(X0, X1); }
    if (Y0 > Y2){ std::swap(Y0, Y2); std::swap(X0, X2); }
    if (Y1 > Y2){ std::swap(Y1, Y2); std::swap(X1, X2); }

    int total_height = Y2 - Y0;
    for (int i = 0; i < total_height; ++i){
        bool second_half = (i > Y1 - Y0) || (Y1 == Y0);
        int segment_height = second_half? Y2 - Y1 : Y1 - Y0;
        float alpha = float(i) / total_height;
        float beta = float(i-(second_half? (Y1 - Y0) : 0)) / segment_height;
        float XA = X0 + (X2 - X0)*alpha;
        float XB = second_half? (X1 + (X2 - X1) * beta) : (X0 + (X1 - X0) * beta);
        if (XA > XB) std::swap(XA, XB);
        for (int j = int(XA); j < int(XB); ++j ){
            ballicentrate(j, Y0 + i, X0, Y0, X1, Y1, X2, Y2, a,b,c);
            v.setValue(a * .0 + b * 50.0 + c * 100.0, j, Y0 + i);
        }
    }
}

void TriangleSpeller::ballicentrate(const int X, const int Y,
                                    const int x1, const int y1,
                                    const int x2, const int y2,
                                    const int x3, const int y3,
                                    float &m1, float &m2, float &m3)
{
    m3 = float((Y  - y1) * (x2 - x1) - (X  - x1)*(y2 - y1))
            / ((y3 - y1) * (x2 - x1) - (x3 - x1)*(y2 - y1));

    m2 = float((Y  - y1) * (x3 - x1) - (X  - x1)*(y3 - y1))
            / ((y2 - y1) * (x3 - x1) - (x2 - x1)*(y3 - y1));

    m1 = float((Y  - y3) * (x2 - x3) - (X  - x3)*(y2 - y3))
            / ((y1 - y3) * (x2 - x3) - (x1 - x3)*(y2 - y3));
}

void TriangleSpeller::fillTexture(PlaneVector &texture, PlaneVector &drawTo,
                                  const float xt0, const float yt0,
                                  const float xt1, const float yt1,
                                  const float xt2, const float yt2,
                                  const int x0, const int y0,
                                  const int x1, const int y1,
                                  const int x2, const int y2)
{
    float a,b,c;
    float xt, yt;

    int X0 = x0, Y0 = y0, X1 = x1, Y1 = y1, X2 = x2, Y2 = y2;
    if (Y0 == Y1 && Y0 == Y2) return;
    if (Y0 > Y1){ std::swap(Y0, Y1); std::swap(X0, X1); }
    if (Y0 > Y2){ std::swap(Y0, Y2); std::swap(X0, X2); }
    if (Y1 > Y2){ std::swap(Y1, Y2); std::swap(X1, X2); }

    int total_height = Y2 - Y0;
    for (int i = 0; i < total_height; ++i){
        bool second_half = (i > Y1 - Y0) || (Y1 == Y0);
        int segment_height = second_half? Y2 - Y1 : Y1 - Y0;
        float alpha = float(i) / total_height;
        float beta = float(i-(second_half? (Y1 - Y0) : 0)) / segment_height;
        float XA = X0 + (X2 - X0)*alpha;
        float XB = second_half? (X1 + (X2 - X1) * beta) : (X0 + (X1 - X0) * beta);
        if (XA > XB) std::swap(XA, XB);
        int XAint = int(XA);
        int XBint = int(XB);
        for (int j = XAint; j < XBint; ++j ){
            ballicentrate(j, Y0 + i, x0, y0, x1, y1, x2, y2, a,b,c);
            if (a < 0) a = 0; if (b < 0) b = 0; if (c < 0) c = 0;

            xt = (xt0 * a + xt1 * b + xt2 * c) * texture.width();
            yt =( yt0 * a + yt1 * b + yt2 * c) * texture.height();

            double barValue = texture.getValue(xt, yt, 2);
            drawTo.setValue(barValue, j, Y0 + i);
            //texture.setValue(100, int(xt), int(yt));
        }
    }
}

void TriangleSpeller::ballicentrate(const float X, const float Y, const float x1, const float y1, const float x2, const float y2, const float x3, const float y3, float &m1, float &m2, float &m3)
{
    m3 = float((Y  - y1) * (x2 - x1) - (X  - x1)*(y2 - y1))
            / ((y3 - y1) * (x2 - x1) - (x3 - x1)*(y2 - y1));

    m2 = float((Y  - y1) * (x3 - x1) - (X  - x1)*(y3 - y1))
            / ((y2 - y1) * (x3 - x1) - (x2 - x1)*(y3 - y1));

    m1 = float((Y  - y3) * (x2 - x3) - (X  - x3)*(y2 - y3))
            / ((y1 - y3) * (x2 - x3) - (x1 - x3)*(y2 - y3));
}

#include "trianglespeller.h"

void TriangleSpeller::findAllPixelCoordinates(PlaneVector &v,
                                              const int x1, const int y1,
                                              const int x2, const int y2,
                                              const int x3, const int y3)
{
    int X1 = x1, Y1 = y1, X2 = x2, Y2 = y2, X3 = x3, Y3 = y3;

    if (X1 >= X3){ swap(X1, X3); swap(Y1, Y3); }
    if (X1 >= X2){ swap(X1, X2); swap(Y1, Y2); }
    if (X2 >= X3){ swap(X2, X3); swap(Y2, Y3); }

    float tan12 = (X2 - X1)*1.0/(Y2-Y1);
    float tan13 = (X3 - X1)*1.0/(Y3-Y1);
    float tan23 = (X3 - X2)*1.0/(Y3-Y2);

    for (int h = 0; h < Y2 - Y1; ++h){
        int x12 = X1 + (int)(h * tan12);
        int x13 = X1 + (int)(h * tan13);

        if (x13 < x12) swap(x12,x13);
        for (int j = x12; j < x13; ++j)
            v.setValue(20, j, Y1 + h);

        v.setValue(50, x13, Y1 + h);
        v.setValue(80, x12, Y1 + h);
    }
    for (int h = 0; h < Y3 - Y2; ++h){
        int x23 = X2 + (int)(h * tan23);
        int x13 = X1 + (int)((Y2 - Y1 + h) * tan13);

        if (x13 < x23) swap(x23,x13);
        for (int j = x23; j < x13; ++j)
            v.setValue(20, j, Y2 + h);

        v.setValue(40, x13, Y2 + h);
        v.setValue(80, x23, Y2 + h);
    }

    v.setValue(100, x1, y1);
    v.setValue(100, x2, y2);
    v.setValue(100, x3, y3);

}

void TriangleSpeller::swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

void TriangleSpeller::swapMax(int &a, int &b, int &c)
{
    if (a >= c) swap(a, c);
    if (a >= b) swap(a, b);
    if (b >= c) swap(b, c);
}

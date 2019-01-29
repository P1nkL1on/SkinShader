#include "crossshading.h"
#include "math.h"
#include "qdebug.h"
CrossShading::CrossShading()
{

}

void CrossShading::smooth(const PlaneVector &v, PlaneVector &to, const int interpolation) const
{
    const double r = 1;
    double sigma = (r>=1.0)? (38.2 * r - 26.5) : (70.5 * r - 46.9);

    const int rad = 31;
    const double numSigma = 2.5;

    const double xvec = 1.0, yvec = 1.0;
    double L = sqrt(xvec * xvec + yvec * yvec);
    double xvec1 = xvec / L;
    double yvec1 = yvec / L;


    for (int x = 0; x < to.width(); ++x)
        for (int y = 0; y < to.height(); ++y){

            double summ = 0;
            double summWeigth = 0;
            for (int i = 0; i <= rad; ++i){
                const double val = ( i - rad / 2.0) * numSigma / (rad + 1);
                const double weigth = getGaussian(sigma, val);
                summWeigth += weigth;
                summ += weigth * getInVec(v, x, y, xvec1, yvec1, i - rad / 2.0, interpolation);
            }
            to.setValue(summ / summWeigth, x, y);
        }
}

double CrossShading::getC(const int center, const double tan, const int number, const int max) const
{
    double res = center + (tan * number);
    if (res < 0.0) return 0.0;
    if (res > max) return max * 1.0;
    return res;
}



double CrossShading::getInVec(const PlaneVector &v, const int x, const int y, const double xvec1, const double yvec1, const int K, const int interPolation) const
{
    const double getX = getC(x, xvec1, K, v.width() - 1);
    const double getY = getC(y, yvec1, K, v.height() - 1);
    return v.getValue(getX, getY, interPolation);
}

double CrossShading::getGaussian(double sigma, double x) const
{
    double xs = x / sigma;
    return exp(-.5 * xs * xs);
}


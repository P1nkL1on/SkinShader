#include "crossshading.h"
#include "math.h"
#include "qdebug.h"
CrossShading::CrossShading()
{

}

void CrossShading::smooth(const PlaneVector &v, PlaneVector &to) const
{
    const double r = 1.28;
    const double delt = (r>=1.0)? (38.2 * r - 26.5) : (70.5 * r - 46.9);
//    const double alph1 = 15.4 * r - 13.8;
//    const double alph2 = 3.0 * r - 3.09;
//    double alpha = (alph1 < alph2)? alph1 : alph2;
//    if (alpha >= 1.0) alpha = 1.0;
    const int rad = 31;


    //for (int i = -rad; i < rad; ++i)
    //    qDebug() << i << "->" << getGaussian(delt, i);

    const double xvec = 1.0, yvec = .0;
    double L = sqrt(xvec * xvec + yvec * yvec);
    double xvec1 = xvec / L;
    double yvec1 = yvec / L;


    for (int x = 0; x < to.width(); ++x)
        for (int y = 0; y < to.height(); ++y){

            double summ = 0;
            double summWeigth = 0;
            for (int i = -rad; i <= rad; ++i){
                const double weigth = getGaussian(delt, i);//std::max(0.0, 1.0 - i * i * 1.0 / rad / rad);
                summWeigth += weigth;
                summ += weigth * getInVec(v, x, y, xvec1, yvec1, i);
            }
            //if (v.getValue(x,y) != summ/summWeigth)
            //qDebug() << v.getValue(x,y) << " --> " << summ/summWeigth;
            to.setValue(summ / summWeigth, x, y);
        }
}

int CrossShading::getC(const int center, const double tan, const int number, const int max) const
{
    int res = center + int(tan * number);
    if (res < 0) return 0;
    if (res > max) return max;
    return res;
}



double CrossShading::getInVec(const PlaneVector &v, const int x, const int y, const double xvec1, const double yvec1, const int K) const
{
    const int getX = getC(x, xvec1, K, v.width() - 1);
    const int getY = getC(y, yvec1, K, v.height() - 1);
    return v.getValue(getX, getY);
}

double CrossShading::getGaussian(double delt, double x) const
{
    //qDebug() << x << "->" << res;
    return .5/(M_PI * delt) * exp(-(x*x)/(2*delt*delt));;
}


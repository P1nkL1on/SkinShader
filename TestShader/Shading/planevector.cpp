#include "planevector.h"
#include <QtGlobal>
#include <math.h>

#include "qdebug.h"

PlaneVector::PlaneVector(const int width, const int height)
{
    m_values = std::vector<double>(width * height);
    std::fill(m_values.begin(), m_values.end(), 0.0);
    m_width = width;
    m_height = height;
}

PlaneVector::PlaneVector(const QImage &image)
{
    setParamsFromQImage(image);
}

PlaneVector::PlaneVector(const QString &imagePath)
{
    setParamsFromQImage(QImage(imagePath));
}

void PlaneVector::setParamsFromQImage(const QImage &image)
{
    if (image.isNull())
        return;
    m_height = image.height();
    m_width = image.width();
    m_values = std::vector<double>(m_width * m_height);
    std::fill(m_values.begin(), m_values.end(), 0.0);

    int pixelIndex = 0;
    QVector<QRgb> v = image.colorTable(); // returns a list of colors contained in the image's color table.
    //for ( QVector<QRgb>::const_iterator it = v.begin(), itE = v.end(); it != itE; ++it )
    //{

    for (int i = 0; i < width(); ++i)
        for (int j = 0; j < height(); ++j){
            QColor clrCurrent = image.pixelColor(i, j);
            //QColor clrCurrent( *it );

            setValue((clrCurrent.red() + clrCurrent.blue() + clrCurrent.green()) / 7.65,
                     i, j);
            pixelIndex ++;
        }
    //}
}

void PlaneVector::setValue(const double value, const int x, const int y)
{
    assertCoordinates(x,y);
    m_values[y * width() + x] = value;
}

void PlaneVector::setValue(const double value, const int number)
{
    if (number < 0 || number > m_values.size() - 1)
        throw std::out_of_range("Out of range in coordinate");
    m_values[number] = value;
}

double PlaneVector::getValue(const int x, const int y) const
{
    assertCoordinates(x,y);
    return m_values[y * width() + x];
}

double PlaneVector::getValue(const float x, const float y, const int flagInterpolation) const
{
    switch (flagInterpolation){
    case 1:
        return getValue(std::round(x), std::round(y));
    case 2:
        return bilinearInterpolateCoordinate(x, y);
    default:
        return getValue(std::floor(x), std::floor(y));
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

PlaneVector PlaneVector::changeSize(const int wid, const int hei, const int flagInterpolation) const
{
    PlaneVector res = PlaneVector(wid, hei);
    const float xS = (width() - 1) * 1.0 / wid;
    const float yS = (height() - 1) * 1.0 / hei;
    for (int i = 0; i < wid; ++i)
        for (int j = 0; j < hei; ++j)
            res.setValue(getValue(i * xS, j * yS, flagInterpolation), i, j);
    return res;
}

double PlaneVector::bilinearInterpolateCoordinate(const float x, const float y) const
{
    const int pX = std::floor(x);
    const int pY = std::floor(y);

    const double v00 = getValue(std::min(pX, width() - 1), std::min(pY, height() - 1));
    const double v10 = getValue(std::min(pX + 1, width() - 1), std::min(pY, height() - 1));
    const double v01 = getValue(std::min(pX, width() - 1), std::min(pY + 1, height() - 1));
    const double v11 = getValue(std::min(pX + 1, width() - 1), std::min(pY + 1, height() - 1));

    return bilinearInterpolate(x - pX, y - pY, v00, v10, v01, v11);
}

double PlaneVector::bilinearInterpolate(const float x, const float y, const double a00, const double a10, const double a01, const double a11)
{
    if (x < 0 || x > 1 || y < 0 || y > 1)
        throw std::out_of_range("Interpolation coordinate is out of [0..1]");
    return  a11 * x * y
            + a01 * (1.0 - x) * y
            + a10 * x * (1.0 - y)
            + a00 * (1.0 - x) * (1.0 - y);
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

void PlaneVector::summ(const PlaneVector &a, const double ka, const PlaneVector &b, const double kb, PlaneVector &res)
{
    if (a.width() != b.width() || a.height() != b.height())
        throw std::out_of_range("Not same sizes!");
    const int size = a.width() * a.height();
    for (int i = 0; i < size; ++i)
        res.setValue(ka * a.m_values[i] + kb * b.m_values[i], i);
}

void PlaneVector::setValue(const double value, const Point xy)
{
    setValue(value, xy.x(), xy.y());
}

double PlaneVector::getValue(const Point xy) const
{
    return getValue(xy.x(), xy.y());
}

double PlaneVector::getValue(const FPoint xy, const int flagInterpolation) const
{
    getValue(xy.x(), xy.y(), flagInterpolation);
}

void PlaneVector::assertCoordinates(const int x, const int y) const
{
    const bool xAccept = (x >= 0) && (x < width());
    const bool yAccept = (y >= 0) && (y < height());
    if (xAccept && yAccept)
        return;

    throw std::out_of_range("Out of range in coordinate");
}
